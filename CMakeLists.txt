cmake_minimum_required(VERSION 2.8)

project(QQCrawler)

set(CRAWLER_VERSION 1)

aux_source_directory(./GameResultCrawler, SRC_FILES)

add_executable(QQCrawler, ${SRC_FILES})
