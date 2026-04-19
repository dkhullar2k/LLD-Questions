#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
using namespace std;

enum class PaymentStatus{
    INITIATED,
    PENDING,
    SUCCESS,
    FAILED,
    REFUNDED
};

class Payment{
    public:
    string paymentId;
    string userID;
    string currency;
    int amount;
    PaymentStatus status;

    Payment(string pid, string uid, string curr, int amt)
        : paymentId(pid), userID(uid), currency(curr), amount(amt), 
            status(PaymentStatus::INITIATED){}
};

#endif
