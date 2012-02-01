#ifndef __VANILLA_BREEZE_HTTP__
#define __VANILLA_BREEZE_HTTP__

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

//#define vbHTTPDebug

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct VBHTTP VBHTTP;
    
    struct VBHTTP {
        char* host_name;
        char* port;
        unsigned int break_time;
        unsigned int read_interval;
        void (*error_handle)(VBHTTP* _http, unsigned char error_code);
        void (*success_handle)(VBHTTP* _http);
        int sock;
        char* method;
        char* request;
        char* response;
        char* data;
        size_t data_len;
        char* header;
        pthread_t tid;
        int complete;
    };
    
    char* CutHeader(char *response);
    
    //초기화
    VBHTTP* VBHTTPCreate(const char* _host_name,
                         const char* _port,
                         double _break_time, //최대 응답대기시간
                         double _read_interval, //응답확인 인터벌
                         const char* _method, //GET, POST
                         const char* _request, //request
                         const char* _data, //POST시 데이터
                         size_t _data_len, //POST시 데이터 길이
                         void (_error_handle)(VBHTTP* _http, unsigned char error_code), 
                         void (_success_handle)(VBHTTP* _http));
    
    //js
    VBHTTP* VBHTTPCreateByJS(const char* _js_fileName,
                             const char* _request,
                             void (_error_handle)(VBHTTP* _http, unsigned char error_code), 
                             void (_success_handle)(VBHTTP* _http));
    
    void VBHTTPRelease(VBHTTP** http);
    
#ifdef __cplusplus
}
#endif

#endif
