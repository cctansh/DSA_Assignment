/*
DSA T02
Group 7
Tan Si Huei Chloe S10260078
Ng Joe Yi S10262850
*/

#include <iostream>
#include "Dictionary.h"
#include "List.h"
#include "Actor.h"
#include "Movie.h"
#include "KeyValue.h"
#include "Graph.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <cctype>
using namespace std;

// Parse and update base CSV data

// Parses actors from a CSV file and stores them in the dictionary
// Parameters: const string& filename - path to CSV file, Dictionary<Actor>& actorTable - dictionary to store actors
// Pre : CSV file should exist and be formatted correctly
// Post: Actors are added to the dictionary
void parseActors(const string& filename, Dictionary<Actor>& actorTable);

// Parses movies from a CSV file and stores them in the dictionary
// Parameters: const string& filename - path to CSV file, Dictionary<Movie>& movieTable - dictionary to store movies
// Pre : CSV file should exist and be formatted correctly
// Post: Movies are added to the dictionary
void parseMovies(const string& filename, Dictionary<Movie>& movieTable);

// Parses actor IDs and movie IDs from a CSV file and stores them in actors/movies list in Actor and Movie respectively
// Parameters: const string& filename - path to CSV file, Dictionary<Actor>& actorTable - dictionary to store actors, Dictionary<Movie>& movieTable - dictionary to store movies
// Pre : CSV file should exist and be formatted correctly, Actor IDs and Movie IDs should correspond to actors and movies in the dictionaries
// Post: Actor IDs are added to actors list in the specified movie, Movie IDs are added to the movies list in the specific actor
void parseCast(const string& filename, Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable);

// Updates the CSV file with the current data from the actor dictionary
// Parameter: const Dictionary<Actor>& actorTable - dictionary of actors
// Pre : actorTable should contain updated actor data
// Post: CSV file is updated with actor data
void updateActorsCSV(const Dictionary<Actor>& actorTable);

// Updates the CSV file with the current data from the movie dictionary
// Parameter: const Dictionary<Movie>& movieTable - dictionary of movies
// Pre : movieTable should contain updated movie data
// Post: CSV file is updated with movie data
void updateMoviesCSV(const Dictionary<Movie>& movieTable);

// Updates the CSV file with the current cast data linking actors and movies
// Parameter: const Dictionary<Movie>& movieTable - dictionary of movies
// Pre : movieTable should contain updated cast data
// Post: CSV file is updated with cast data
void updateCastCSV(const Dictionary<Movie>& movieTable);

// Basic Features

// Displays actors within a specified age range, sorted by age
// Parameter: const Dictionary<Actor>& actorTable - dictionary of actors
// Pre : actorTable should contain actor data
// Post: Actors within the specified age range are displayed, sorted by age
void displayActorsByAge(const Dictionary<Actor>& actorTable);

// Displays movies released within a specific timeframe, sorted by release year
// Parameter: const Dictionary<Movie>& movieTable - dictionary of movies
// Pre : movieTable should contain movie data
// Post: Movies within the specified timeframe are displayed, sorted by release year
void displayMoviesByYear(const Dictionary<Movie>& movieTable);

// Displays all movies an actor has starred in, sorted alphabetically
// Parameters: Dictionary<Actor>& actorTable - dictionary of actors, const Dictionary<Movie>& movieTable - dictionary of movies
// Pre : actorTable and movieTable should contain relevant data
// Post: Movies starred in by the actor are displayed alphabetically
void displayMoviesActorStarredIn(Dictionary<Actor>& actorTable, const Dictionary<Movie>& movieTable);

// Displays all actors in a specific movie, sorted alphabetically
// Parameters: Dictionary<Movie>& movieTable - dictionary of movies, const Dictionary<Actor>& actorTable - dictionary of actors
// Pre : movieTable and actorTable should crontain relevant data
// Post: Actors in the specified movie are displayed alphabetically
void displayActorsInMovie(Dictionary<Movie>& movieTable, const Dictionary<Actor>& actorTable);

// Displays all actors that a specific actor knows based on movie collaborations
// Parameters: Graph& graph - graph representing actor-movie relationships, Dictionary<Actor>& actorTable - dictionary of actors
// Pre : graph and actorTable should be properly initialized
// Post: Known actors are displayed
void displayKnownActors(Graph& graph, Dictionary<Actor>& actorTable);

// Adds a new actor to the dictionary
// Parameter: Dictionary<Actor>& actorTable - dictionary to add the actor
// Pre : None
// Post: A new actor is added to the dictionary if not already present
void addActor(Dictionary<Actor>& actorTable);

// Adds a new movie to the dictionary
// Parameter: Dictionary<Movie>& movieTable - dictionary to add the movie
// Pre : None
// Post: A new movie is added to the dictionary if not already present
void addMovie(Dictionary<Movie>& movieTable);

// Updates an existing actor's information in the dictionary
// Parameter: Dictionary<Actor>& actorTable - dictionary containing the actor
// Pre : actorTable should contain the actor to update
// Post: Actor's information is updated in the dictionary
void updateActor(Dictionary<Actor>& actorTable);

// Updates an existing movie's information in the dictionary
// Parameter: Dictionary<Movie>& movieTable - dictionary containing the movie
// Pre : movieTable should contain the movie to update
// Post: Movie's information is updated in the dictionary
void updateMovie(Dictionary<Movie>& movieTable);

// Adds an actor to a movie's cast and updates both actor and movie lists
// Parameters: Dictionary<Actor>& actorTable - dictionary of actors, Dictionary<Movie>& movieTable - dictionary of movies
// Pre : actorTable and movieTable should contain relevant data
// Post: Actor is added to the movie's cast and vice versa
void addActorToMovie(Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable);

// Advanced Features (Ratings)

// Parses actor ratings from a CSV file and updates the dictionary
// Parameters: const string& filename - path to CSV file, Dictionary<Actor>& actorTable - dictionary to store ratings
// Pre : CSV file should exist and be formatted correctly
// Post: Actor ratings are updated in the dictionary
void parseActorRatings(const string& filename, Dictionary<Actor>& actorTable);

// Parses movie ratings from a CSV file and updates the dictionary
// Parameters: const string& filename - path to CSV file, Dictionary<Movie>& movieTable - dictionary to store ratings
// Pre : CSV file should exist and be formatted correctly
// Post: Movie ratings are updated in the dictionary
void parseMovieRatings(const string& filename, Dictionary<Movie>& movieTable);

// Displays all ratings for a specific actor
// Parameter: Dictionary<Actor>& actorTable - dictionary of actors
// Pre : actorTable should contain rating data
// Post: Actor ratings are displayed
void displayActorRatings(Dictionary<Actor>& actorTable);

