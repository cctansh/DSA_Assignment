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

	// Sorting methods
	static void insertionSortNames(string arr[], int n);
	static void mergeSortByAge(Actor* arr[], int left, int right, int currentYear);
	static void sortActorsByRatingDescending(Actor* arr[], int n);
};