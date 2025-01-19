#pragma once
#include <string>
#include <iostream>
#include "List.h"
using namespace std;
class Actor
{
private:
	string name;
	int birthYear;
	List movies;
public:
	Actor(string, int);
	void setName(string);
	string getName();
	void setBirthYear(int);
	int getBirthYear();
	void setMovies(List);
	List getMovies();
	void addMovie(int);
	void print();
};
