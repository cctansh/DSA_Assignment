#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "List.h"
using namespace std;
class Movie
{
private:
	string title;
	string plot;
	int year;
	List<int> actors;
	List<float> ratings;
public:
	Movie(const string&, const string&, int);
	void setTitle(const string&);
	string getTitle() const;
	void setPlot(const string&);
	string getPlot() const;
	void setYear(int);
	int getYear() const;
	const List<int>& getActors() const;
	void addActor(int);
	const List<float>& getRatings() const;
	void addRating(float);
	float getAverageRating() const;
	void displayRatings();
	void print();
	void printFullDetails();
};