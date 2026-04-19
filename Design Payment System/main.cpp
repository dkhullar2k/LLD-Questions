#include "PaymentService.h"
#include "Factory.h"
#include "RefundService.h"
#include <iostream>

using namespace std;

int main(){
    Payment payment("p1","u1","INR",5000);
    PaymentMethod* method=PaymentMethodFactory::create("UPI");
    PaymentGateway* gateway=PaymentGatewayFactory::create("RAZORPAY");

    PaymentService paymentService(gateway);
    bool result= paymentService.makePayment(payment, method, "unique_key_123");

    cout<<"Payment Status: "<<(int)payment.status<<endl;

    RefundService refundService(gateway);
    refundService.refund(payment);
    
    return 0;
}