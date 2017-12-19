#include "GameResultCrawler.h"
#include "curl/curl.h"

#ifndef _GLIBCXX_USE_NANOSLEEP
#define _GLIBCXX_USE_NANOSLEEP
#endif

namespace crawler {

GameResultCrawler::GameResultCrawler(const std::string& url)
    : url_(url) {
}

GameResultCrawler::~GameResultCrawler() {
}

void GameResultCrawler::MainLoop(int n) {
  while(thread_state_.load()) {
    std::string result;
    GetResultOnce(url_, result);
    std::cout << "Get Result = " << result << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
}

size_t WriteToString(void *ptr, size_t size, size_t count,
    void *stream) {
  ((std::string*)stream)->append((char*)ptr, 0, size* count);
  return size* count;
}

void GameResultCrawler::GetResultOnce(
    const std::string& url, std::string& responseData) {
  CURL* curl;
  CURLcode res;
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

  curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
  /* interval time between keep-alive probes: 60 seconds */
  curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteToString);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
  /** 
  * 当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。 
  * 如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。 
  */  
  curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
  res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);
}

void GameResultCrawler::Start() {
  if (main_thread_) {
    return;
  }
  thread_state_.store(1);
  main_thread_.reset(new std::thread(
      std::mem_fn(&GameResultCrawler::MainLoop), this, 100));
}

void GameResultCrawler::Stop() {
  thread_state_.store(0);
  main_thread_->join();
  main_thread_.reset(nullptr);
}

void GameResultCrawler::Wait() {
  if (main_thread_) {
    main_thread_->join();
  }
}

} // name space crawler
