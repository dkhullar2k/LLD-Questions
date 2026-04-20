#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>
using namespace std;

class Movie{
    public:
    string id;
    string name;
    double rating;

    Movie(string id, string name, int rating)
        : id(id), name(name), rating(rating){}
};

#endif