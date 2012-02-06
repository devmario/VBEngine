#include "PlatformFunctions.h"

PlatformCallback PlatformCallbackCreate(void* _reference, PlatformCallbackFunction _function) {
    PlatformCallback callback;
    callback.reference = _reference;
    callback.function = _function;
    return callback;
}

int PlatformReturnIsSuccess(cJSON* _json) {
    cJSON* success = cJSON_GetObjectItem(_json, "success");
    if(success) {
        return cJSON_IsTrue(success);
    } else {
        return -1;
    }
}

PlatformError PlatformReturnError(cJSON* _json) {
    cJSON* error = cJSON_GetObjectItem(_json, "error");
    if(error) {
        return cJSON_GetInt(error);
    } else {
        return -1;
    }
}