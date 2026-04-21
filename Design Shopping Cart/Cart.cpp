#ifndef CART_H
#define CART_H

#include "CartItem.cpp"
#include "Discount.cpp"
#include<unordered_map>

class Cart{
    unordered_map<string, CartItem*> itemsList;
    DiscountStrategy* discount;
    
    public:
    Cart():discount(nullptr){}

    void printCart(){
        for(auto& item : itemsList){
            //product //quantity //price
            cout<<"Product: "<<item.second->product.name<<" ";
            cout<<"Quantity: "<<item.second->quantity<<" ";
            cout<<"Price: "<<item.second->cartItemPrice()<<endl;
        }
    }

    double getTotalPrice(){
        double totalPrice=0;
        for(auto& item : itemsList){
            totalPrice+=item.second->cartItemPrice();
        }
        if(discount){
            totalPrice=discount->applyDiscount(totalPrice);
        }
        return totalPrice;
    }

    void addCartItem(const Product& product, int quantity){
        if(itemsList.count(product.id)){
            itemsList[product.id]->quantity += quantity;
            return;
        }
        CartItem* newCartItem=new CartItem(product,quantity);
        itemsList[product.id]=newCartItem;
    }

    void deleteCartItem(string product_id){
        if(itemsList.count(product_id)){
            CartItem* item=itemsList[product_id];
            delete item;
            itemsList.erase(product_id);
            return;
        }
        cout<<"Cannot delete product as it is not in cart"<<endl;
    }

    void updateCartItem(const Product& product, int quantity){
        if(itemsList.count(product.id)){
            CartItem* item=itemsList[product.id];
            item->quantity=quantity;
            return;
        }
        cout<<"Cannot update product as it is not in cart"<<endl;
    }

    void applyDiscount(DiscountStrategy* discount){
        this->discount=discount;
    }

    ~Cart(){
        for(auto& item : itemsList){
            delete(item.second);
        }
        itemsList.clear();
    }
};

#endif