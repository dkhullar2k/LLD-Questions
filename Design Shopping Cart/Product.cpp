#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>
using namespace std;

class Product{
    public:
    string id;
    string name;
    double price;

    Product(string id, string name, double price)
        : id(id), name(name), price(price){}
};

#endif