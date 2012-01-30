#ifndef gelatomania_callback_h
#define gelatomania_callback_h


class cCallback
{
public:
    virtual void Execute(int Param) const =0;
};

template <class cInstance>
class TCallback : public cCallback
{
public:
    TCallback()
    {
        pFunction = 0;
    }
    
    typedef void (cInstance::*tFunction)(int Param);
    
    virtual void Execute(int Param) const 
    {
        if (pFunction) (cInst->*pFunction)(Param);
        else printf("ERROR : the callback function has not been defined !!!!");
    }
    
    void SetCallback (cInstance  *cInstancePointer, 
                      tFunction   pFunctionPointer)
    {
        cInst     = cInstancePointer;
        pFunction = pFunctionPointer;
    }
    
private:
    cInstance  *cInst;
    tFunction  pFunction;
};
                    
#endif
