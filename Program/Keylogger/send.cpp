#include <curl/curl.h>
#include "send.h"
#include <fstream>
#include <cstring>

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
  size_t realsize = size * nmemb;
  struct string_data* mem = (struct string_data*)userdata;

  mem->data = (char*)realloc(mem->data, mem->size + realsize + 1);
  if (mem->data == NULL) {
    /* out of memory! */
    std::cerr << "Error: out of memory" << std::endl;
    return 0;
  }

  memcpy(&(mem->data[mem->size]), ptr, realsize);
  mem->size += realsize;
  mem->data[mem->size] = '\0';

  return realsize;
}

bool sendFileHttps(std::string filename, std::string url) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size];
    if(file.read(buffer,size)){
        curl_global_init(CURL_GLOBAL_ALL);
        CURL* curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl,CURLOPT_URL,url.c_str());

            curl_httppost* formpost = NULL;
            curl_httppost* lastptr = NULL;

            curl_formadd(&formpost,&lastptr,CURLFORM_COPYNAME,"file",CURLFORM_FILE,filename.c_str(),CURLFORM_END);

            struct curl_slist* headerlist = NULL;
            headerlist = curl_slist_append(headerlist,"Content-Type: multipart/form-data");
            curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headerlist);

            struct string_data reponse_data;
            reponse_data.data = (char*)malloc(1);
            reponse_data.size = 0;

            curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_callback);
            curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)&reponse_data);

            curl_easy_setopt(curl,CURLOPT_HTTPPOST,formpost);
            CURLcode res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                fprintf(stderr,"curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
            } else {
                std::cout << reponse_data.data << std::endl;
            }

            curl_formfree(formpost);
            curl_slist_free_all(headerlist);
            curl_easy_cleanup(curl);
            free(reponse_data.data);

        } else {
            fprintf(stderr,"curl_easy_init() failed\n");
        }
    } else {
        fprintf(stderr,"file.read() failed\n");
    }
    delete[] buffer;

return true;
}

// Supprimer les fprintf avant push sur github