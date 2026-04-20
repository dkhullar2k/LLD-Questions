#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <string>
#include <iostream>
#include "Seat.cpp"
using namespace std;

class Screen{
    public:
    string id;
    vector<Seat> seats;

    Screen(string id, vector<Seat> s)
        : id(id), seats(s){}
};

#endif