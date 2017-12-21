inc_dirs = -I../curl_build_install/include -I../json/JsonBox/include -I./
lib_dirs = -L../curl_build_install/lib/ -L../json/JsonBox/

cflags = -std=c++11 -g $(inc_dirs) $(lib_dirs)
cc = g++
cc_lib = -lcurl -lJsonBox
output_name = QQCrawler

src = QQOnlineCrawler.cpp GameResultCrawler.cpp Main.cpp

all: target

target: $(src) 
	$(cc) $(cflags) $(src) $(cc_lib) -o $(output_name)
