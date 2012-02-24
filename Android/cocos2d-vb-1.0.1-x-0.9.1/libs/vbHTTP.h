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
#include <stdbool.h>

//#define vbHTTPDebug

#ifdef __cplusplus
extern "C" {
#endif
    /* Converts a hex character to its integer value */
    char from_hex(char ch);
    
    /* Converts an integer value to its hex character*/
    char to_hex(char code);
    
    /* Returns a url-encoded version of str */
    /* IMPORTANT: be sure to free() the returned string after use */
    char *url_encode(char *str);
    
    /* Returns a url-decoded version of str */
    /* IMPORTANT: be sure to free() the returned string after use */
    char *url_decode(char *str);
    
    typedef enum VBHTTPError {
        //에러없음
        VBHTTPErrorNone                =    0,
        
        //로컬에 포트검색 실패
        VBHTTPErrorNotFoundLocalPort   =    1,
        
        //서버검색 실패
        VBHTTPErrorNotFoundServer      =    2,
        
        //소켓생성 실패
        VBHTTPErrorSocketCreateFail    =    3,
        
        //연결 실패
        VBHTTPErrorConnectFail         =    4,
        
        //전송 실패
        VBHTTPErrorWriteFail           =    5,
        
        //타임아웃
        VBHTTPErrorTimeOut             =    6
    } VBHTTPError;
    
    typedef struct VBHTTP VBHTTP;
    
    struct VBHTTP {
        char* host_name;
        char* port;
        unsigned long break_time;
        unsigned long interval;
        int readBufLen;
        void (*success_handle)(VBHTTP* _http, VBHTTPError _error, void* _reference);
        int sock;
        char* method;
        char* request;
        char* response;
        char* data;
        size_t data_len;
        char* header;
        pthread_t tid;
        int complete;
        void* reference;
        bool auto_release;
    };
    
    char* VBHTTPCutHeaderByOffset(char* _response, int* offset);
    //HTTP 응답에서 헤더를 제거한 문자열 리턴(응답 문자열 포인터에서 해더길이만큼 이동된 값을 전달해줌) 
    char* VBHTTPCutHeader(char* _response);
    
    //초기화
    VBHTTP* VBHTTPCreate(const char* _host_name, //서버주소
                         const char* _port, //서버포트
                         double _break_time, //최대 응답대기시간
                         double _read_interval, //하나의 read인터벌
                         int _read_buf_len, //read buf len
                         const char* _method, //GET, POST
                         const char* _data, //POST시 데이터
                         size_t _data_len, //POST시 데이터 길이
                         void* _reference, //success_hande에 _reference인자로 넘어갈 유저 포인터
                         void (*_success_handle)(VBHTTP* _http, VBHTTPError _error, void* _reference), //완료후 리턴
                         bool _auto_release, //완료후 자동으로 해제 되는지의 여부
                         const char* _request, //request(서버주소 뒤에 붙는 경로랑 쿼리) formatter
                         ...
                         );
    
    void VBHTTPRelease(VBHTTP** http);
    
//#ifdef DEBUG
    //매니아 테스트서버에 서버코드와 쿼리를 전송 
    void VBHTTPCreateByJS(const char* _json_file_path,
                          void* _reference,
                          void (*_success_handle)(VBHTTP* _http, VBHTTPError _error, void* _reference),
                          const char* _request,
                          ...);
//#endif
    
#ifdef __cplusplus
}
#endif

#endif