// Displays all ratings for a specific movie
// Parameter: Dictionary<Movie>& movieTable - dictionary of movies
// Pre : movieTable should contain rating data
// Post: Movie ratings are displayed
void displayMovieRatings(Dictionary<Movie>& movieTable);

// Adds a rating to a specific actor
// Parameter: Dictionary<Actor>& actorTable - dictionary of actors
// Pre : actorTable should contain the actor to rate
// Post: Rating is added to the actor
void rateActor(Dictionary<Actor>& actorTable);

// Adds a rating to a specific movie
// Parameter: Dictionary<Movie>& movieTable - dictionary of movies
// Pre : movieTable should contain the movie to rate
// Post: Rating is added to the movie
void rateMovie(Dictionary<Movie>& movieTable);

// Updates the CSV file with the current movie ratings
// Parameter: const Dictionary<Movie>& movieTable - dictionary of movies
// Pre : movieTable should contain updated rating data
// Post: CSV file is updated with movie ratings
void updateMovieRatingsCSV(const Dictionary<Movie>& movieTable);

// Updates the CSV file with the current actor ratings
// Parameter: const Dictionary<Actor>& actorTable - dictionary of actors
// Pre : actorTable should contain updated rating data
// Post: CSV file is updated with actor ratings
void updateActorRatingsCSV(const Dictionary<Actor>& actorTable);

// Displays movies with an average rating above a specified minimum
// Parameter: const Dictionary<Movie>& movieTable - dictionary of movies
// Pre : movieTable should contain rating data
// Post: Movies above the specified rating are displayed
void displayMoviesByMinimumRating(const Dictionary<Movie>& movieTable);

// Displays actors with an average rating above a specified minimum
// Parameter: const Dictionary<Actor>& actorTable - dictionary of actors
// Pre : actorTable should contain rating data
// Post: Actors above the specified rating are displayed
void displayActorsByMinimumRating(const Dictionary<Actor>& actorTable);

// Helper Functions

// Retrieves the current year for age calculations
// Pre : None
// Post: Current year is returned
// Returns: int - current year
int getCurrentYear();

// Generates a unique ID for new entries in the dictionary
// Parameter: const Dictionary<T>& dictionary - dictionary to check for existing IDs
// Pre : dictionary should be initialized
// Post: A unique ID is generated
// Returns: int - unique ID
template <typename T>
int generateUniqueID(const Dictionary<T>& dictionary);

// Normalizes a string by removing spaces and converting to lowercase
// Parameter: const string& str - string to normalize
// Pre : None
// Post: Normalized string is returned
// Returns: string - normalized string
string normalizeString(const string& str);

// Finds an actor by name in the dictionary
// Parameters: const Dictionary<Actor>& actorTable - dictionary of actors, const string& name - name of the actor
// Pre : actorTable should contain actor data
// Post: Actor is returned if found
// Returns: Actor* - pointer to the actor or nullptr if not found
Actor* findActorByName(const Dictionary<Actor>& actorTable, const string& name);

// Finds a movie by title in the dictionary
// Parameters: const Dictionary<Movie>& movieTable - dictionary of movies, const string& title - title of the movie
// Pre : movieTable should contain movie data
// Post: Movie is returned if found
// Returns: Movie* - pointer to the movie or nullptr if not found
Movie* findMovieByTitle(const Dictionary<Movie>& movieTable, const string& title);

int main()
{
	Dictionary<Actor> actorTable;
	Dictionary<Movie> movieTable;
	int choice = -1;

	parseActors("data/actors.csv", actorTable);
	parseMovies("data/movies.csv", movieTable);
	parseCast("data/cast.csv", actorTable, movieTable);
	parseActorRatings("data/actorRatings.csv", actorTable);
	parseMovieRatings("data/movieRatings.csv", movieTable);
	Graph graph;
	graph.buildGraph(actorTable);

	while (true)
	{
		// Prompt for role
		//string role;
		//cout << "Log in as Admin or User (0 to exit): ";
		//cin >> role;
		//cout << endl;

		//// Convert role to lowercase
		//transform(role.begin(), role.end(), role.begin(), ::tolower);

		string role;
		cout << "Log in as Admin or User (0 to exit): ";
		cin >> ws;  // Eat up any leading whitespace
		getline(cin, role);  // Read the entire line (in case user typed spaces)
		cout << endl;

		// Normalize the input (removes spaces and converts to lowercase)
		role = normalizeString(role);

		// If user types "exit", break out of the outer loop and end the program
		if (role == "0")
		{
			cout << "Exiting the program...\n";

			// Update CSVs on logout
			updateMoviesCSV(movieTable);
			updateActorsCSV(actorTable);
			updateCastCSV(movieTable);
			updateMovieRatingsCSV(movieTable);
			updateActorRatingsCSV(actorTable);
			break;
		}

		// --------------------- ADMIN SECTION ---------------------
		if (role == "admin")
		{
			while (true)
			{
				int choice = -1;
				// Display admin menu
				cout << "--------------- ADMIN MENU ---------------" << endl;
				cout << "1.  Add actor" << endl;
				cout << "2.  Add movie" << endl;
				cout << "3.  Add actor to movie" << endl;
				cout << "4.  Update actor" << endl;
				cout << "5.  Update movie" << endl;
				cout << "0.  Log out" << endl;
				cout << "Enter your choice: ";
				cin >> choice;

				// Handle invalid input
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nInvalid choice. Please try again.\n\n";
					continue;
				}

				cout << endl;

				if (choice == 0)  // Log out
				{
					cout << "Logging out...\n\n";

					break; // Breaks out of admin loop => back to login prompt
				}
				else if (choice == 1)
				{
					cout << "------------ ADD ACTOR ------------" << endl;
					addActor(actorTable);
				}
				else if (choice == 2)
				{
					cout << "------------ ADD MOVIE ------------" << endl;
					addMovie(movieTable);
				}
				else if (choice == 3)
				{
					cout << "------- ADD ACTOR TO MOVIE -------" << endl;
					addActorToMovie(actorTable, movieTable);
				}
				else if (choice == 4)
				{
					cout << "----------- UPDATE ACTOR -----------" << endl;
					updateActor(actorTable);
				}
				else if (choice == 5)
				{
					cout << "----------- UPDATE MOVIE -----------" << endl;
					updateMovie(movieTable);
				}
				else
				{
					cout << "Invalid choice. Please try again." << endl;
				}
				cout << endl;
			}
		}
		// --------------------- USER SECTION ---------------------
		else if (role == "user")
		{
			while (true)
			{
				int choice = -1;
				// Display user menu
				cout << "--------------- USER MENU ---------------" << endl;
				cout << "1.  Display actors within a specified age range" << endl;
				cout << "2.  Display movies released within the past 3 years" << endl;
				cout << "3.  Display movies an actor has starred in" << endl;
				cout << "4.  Display actors in a particular movie" << endl;
				cout << "5.  Display a list of all actors that a particular actor knows" << endl;
				cout << "6.  Display all ratings for an actor" << endl;
				cout << "7.  Display all ratings for a movie" << endl;
				cout << "8.  Rate an actor" << endl;
				cout << "9.  Rate a movie" << endl;
				cout << "10. Display actors above a minimum rating" << endl;
				cout << "11. Display movies above a minimum rating" << endl;
				cout << "0.  Log out" << endl;
				cout << "Enter your choice: ";
				cin >> choice;

				// Handle invalid input
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nInvalid choice. Please try again.\n\n";
					continue;
				}

				cout << endl;

				if (choice == 0) // Log out
				{
					cout << "Logging out...\n\n";

					break; // Breaks out of user loop => back to login prompt
				}
				else if (choice == 1)
				{
					cout << "----------- DISPLAY ACTOR IN AGE RANGE -----------" << endl;
					displayActorsByAge(actorTable);
				}
				else if (choice == 2)
				{
					cout << "----------- DISPLAY MOVIES MADE WITHIN PAST 3 YEARS -----------" << endl;
					displayMoviesByYear(movieTable);
				}
				else if (choice == 3)
				{
					cout << "----------- DISPLAY MOVIES BY ACTOR -----------" << endl;
					displayMoviesActorStarredIn(actorTable, movieTable);
				}
				else if (choice == 4)
				{
					cout << "----------- DISPLAY ACTORS IN A MOVIE -----------" << endl;
					displayActorsInMovie(movieTable, actorTable);
				}
				else if (choice == 5)
				{
					cout << "----------- DISPLAY KNOWN ACTORS -----------" << endl;
					displayKnownActors(graph, actorTable);
				}
				else if (choice == 6)
				{
					cout << "------ DISPLAY ACTOR RATINGS ------" << endl;
					displayActorRatings(actorTable);
				}
				else if (choice == 7)
				{
					cout << "------ DISPLAY MOVIE RATINGS ------" << endl;
					displayMovieRatings(movieTable);
				}
				else if (choice == 8)
				{
					cout << "----------- RATE ACTOR -----------" << endl;
					rateActor(actorTable);
				}
				else if (choice == 9)
				{
					cout << "----------- RATE MOVIE -----------" << endl;
					rateMovie(movieTable);
				}
				else if (choice == 10)
				{
					cout << "----------- DISPLAY ACTORS OF A MINIMUM RATING -----------" << endl;
					displayActorsByMinimumRating(actorTable);
				}
				else if (choice == 11)
				{
					cout << "----------- DISPLAY MOVIES OF A MINIMUM RATING -----------" << endl;
					displayMoviesByMinimumRating(movieTable);
				}
				else
				{
					cout << "Invalid choice. Please try again." << endl;
				}
				cout << endl;
			}
		}
		else
		{
			cout << "Invalid role entered. Please try again.\n\n";
		}
	}

	return 0;
}

