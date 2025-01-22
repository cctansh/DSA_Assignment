#include <iostream>
#include "Dictionary.h"
#include "List.h"
#include "Actor.h"
#include "Movie.h"
#include "KeyValue.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
using namespace std;

void parseActors(const string& filename, Dictionary<Actor>& actorTable);
void parseMovies(const string& filename, Dictionary<Movie>& movieTable);
void parseCast(const string& filename, Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable);
int getCurrentYear();
int compareMovies(void* a, void* b);
int compareActors(void* a, void* b);
void printMovie(void* item);
void printActor(void* item);
//void displayActorsByAge(Dictionary<Actor>& actorTable, int x, int y);
//void displayMoviesWithinPastYears(Dictionary<Movie>& movieTable, int currentYear);
void updateActorsCSV(const Dictionary<Actor>& actorTable);
void updateMoviesCSV(const Dictionary<Movie>& movieTable);
template <typename T>
int generateUniqueID(const Dictionary<T>& dictionary);
void addActor(Dictionary<Actor>& actorTable);
void addMovie(Dictionary<Movie>& movieTable);

int main()
{
    Dictionary<Actor> actorTable;
    Dictionary<Movie> movieTable;
    int choice = -1;

    parseActors("data/actors.csv", actorTable);
    parseMovies("data/movies.csv", movieTable);
    parseCast("data/cast.csv", actorTable, movieTable);

    while (choice != 0) {
        cout << "--------------- MENU ---------------" << endl;
        cout << "1. Display actors by age range" << endl;
        cout << "2. Display movies within past 3 years" << endl;
        cout << "3. Add actor" << endl;
        cout << "4. Add movie" << endl;
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
            //displayActorsByAge(actorTable, x, y);
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
			//displayMoviesWithinPastYears(movieTable, currentYear);
        }
        else if (choice == 3) {
            addActor(actorTable);
        }
        else if (choice == 4) {
            addMovie(movieTable);
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
/*
void displayMoviesWithinPastYears(Dictionary<Actor>& movieTable, int currentYear) {
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


void displayActorsByAge(Dictionary<Actor>& actorTable, int x, int y) {
    SortedLinkedList sortedList(compareActors); // using the comparator to sort actors by age
    actorTable.getActorsByAge(x, y, sortedList, getCurrentYear()); // filter actors into the sorted list

    if (sortedList.getLength() == 0) {
        cout << "No actors found in the specified age range.\n";
        return;
    }

    cout << "Actors aged between " << x << " and " << y << ":\n";
    sortedList.display(printActor); // use the print function for actors
}
*/

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

// Function to generate a unique ID
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

void addActor(Dictionary<Actor>& actorTable) {
    int birthYear;
    string name;

    int id = generateUniqueID(actorTable); // Generate a unique ID
    cout << "Generated actor ID: " << id << endl;
    cout << "Enter actor name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter actor birth year: ";
    cin >> birthYear;

    Actor* actor = new Actor(name, birthYear);
    if (actorTable.add(id, actor)) {
        cout << "Actor added successfully.\n";
        updateActorsCSV(actorTable);
    }
    else {
        cout << "Actor with this ID already exists.\n";
    }
}

void addMovie(Dictionary<Movie>& movieTable) {
    int year;
    string title, plot;

    int id = generateUniqueID(movieTable); // Generate a unique ID
    cout << "Generated movie ID: " << id << endl;
    cout << "Enter movie title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter movie plot: ";
    getline(cin, plot);
    cout << "Enter movie release year: ";
    cin >> year;

    Movie* movie = new Movie(title, plot, year);
    if (movieTable.add(id, movie)) {
        cout << "Movie added successfully.\n";
        updateMoviesCSV(movieTable);
    }
    else {
        cout << "Movie with this ID already exists.\n";
    }
}

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
        Actor* actor = new Actor(name, birthYear);
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
        Movie* movie = new Movie(title, plot, year);
        movieTable.add(id, movie);
    }
    file.close();
}

// Parse cast and establish relationships
void parseCast(const string& filename, Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int actorID, movieID;
        ss >> actorID;
        ss.ignore();
        ss >> movieID;

        Actor* actor = actorTable.get(actorID);
        Movie* movie = movieTable.get(movieID);

        if (actor && movie) {
            // Add movieID to the actor and actorID to the movie
            actor->addMovie(movieID);
            movie->addActor(actorID);
        }
    }
    file.close();
}