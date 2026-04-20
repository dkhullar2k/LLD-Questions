#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include <iostream>
#include "User.cpp"
#include "Show.cpp"
#include "BookingStatus.cpp"
using namespace std;

class Booking{
    public:
    string id;
    User user;
    Show show;
    vector<string> selectedSeats;
    BookingStatus status;

    Booking(string id, User user, Show show, vector<string> seatIds)
        : id(id), user(user), show(show), selectedSeats(seatIds),
        status(BookingStatus::PENDING){}

};

#endif