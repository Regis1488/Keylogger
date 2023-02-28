#include <string>
#include <iostream>
struct string_data {
  char* data;
  size_t size;
};

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata);

bool sendFileHttps(std::string filename,std::string url);