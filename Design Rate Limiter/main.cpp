/*
Approach- Token Bucket
*/
#include "RateLimiter.cpp"
#include "Bucket.cpp"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main(){
    RateLimiter limiter;
    string user="user1";

    cout << "Sending 10 rapid requests:\n";
    for (int i = 0; i < 10; i++) {
        if (limiter.isAllowed(user)) {
            cout << "Request " << i + 1 << ": Allowed\n";
        } else {
            cout << "Request " << i + 1 << ": Blocked\n";
        }
    }

    cout << "\nSleeping for 2 seconds...\n";
    this_thread::sleep_for(chrono::seconds(2));

    cout << "\nSending 5 more requests:\n";

    for (int i = 0; i < 5; i++) {
        if (limiter.isAllowed(user)) {
            cout << "Request " << i + 1 << ": Allowed\n";
        } else {
            cout << "Request " << i + 1 << ": Blocked\n";
        }
    }

    return 0;
}