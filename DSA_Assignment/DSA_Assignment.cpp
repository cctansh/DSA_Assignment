#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Dictionary.h"
#include "List.h"
#include "Actor.h"
#include "Movie.h"
using namespace std;

void parseActors(const string& filename, Dictionary& actorTable);
void parseMovies(const string& filename, Dictionary& movieTable);
void parseCast(const string& filename, Dictionary& actorTable, Dictionary& movieTable);

int main()
{
    Dictionary actorTable;
    Dictionary movieTable;

    parseActors("data/actors.csv", actorTable);
    parseMovies("data/movies.csv", movieTable);
    parseCast("data/cast.csv", actorTable, movieTable);

    // testing
    Actor* actor = static_cast<Actor*>(actorTable.get(200));
    Movie* movie = static_cast<Movie*>(movieTable.get(93779));
    actor->print();
    movie->print();

    return 0;
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
            actor->addMovie(movieID);
            movie->addActor(actorID);
        }
    }
    file.close();
}