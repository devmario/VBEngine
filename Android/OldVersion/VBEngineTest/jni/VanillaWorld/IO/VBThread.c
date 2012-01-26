#include "VBThread.h"
#include "VBSystem.h"
#include <pthread.h>

void* _VBThreadThreadFunc(void* _arg) {
    VBThread* _thread = _arg;
    _thread->func(_thread->user_reference);
    _thread->is_run = VBFalse;
    pthread_exit(VBNull);
    return VBNull;
}

VBThread* VBThreadAlloc(void) {
    VBThread* _thread = VBSystemCalloc(sizeof(VBThread), 1);
    _thread->thread_id = VBSystemCalloc(sizeof(pthread_t), 1);
    return _thread;
}

VBThread* VBThreadInit(VBThread* _thread, VBThreadLoopFunc _func, void* _user_reference) {
    _thread->func = _func;
    _thread->user_reference = _user_reference;
    return _thread;
}

void VBThreadRun(VBThread* _thread) {
    if(!_thread->is_run) {
        _thread->is_run = VBTrue;
        pthread_create(_thread->thread_id, VBNull, _VBThreadThreadFunc, _thread);
        pthread_detach(*((pthread_t*)_thread->thread_id));
    }
}

void VBThreadStop(VBThread* _thread) {
    if(_thread->is_run) {
        _thread->is_run = VBFalse;
        pthread_exit(VBNull);
    }
}

VBBool VBThreadGetIsRun(VBThread* _thread) {
    return _thread->is_run;
}

void* VBThreadGetUserReference(VBThread* _thread) {
    return _thread->user_reference;
}

void* VBThreadGetID(VBThread* _thread) {
    return _thread->thread_id;
}

void VBThreadFree(VBThread** _thread) {
    VBSystemFree((*_thread)->thread_id);
    VBSystemFree(*_thread);
    *_thread = VBNull;
}
