cmake_minimum_required(VERSION 2.8)

project(QQCrawler)

set(CRAWLER_VERSION 1)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
#add_compile_options(-std=c++11 -pthread)

# add dependence of curl
# can't link curl to target, how to fix ? use imported libcurl which been builded.
include_directories(curl/include)
add_subdirectory(curl ./.cmake_curl_build)
#include_directories(curl_build_install/include)
#add_library(LIBCURL SHARED IMPORTED)
#set_target_properties(
#  LIBCURL
#  PROPERTIES IMPORTED_LOCATION
#  curl_build_install/lib/libcurl.so
#  )

# add dependence of jsonbox
#include_directories(json/JsonBox/include)
#add_subdirectory(json/JsonBox ./.cmake_jsonbox_build)
include_directories(json/jsoncpp/include)
add_subdirectory(json/jsoncpp/ ./.cmake_jsoncpp_build)

set(CRAWLER_HEADERS
  GameResultCrawler/QQOnlineCrawler.h
  GameResultCrawler/GameResultCrawler.h
)

set(CRAWLER_SOURCES
  GameResultCrawler/QQOnlineCrawler.cpp
  GameResultCrawler/GameResultCrawler.cpp
)

add_library(crawler SHARED ${CRAWLER_SOURCES} ${CRAWLER_HEADERS} )

#target_link_libraries(crawler LIBCURL jsoncpp_lib_static)
target_link_libraries(crawler libcurl jsoncpp_lib_static)

add_executable(crawler_test GameResultCrawler/Main.cpp)
target_link_libraries(crawler_test crawler)
