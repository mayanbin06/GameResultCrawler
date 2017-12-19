#ifndef QQ_ONLINE_CRAWLER_H
#define QQ_ONLINE_CRAWLER_H

#include <string>
#include <memory>

#include "GameResultCrawler.h"

namespace crawler {

class QQOnlineCrawler : public GameResultCrawler::Client {
public:
  static const std::string url_;

  void OnGameResult(const std::string& result) override;

  void Start();

  QQOnlineCrawler();
  ~QQOnlineCrawler();
private:
  std::unique_ptr<GameResultCrawler> crawler_;
};

} // name space crawler
#endif
