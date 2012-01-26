#ifndef __VBThread_H__
#define __VBThread_H__

#include "../VBType.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef void (*VBThreadLoopFunc)(void* _user_reference);

    typedef struct VBThread VBThread;
    
    struct VBThread {
        void* thread_id;
        VBThreadLoopFunc func;
        void* user_reference;
        VBBool is_run;
    };
    
    VBThread* VBThreadAlloc(void);
    
    VBThread* VBThreadInit(VBThread* _thread, VBThreadLoopFunc _func, void* _user_reference);
    
    void VBThreadRun(VBThread* _thread);
    
    void VBThreadStop(VBThread* _thread);
    
    VBBool VBThreadGetIsRun(VBThread* _thread);
    
    void* VBThreadGetUserReference(VBThread* _thread);
    
    void* VBThreadGetID(VBThread* _thread);
    
    void VBThreadFree(VBThread** _thread);
    
#ifdef __cplusplus
}
#endif

#endif