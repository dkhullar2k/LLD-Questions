#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

class User{
    public:
    string id;
    string name;

    User(string id, string name)
        : id(id), name(name){}

};

#endif