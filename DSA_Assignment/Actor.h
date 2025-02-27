#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "List.h"
using namespace std;
class Actor
{
private:
	string name;
	int birthYear;
	List<int> movies;
	List<float> ratings;
public:
	Actor(const string&, int);
	void setName(const string&);
	string getName() const;
	void setBirthYear(int);
	int getBirthYear() const;
	const List<int>& getMovies() const;
	void addMovie(int);
	const List<float>& getRatings() const;
	void addRating(float);
	float getAverageRating() const;
	void displayRatings();
	void print();
	bool operator<(const Actor& other) const;
	friend ostream& operator<<(ostream& os, const Actor& actor);
};