// a
void addActor(Dictionary<Actor>& actorTable) {
	int birthYear;
	string name;

	// Generate a unique ID
	int id = generateUniqueID(actorTable);
	cout << "Generated actor ID: " << id << endl;

	// Input actor name
	cout << "Enter actor name (or 0 to exit): ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, name);

	if (name == "0") return;

	// Input actor birth year
	while (true) {
		cout << "Enter actor birth year (or 0 to exit): ";
		cin >> birthYear;

		if (cin.fail()) {
			// Handle invalid input
			cin.clear();               // Clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << endl << "Invalid input. Please enter a valid birth year." << endl << endl;
			continue;
		}

		if (birthYear == 0) return;

		if (birthYear >= 1700 && birthYear <= 2025) {
			break; // Valid year
		}
		else {
			cout << endl << "Please enter a birth year between 1700 and 2025." << endl << endl;
		}
	}

	// Create actor
	Actor* actor = new Actor(id, name, birthYear);

	// Add actor to dictionary
	bool success = actorTable.add(id, actor);

	if (!success) {
		cout << "Failed to add actor." << endl;
		delete actor; // Free memory
		return;
	}

	cout << endl << "Actor added successfully." << endl;
}

// b
void addMovie(Dictionary<Movie>& movieTable) {
	int year;
	string title, plot;

	// Generate a unique ID
	int id = generateUniqueID(movieTable);
	cout << "Generated movie ID: " << id << endl;

	// Input movie title
	cout << "Enter movie title (or 0 to exit): ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, title);
	if (title == "0") return;

	// Input movie plot
	cout << "Enter movie plot (or 0 to exit): ";
	getline(cin, plot);
	if (plot == "0") return;

	// Input movie release year
	while (true) {
		cout << "Enter movie release year (or 0 to exit): ";
		cin >> year;

		if (cin.fail()) {
			// Handle invalid input
			cin.clear(); // Clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << endl << "Invalid input. Please enter a valid release year." << endl << endl;
			continue;
		}

		if (year == 0) return;

		if (year >= 1800 && year <= 2025) {
			break; // Valid year
		}
		else {
			cout << endl << "Please enter a release year between 1800 and 2025." << endl << endl;
		}
	}

	// Add the movie to the dictionary
	Movie* movie = new Movie(id, title, plot, year);
	if (movieTable.add(id, movie)) {
		cout << endl << "Movie added successfully." << endl;
	}
	else {
		cout << "Movie with this ID already exists." << endl;
		delete movie; // Clean up memory if adding fails
	}
}

// c
void addActorToMovie(Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable) {
	string movieTitle, actorName;
	Movie* movie;
	Actor* actor;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	
	while (true) {
		// Get movie
		cout << "\nEnter the title of the movie you want to add an actor to (or enter 0 to exit): ";
		getline(cin, movieTitle);
		if (movieTitle == "0") return;

		// Get the movie from the movie table
		movie = findMovieByTitle(movieTable, movieTitle);
		if (movie == nullptr) {
			cout << endl << "Movie not found. Please try again." << endl;
			continue; // Loop to get movie
		}

		// Get actor
		cout << endl;
		while (true) {
			cout << "Enter the name of the actor you want to add (or enter 0 to exit): ";
			getline(cin, actorName);
			if (actorName == "0") return;

			actor = findActorByName(actorTable, actorName);
			if (actor == nullptr) {
				cout << endl << "Actor not found. Please try again." << endl << endl;
				continue; // Loop to get actor
			}
			break;
		}

		// Add the actor to the movie and vice versa
		actor->addMovie(movie->getId());
		movie->addActor(actor->getId());

		// Success message
		cout << endl << "Actor " << actor->getName() << " has been added to the movie " << movie->getTitle() << "." << endl;
		return;
	}
}

