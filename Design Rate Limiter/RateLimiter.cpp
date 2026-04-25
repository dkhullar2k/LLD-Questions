#ifndef RATELIMITER_H
#define RATELIMITER_H 

#include "Bucket.cpp"
#include <iostream>
#include <unordered_map>
#include <mutex>
using namespace std;

class RateLimiter{
    unordered_map<string, Bucket*> userBucket;
    mutex globalMutex;
    
    public:
    bool isAllowed(const string& user){
        lock_guard<mutex> lock(globalMutex);

        if(!userBucket.count(user)){
            Bucket* newBucket=new Bucket(2, 1);
            userBucket[user]=newBucket;
        }
        return userBucket[user]->allowRequest();
    }

    ~RateLimiter(){
        for(auto& item:userBucket){
            delete item.second;
        }
    }
};

#endif