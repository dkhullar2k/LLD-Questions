#ifndef FACTORY_H
#define FACTORY_H

#include "PaymentMethod.h"
#include "PaymentGateway.h"
#include <iostream>
using namespace std;

class PaymentMethodFactory{
    public:
    static PaymentMethod* create (const string& type){
        if(type=="CARD"){
            return new CardPayment();
        }
        if(type=="UPI"){
            return new UPIPayment();
        }
        return nullptr;
    }
};

class PaymentGatewayFactory{
    public:
    static PaymentGateway* create (const string& type){
        if(type=="RAZORPAY"){
            return new RazorpayGateway();
        }
        if(type=="STRIPE"){
            return new StripeGateway();
        }
        return nullptr;
    }
};

#endif