// d
void updateActor(Dictionary<Actor>& actorTable) {
	string name;
	int choice = -1;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true) {
		name = "-1";
		cout << endl;

		// Get actor
		cout << "Select actor to update (Enter actor name, or 0 to exit): ";
		getline(cin, name);
		if (name == "0") return;

		cout << endl;

		Actor* actor = findActorByName(actorTable, name);

		if (actor != nullptr) {
			choice = -1;

			while (choice != 0) {
				// Select actor attribute to edit
				actor->print();
				cout << "1. Name" << endl << "2. Birth Year" << endl << "0. Return to actor select" << endl << endl;
				cout << "Select which to update: ";
				cin >> choice;

				if (cin.fail()) {
					// Handle invalid input
					cin.clear();               // Clear error flag
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Invalid choice. Please try again." << endl << endl;
					choice = -1;
					continue;
				}

				if (choice == 1) {
					// Edit name
					string newName;
					cout << endl << "Enter new name: ";
					cin.ignore();
					getline(cin, newName);

					actor->setName(newName);

					cout << endl;
				}
				else if (choice == 2) {
					// Edit birth year
					int newYear;
					while (true) {
						cout << endl << "Enter new birth year: ";
						cin >> newYear;

						if (cin.fail()) {
							// Handle invalid input
							cin.clear();               // Clear error flag
							cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
							cout << endl << "Invalid input. Please enter a valid birth year." << endl;
							continue;
						}
						if (newYear >= 1700 && newYear <= 2025) {
							break; // Valid year
						}
						else {
							cout << endl << "Please enter a birth year between 1700 and 2025." << endl;
						}
					}

					actor->setBirthYear(newYear);

					cout << endl;
				}
				else if (choice == 0) {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				else {
					cout << endl << "Invalid choice. Please try again." << endl << endl;
				}
			}
		}
		else {
			cout << "Actor not found. Please try again." << endl;
		}
	}
}

// d
void updateMovie(Dictionary<Movie>& movieTable) {
	string name;
	int choice = -1;
	Movie* movie;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true) {
		name = "-1";
		cout << endl;

		// Get movie
		cout << "Select movie to update (Enter movie title, or 0 to exit): ";
		getline(cin, name);
		if (name == "0") return;

		cout << endl;

		movie = findMovieByTitle(movieTable, name);

		if (movie != nullptr) {
			choice = -1;

			while (choice != 0) {
				// Select movie attribute to edit
				movie->printFullDetails();
				cout << "1. Title" << endl << "2. Plot" << endl << "3. Release Year" << endl << "0. Return to movie select" << endl << endl;
				cout << "Select which to update: ";
				cin >> choice;

				if (cin.fail()) {
					// Handle invalid input
					cin.clear();               // Clear error flag
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Invalid choice. Please try again." << endl << endl;
					choice = -1;
					continue;
				}

				if (choice == 1) {
					// Edit title
					string newTitle;
					cout << endl << "Enter new title: ";
					cin.ignore();
					getline(cin, newTitle);

					movie->setTitle(newTitle);

					cout << endl;
				}
				else if (choice == 2) {
					// Edit plot
					string newPlot;
					cout << endl << "Enter new plot: ";
					cin.ignore();
					getline(cin, newPlot);

					movie->setPlot(newPlot);

					cout << endl;
				}
				else if (choice == 3) {
					// Edit release year
					int newYear;
					while (true) {
						cout << endl << "Enter new release year: ";
						cin >> newYear;

						if (cin.fail()) {
							// Handle invalid input
							cin.clear();               // Clear error flag
							cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
							cout << endl << "Invalid input. Please enter a valid release year." << endl;
							continue;
						}
						if (newYear >= 1800 && newYear <= 2025) {
							break; // Valid year
						}
						else {
							cout << endl << "Please enter a release year between 1800 and 2025." << endl;
						}
					}

					movie->setYear(newYear);

					cout << endl;
				}
				else if (choice == 0) {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				else {
					cout << endl << "Invalid choice. Please try again." << endl << endl;
				}
			}
		}
		else {
			cout << "Movie not found. Please try again." << endl;
		}
	}
}

// e) merge sort
void displayActorsByAge(const Dictionary<Actor>& actorTable) {
	while (true) {
		int x, y;

		while (true) {
			// Get min age
			cout << "Enter the minimum age (0 to exit): ";
			cin >> x;

			if (cin.fail()) { // Invalid input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a valid integer for minimum age." << endl;
				continue; // Loop to prompt again
			}

			if (x == 0) {
				return;
			}

			// Get max age
			cout << "Enter the maximum age (0 to exit): ";
			cin >> y;

			if (cin.fail()) { // Invalid input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a valid integer for maximum age." << endl;
				continue; // Loop to prompt again
			}

			if (y == 0) {
				return;
			}

			// If max age less than min age
			if (y <= x) {
				cout << "Invalid age range. Maximum age must be greater than minimum age. Please try again." << endl;
				continue;
			}

			break;
		}

		List<KeyValue<int, Actor>> actors = actorTable.getAllItemsWithKeys(); // Get all actors
		int count = actors.getLength(); // Number of actors

		// Dynamically allocate the array
		Actor** actorsArr = new Actor * [count];
		int index = 0;

		for (int i = 0; i < count; i++) {
			Actor* actor = actors.get(i).value; // Retrieve actor
			int age = getCurrentYear() - actor->getBirthYear(); // Find actor age
			// If actor age is within the range, add actor to array
			if (age >= x && age <= y) {
				actorsArr[index++] = actor;
			}
		}

		if (index == 0) {
			cout << endl << "No actors found within the age range of " << x << " to " << y << "." << endl;
		}
		else {
			// Sort actors by age using the Actor class's static method
			Actor::mergeSortByAge(actorsArr, 0, index - 1, getCurrentYear());

			// Display sorted actors
			cout << endl << left << setw(35) << "Actor Name"
				<< setw(15) << ("Age (" + to_string(x) + " - " + to_string(y) + ")") << endl;
			cout << string(50, '-') << endl; // Adds a separator line
			for (int i = 0; i < index; i++) {
				cout << left << setw(35) << actorsArr[i]->getName()
					<< right << setw(2) << (getCurrentYear() - actorsArr[i]->getBirthYear())
					<< " Years Old" << endl;
			}
		}

		delete[] actorsArr; // Free dynamically allocated memory
		cout << endl;
	}
}

