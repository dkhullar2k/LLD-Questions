#ifndef SHOW_H
#define SHOW_H

#include <string>
#include <unordered_map>
#include "Movie.cpp"
#include "Screen.cpp"
#include "Seat.cpp"
using namespace std;

class Show{
    public:
    string id;
    Movie movie;
    Screen screen;
    string time;
    unordered_map<string,bool> seatAvailability;

    Show(string id, Movie m, Screen s)
        : id(id), movie(m), screen(s){
        
        for(auto& seat: s.seats){
            seatAvailability[seat.number]=true;
        }
    }
    
};

#endif