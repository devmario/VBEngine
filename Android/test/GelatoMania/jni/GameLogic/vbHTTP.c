#include "vbHTTP.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include "VBEngine.h"

#ifndef vbHTTPDebug

#define printf(str, ...) \

#endif

#define VBHTTP_MAXTK 0xFF
#define GET_HEADER "GET /%s HTTP/1.0\nAccept:text/plain\nAccept-Language:en\nConnection:Close\nHost:%s\nUser-Agen:Mozilla/4.0\n\n"
#define POST_HEADER "POST /%s HTTP/1.0\r\nContent-Length: %ld\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s"

void* VBHTTPResponseRead(void* _arg);

char* VBHTTPCutHeader(char* _response) {
    if(_response) {
        int i = 0;
        char chunk[0xF] = "\r\n\r\n";
        int chunk_idx = 0;
        while(chunk_idx < strlen(chunk)) {
            if(*(_response + i) == chunk[chunk_idx]) {
                chunk_idx++;
            } else {
                chunk_idx = 0;
            }
            i++;
        }
        return _response + i;
    } else {
        return NULL;
    }
}

VBHTTP* VBHTTPCreateVALIST(const char* _host_name,
                           const char* _port,
                           double _break_time, //최대 응답대기시간
                           const char* _method, //GET, POST
                           const char* _data, //POST시 데이터
                           size_t _data_len, //POST시 데이터 길이
                           void* _reference,
                           void (*_success_handle)(VBHTTP* _http, VBHTTPError _error, void* _reference),
                           bool _auto_release,
                           const char* _request, //request formatter
                           va_list _arguments) {
    VBHTTP* http = calloc(sizeof(VBHTTP), 1);
	
    http->host_name = calloc(sizeof(char), (strlen(_host_name) + 1));
    memmove(http->host_name, _host_name, sizeof(char) * (strlen(_host_name)));
	
    http->port = calloc(sizeof(char), (strlen(_port) + 1));
    memmove(http->port, _port, sizeof(char) * (strlen(_port)));
    
    http->break_time = 1000000.0 * _break_time;
	
	http->success_handle = _success_handle;
	
    http->method = calloc(sizeof(char), (strlen(_method) + 1));
    memmove(http->method, _method, sizeof(char) * (strlen(_method)));
    
    if(_request) {
        vasprintf(&http->request, _request, _arguments);
    }
    
    if(_data && _data_len > 0) {
        http->data = calloc(sizeof(char), (_data_len + 1));
        memmove(http->data, _data, sizeof(char) * _data_len);
        http->data_len = _data_len;
    }
    
    http->reference = _reference;
    
    http->auto_release = _auto_release;
    
	pthread_create(&http->tid, NULL, VBHTTPResponseRead, http);
    pthread_detach(http->tid);
    
    return http;
}

VBHTTP* VBHTTPCreate(const char* _host_name,
                     const char* _port,
                     double _break_time, //최대 응답대기시간
                     const char* _method, //GET, POST
                     const char* _data, //POST시 데이터
                     size_t _data_len, //POST시 데이터 길이
                     void* _reference,
                     void (*_success_handle)(VBHTTP* _http, VBHTTPError _error, void* _reference),
                     bool _auto_release,
                     const char* _request, //request formatter
                     ...
                     ) {
    va_list list;
    va_start(list, _request);
    VBHTTP* http = VBHTTPCreateVALIST(_host_name, _port, _break_time, _method, _data, _data_len, _reference, _success_handle, _auto_release, _request, list);
    va_end(list);
    return http;
}

void VBHTTPRelease(VBHTTP** http) {
    if(*http) {
        if((*http)->sock)
            close((*http)->sock);
        
        if((*http)->header)
            free((*http)->header);
        
        if((*http)->request)
            free((*http)->request);
        
        if((*http)->method)
            free((*http)->method);
        
        if((*http)->port)
            free((*http)->port);
        
        if((*http)->host_name)
            free((*http)->host_name);
        
        if((*http)->response)
        	free((*http)->response);
        
        if((*http)->data)
            free((*http)->data);
        
        pthread_t _tId = (*http)->tid;
        
        memset(*http, 0, sizeof(VBHTTP));
        free(*http);
        *http = NULL;
        
        if(_tId)
            pthread_detach(_tId);
    }
}

//#ifdef DEBUG

void VBHTTPCreateByJS(const char* _json_file_path,
                      void* _reference,
                      void (*_success_handle)(VBHTTP* _http, VBHTTPError _error, void* _reference),
                      const char* _request,
                      ...) {
    VBString* _string = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), _json_file_path);
