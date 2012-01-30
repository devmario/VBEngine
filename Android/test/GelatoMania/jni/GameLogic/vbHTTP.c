#include "vbHTTP.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "VBEngine.h"

#define GET_HEADER "GET /%s HTTP/1.0\nAccept:text/plain\nAccept-Language:en\nConnection:Close\nHost:%s\nUser-Agen:Mozilla/4.0\n\n"
#define POST_HEADER "POST /%s HTTP/1.0\r\nContent-Length: %ld\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s"

char* CutHeader(char *response);
char* CutHeader(char *response) {
	int i = 0;
	size_t header_len = strlen(response);
	while(i < header_len) {
		if(response[i] == '\0')
			break;
		i++;
	}
	return response + i + 1;
}

void* VBHTTPResponseRead(void* _arg);

void* VBHTTPResponseRead(void* _arg) {
    VBHTTP* http = _arg;
    unsigned int _interval = 0;
    printf("\nResponse Header\n\n");
    fflush(stdout);
    unsigned long _tl = 0;
    while(_interval < http->break_time) {
        char buf[0xFF] = {'\0',};
		unsigned long _read_len = read(http->sock, buf, 0xF);
		_tl += _read_len;
		if(http->response) {
			http->response = realloc(http->response, (_tl + 1) * sizeof(char));
		} else {
			http->response = calloc((_tl + 1), sizeof(char));
		}
		sprintf(http->response + _tl - _read_len, "%s\0", buf);
        printf("%s", buf);
        fflush(stdout);
		if(_read_len < 1) {
			if(http->tid) {
                //성공
                http->complete = 1;
                http->success_handle();
				http->tid = NULL;
                return NULL;
			}
        }
		_interval += http->read_interval;
        usleep(http->read_interval);
    }
    //타임아웃
    http->complete = 1;
    //for DEBUG http->error_handle(0);
    printf("포트 없음\n");
    fflush(stdout);
    http->tid = NULL;
    return NULL;
}

VBHTTP* VBHTTPCreateByJS(const char* _js_fileName,
                         void (_error_handle)(unsigned char error_code), 
                         void (_success_handle)(void)) {
    VBString* _str = VBStringInitWithCStringFormat(VBStringAlloc(), "%s/%s", VBStringGetCString(VBEngineGetResourcePath()), _js_fileName);
    printf("%s\n",_str->data);
    FILE* _f = fopen(VBStringGetCString(_str), "rb");
    VBStringFree(&_str);
    fseek(_f, 0, SEEK_END);
    size_t _size = ftell(_f);
    fseek(_f, 0, SEEK_SET);
    char* _buf = (char*)calloc(sizeof(char), _size + 1);
    fread(_buf, _size, sizeof(char), _f);
    fclose(_f);
    
    VBHTTP* http = VBHTTPCreate("ec2-23-20-6-240.compute-1.amazonaws.com", "80", 5.0, 0, "POST", _buf, _error_handle, _success_handle);
    free(_buf);
    
    return http;
}

VBHTTP* VBHTTPCreate(const char* _host_name,
                     const char* _port,
                     double _break_time, //최대 응답대기시간
                     double _read_interval, //응답확인 인터벌
                     const char* _method, //GET
                     const char* _request, //request
                     void (_error_handle)(unsigned char error_code), 
                     void (_success_handle)(void)) {
    VBHTTP* http = calloc(sizeof(VBHTTP), 1);
	
    http->host_name = calloc(sizeof(char), (strlen(_host_name) + 1));
    memmove(http->host_name, _host_name, sizeof(char) * (strlen(_host_name)));
	
    http->port = calloc(sizeof(char), (strlen(_port) + 1));
    memmove(http->port, _port, sizeof(char) * (strlen(_port)));
    
    http->break_time = 1000000.0 * _break_time;
    http->read_interval = 1000000.0 * _read_interval;
	
    http->error_handle = _error_handle;
	http->success_handle = _success_handle;
	
    http->method = calloc(sizeof(char), (strlen(_method) + 1));
    memmove(http->method, _method, sizeof(char) * (strlen(_method)));
    
    http->request = calloc(sizeof(char), (strlen(_request) + 1));
    memmove(http->request, _request, sizeof(char) * (strlen(_request)));
    
	struct hostent *__hostent_pnt;
	struct servent *__servent_pnt;
	struct sockaddr_in __sockaddr_in;
	memset((void*)&__sockaddr_in, 0, sizeof(__sockaddr_in));
	__sockaddr_in.sin_family = AF_INET;
    __servent_pnt = getservbyname("http", "tcp");
	
    if(__servent_pnt) {
		__sockaddr_in.sin_port = __servent_pnt->s_port;
	} else if((__sockaddr_in.sin_port = htons(atoi(http->port)))==0) {
        http->complete = 1;
        http->error_handle(0);
        printf("포트 없음\n");
        fflush(stdout);
    }
    
    __hostent_pnt = gethostbyname(http->host_name);
	if(__hostent_pnt) {
		memcpy((void*)&__sockaddr_in.sin_addr, (void*)__hostent_pnt->h_addr, __hostent_pnt->h_length);
	} else if((__sockaddr_in.sin_addr.s_addr = inet_addr(http->host_name)) == INADDR_NONE) {
        http->complete = 1;
        http->error_handle(0);
        printf("호스트 또는 포트 없음\n");
        fflush(stdout);
	}
	
    if((http->sock = socket(PF_INET,SOCK_STREAM,0)) < 0) {
        http->complete = 1;
        http->error_handle(0);
        printf("소켓 생성 실패\n");
        fflush(stdout);
    }
	
    if(connect(http->sock,(struct sockaddr*)&__sockaddr_in, sizeof(__sockaddr_in)) < 0) {
        http->complete = 1;
        http->error_handle(0);
        printf("연결 실패\n");
        fflush(stdout);
    }
    
    if(strcmp(http->method, "GET") == 0) {
        http->header = calloc(sizeof(char), (strlen(GET_HEADER) + strlen(http->host_name) + strlen(http->request) + 0xFF));
        sprintf(http->header, GET_HEADER, http->request, http->host_name);
        size_t _len = strlen(http->header);
        if(_len != write(http->sock, http->header, _len)) {
            http->complete = 1;
            http->error_handle(0);
            printf("헤더전송 실패\n");
            fflush(stdout);
        }
    } else if(strcmp(http->method, "POST") == 0) {
        http->header = calloc(sizeof(char), (strlen(POST_HEADER) + strlen(http->host_name) + strlen(http->request) + 0xFF));
        sprintf(http->header, POST_HEADER, "", strlen(http->request), http->request);
        printf("Request Header\n\n%s\n\n\n\n", http->header);
        fflush(stdout);
        size_t _len = strlen(http->header);
        if(_len != write(http->sock, http->header, _len)) {
            http->complete = 1;
            http->error_handle(0);
            printf("헤더전송 실패\n");
            fflush(stdout);
        }
    }
    
	pthread_create(&http->tid, NULL, VBHTTPResponseRead, http);
    
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
        if((*http)->tid)
            pthread_detach((*http)->tid);
        free(*http);
        *http = NULL;
    }
}
