#pragma once
#include <string>
#include <iostream>
#include "List.h"
using namespace std;
class Movie
{
private:
	string title;
	string plot;
	int year;
	List actors;
public:
	void setTitle(string);
	string getTitle();
	void setPlot(string);
	string getPlot();
	void setYear(int);
	int getYear();
	void setActors(List);
	List getActors();
	void print();
};