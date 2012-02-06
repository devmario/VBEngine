#ifdef __ANDROID__

#include "PlatformFunctions.h"

int PlatformGameCenterIsSigned() {
    return 0;
}

void PlatformGameCenterLogin(void (*_completeCallback)(cJSON*)) {
    
}

void* _getFB() {
    return NULL;
}

int PlatformFacebookIsSigned() {
    return 0;
}

void PlatformFacebookLogin(void (*_completeCallback)(cJSON*)) {
    
}

void PlatformFacebookRequestGraphPath(const char* _path, void (*_completeCallback)(cJSON*)) {
    
}

void PlatformFacebookAppRequest(const char* _msg, const char* _to, const char* _notification_text, void (*_completeCallback)(cJSON*)) {
    
}

void PlatformFacebookFeed(const char* _name, const char* _caption, const char* _description, const char* _link, const char* _picture, void (*_completeCallback)(cJSON*)) {
    
}

void PlatformMobageLogin(void (*_completeCallback)(cJSON*)) {
    
}

void PlatformTwitterLogin(void (*_completeCallback)(cJSON*)) {
    
}


#endif
