#ifndef PAYMENTSERVICE_H
#define PAYMENTSERVICE_H

#include "PaymentGateway.h"
#include "PaymentMethod.h"
#include "PaymentProcessor.h"
#include "IdempotencyService.h"
#include "RetryHandler.h"
#include <iostream>
using namespace std;

class PaymentService{
    PaymentGateway* gateway;
    PaymentProcessor processor;
    IdempotencyService idempotencyService;
    RetryHandler retryHandler;
    
    public:
    PaymentService(PaymentGateway* g):gateway(g){}

    bool makePayment(Payment& payment, PaymentMethod* method, string key){
        // Step 1: Idempotency check
        if(idempotencyService.isDuplicate(key)){
            cout<<"Duplicate request detected"<<endl;
            return false;
        }

        //Step 2: Process payment
        if(!processor.process(payment, method)){
            return false;
        }

        //Step3: Call external gateway with retry
        bool success= retryHandler.execute([&](){
            return gateway->charge(payment);
        });

        payment.status=success? PaymentStatus::SUCCESS : PaymentStatus::FAILED;
        return success;
    }
};

#endif
