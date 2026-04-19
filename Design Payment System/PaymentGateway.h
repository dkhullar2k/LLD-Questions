#ifndef PAYMENTGATEWAY_H
#define PAYMENTGATEWAY_H

#include "Payment.h"
#include <iostream>
using namespace std;

/* 
-> We pass in Payment object bcuz the payment gateway talks to the bank and it needs payment details.
-> Charge and Refund are two methods exposed by the gateway for simplicity
*/

class PaymentGateway{
    public:
    virtual bool charge(Payment& payment)=0;
    virtual bool refund(Payment& payment)=0;
    virtual ~PaymentGateway(){}
};

class RazorpayGateway: public PaymentGateway{
    public:
    bool charge(Payment& payment) override{
        cout<<"Razorpay processing payment"<<endl;
        return true;
    }
    bool refund(Payment& payment) override{
        cout<<"Razorpay refunding payment"<<endl;
        return true;
    }
};

class StripeGateway: public PaymentGateway{
    public:
    bool charge(Payment& payment)override{
        cout<<"Stripe processing payment"<<endl;
        return true;
    }
    bool refund(Payment& payment) override{
        cout<<"Stripe refunding payment"<<endl;
        return true;
    }
};

#endif
