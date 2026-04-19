#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H

#include "Payment.h"
#include <iostream>
using namespace std;

// Strategy pattern
class PaymentMethod{
    public:
    virtual bool validate(Payment& payment)=0;
    virtual bool process(Payment& payment)=0;
    virtual ~PaymentMethod (){}
};

class CardPayment: public PaymentMethod{
    public:
    bool validate(Payment& payment) override{
        cout<<"Validating card details"<<endl;
        return true;
    }
    bool process(Payment& payment) override{
        cout<<"Processing card payment"<<endl;
        return true;
    }
};

class UPIPayment: public PaymentMethod{
    public:
    bool validate(Payment& payment) override{
        cout<<"Validating UPI details"<<endl;
        return true;
    }
    bool process(Payment& payment) override{
        cout<<"Processing UPI payment"<<endl;
        return true;
    }
};

#endif
