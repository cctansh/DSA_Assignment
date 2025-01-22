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
	List<int> movies;
public:
	Actor(const string&, int);
	void setName(const string&);
	string getName() const;
	void setBirthYear(int);
	int getBirthYear() const;
	const List<int>& getMovies() const;
	void addMovie(int);
	void print();
};
