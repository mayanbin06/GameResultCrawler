#include "QQOnlineCrawler.h"

#include <iostream>

namespace crawler {

const std::string QQOnlineCrawler::url_("http://cgi.im.qq.com/data/1min_city.dat");

QQOnlineCrawler::QQOnlineCrawler()
    : crawler_(new GameResultCrawler(url_)){
}

QQOnlineCrawler::~QQOnlineCrawler() {
}


void QQOnlineCrawler::OnGameResult(const std::string& result) {
  std::cout << "result = " << result << std::endl;
}

void QQOnlineCrawler::Start() {
  crawler_->Start();
  // block here.
  crawler_>Wait();
}

} // name space crawler
