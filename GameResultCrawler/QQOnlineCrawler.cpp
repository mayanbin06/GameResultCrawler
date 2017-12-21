#include "QQOnlineCrawler.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "json/json.h"

#include "time.h"

namespace {

std::vector<int> ParseAwardNums(const std::string& nums) {

  char c;
  int sum = 0;
  std::stringstream ss(nums);
  std::vector<int> result;
  while( ss >> c) {
    sum += (c - '0');
  }

  result.push_back(sum % 10);
  result.push_back(nums[nums.size() - 4] - '0');
  result.push_back(nums[nums.size() - 3] - '0');
  result.push_back(nums[nums.size() - 2] - '0');
  result.push_back(nums[nums.size() - 1] - '0');

  return result;
}

void ParseResult(const std::string& result) {
  Json::Reader reader;
  // parse result 1min_city.dat result.
  Json::Value root;
  if (!reader.parse(result, root, false)) {
    std::cout << "parse error ....... " << std::endl;
    return;
  }

  Json::Value v = root["time"];
  std::string time = v.type() == Json::stringValue ? v.asString() : "";

  v = root["minute"];
  if (!v.isArray()) {
    // check minute array.
    return;
  }
  // get the first nums ?
  std::string numstr = v[0].asString();
  std::cout << "time = " << time << " nums = " << numstr << " --- ";
  std::vector<int> nums = ParseAwardNums(numstr);

  for (auto it = nums.begin(); it != nums.end(); it ++)
    std::cout << *it;
  std::cout << std::endl;
}

} // namespace internal

namespace crawler {

//const std::string QQOnlineCrawler::url_("http://cgi.im.qq.com/data/1min_city.dat");
const std::string QQOnlineCrawler::url_("https://mma.qq.com/cgi-bin/im/online");

QQOnlineCrawler::QQOnlineCrawler()
    : crawler_(new GameResultCrawler(url_, this, 2, 50)){
  // crawler per 2s, and sleep for 50s after get.
}

QQOnlineCrawler::~QQOnlineCrawler() {
}


void QQOnlineCrawler::OnGameResult(const std::string& result) {
  if (result.size() < 26) {
    return;
  }
  std::string numstr = result.substr(17, 9);

  std::vector<int> nums = ParseAwardNums(numstr);

  std::string issueStr;
  std::string timeStr;
  std::stringstream ss;

  time_t tt = time(0);
  struct tm* timeinfo = localtime(&tt);

  ss << (timeinfo->tm_year + 1900);
  if (timeinfo->tm_mon > 8)
    ss << (timeinfo->tm_mon + 1);
  else
    ss << 0 << (timeinfo->tm_mon + 1);

  if (timeinfo->tm_mday > 9)
    ss << (timeinfo->tm_mday);
  else
    ss << 0 << (timeinfo->tm_mday);

  int dayIssue = timeinfo->tm_hour * 60 + timeinfo->tm_min;
  ss << dayIssue;
  ss >> issueStr;

  char format[100];
  strftime(format, 100, "%F %X", timeinfo);
  
  std::ofstream out("./game_result.txt", std::ofstream::app);
  out << issueStr << " ";
  for (auto it = nums.begin(); it != nums.end(); it ++)
    out << *it;
  out << " " << format << std::endl;
  out.close();
}

void QQOnlineCrawler::Start() {
  crawler_->Start();
  // block here.
  crawler_->Wait();
}

} // name space crawler
