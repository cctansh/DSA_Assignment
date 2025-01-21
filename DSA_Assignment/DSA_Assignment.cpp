#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Dictionary.h"
#include "List.h"
#include "Actor.h"
#include "Movie.h"
#include <ctime>
using namespace std;

void parseActors(const string& filename, Dictionary& actorTable);
void parseMovies(const string& filename, Dictionary& movieTable);
void parseCast(const string& filename, Dictionary& actorTable, Dictionary& movieTable);
int getCurrentYear();
int compareMovies(void* a, void* b);
int compareActors(void* a, void* b);
void printMovie(void* item);
void printActor(void* item);
void displayActorsByAge(Dictionary& actorTable, int x, int y);
void displayMoviesWithinPastYears(Dictionary& movieTable, int currentYear);


int main()
{
    Dictionary actorTable;
    Dictionary movieTable;
    int choice = -1;

    parseActors("data/actors.csv", actorTable);
    parseMovies("data/movies.csv", movieTable);
    parseCast("data/cast.csv", actorTable, movieTable);

    // testing
    Actor* actor = static_cast<Actor*>(actorTable.get(200));
    Movie* movie = static_cast<Movie*>(movieTable.get(93779));
    actor->print();
    movie->print();
    List movies = actor->getMovies();
    movies.print();
    

    while (choice != 0) {
        cout << "--------------- MENU ---------------" << endl;
        cout << "1. Display actors by age range" << endl;
        cout << "2. Display movies within past 3 years" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 0) {
			break;
        }
        else if (choice == 1) {
            int x, y;
            cout << "Enter the minimum age (x): ";
            cin >> x;
            cout << "Enter the maximum age (y): ";
            cin >> y;
            if (y <= x) {
				cout << "Invalid age range. Please try again." << endl;
				continue;
            }
            // display actors by age range
            displayActorsByAge(actorTable, x, y);
        }
        else if (choice == 2) {
            int currentYear;
			cout << "Enter the current year: ";
			cin >> currentYear;
            if (currentYear > getCurrentYear()) {
				cout << "Invalid year. Please try again." << endl;
				continue;
            }

			// display movies within the past 3 years
			displayMoviesWithinPastYears(movieTable, currentYear);
        }
		else {
			cout << "Invalid choice. Please try again.\n";
		}
    }

    return 0;
}

int getCurrentYear() { // current year to calc how old the actor is
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);
    return now.tm_year + 1900;
}

int compareMovies(void* a, void* b) {
    Movie* movieA = static_cast<Movie*>(a);
    Movie* movieB = static_cast<Movie*>(b);
    return movieA->getYear() - movieB->getYear(); // compare by release year
}

int compareActors(void* a, void* b) {
    Actor* actorA = static_cast<Actor*>(a);
    Actor* actorB = static_cast<Actor*>(b);
    return actorA->getBirthYear() - actorB->getBirthYear(); // older actors appear first
}

void printMovie(void* item) {
    Movie* movie = static_cast<Movie*>(item); // cast void* to Movie*
    movie->print(); // using movie's print method
}

void printActor(void* item) {
    Actor* actor = static_cast<Actor*>(item); // cast void* to Actor*
    actor->print(); // using actor's print method
}

void displayMoviesWithinPastYears(Dictionary& movieTable, int currentYear) {
    SortedLinkedList sortedList(compareMovies); // using the comparator to sort movies
    int yearThreshold = currentYear - 3;

	// add movies within the threshold to the sorted list
    movieTable.getMoviesWithinYearRange(yearThreshold, sortedList);

    if (sortedList.getLength() == 0) {
        cout << "No movies found within the past 3 years.\n";
        return;
    }

    cout << "Movies made within the past 3 years:\n";
    sortedList.display(printMovie); // Use the print function for movies
}


void displayActorsByAge(Dictionary& actorTable, int x, int y) {
    SortedLinkedList sortedList(compareActors); // using the comparator to sort actors by age
    actorTable.getActorsByAge(x, y, sortedList, getCurrentYear()); // filter actors into the sorted list

    if (sortedList.getLength() == 0) {
        cout << "No actors found in the specified age range.\n";
        return;
    }

    cout << "Actors aged between " << x << " and " << y << ":\n";
    sortedList.display(printActor); // use the print function for actors
}

void parseActors(const string& filename, Dictionary& actorTable) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int id;
        string name;
        int birthYear;

        // Read the ID
        ss >> id;
        ss.ignore(); // Skip the comma

        // Read the name, handling quotes
        if (ss.peek() == '"') { // Check if the name starts with a quote
            ss.ignore(); // Skip the opening quote
            getline(ss, name, '"'); // Read until the closing quote
            ss.ignore(); // Skip the comma after the closing quote
        }
        else {
            getline(ss, name, ','); // Read until the comma
        }

        // Read the birth year
        ss >> birthYear;

        // Create and add the actor
        Actor* actor = new Actor(name, birthYear);
        actorTable.add(id, actor);
    }
    file.close();
}

void parseMovies(const string& filename, Dictionary& movieTable) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int id;
        string title, plot;
        int year;

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
            getline(ss, title, ',');
        }

        // Read the plot, handling quotes
        if (ss.peek() == '"') {
            ss.ignore(); // Skip the opening quote
            getline(ss, plot, '"'); // Read until the closing quote
            ss.ignore(); // Skip the comma after the closing quote
        }
        else {
            getline(ss, plot, ',');
        }

        // Read the year
        ss >> year;

        // Create and add the movie
        Movie* movie = new Movie(title, plot, year);
        movieTable.add(id, movie);
    }
    file.close();
}

void parseCast(const string& filename, Dictionary& actorTable, Dictionary& movieTable) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int actorID, movieID;
        ss >> actorID;
        ss.ignore();
        ss >> movieID;

        Actor* actor = static_cast<Actor*>(actorTable.get(actorID));
        Movie* movie = static_cast<Movie*>(movieTable.get(movieID));

        if (actor && movie) {
            // Create pointers to the IDs
            int* actorIDPtr = new int(actorID);
            int* movieIDPtr = new int(movieID);

            // Add movieID to the actor and actorID to the movie
            actor->addMovie(movieIDPtr);
            movie->addActor(actorIDPtr);
        }
    }
    file.close();
}