// f) merge sort
void displayMoviesByYear(const Dictionary<Movie>& movieTable) {
	while (true) {
		int currentYear;

		while (true) {
			// Get user input year
			cout << "Enter year (0 to exit): ";
			cin >> currentYear;

			if (cin.fail()) { // Invalid input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a valid year." << endl;
				continue; // Loop to prompt again
			}

			if (currentYear == 0) {
				return;
			}

			// If user input year is later than current year
			if (currentYear > getCurrentYear()) {
				cout << "Invalid year. The year cannot be in the future. Please try again." << endl;
				continue;
			}

			break;
		}

		List<KeyValue<int, Movie>> movies = movieTable.getAllItemsWithKeys(); // Get all movies
		int count = movies.getLength(); // Number of movies

		// Dynamically allocate the array
		Movie** moviesArr = new Movie * [count];
		int index = 0;

		for (int i = 0; i < count; i++) {
			Movie* movie = movies.get(i).value; // Retrieve movie
			// If movie is released within 3 years before user input year, add to array
			if (movie->getYear() >= (currentYear - 3) && movie->getYear() <= currentYear) {
				moviesArr[index++] = movie;
			}
		}

		if (index > 0) {
			// Sort movies by year using the Movie class's static method
			Movie::mergeSortByYear(moviesArr, 0, index - 1);

			// Display sorted movies
			cout << endl;
			cout << left << setw(100) << "Movie Title" << setw(10) << "Year" << endl;
			cout << string(110, '-') << endl; // Adjusted line separator length
			for (int i = 0; i < index; i++) {
				cout << left << setw(100) << moviesArr[i]->getTitle()
					<< setw(10) << moviesArr[i]->getYear() << endl;
			}
		}
		else {
			cout << endl << "No movies found within the past 3 years." << endl;
		}

		delete[] moviesArr; // Free dynamically allocated memory
		cout << endl;
	}
}

// g) insertion sort
void displayMoviesActorStarredIn(Dictionary<Actor>& actorTable, const Dictionary<Movie>& movieTable) {
	string name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true) {
		name = "-1";
		
		// Get actor
		cout << "Select actor (Enter actor name, or 0 to exit): ";
		getline(cin, name);
		if (name == "0") return;

		cout << endl;

		Actor* actor = findActorByName(actorTable, name);

		if (!actor) {
			cout << "Actor not found." << endl << endl;
			continue;
		}

		// Get movies from actor
		const List<int>& movieIDs = actor->getMovies(); // Retrieve all movie IDS
		int movieCount = movieIDs.getLength(); // Number of movies
		if (movieCount == 0) {
			cout << "No movies found for \"" << actor->getName() << "\"." << endl << endl;
			continue;
		}
		string* movieTitles = new string[movieCount]; // Dynamically allocate array
		int index = 0;

		// Collect movie titles
		for (int i = 0; i < movieCount; i++) {
			Movie* movie = movieTable.get(movieIDs.get(i)); // Get movie from dictionary
			// If movie exists, add title to array
			if (movie) {
				movieTitles[index++] = movie->getTitle();
			}
		}

		// Sort movie titles alphabetically using the Movie class's static method
		Movie::insertionSortTitles(movieTitles, index);

		// Display sorted movie titles
		cout << "Movies starred in by " << actor->getName() << " (Alphabetical Order):" << endl;
		for (int i = 0; i < index; i++) {
			cout << "- " << movieTitles[i] << endl;
		}
		cout << endl;

		delete[] movieTitles; // Free dynamically allocated memory
	}
}

// h) insertion sort
void displayActorsInMovie(Dictionary<Movie>& movieTable, const Dictionary<Actor>& actorTable) {
	string name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true) {
		name = "-1";

		// Get movie
		cout << "Select movie (Enter movie title, or 0 to exit): ";
		getline(cin, name);
		if (name == "0") return;

		cout << endl;

		Movie* movie = findMovieByTitle(movieTable, name);

		if (!movie) {
			cout << "Movie not found." << endl << endl;
			continue;
		}

		// Get actors from movie
		const List<int>& actorIDs = movie->getActors(); // Retrieve all actor IDs
		int actorCount = actorIDs.getLength(); // Number of actors
		if (actorCount == 0) {
			cout << "No actors found in the movie \"" << movie->getTitle() << "\"." << endl << endl;
			continue;
		}
		string* actorNames = new string[actorCount]; // Dynamically allocate array
		int index = 0;

		// Collect actor names
		for (int i = 0; i < actorCount; i++) {
			Actor* actor = actorTable.get(actorIDs.get(i)); // Get actor from dictionary
			// If actor exists, add name to array
			if (actor) {
				actorNames[index++] = actor->getName();
			}
		}

		// Sort actor names alphabetically using the Actor class's static method
		Actor::insertionSortNames(actorNames, index);

		// Display sorted actor names
		cout << "Actors in the movie \"" << movie->getTitle() << "\" (Alphabetical Order):" << endl;
		for (int i = 0; i < index; i++) {
			cout << "- " << actorNames[i] << endl;
		}
		cout << endl;
		delete[] actorNames; // Free dynamically allocated memory
	}
}

// i) 
void displayKnownActors(Graph& graph, Dictionary<Actor>& actorTable) {
	string name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer

	while (true) {
		// Get actor
		cout << "Select actor (Enter actor name, or 0 to exit): ";
		getline(cin, name);
		if (name == "0") return;
		cout << endl;

		Actor* actor = findActorByName(actorTable, name);

		if (!actor) {
			cout << "Actor not found." << endl << endl ;
			continue;
		}

		// Use the Graph class to find and display co-actors
		graph.findCoActors(actor->getId(), actorTable);
	}
}


// ADVANCED

// Display ratings for a selected actor
void displayActorRatings(Dictionary<Actor>& actorTable) {
	string name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

	while (true) {
		name = "-1";
		cout << "Select actor (Enter actor name, or 0 to exit): ";

		getline(cin, name); // Get actor name from user
		if (name == "0") return; // Exit if user inputs 0

		cout << endl;

		Actor* actor = findActorByName(actorTable, name); // Find actor by name

		if (actor != nullptr) {
			cout << actor->getName() << endl; // Display actor's name
			actor->displayRatings(); // Display actor's ratings
			cout << endl;
		}
		else {
			cout << "Actor not found. Please try again." << endl << endl; // Handle actor not found
		}
	}
}

// Display ratings for a selected movie
void displayMovieRatings(Dictionary<Movie>& movieTable) {
	string name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

	while (true) {
		name = "-1";
		cout << "Select movie (Enter movie title, or 0 to exit): ";
		getline(cin, name); // Get movie title from user
		if (name == "0") return; // Exit if user inputs 0

		cout << endl;

		Movie* movie = findMovieByTitle(movieTable, name); // Find movie by title

		if (movie != nullptr) {
			cout << movie->getTitle() << endl; // Display movie's title
			movie->displayRatings(); // Display movie's ratings
			cout << endl << endl;
		}
		else {
			cout << "Movie not found. Please try again." << endl << endl; // Handle movie not found
		}
	}
}

