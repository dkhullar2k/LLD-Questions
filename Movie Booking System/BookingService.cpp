#ifndef BOOKINGSERVICE_H
#define BOOKINGSERVICE_H

#include <string>
#include <vector>
#include <iostream>
#include "User.cpp"
#include "Show.cpp"
#include "Booking.cpp"
using namespace std;

class BookingService{
    public:
    Booking* bookTicket(User user, Show s, vector<string>& seatIds){
        //Create Booking
        Booking* booking=new Booking("B1",user,s,seatIds);

        //Check Availability
        for(auto& seat : seatIds){
            if(!s.seatAvailability[seat]){
                booking->status = BookingStatus::FAILED;
                cout<<"Seat ID "<<seat<<" is already booked"<<endl;
                return booking;
            }
        }

        //Mark seats available
        for(auto& seat : seatIds){
            s.seatAvailability[seat]=false;
        }

        booking->status=BookingStatus::CONFIRMED;

        cout<<"Seats booked successfully"<<endl;
        return booking;
    }
};

#endif