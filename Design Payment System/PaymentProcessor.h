#ifndef PAYMENTPROCESSOR_H
#define PAYMENTPROCESSOR_H

#include "Payment.h"
#include "PaymentMethod.h"
#include <iostream>
using namespace std;

class PaymentProcessor{
    public:
    bool process(Payment& payment, PaymentMethod* method){
        payment.status=PaymentStatus::PENDING;

        if(!method->validate(payment)){
            payment.status=PaymentStatus::FAILED;
            return false;
        }
        if(!method->process(payment)){
            payment.status=PaymentStatus::FAILED;
            return false;
        }
        return true;
    }
};

#endif
