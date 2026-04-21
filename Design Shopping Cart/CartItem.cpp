#ifndef CARTITEM_H
#define CARTITEM_H

#include "Product.cpp"

class CartItem{
    public:
    Product product;
    int quantity;

    CartItem(Product product, int quantity)
        : product(product), quantity(quantity){}
    
    double cartItemPrice(){
        return product.price*quantity;
    }
};

#endif