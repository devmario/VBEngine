#ifndef __VANILLA_BREEZE_HTTP__
#define __VANILLA_BREEZE_HTTP__

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct VBHTTP {
        char* host_name;
        char* port;
        unsigned int break_time;
        unsigned int read_interval;
        void (*error_handle)(unsigned char error_code);
        void (*success_handle)(void);
        int sock;
        char* method;
        char* request;
        char* header;
        char* response;
        pthread_t tid;
        int complete;
    } VBHTTP;
    
    //초기화
    VBHTTP* VBHTTPCreate(const char* _host_name,
                         const char* _port,
                         double _break_time, //최대 응답대기시간
                         double _read_interval, //응답확인 인터벌
                         const char* _method, //GET
                         const char* _request, //request
                         void (_error_handle)(unsigned char error_code), 
                         void (_success_handle)(void));
    
    //js
    VBHTTP* VBHTTPCreateByJS(const char* _js_fileName, //request
                             void (_error_handle)(unsigned char error_code), 
                             void (_success_handle)(void));
    
    void VBHTTPRelease(VBHTTP** http);
    
#ifdef __cplusplus
}
#endif

#endif
