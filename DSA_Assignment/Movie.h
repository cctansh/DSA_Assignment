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
class Movie
{
private:
	int id;
	string title;
	string plot;
	int year;
	List<int> actors;
	List<float> ratings;
public:
	Movie(int, const string&, const string&, int);

	// Sets the ID of the movie
	// Parameter: int id
	// Pre : None
	// Post: Movie's ID is updated
	void setId(int);

	// Gets the ID of the movie
	// Pre : None
	// Post: None
	// Returns: int - movie's ID
	int getId() const;

	// Sets the title of the movie
	// Parameter: const string& title
	// Pre : None
	// Post: Movie's title is updated
	void setTitle(const string&);

	// Gets the title of the movie
	// Pre : None
	// Post: None
	// Returns: string - movie's title
	string getTitle() const;

	// Sets the plot of the movie
	// Parameter: const string& plot
	// Pre : None
	// Post: Movie's plot is updated
	void setPlot(const string&);

	// Gets the plot of the movie
	// Pre : None
	// Post: None
	// Returns: string - movie's plot
	string getPlot() const;

	// Sets the release year of the movie
	// Parameter: int year
	// Pre : None
	// Post: Movie's release year is updated
	void setYear(int);

	// Gets the release year of the movie
	// Pre : None
	// Post: None
	// Returns: int - movie's release year
	int getYear() const;

	// Gets the list of actors in the movie
	// Pre : None
	// Post: None
	// Returns: const List<int>& - list of actor IDs
	const List<int>& getActors() const;

	// Adds an actor to the movie's list
	// Parameter: int actorID
	// Pre : actorID should be valid
	// Post: actorID is added to the movie's list of actors
	void addActor(int);

	// Gets the list of ratings for the movie
	// Pre : None
	// Post: None
	// Returns: const List<float>& - list of ratings
	const List<float>& getRatings() const;

	// Adds a rating to the movie's list
	// Parameter: float rating
	// Pre : rating should be between 0 and 10
	// Post: rating is added to the movie's ratings list
	void addRating(float);

	// Calculates the average rating of the movie
	// Pre : Movie should have at least one rating
	// Post: None
	// Returns: float - average rating
	float getAverageRating() const;

	// Displays all ratings of the movie
	// Pre : None
	// Post: Ratings are printed to the console
	void displayRatings();

	// Prints basic information of the movie
	// Pre : None
	// Post: Movie's information is printed to the console
	void print();

	// Prints full details of the movie including plot and actors
	// Pre : None
	// Post: Full details are printed to the console
	void printFullDetails();

	// Sorting methods

	// Sorts an array of movie titles using insertion sort
	// Parameters: string arr[] - array of titles, int n - size of array
	// Pre : Array must be initialized
	// Post: Array is sorted alphabetically
	static void insertionSortTitles(string arr[], int n);

	// Sorts movies by release year using merge sort
	// Parameters: Movie* arr[] - array of movie pointers, int left - left index, int right - right index
	// Pre : Array must be initialized and indices valid
	// Post: Array is sorted by release year
	static void mergeSortByYear(Movie* arr[], int left, int right);

	// Sorts movies by rating in descending order
	// Parameters: Movie* arr[] - array of movie pointers, int left - left index, int right - right index
	// Pre : Array must be initialized and indices valid
	// Post: Array is sorted by rating in descending order
	static void sortMoviesByRatingDescending(Movie* arr[], int left, int right);
};