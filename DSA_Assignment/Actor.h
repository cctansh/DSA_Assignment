/*
DSA T02
Group 7
Tan Si Huei Chloe S10260078
Ng Joe Yi S10262850
*/

#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "List.h"
using namespace std;
class Actor
{
private:
	int id;
	string name;
	int birthYear;
	List<int> movies;
	List<float> ratings;
public:
	// Constructor
	// Parameters: int id, const string& name, int birthYear
	Actor(int, const string&, int);

	// Sets the ID of the actor
	// Parameter: int id
	// Pre : None
	// Post: Actor's ID is updated
	void setId(int);

	// Gets the ID of the actor
	// Pre : None
	// Post: None
	// Returns: int - actor's ID
	int getId() const;

	// Sets the name of the actor
	// Parameter: const string& name
	// Pre : None
	// Post: Actor's name is updated
	void setName(const string&);

	// Gets the name of the actor
	// Pre : None
	// Post: None
	// Returns: string - actor's name
	string getName() const;

	// Sets the birth year of the actor
	// Parameter: int birthYear
	// Pre : None
	// Post: Actor's birth year is updated
	void setBirthYear(int);

	// Gets the birth year of the actor
	// Pre : None
	// Post: None
	// Returns: int - actor's birth year
	int getBirthYear() const;

	// Gets the list of movies the actor has participated in
	// Pre : None
	// Post: None
	// Returns: const List<int>& - list of movie IDs
	const List<int>& getMovies() const;

	// Adds a movie to the actor's list
	// Parameter: int movieID
	// Pre : movieID should be valid
	// Post: movieID is added to the actor's list of movies
	void addMovie(int);

	// Gets the list of ratings for the actor
	// Pre : None
	// Post: None
	// Returns: const List<float>& - list of ratings
	const List<float>& getRatings() const;

	// Adds a rating to the actor's list
	// Parameter: float rating
	// Pre : rating should be between 0 and 10
	// Post: rating is added to the actor's ratings list
	void addRating(float);

	// Calculates the average rating of the actor
	// Pre : Actor should have at least one rating
	// Post: None
	// Returns: float - average rating
	float getAverageRating() const;

	// Displays all ratings of the actor
	// Pre : None
	// Post: Ratings are printed to the console
	void displayRatings();

	// Prints basic information of the actor
	// Pre : None
	// Post: Actor's information is printed to the console
	void print();

	// Sorting methods

	// Sorts an array of actor names using insertion sort
	// Parameters: string arr[] - array of names, int n - size of array
	// Pre : Array must be initialized
	// Post: Array is sorted alphabetically
	static void insertionSortNames(string arr[], int n);

	// Sorts actors by age using merge sort
	// Parameters: Actor* arr[] - array of actor pointers, int left - left index, int right - right index, int currentYear - current year
	// Pre : Array must be initialized and indices valid
	// Post: Array is sorted by age in ascending order
	static void mergeSortByAge(Actor* arr[], int left, int right, int currentYear);

	// Sorts actors by rating in descending order
	// Parameters: Actor* arr[] - array of actor pointers, int left - left index, int right - right index
	// Pre : Array must be initialized and indices valid
	// Post: Array is sorted by rating in descending order
	static void sortActorsByRatingDescending(Actor* arr[], int left, int right);
};