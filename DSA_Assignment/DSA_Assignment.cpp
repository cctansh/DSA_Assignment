#include <iostream>
#include "Dictionary.h"
#include "List.h"
#include "Actor.h"
#include "Movie.h"
#include "KeyValue.h"
#include "SortedLinkedList.h"
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
void displayActorsByAge(const Dictionary<Actor>& actorTable, int x, int y);
void displayMoviesByYear(const Dictionary<Movie>& movieTable, int currentYear);
void displayMoviesForActor(const Dictionary<Actor>& actorTable, const string& actorName, const Dictionary<Movie>& movieTable);
void displayActorsInMovie(const Dictionary<Movie>& movieTable, const string& movieName, const Dictionary<Actor>& actorTable);
void updateActorsCSV(const Dictionary<Actor>& actorTable);
void updateMoviesCSV(const Dictionary<Movie>& movieTable);
template <typename T>
int generateUniqueID(const Dictionary<T>& dictionary);
void addActor(Dictionary<Actor>& actorTable);
void addMovie(Dictionary<Movie>& movieTable);
void updateActor(Dictionary<Actor>& actorTable);
void updateMovie(Dictionary<Movie>& movieTable);
void addActorToMovie(Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable);
void updateCastCSV(const Dictionary<Movie>& movieTable);

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
        cout << "1. Add actor" << endl;
        cout << "2. Add movie" << endl;
        cout << "3. Add actor to movie" << endl;
        cout << "4. Update actor" << endl;
        cout << "5. Update movie" << endl;
        cout << "6. Display actors within a specified age range, sorted in ascending order by age" << endl;
        cout << "7. Display movies released within the past 3 years, sorted in ascending order by release year" << endl;
        cout << "8. Display all movies an actor has starred in, sorted in alphabetical order" << endl;
        cout << "9. Display all actors in a particular movie, sorted in alphabetical order" << endl;
        cout << "0. Exit" << endl << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            cout << "------------ ADD ACTOR ------------" << endl;
            addActor(actorTable);
        }
        else if (choice == 2) {
            cout << "------------ ADD MOVIE ------------" << endl;
            addMovie(movieTable);
        }
        else if (choice == 3) {
            cout << "------- ADD ACTOR TO MOVIE -------" << endl;
            addActorToMovie(actorTable, movieTable);

        }
        else if (choice == 4) {
            cout << "----------- UPDATE ACTOR -----------" << endl;
            updateActor(actorTable);
        }
        else if (choice == 5) {
            cout << "----------- UPDATE MOVIE -----------" << endl;
            updateMovie(movieTable);
        }
        else if (choice == 6) {
            int x, y;
            cout << "----------- DISPLAY ACTOR IN AGE RANGE -----------" << endl;
            cout << "Enter the minimum age: ";
            cin >> x;
            cout << "Enter the maximum age: ";
            cin >> y;
            if (y <= x) {
                cout << "Invalid age range. Please try again." << endl;
                continue;
            }
            // display actors by age range
            displayActorsByAge(actorTable, x, y);
        }
        else if (choice == 7) {
            cout << "----------- DISPLAY MOVIES MADE WITHIN PAST 3 YEARS -----------" << endl;
            int currentYear;
            cout << "Enter the current year: ";
            cin >> currentYear;
            if (currentYear > getCurrentYear()) {
                cout << "Invalid year. Please try again." << endl;
                continue;
            }

            // display movies within the past 3 years
            displayMoviesByYear(movieTable, currentYear);
        }
		else if (choice == 8) {
			string actorName;
			cout << "----------- DISPLAY MOVIES BY ACTOR STARRED IN -----------" << endl;
            cout << "Enter Actor Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, actorName);
			displayMoviesForActor(actorTable, actorName, movieTable);
		}
        else if (choice == 9) {
			string movieName;
			cout << "----------- DISPLAY ACTORS IN A MOVIE -----------" << endl;
			cout << "Enter Movie Name: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, movieName);
			displayActorsInMovie(movieTable, movieName, actorTable);
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    }

    return 0;
}