// Add a rating to a selected actor
void rateActor(Dictionary<Actor>& actorTable) {
	string name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

	while (true) {
		name = "-1";
		cout << "Select actor (Enter actor name, or 0 to exit): ";
		getline(cin, name); // Get actor name from user
		if (name == "0") return; // Exit if user inputs 0

		cout << endl;

		Actor* actor = findActorByName(actorTable, name); // Find actor by name

		if (actor != nullptr) {
			float rating;
			while (true) {
				rating = -1;
				cout << "Enter a rating between 1-5 (or 0 to return to actor select): ";
				cin >> rating; // Get rating from user

				if (cin.fail()) {
					// Handle invalid input
					cin.clear();               // Clear error flag
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Invalid rating. Please try again." << endl << endl;
					continue;
				}

				if (rating == 0) break; // Return to actor select if 0

				if (rating < 1 || rating > 5) {
					cout << endl << "Invalid rating. Please enter a number between 1-5." << endl << endl;
					continue;
				}

				actor->addRating(rating); // Add rating to actor
				return;
			}
		}
		else {
			cout << "Actor not found. Please try again." << endl << endl ; // Handle actor not found
		}
	}
}

// Add a rating to a selected movie
void rateMovie(Dictionary<Movie>& movieTable) {
	string name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

	while (true) {
		name = "-1";
		cout << "Select movie (Enter movie title, or 0 to exit): ";
		getline(cin, name); // Get movie title from user
		if (name == "0") return; // Exit if user inputs 0

		cout << endl;

		Movie* movie = findMovieByTitle(movieTable, name); // Find movie by title

		if (movie != nullptr) {
			float rating;
			while (true) {
				rating = -1;
				cout << "Enter a rating between 1-5 (or 0 to return to movie select): ";
				cin >> rating; // Get rating from user

				if (cin.fail()) {
					// Handle invalid input
					cin.clear();               // Clear error flag
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl << "Invalid rating. Please try again." << endl << endl;
					continue;
				}

				if (rating == 0) break; // Return to movie select if 0

				if (rating < 1 || rating > 5) {
					cout << endl << "Invalid rating. Please enter a number between 1-5." << endl << endl;
					continue;
				}

				movie->addRating(rating); // Add rating to movie
				return;
			}
		}
		else {
			cout << "Movie not found. Please try again." << endl << endl; // Handle movie not found
		}
	}
}

// movies by minimum rating
void displayMoviesByMinimumRating(const Dictionary<Movie>& movieTable) {
	while (true) {
		float minRating;

		// Input validation for minimum rating
		while (true) {
			cout << "Enter the minimum rating (1-5, or 0 to exit): ";
			cin >> minRating;

			if (cin.fail() || minRating < 0 || minRating > 5) { // Invalid input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Invalid rating. Please enter a number between 1 and 5, or 0 to exit." << endl << endl;
				continue; // Loop to prompt again
			}

			if (minRating == 0) {
				return; // Exit the function
			}

			break; // Exit the loop if input is valid
		}

		// Retrieve all movies from the dictionary
		List<KeyValue<int, Movie>> movies = movieTable.getAllItemsWithKeys();
		int count = movies.getLength();

		// Collect movies with a rating greater than or equal to the minimum rating
		Movie** movieArr = new Movie * [count];
		int index = 0;

		for (int i = 0; i < count; i++) {
			Movie* movie = movies.get(i).value;
			// If movie rating is above min rating, add to array
			if (movie->getAverageRating() >= minRating) {
				movieArr[index++] = movie;
			}
		}

		if (index > 0) {
			// Sort movies by rating using the Movie class's static method
			Movie::sortMoviesByRatingDescending(movieArr, 0, index - 1);

			// Display the movies
			cout << endl << left << setw(35) << "Movie Title" << setw(10) << "Rating" << endl;
			cout << string(45, '-') << endl;

			for (int i = 0; i < index; i++) {
				cout << left << setw(35) << movieArr[i]->getTitle()
					<< right << setw(4) << fixed << setprecision(1) << movieArr[i]->getAverageRating() << endl;
			}
		}
		else {
			cout << "No movies found with a rating of at least " << minRating << "." << endl;
		}

		delete[] movieArr; // Free the dynamically allocated array
		cout << endl;
	}
}

// Display actors by minimum rating
void displayActorsByMinimumRating(const Dictionary<Actor>& actorTable) {
	while (true) {
		float minRating;

		// Input validation for minimum rating
		while (true) {
			cout << "Enter the minimum rating (1-5, or 0 to exit): ";
			cin >> minRating;

			if (cin.fail() || minRating < 0 || minRating > 5) {// Invalid input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl << "Invalid rating. Please enter a number between 1 and 5, or 0 to exit." << endl << endl;
				continue; // Loop to prompt again
			}

			if (minRating == 0) {
				return; // Exit the function
			}

			break; // Exit the loop if input is valid
		}

		// Retrieve all actors from the dictionary
		List<KeyValue<int, Actor>> actors = actorTable.getAllItemsWithKeys();
		int count = actors.getLength();

		// Collect actors with a rating greater than or equal to the minimum rating
		Actor** actorArr = new Actor * [count];
		int index = 0;

		for (int i = 0; i < count; i++) {
			Actor* actor = actors.get(i).value;
			// If actor rating above min rating, add to array
			if (actor->getAverageRating() >= minRating) {
				actorArr[index++] = actor;
			}
		}

		if (index > 1) {
			// Sort actors by rating using Merge Sort
			Actor::sortActorsByRatingDescending(actorArr, 0, index - 1);
		}

		if (index > 0) {
			// Display the sorted actors
			cout << endl << left << setw(25) << "Actor Name" << setw(10) << "Rating" << endl;
			cout << string(35, '-') << endl;

			for (int i = 0; i < index; i++) {
				cout << left << setw(25) << actorArr[i]->getName()
					<< right << setw(4) << fixed << setprecision(1) << actorArr[i]->getAverageRating() << endl;
			}
		}
		else {
			cout << "No actors found with a rating of at least " << minRating << "." << endl;
		}

		delete[] actorArr; // Free the dynamically allocated array
		cout << endl;
	}
}


// HELPER FUNCTIONS

int getCurrentYear() { // current year to calc how old the actor is
	time_t t = time(nullptr);
	tm now;
	localtime_s(&now, &t);
	return now.tm_year + 1900;
}

