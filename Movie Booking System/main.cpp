#include "Movie.cpp"
#include "Screen.cpp"
#include "Seat.cpp"
#include "Show.cpp"
#include "User.cpp"
#include "BookingService.cpp"

#include<iostream>
using namespace std;

int main(){
    //Create movie
    Movie m1("movie_id_123", "Avatar", 9.0);

    //Create seats
    vector<Seat> seats;
    for(int i=1; i<=5; i++){
        seats.push_back(Seat("S"+to_string(i), 1, i, SeatType::REGULAR));
    }

    //Create screen
    Screen screen1("screen_id_123", seats);

    //Create show
    Show show1("show_id_123", m1, screen1);

    //Create user
    User user1("user_id_123", "Dhruv");

    //Select seats
    vector<string> selectedSeats={"S1","S2"};

    //Booking service
    BookingService bookingService;
    Booking* booking=bookingService.bookTicket(user1, show1, selectedSeats);

    if(booking==nullptr){
        cout<<"Booking failed"<<endl;
        return 0;
    }

    //Final Output:
    cout<<"-----BOOKING DETAILS-----"<<endl;
    cout<<booking->user.name<<endl;
    cout<<booking->show.movie.name<<endl;
    cout<<"Seats:";
    for(auto& seat : booking->selectedSeats){
        cout<<seat<<" ";
    }
    cout<<"Status: "<<(int)booking->status<<endl;
    cout<<"-------------------";

    return 0;
}