#ifdef __ANDROID__
    FILE* _file = android_fopen(VBStringGetCString(_string), "rb");
#else
    FILE* _file = fopen(VBStringGetCString(_string), "rb");
#endif
    VBStringFree(&_string);
    fseek(_file, 0, SEEK_END);
    size_t _size = ftell(_file);
    fseek(_file, 0, SEEK_SET);
    char* _buffer = (char*)calloc(sizeof(char), _size + 1);
    fread(_buffer, _size, sizeof(char), _file);
    fclose(_file);
    
    va_list list;
    va_start(list, _request);
    VBHTTPCreateVALIST("ec2-23-20-6-240.compute-1.amazonaws.com", "80", 5.0, "POST", _buffer, _size, _reference, _success_handle, true, _request, list);
    va_end(list);
    
    free(_buffer);
}

//#endif

void VBHTTPComplete(VBHTTP* _http, int _error) {
    _http->complete = 1;
    if(_http->success_handle)
        _http->success_handle(_http, _error, _http->reference);
    if(_http->auto_release)
        VBHTTPRelease(&_http);
}

void* VBHTTPResponseRead(void* _reference) {
    VBHTTP* http = _reference;
    
	struct hostent *__hostent_pnt;
	struct servent *__servent_pnt;
	struct sockaddr_in __sockaddr_in;
	memset((void*)&__sockaddr_in, 0, sizeof(__sockaddr_in));
	__sockaddr_in.sin_family = AF_INET;
    __servent_pnt = getservbyname("http", "tcp");
	
    if(__servent_pnt) {
		__sockaddr_in.sin_port = __servent_pnt->s_port;
	} else if((__sockaddr_in.sin_port = htons(atoi(http->port)))==0) {
        VBHTTPComplete(http, VBHTTPErrorNotFoundLocalPort);
        return NULL;
    }
    
    __hostent_pnt = gethostbyname(http->host_name);
	if(__hostent_pnt) {
		memcpy((void*)&__sockaddr_in.sin_addr, (void*)__hostent_pnt->h_addr, __hostent_pnt->h_length);
	} else if((__sockaddr_in.sin_addr.s_addr = inet_addr(http->host_name)) == INADDR_NONE) {
        VBHTTPComplete(http, VBHTTPErrorNotFoundServer);
        return NULL;
	}
	
    if((http->sock = socket(PF_INET,SOCK_STREAM,0)) < 0) {
        VBHTTPComplete(http, VBHTTPErrorSocketCreateFail);
        return NULL;
    }
	
    if(connect(http->sock,(struct sockaddr*)&__sockaddr_in, sizeof(__sockaddr_in)) < 0) {
        VBHTTPComplete(http, VBHTTPErrorConnectFail);
        return NULL;
    }
    
    if(strcmp(http->method, "GET") == 0) {
        http->header = calloc(sizeof(char), (strlen(GET_HEADER) + strlen(http->host_name) + strlen(http->request) + VBHTTP_MAXTK));
        sprintf(http->header, GET_HEADER, http->request, http->host_name);
        size_t _len = strlen(http->header);
        if(_len != write(http->sock, http->header, _len)) {
            VBHTTPComplete(http, VBHTTPErrorWriteFail);
            return NULL;
        }
    } else if(strcmp(http->method, "POST") == 0) {
        http->header = calloc(sizeof(char), (strlen(POST_HEADER) + strlen(http->host_name) + (http->request ? strlen(http->request) : 0) + (http->data ? strlen(http->data) : 0) + VBHTTP_MAXTK));
        sprintf(http->header, POST_HEADER, http->request, http->data_len, http->data);
        size_t _len = strlen(http->header);
        if(_len != write(http->sock, http->header, _len)) {
            VBHTTPComplete(http, VBHTTPErrorWriteFail);
            return NULL;
        }
    }
    
    unsigned int _interval = 0;
    unsigned long _total_len = 0;
    while(_interval < http->break_time) {
        char _buf[0xF] = {'\0',};
        long _read_len = read(http->sock, _buf, 0xF);
		if(_read_len > 0) {
            _total_len += _read_len;
            if(http->response) {
                http->response = realloc(http->response, (_total_len + 1) * sizeof(char));
            } else {
                http->response = calloc(_total_len + 1, sizeof(char));
            }
            memcpy(http->response + _total_len - _read_len, _buf, _read_len);
        } else {
            VBHTTPComplete(http, VBHTTPErrorNone);
            return NULL;
        }
        usleep(16666);
        _interval += 16666;
    }
    //타임아웃
    VBHTTPComplete(http, VBHTTPErrorTimeOut);
    return NULL;
}

#undef printf
