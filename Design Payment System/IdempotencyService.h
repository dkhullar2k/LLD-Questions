#ifndef IDEMPOTENCYSERVICE_H
#define IDEMPOTENCYSERVICE_H

#include <iostream>
#include <unordered_set>
using namespace std;

class IdempotencyService{
    unordered_set<string> processedKeys;
    public:

    bool isDuplicate(const string& key){
        if(processedKeys.count(key)){
            return true;
        }
        processedKeys.insert(key);
        return false;
    }
};

#endif
