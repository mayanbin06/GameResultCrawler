#ifndef GAME_RESULT_CRAWLER_H
#define GAME_RESULT_CRAWLER_H

#include <string>
#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

namespace crawler {

class GameResultCrawler {
public:
  class Client {
    public:
      virtual void OnGameResult(const std::string& result) = 0;
  };

  GameResultCrawler(const std::string&, Client*, int, int);
  virtual ~GameResultCrawler();

  void Start();
  // this method will wait thread exit.
  void Stop();
  // wait the thread to exit.
  void Wait();

  void MainLoop(int n);

private:
  void GetResultOnce(const std::string&, std::string&);

  int crawler_time_;
  int sleep_time_;
  std::string url_;
  std::unique_ptr<std::thread> main_thread_;
  std::atomic<int> thread_state_;
  Client* client_;
};

} // name space crawler
#endif
