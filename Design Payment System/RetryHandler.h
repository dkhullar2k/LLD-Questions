#ifndef RETRYHANDLER_H
#define RETRYHANDLER_H

class RetryHandler{
    public:
    template<typename Func>
    bool execute(Func func, int retries=3){
        while(retries--){
            if(func()) return true;
        }
        return false;
    }
};

#endif
