#ifndef BUCKET_H
#define BUCKET_H

#include <iostream>
#include <mutex>
#include <chrono>
using namespace std;

static long currentTime(){
    return chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now().time_since_epoch()
    ).count();
}

class Bucket{
    int capacity;
    double tokens;
    double refillRate;
    long lastRefillTime;
    mutex mtx;

    public:
    Bucket(int capacity, double refillRate): capacity(capacity), tokens(capacity),
        refillRate(refillRate), lastRefillTime(currentTime()) {}

        void refill(){
            //find current time
            long now=currentTime();

            //elapsed time
            long elapsed=now-lastRefillTime;

            //tokens to be added since last refill
            double tokensToAdd=elapsed*refillRate;

            //calculate tokens
            tokens=min((double)capacity, tokens+tokensToAdd);

            //update lastRefillTime
            lastRefillTime=now;
        }

        bool allowRequest(){
            lock_guard<mutex> lock(mtx);
            refill();

            if(tokens>0){
                tokens-=1.0;
                return true;
            }
            return false;
        }
};

#endif