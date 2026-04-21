#ifndef CARTSERVICE_H
#define CARTSERVICE_H

#include "Cart.cpp"
#include "User.cpp"
#include "Discount.cpp"
#include<iostream>
#include<unordered_map>
using namespace std;

class CartService{
    unordered_map<string,Cart*> cartList;
    
    public:
    void addItem(const User& user, const Product& product, int quantity){
        if(!cartList.count(user.id)){
            Cart* cart=new Cart();
            cartList[user.id]=cart;
        }
        cartList[user.id]->addCartItem(product, quantity);
    }

    void viewCart(const User& user){
        if(cartList.count(user.id)){
            cartList[user.id]->printCart();
            return;
        }
        cout<<"No cart found for this user"<<endl;
    }

    void deleteItem(const User& user, const Product& product){
        if(cartList.count(user.id)){
            cartList[user.id]->deleteCartItem(product.id);
            return;
        }
        cout<<"Cannot delete product as no cart found for this user"<<endl;
    }

    void updateItem(const User& user, const Product& product, int quantity){
        if(cartList.count(user.id)){
            cartList[user.id]->updateCartItem(product,quantity);
            return;
        }
        cout<<"Cannot update product as no cart found for this user"<<endl;
    }

    void checkout(const User& user){
        if(cartList.count(user.id)){
            double totalCost= cartList[user.id]->getTotalPrice();
            cout<<"Total Amount: "<<totalCost<<endl;
            return;
        }
        cout<<"Cannot checkout as no cart found for this user"<<endl;
    }

    void applyDiscount(const User& user, DiscountStrategy* discount){
        if(cartList.count(user.id)){
            cartList[user.id]->applyDiscount(discount);
            return;
        }
        cout<<"Cannot apply discount as no cart found for this user"<<endl;
    }

    ~CartService(){
        for(auto& cart : cartList){
            delete(cart.second);
        }
        cartList.clear();
    }
};

#endif