void addActorToMovie(Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable) {
    int movieID, actorID;
    Movie* movie = nullptr;
    Actor* actor = nullptr;

    cout << endl;
    cout << "MOVIE LIST" << endl << "----------" << endl;
    movieTable.print();

    // Get movie
    while (true) {
        // Prompt user for movie ID
        cout << endl << "Enter the ID of the movie you want to add an actor to (or enter 0 to exit):  ";
        cin >> movieID;

        if (cin.fail()) {
            // Handle invalid input
            cin.clear();               // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (movieID == 0) return;

        // Get the movie from the movie table
        movie = movieTable.get(movieID);
        if (movie == nullptr) {
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }
        break;
    }

    // Get actor
    cout << endl;
    cout << "ACTOR LIST" << endl << "----------" << endl;
    actorTable.print();
    while (true) {
        // Prompt user for actor ID
        cout << endl << "Enter the ID of the actor you want to add (or enter 0 to exit): ";
        cin >> actorID;

        if (cin.fail()) {
            // Handle invalid input
            cin.clear();               // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (actorID == 0) return;

        // Get the movie from the movie table
        actor = actorTable.get(actorID);
        if (actor == nullptr) {
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }
        break;
    }

    // Add the actor to the movie and vice versa
    actor->addMovie(movieID);
    movie->addActor(actorID);

    updateCastCSV(movieTable);

    cout << endl << "Actor " << actor->getName() << " has been added to the movie " << movie->getTitle() << "." << endl;
}

void updateActor(Dictionary<Actor>& actorTable) {
    int id;
    int choice = -1;

    while (true) {
        id = -1;
        cout << endl;
        cout << "ACTOR LIST" << endl << "----------" << endl;
        actorTable.print();
        cout << "0. Return to menu" << endl << endl;
        cout << "Select actor to update (Enter actor ID): ";
        cin >> id;

        if (id == 0) return;

        cout << endl;

        Actor* actor = actorTable.get(id);

        if (actor != nullptr) {
            while (choice != 0) {
                actor->print();
                cout << "1. Name" << endl << "2. Birth Year" << endl << "0. Return to actor select" << endl << endl;
                cout << "Select which to update: ";
                cin >> choice;

                if (choice == 1) {
                    string newName;
                    cout << endl << "Enter new name: ";
                    cin.ignore();
                    getline(cin, newName);

                    actor->setName(newName);

                    cout << endl;
                }
                else if (choice == 2) {
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
                    break;
                }
                else {
                    cout << endl << "Invalid choice. Please try again." << endl << endl;
                }
            }
            updateActorsCSV(actorTable);
        }
        else {
            cout << "Invalid ID. Please try again." << endl << endl;
        }
    }
}

void updateMovie(Dictionary<Movie>& movieTable) {
    int id;
    int choice = -1;

    while (true) {
        id = -1;
        cout << endl;
        cout << "MOVIE LIST" << endl << "----------" << endl;
        movieTable.print();
        cout << "0. Return to menu" << endl << endl;
        cout << "Select movie to update (Enter movie ID): ";
        cin >> id;

        if (id == 0) return;

        cout << endl;

        Movie* movie = movieTable.get(id);

        if (movie != nullptr) {
            while (choice != 0) {
                movie->print();
                cout << "1. Title" << endl << "2. Plot" << endl << "3. Release Year" << endl << "0. Return to movie select" << endl << endl;
                cout << "Select which to update: ";
                cin >> choice;

                if (choice == 1) {
                    string newTitle;
                    cout << endl << "Enter new title: ";
                    cin.ignore();
                    getline(cin, newTitle);

                    movie->setTitle(newTitle);

                    cout << endl;
                }
                else if (choice == 2) {
                    string newPlot;
                    cout << endl << "Enter new plot: ";
                    cin.ignore();
                    getline(cin, newPlot);

                    movie->setPlot(newPlot);

                    cout << endl;
                }
                else if (choice == 3) {
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
                    break;
                }
                else {
                    cout << endl << "Invalid choice. Please try again." << endl << endl;
                }
            }
            updateMoviesCSV(movieTable);
        }
        else {
            cout << "Invalid ID. Please try again." << endl;
        }
    }
}

int getCurrentYear() { // current year to calc how old the actor is
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);
    return now.tm_year + 1900;
}

// e)
void displayActorsByAge(const Dictionary<Actor>& actorTable, int x, int y) {
    // Create a sorted linked list with a custom comparison function for age
    SortedLinkedList<Actor*> sortedList([](Actor* a, Actor* b) {
        int ageA = getCurrentYear() - a->getBirthYear();
        int ageB = getCurrentYear() - b->getBirthYear();
        return ageA < ageB; // Sort in ascending order of age
        });

    List<KeyValue<int, Actor>> actors = actorTable.getAllItemsWithKeys();
    for (int i = 0; i < actors.getLength(); i++) {
        Actor* actor = actors.get(i).value;
        int age = getCurrentYear() - actor->getBirthYear();
        if (age >= x && age <= y) {
            sortedList.add(actor); // Add to the sorted list if within age range
        }
    }

    cout << "Actors between ages " << x << " and " << y << " (sorted by age):" << endl;
    sortedList.print(); // Print sorted actors
}

// f)
void displayMoviesByYear(const Dictionary<Movie>& movieTable, int currentYear) {
    // Create a sorted linked list with a comparison function for ascending order of year
    SortedLinkedList<Movie*> sortedList([](Movie* a, Movie* b) {
        return *a < *b; // Use the Movie's custom operator<
        });

    // Retrieve all movies from the dictionary
    List<KeyValue<int, Movie>> movies = movieTable.getAllItemsWithKeys();

    // Add movies from the past 3 years (inclusive) to the sorted list
    for (int i = 0; i < movies.getLength(); i++) {
        Movie* movie = movies.get(i).value;
        if (movie->getYear() >= (currentYear - 3) && movie->getYear() <= currentYear) {
            sortedList.add(movie); // Add only movies within the past 3 years
        }
    }

    // Print sorted movies
    if (sortedList.getSize() > 0) {
        cout << "Movies made within the past 3 years (sorted by year):" << endl;
        sortedList.print();
    }
    else {
        cout << "No movies found within the past 3 years." << endl;
    }
}

// g)
void displayMoviesForActor(const Dictionary<Actor>& actorTable, const string& actorName, const Dictionary<Movie>& movieTable) {
    // Search for the actor by name in the actorTable
    Actor* actor = nullptr;

    List<KeyValue<int, Actor>> actors = actorTable.getAllItemsWithKeys(); // Get all actors in the dictionary
    for (int i = 0; i < actors.getLength(); i++) {
        if (actors.get(i).value->getName() == actorName) {
            actor = actors.get(i).value; // Found the actor
            break;
        }
    }

    if (!actor) {
        cout << "Actor \"" << actorName << "\" not found!" << endl;
        return;
    }

    // Use SortedLinkedList for alphabetical order
    SortedLinkedList<string> sortedList([](const string& a, const string& b) {
        return a < b; // alphabetical order
        });

    const List<int>& movieIDs = actor->getMovies(); // Get the movie IDs the actor starred in
    for (int i = 0; i < movieIDs.getLength(); i++) {
        Movie* movie = movieTable.get(movieIDs.get(i));
        if (movie) {
            sortedList.add(movie->getTitle()); // Add movie titles to the sorted list
        }
    }

    cout << "Movies starred in by " << actor->getName() << " (Alphabetical Order):" << endl;
    sortedList.print(); // Print sorted movie titles
}

// h)
void displayActorsInMovie(const Dictionary<Movie>& movieTable, const string& movieName, const Dictionary<Actor>& actorTable) {
    // Search for the movie by name in the movieTable
    Movie* movie = nullptr;

    List<KeyValue<int, Movie>> movies = movieTable.getAllItemsWithKeys(); // Get all movies in the dictionary
    for (int i = 0; i < movies.getLength(); i++) {
        if (movies.get(i).value->getTitle() == movieName) {
            movie = movies.get(i).value; // Found the movie
            break;
        }
    }

    if (!movie) {
        cout << "Movie \"" << movieName << "\" not found!" << endl;
        return;
    }

    // Use SortedLinkedList for alphabetical order
    SortedLinkedList<string> sortedList([](const string& a, const string& b) {
        return a < b; // alphabetical order
        });

    const List<int>& actorIDs = movie->getActors(); // Get the actor IDs in the movie
    for (int i = 0; i < actorIDs.getLength(); i++) {
        Actor* actor = actorTable.get(actorIDs.get(i));
        if (actor) {
            sortedList.add(actor->getName()); // Add actor names to the sorted list
        }
    }

    cout << "Actors in the movie \"" << movie->getTitle() << "\" (Alphabetical Order):" << endl;
    sortedList.print(); // Print sorted actor names
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

    // Generate a unique ID
    int id = generateUniqueID(actorTable);
    cout << "Generated actor ID: " << id << endl;

    // Input actor name
    cout << "Enter actor name (or 0 to exit): ";
    cin.ignore(); // Clear any leftover newline from previous input
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

    Actor* actor = new Actor(name, birthYear);
    if (actorTable.add(id, actor)) {
        cout << endl << "Actor added successfully." << endl;
        updateActorsCSV(actorTable);
    }
    else {
        cout << "Actor with this ID already exists." << endl;
        delete actor;
    }
}

void addMovie(Dictionary<Movie>& movieTable) {
    int year;
    string title, plot;

    // Generate a unique ID
    int id = generateUniqueID(movieTable);
    cout << "Generated movie ID: " << id << endl;

    // Input movie title
    cout << "Enter movie title (or 0 to exit): ";
    cin.ignore(); // Clear leftover newline from previous input
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
    Movie* movie = new Movie(title, plot, year);
    if (movieTable.add(id, movie)) {
        cout << endl << "Movie added successfully." << endl;
        updateMoviesCSV(movieTable);
    }
    else {
        cout << "Movie with this ID already exists." << endl;
        delete movie; // Clean up memory if adding fails
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