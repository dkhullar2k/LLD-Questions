#ifndef SEAT_H
#define SEAT_H

#include <string>
#include "SeatType.cpp"
using namespace std;

class Seat{
    public:
    string number;
    int row;
    int col;
    SeatType type;

    Seat(string n, int r, int c, SeatType t)
        : number(n), row(r), col(c), type(t){}
};

#endif