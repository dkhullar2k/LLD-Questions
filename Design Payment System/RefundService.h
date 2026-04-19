#include "PaymentGateway.h"
#include <iostream>
using namespace std;

class RefundService{
    PaymentGateway* gateway;

    public:
    RefundService(PaymentGateway* g) : gateway(g){}

    bool refund(Payment& payment){
        if(payment.status!=PaymentStatus::SUCCESS){
            cout<<"Refund is not allowed"<<endl;
            return false;
        }
        bool success=gateway->refund(payment);
        if(success){
            payment.status=PaymentStatus::REFUNDED;
        }
        return success;
    }
};