template <typename T>
int generateUniqueID(const Dictionary<T>& dictionary) {
	random_device rd;  // Seed for random number generation
	mt19937 gen(rd()); // Mersenne Twister random number generator
	uniform_int_distribution<> dist(1, 10000); // Random IDs between 1 and 10,000

	int id;
	do {
		id = dist(gen); // Generate a random ID
	} while (dictionary.get(id) != nullptr); // Check if ID already exists in the dictionary

	return id;
}

string normalizeString(const string& str) {
	if (str.empty()) {
		return ""; // Handle empty string safely
	}
	string result = str;
	result.erase(remove(result.begin(), result.end(), ' '), result.end());
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

Actor* findActorByName(const Dictionary<Actor>& actorTable, const string& name) {
	List<KeyValue<int, Actor>> actors = actorTable.getAllItemsWithKeys();

	// Normalize the search name
	string normalizedSearchName = normalizeString(name);

	// Allocate dynamic array for matching actors
	Actor** matchingActors = new Actor * [actors.getLength()];
	int matchCount = 0;

	// Collect all matching actors
	for (int i = 0; i < actors.getLength(); ++i) {
		if (normalizeString(actors.get(i).value->getName()) == normalizedSearchName) {
			matchingActors[matchCount++] = actors.get(i).value;
		}
	}

	if (matchCount == 0) {
		delete[] matchingActors;  // No matches, clean up memory
		return nullptr;
	}
	else if (matchCount == 1) {
		Actor* selectedActor = matchingActors[0];
		delete[] matchingActors;  // Only one match, clean up memory
		return selectedActor;
	}
	else {
		// Multiple matches found
		cout << "Multiple actors found with the name \"" << name << "\". Please select one:\n";
		for (int i = 0; i < matchCount; ++i) {
			cout << i + 1 << ". ";
			matchingActors[i]->print();
		}

		int choice;
		while (true) {
			// Select actor from matches
			cout << "Enter the number of the correct actor: ";
			cin >> choice;

			if (cin.fail() || choice < 1 || choice > matchCount) { // Invalid input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid choice. Please select a valid number.\n";
				continue;
			}

			Actor* selectedActor = matchingActors[choice - 1];
			delete[] matchingActors;  // Clean up memory after selection
			return selectedActor;
		}
	}
}

Movie* findMovieByTitle(const Dictionary<Movie>& movieTable, const string& title) {
	List<KeyValue<int, Movie>> movies = movieTable.getAllItemsWithKeys();

	// Normalize the search title
	string normalizedSearchTitle = normalizeString(title);

	// Allocate dynamic array for matching movies
	Movie** matchingMovies = new Movie * [movies.getLength()];
	int matchCount = 0;

	// Collect all matching movies
	for (int i = 0; i < movies.getLength(); ++i) {
		if (normalizeString(movies.get(i).value->getTitle()) == normalizedSearchTitle) {
			matchingMovies[matchCount++] = movies.get(i).value;
		}
	}

	if (matchCount == 0) {
		delete[] matchingMovies;  // No matches, clean up memory
		return nullptr;
	}
	else if (matchCount == 1) {
		Movie* selectedMovie = matchingMovies[0];
		delete[] matchingMovies;  // Only one match, clean up memory
		return selectedMovie;
	}
	else {
		// Multiple matches found
		cout << "Multiple movies found with the title \"" << title << "\". Please select one:\n";
		for (int i = 0; i < matchCount; ++i) {
			cout << i + 1 << ". ";
			matchingMovies[i]->print();
		}

		int choice;
		while (true) {
			// Select movie from matches
			cout << "Enter the number of the correct movie: ";
			cin >> choice;

			if (cin.fail() || choice < 1 || choice > matchCount) { // Invalid input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid choice. Please select a valid number.\n";
				continue;
			}

			Movie* selectedMovie = matchingMovies[choice - 1];
			delete[] matchingMovies;  // Clean up memory after selection
			return selectedMovie;
		}
	}
}

// PARSING & UPDATING CSV

// Parse actors and store them in the dictionary
void parseActors(const string& filename, Dictionary<Actor>& actorTable) {
	ifstream file(filename);
	string line;
	getline(file, line); // Skip the header line

	while (getline(file, line)) {
		stringstream ss(line);
		int id, birthYear;
		string name;

		// Read the ID
		ss >> id;
		ss.ignore(); // Skip the comma

		// Read the name, handling quotes
		if (ss.peek() == '"') {
			ss.ignore(); // Skip the opening quote
			getline(ss, name, '"'); // Read until the closing quote
			ss.ignore(); // Skip the comma after the closing quote
		}
		else {
			getline(ss, name, ','); // Read until the comma
		}

		// Read the birth year
		ss >> birthYear;

		// Create and add the actor using a smart pointer
		Actor* actor = new Actor(id, name, birthYear);
		actorTable.add(id, actor);
	}
	file.close();
}

// Parse movies and store them in the dictionary
void parseMovies(const string& filename, Dictionary<Movie>& movieTable) {
	ifstream file(filename);
	string line;
	getline(file, line); // Skip the header line

	while (getline(file, line)) {
		stringstream ss(line);
		int id, year;
		string title, plot;

		// Read the ID
		ss >> id;
		ss.ignore(); // Skip the comma

		// Read the title, handling quotes
		if (ss.peek() == '"') {
			ss.ignore(); // Skip the opening quote
			getline(ss, title, '"'); // Read until the closing quote
			ss.ignore(); // Skip the comma after the closing quote
		}
		else {
			getline(ss, title, ','); // Read until the comma
		}

		// Read the plot, handling quotes
		if (ss.peek() == '"') {
			ss.ignore(); // Skip the opening quote
			getline(ss, plot, '"'); // Read until the closing quote
			ss.ignore(); // Skip the comma after the closing quote
		}
		else {
			getline(ss, plot, ','); // Read until the comma
		}

		// Read the year
		ss >> year;

		// Create and add the movie using a smart pointer
		Movie* movie = new Movie(id, title, plot, year);
		movieTable.add(id, movie);
	}
	file.close();
}

// Parse cast and establish relationships
void parseCast(const string& filename, Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable) {
	ifstream file(filename); // Open the file
	string line;
	while (getline(file, line)) { // Read each line from the file
		stringstream ss(line); // Use stringstream to parse the line
		int actorID, movieID;
		ss >> actorID; // Extract actor ID
		ss.ignore(); // Ignore delimiter
		ss >> movieID; // Extract movie ID

		Actor* actor = actorTable.get(actorID); // Retrieve actor by ID
		Movie* movie = movieTable.get(movieID); // Retrieve movie by ID

		if (actor && movie) {
			// Add movieID to the actor and actorID to the movie
			actor->addMovie(movieID);
			movie->addActor(actorID);
		}
	}
	file.close(); // Close the file
}

// Parse actor ratings
void parseActorRatings(const string& filename, Dictionary<Actor>& actorTable) {
	ifstream file(filename); // Open the file
	string line;
	while (getline(file, line)) { // Read each line from the file
		stringstream ss(line); // Use stringstream to parse the line
		int actorID;
		float rating;
		ss >> actorID; // Extract actor ID
		ss.ignore(); // Ignore delimiter
		ss >> rating; // Extract rating

		Actor* actor = actorTable.get(actorID); // Retrieve actor by ID

		if (actor) {
			actor->addRating(rating); // Add rating to actor
		}
	}
	file.close(); // Close the file
}

// Parse movie ratings
void parseMovieRatings(const string& filename, Dictionary<Movie>& movieTable) {
	ifstream file(filename); // Open the file
	string line;
	while (getline(file, line)) { // Read each line from the file
		stringstream ss(line); // Use stringstream to parse the line
		int movieID;
		float rating;
		ss >> movieID; // Extract movie ID
		ss.ignore(); // Ignore delimiter
		ss >> rating; // Extract rating

		Movie* movie = movieTable.get(movieID); // Retrieve movie by ID

		if (movie) {
			movie->addRating(rating); // Add rating to movie
		}
	}
	file.close(); // Close the file
}

void updateActorsCSV(const Dictionary<Actor>& actorTable) {
	ofstream file("data/actors.csv");  // Open the file in overwrite mode
	if (file.is_open()) {
		// Write the header (optional, if your CSV needs one)
		file << "id,name,birth\n";

		// Get all the actors with their keys (actor IDs)
		List<KeyValue<int, Actor>> allActors = actorTable.getAllItemsWithKeys();

		// Iterate over all actors and write their details to the CSV
		for (int i = 0; i < allActors.getLength(); ++i) {
			KeyValue<int, Actor> pair = allActors.get(i);  // Get each key-value pair
			int actorID = pair.key;  // Actor ID (key)
			Actor* actor = pair.value;  // Actor object (value)

			// Write the actor details to the CSV
			file << actorID << ","  // Actor ID
				<< "\"" << actor->getName() << "\"" << ","  // Actor name (quoted)
				<< actor->getBirthYear() << "\n";  // Actor birth year
		}

		file.close();
	}
	else {
		cerr << "Failed to open actors.csv for writing.\n";
	}
}

void updateMoviesCSV(const Dictionary<Movie>& movieTable) {
	ofstream file("data/movies.csv");  // Open the file in overwrite mode
	if (file.is_open()) {
		// Write the header (optional, if your CSV needs one)
		file << "id,title,plot,year\n";

		// Get all the actors with their keys (actor IDs)
		List<KeyValue<int, Movie>> allMovies = movieTable.getAllItemsWithKeys();

		// Iterate over all actors and write their details to the CSV
		for (int i = 0; i < allMovies.getLength(); ++i) {
			KeyValue<int, Movie> pair = allMovies.get(i);  // Get each key-value pair
			int movieID = pair.key;  // Actor ID (key)
			Movie* movie = pair.value;  // Actor object (value)

			// Write the actor details to the CSV
			file << movieID << ","  // Actor ID
				<< movie->getTitle() << ","
				<< movie->getPlot() << ","
				<< movie->getYear() << "\n";
		}

		file.close();
	}
	else {
		cerr << "Failed to open movies.csv for writing.\n";
	}
}

void updateCastCSV(const Dictionary<Movie>& movieTable) {
	ofstream file("data/cast.csv");  // Open the file in overwrite mode
	if (file.is_open()) {
		// Write the header (optional, if your CSV needs one)
		file << "person_id,movie_id\n";

		// Get all the movies with their keys (movie IDs)
		List<KeyValue<int, Movie>> allMovies = movieTable.getAllItemsWithKeys();

		// Iterate over all movies and their associated actors
		for (int i = 0; i < allMovies.getLength(); ++i) {
			KeyValue<int, Movie> pair = allMovies.get(i);  // Get each key-value pair
			int movieID = pair.key;  // Movie ID (key)
			Movie* movie = pair.value;  // Movie object (value)

			// Get the list of actor IDs associated with the movie
			const List<int>& actorIDs = movie->getActors();

			// Write each actor-movie relationship to the CSV
			for (int j = 0; j < actorIDs.getLength(); ++j) {
				int actorID = actorIDs.get(j);
				file << actorID << "," << movieID << "\n";  // Write actor ID and movie ID
			}
		}

		file.close();
	}
	else {
		cerr << "Failed to open cast.csv for writing.\n";
	}
}

void updateActorRatingsCSV(const Dictionary<Actor>& actorTable) {
	ofstream file("data/actorRatings.csv");  // Open the file in overwrite mode
	if (file.is_open()) {
		// Write the header
		file << "id,rating\n";

		// Get all the movies with their keys (movie IDs)
		List<KeyValue<int, Actor>> allActors = actorTable.getAllItemsWithKeys();

		// Iterate over all movies and ratings
		for (int i = 0; i < allActors.getLength(); ++i) {
			KeyValue<int, Actor> pair = allActors.get(i);  // Get each key-value pair
			int actorID = pair.key;  // Actor ID (key)
			Actor* actor = pair.value;  // Actor object (value)

			// Get the list of ratings associated with the movie
			const List<float>& ratings = actor->getRatings();

			// Write each movie-rating relationship to the CSV
			for (int j = 0; j < ratings.getLength(); ++j) {
				float rating = ratings.get(j);
				file << actorID << "," << rating << "\n";  // Write movie ID and rating
			}
		}

		file.close();
	}
	else {
		cerr << "Failed to open actorRatings.csv for writing.\n";
	}
}

void updateMovieRatingsCSV(const Dictionary<Movie>& movieTable) {
	ofstream file("data/movieRatings.csv");  // Open the file in overwrite mode
	if (file.is_open()) {
		// Write the header
		file << "id,rating\n";

		// Get all the movies with their keys (movie IDs)
		List<KeyValue<int, Movie>> allMovies = movieTable.getAllItemsWithKeys();

		// Iterate over all movies and ratings
		for (int i = 0; i < allMovies.getLength(); ++i) {
			KeyValue<int, Movie> pair = allMovies.get(i);  // Get each key-value pair
			int movieID = pair.key;  // Movie ID (key)
			Movie* movie = pair.value;  // Movie object (value)

			// Get the list of ratings associated with the movie
			const List<float>& ratings = movie->getRatings();

			// Write each movie-rating relationship to the CSV
			for (int j = 0; j < ratings.getLength(); ++j) {
				float rating = ratings.get(j);
				file << movieID << "," << rating << "\n";  // Write movie ID and rating
			}
		}

		file.close();
	}
	else {
		cerr << "Failed to open movieRatings.csv for writing.\n";
	}
}