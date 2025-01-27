#include <iostream>
#include "Dictionary.h"
#include "List.h"
#include "Actor.h"
#include "Movie.h"
#include "KeyValue.h"
#include "BinarySearchTree.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <cctype>
using namespace std;

// parse base data
void parseActors(const string& filename, Dictionary<Actor>& actorTable);
void parseMovies(const string& filename, Dictionary<Movie>& movieTable);
void parseCast(const string& filename, Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable);
void updateActorsCSV(const Dictionary<Actor>& actorTable);
void updateMoviesCSV(const Dictionary<Movie>& movieTable);
void updateCastCSV(const Dictionary<Movie>& movieTable);

int getCurrentYear();
void displayActorsByAge(const Dictionary<Actor>& actorTable);
void displayMoviesByYear(const Dictionary<Movie>& movieTable);
void displayMoviesForActorByID(Dictionary<Actor>& actorTable, const Dictionary<Movie>& movieTable);
void displayActorsInMovieByID(Dictionary<Movie>& movieTable, const Dictionary<Actor>& actorTable);
void displayKnownActors(Dictionary<Actor>& actorTable, const Dictionary<Movie>& movieTable);

template <typename T>
int generateUniqueID(const Dictionary<T>& dictionary);
void addActor(Dictionary<Actor>& actorTable);
void addMovie(Dictionary<Movie>& movieTable);
void updateActor(Dictionary<Actor>& actorTable);
void updateMovie(Dictionary<Movie>& movieTable);
void addActorToMovie(Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable);

// ratings
void parseActorRatings(const string& filename, Dictionary<Actor>& actorTable);
void parseMovieRatings(const string& filename, Dictionary<Movie>& movieTable);
void displayActorRatings(Dictionary<Actor>& actorTable);
void displayMovieRatings(Dictionary<Movie>& movieTable);
void rateActor(Dictionary<Actor>& actorTable);
void rateMovie(Dictionary<Movie>& movieTable);
void updateMovieRatingsCSV(const Dictionary<Movie>& movieTable);
void updateActorRatingsCSV(const Dictionary<Actor>& actorTable);
string normalizeString(const string& str);
void displayMoviesByMinimumRating(const Dictionary<Movie>& movieTable);
void displayActorsByMinimumRating(const Dictionary<Actor>& actorTable);

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

    while (choice != 0) {
        cout << "--------------- MENU ---------------" << endl;
        cout << "1.  Add actor" << endl;
        cout << "2.  Add movie" << endl;
        cout << "3.  Add actor to movie" << endl;
        cout << "4.  Update actor" << endl;
        cout << "5.  Update movie" << endl;
        cout << "6.  Display actors within a specified age range, sorted in ascending order by age" << endl;
        cout << "7.  Display movies released within the past 3 years, sorted in ascending order by release year" << endl;
        cout << "8.  Display all movies an actor has starred in, sorted in alphabetical order" << endl;
        cout << "9.  Display all actors in a particular movie, sorted in alphabetical order" << endl;
        cout << "10. Display a list of all actors that a particular actor knows" << endl;
        cout << "11. Display all ratings for an actor" << endl;
        cout << "12. Display all ratings for a movie" << endl;
        cout << "13. Rate an actor" << endl;
        cout << "14. Rate a movie" << endl;
        cout << "15. Display Movies above a minimum rating" << endl;
        cout << "16. Display Actors above a minimum rating" << endl;
        cout << "0. Exit" << endl << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // handle non ints
        if (cin.fail()) {
            // Handle invalid input
            cin.clear();               // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid choice. Please try again." << endl << endl;
            choice = -1;
            continue;
        }

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
            cout << "----------- DISPLAY ACTOR IN AGE RANGE -----------" << endl;
            // display actors by age range
            displayActorsByAge(actorTable);
        }
        else if (choice == 7) {
            cout << "----------- DISPLAY MOVIES MADE WITHIN PAST 3 YEARS -----------" << endl;
            // display movies within the past 3 years
            displayMoviesByYear(movieTable);
        }
        else if (choice == 8) {
            cout << "----------- DISPLAY MOVIES BY ACTOR STARRED IN -----------" << endl;
            displayMoviesForActorByID(actorTable, movieTable);
        }
        else if (choice == 9) {
            cout << "----------- DISPLAY ACTORS IN A MOVIE -----------" << endl;
            displayActorsInMovieByID(movieTable, actorTable);
        }
		else if (choice == 10) {
            string actorName;
            cout << "----------- DISPLAY KNOWN ACTORS -----------" << endl;
            displayKnownActors(actorTable, movieTable);
		}
        else if (choice == 11) {
            cout << "------ DISPLAY ACTOR RATINGS ------" << endl;
            displayActorRatings(actorTable);
        }
        else if (choice == 12) {
            cout << "------ DISPLAY MOVIE RATINGS ------" << endl;
            displayMovieRatings(movieTable);
        }
        else if (choice == 13) {
            cout << "----------- RATE ACTOR -----------" << endl;
            rateActor(actorTable);
        }
        else if (choice == 14) {
            cout << "----------- RATE MOVIE -----------" << endl;
            rateMovie(movieTable);
        }
        else if (choice == 15) {
            cout << "----------- DISPLAY MOVIES OF A MINIMUM RATING -----------" << endl;
            displayMoviesByMinimumRating(movieTable);
        }
		else if (choice == 16) {
			cout << "----------- DISPLAY ACTORS OF A MINIMUM RATING -----------" << endl;
            displayActorsByMinimumRating(actorTable);
		}
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl;
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

// b
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

// c
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

// d
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

        if (cin.fail()) {
            // Handle invalid input
            cin.clear();               // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (id == 0) return;

        cout << endl;

        Actor* actor = actorTable.get(id);

        if (actor != nullptr) {
            choice = -1;
            while (choice != 0) {
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
            cout << "Invalid ID. Please try again." << endl;
        }
    }
}

// d
void updateMovie(Dictionary<Movie>& movieTable) {
    int id;
    int choice = -1;
    Movie* movie;

    while (true) {
        id = -1;
        cout << endl;
        cout << "MOVIE LIST" << endl << "----------" << endl;
        movieTable.print();
        cout << "0. Return to menu" << endl << endl;
        cout << "Select movie to update (Enter movie ID): ";
        cin >> id;

        if (cin.fail()) {
            // Handle invalid input
            cin.clear();               // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (id == 0) return;

        cout << endl;

        movie = movieTable.get(id);

        if (movie != nullptr) {
            choice = -1;
            while (choice != 0) {
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

// e) merge sort
void sortActorsByAge(Actor* arr[], int left, int right, int currentYear) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Recursive calls to sort left and right halves
    sortActorsByAge(arr, left, mid, currentYear);
    sortActorsByAge(arr, mid + 1, right, currentYear);

    // Merge the sorted halves
    int size = right - left + 1;
    Actor** temp = new Actor * [size];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        int ageLeft = currentYear - arr[i]->getBirthYear();
        int ageRight = currentYear - arr[j]->getBirthYear();
        if (ageLeft <= ageRight) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int m = 0; m < size; m++) arr[left + m] = temp[m];

    delete[] temp; // Free dynamically allocated memory
}

// e) merge sort
void displayActorsByAge(const Dictionary<Actor>& actorTable) {
    int x, y;

    while (true) {
        cout << "Enter the minimum age: ";
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer for minimum age." << endl;
            continue;
        }

        cout << "Enter the maximum age: ";
        cin >> y;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer for maximum age." << endl;
            continue;
        }

        if (y <= x) {
            cout << "Invalid age range. Maximum age must be greater than minimum age. Please try again." << endl;
            continue;
        }

        break;
    }

    List<KeyValue<int, Actor>> actors = actorTable.getAllItemsWithKeys();
    int count = actors.getLength();

    // Dynamically allocate the array
    Actor** actorsArr = new Actor * [count];
    int index = 0;

    for (int i = 0; i < count; i++) {
        Actor* actor = actors.get(i).value;
        int age = getCurrentYear() - actor->getBirthYear();
        if (age >= x && age <= y) {
            actorsArr[index++] = actor;
        }
    }

    if (index == 0) {
        // No actors found in the specified age range
        cout << endl << "No actors found within the age range of " << x << " to " << y << "." << endl;
    }
    else {
        // Sort actors by age using a single recursive function
        sortActorsByAge(actorsArr, 0, index - 1, getCurrentYear());

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
}


// f) merge sort
void sortMoviesByYear(Movie* arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Recursive calls to sort left and right halves
    sortMoviesByYear(arr, left, mid);
    sortMoviesByYear(arr, mid + 1, right);

    // Merge the sorted halves
    int size = right - left + 1;
    Movie** temp = new Movie * [size];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i]->getYear() <= arr[j]->getYear()) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int m = 0; m < size; m++) arr[left + m] = temp[m];

    delete[] temp; // Free dynamically allocated memory
}

// f) merge sort
void displayMoviesByYear(const Dictionary<Movie>& movieTable) {
    while (true) {
        int currentYear;

        while (true) {
            cout << "Enter the current year (0 to exit): ";
            cin >> currentYear;
			cout << endl;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid year." << endl;
                continue;
            }

            if (currentYear == 0) {
                return;
            }

            if (currentYear > getCurrentYear()) {
                cout << "Invalid year. The year cannot be in the future. Please try again." << endl;
                continue;
            }

            break;
        }

        List<KeyValue<int, Movie>> movies = movieTable.getAllItemsWithKeys();
        int count = movies.getLength();

        // Dynamically allocate the array
        Movie** moviesArr = new Movie * [count];
        int index = 0;

        for (int i = 0; i < count; i++) {
            Movie* movie = movies.get(i).value;
            if (movie->getYear() >= (currentYear - 3) && movie->getYear() <= currentYear) {
                moviesArr[index++] = movie;
            }
        }

        if (index > 0) {
            // Sort movies by year using a single recursive function
            sortMoviesByYear(moviesArr, 0, index - 1);

            // Display sorted movies
            cout << left << setw(35) << "Movie Title" << setw(10) << "Year" << endl;
            cout << string(45, '-') << endl; // Line separator
            for (int i = 0; i < index; i++) {
                // Print each movie in a formatted row
                cout << left << setw(35) << moviesArr[i]->getTitle()
                    << right << setw(4) << moviesArr[i]->getYear() << endl;
            }
        }
        else {
            cout << "No movies found within the past 3 years." << endl;
        }

        delete[] moviesArr; // Free dynamically allocated memory
        cout << endl;
    }
}


// g & h) insertion sort
void insertionSort(string arr[], int n) {
    for (int i = 1; i < n; i++) {
        string key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// g) insertion sort
void displayMoviesForActorByID(Dictionary<Actor>& actorTable, const Dictionary<Movie>& movieTable) {
    int actorID;

    while (true) {
        actorID = -1;
        cout << endl;
        cout << "ACTOR LIST" << endl
            << "----------" << endl;
        actorTable.print(); // Print the list of all actors
        cout << "0. Return to menu" << endl
            << endl;
        cout << "Select actor (Enter actor ID): ";
        cin >> actorID;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (actorID == 0) return;

        Actor* actor = actorTable.get(actorID);
        if (!actor) {
            cout << "Actor with ID " << actorID << " not found!" << endl;
            continue;
        }

        const List<int>& movieIDs = actor->getMovies();
        int movieCount = movieIDs.getLength();
        string* movieTitles = new string[movieCount]; // Dynamically allocate array
        int index = 0;

        // Collect movie titles
        for (int i = 0; i < movieCount; i++) {
            Movie* movie = movieTable.get(movieIDs.get(i));
            if (movie) {
                movieTitles[index++] = movie->getTitle();
            }
        }

        // Sort movie titles alphabetically using Insertion Sort
        insertionSort(movieTitles, index);

        // Display sorted movie titles
        cout << "Movies starred in by " << actor->getName() << " (Alphabetical Order):" << endl;
        for (int i = 0; i < index; i++) {
            cout << movieTitles[i] << endl;
        }

        delete[] movieTitles; // Free dynamically allocated memory
    }
}


// h) insertion sort
void displayActorsInMovieByID(Dictionary<Movie>& movieTable, const Dictionary<Actor>& actorTable) {
    int movieID;

    while (true) {
        movieID = -1;
        cout << endl;
        cout << "MOVIE LIST" << endl
            << "----------" << endl;
        movieTable.print(); // Print the list of all movies
        cout << "0. Return to menu" << endl
            << endl;
        cout << "Select movie (Enter movie ID): ";
        cin >> movieID;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (movieID == 0) return;

        Movie* movie = movieTable.get(movieID);
        if (!movie) {
            cout << "Movie with ID " << movieID << " not found!" << endl;
            continue;
        }

        const List<int>& actorIDs = movie->getActors();
        int actorCount = actorIDs.getLength();
        string* actorNames = new string[actorCount]; // Dynamically allocate array
        int index = 0;

        // Collect actor names
        for (int i = 0; i < actorCount; i++) {
            Actor* actor = actorTable.get(actorIDs.get(i));
            if (actor) {
                actorNames[index++] = actor->getName();
            }
        }

        // Sort actor names alphabetically using Insertion Sort
        insertionSort(actorNames, index);

        // Display sorted actor names
        cout << "Actors in the movie \"" << movie->getTitle() << "\" (Alphabetical Order):" << endl;
        for (int i = 0; i < index; i++) {
            cout << actorNames[i] << endl;
        }

        delete[] actorNames; // Free dynamically allocated memory
    }
}

// i) 
void displayKnownActors(Dictionary<Actor>& actorTable, const Dictionary<Movie>& movieTable) {
    int id;

    while (true) {
        id = -1;
        cout << endl;
        cout << "ACTOR LIST" << endl << "----------" << endl;
        actorTable.print(); // Print the list of all actors with IDs
        cout << "0. Return to menu" << endl << endl;
        cout << "Select actor (Enter actor ID): ";
        cin >> id;

        if (cin.fail()) {
            // Handle invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (id == 0) return; // Return to menu

        Actor* actor = actorTable.get(id); // Fetch actor by ID
        if (!actor) {
            cout << "Invalid actor ID. Please try again." << endl;
            continue;
        }

        List<string> directCoActors;   // Stores direct co-actors
        List<string> indirectCoActors; // Stores indirect co-actors
        List<int> visitedMovies;       // Tracks visited movie IDs

        // Helper function to check if a value exists in a List
        auto contains = [](const auto& list, const auto& value) -> bool {
            for (int i = 0; i < list.getLength(); i++) {
                if (list.get(i) == value) return true;
            }
            return false;
            };

        // Process direct co-actors (Level 1)
        const List<int>& movieIDs = actor->getMovies(); // Movies the actor starred in
        for (int i = 0; i < movieIDs.getLength(); i++) {
            int movieID = movieIDs.get(i);
            if (!contains(visitedMovies, movieID)) {
                visitedMovies.add(movieID);

                Movie* movie = movieTable.get(movieID);
                if (movie) {
                    const List<int>& coActorIDs = movie->getActors();
                    for (int j = 0; j < coActorIDs.getLength(); j++) {
                        int coActorID = coActorIDs.get(j);
                        if (coActorID != id) { // Skip the selected actor
                            Actor* coActor = actorTable.get(coActorID);
                            if (coActor && !contains(directCoActors, coActor->getName())) {
                                directCoActors.add(coActor->getName()); // Add direct co-actor
                            }
                        }
                    }
                }
            }
        }

        // Process indirect co-actors (Level 2)
        for (int i = 0; i < directCoActors.getLength(); i++) {
            string coActorName = directCoActors.get(i);
            Actor* coActor = nullptr;

            // Find the co-actor in the actor table
            List<KeyValue<int, Actor>> allActors = actorTable.getAllItemsWithKeys();
            for (int j = 0; j < allActors.getLength(); j++) {
                if (allActors.get(j).value->getName() == coActorName) {
                    coActor = allActors.get(j).value;
                    break;
                }
            }

            if (coActor) {
                const List<int>& coActorMovies = coActor->getMovies();
                for (int k = 0; k < coActorMovies.getLength(); k++) {
                    int movieID = coActorMovies.get(k);
                    if (!contains(visitedMovies, movieID)) {
                        visitedMovies.add(movieID);

                        Movie* movie = movieTable.get(movieID);
                        if (movie) {
                            const List<int>& indirectActorIDs = movie->getActors();
                            for (int l = 0; l < indirectActorIDs.getLength(); l++) {
                                int indirectActorID = indirectActorIDs.get(l);
                                Actor* indirectActor = actorTable.get(indirectActorID);
                                if (indirectActor && indirectActor->getName() != coActorName &&
                                    !contains(directCoActors, indirectActor->getName()) &&
                                    !contains(indirectCoActors, indirectActor->getName())) {
                                    indirectCoActors.add(indirectActor->getName()); // Add indirect co-actor
                                }
                            }
                        }
                    }
                }
            }
        }

        // Display results
        cout << "Actors known by \"" << actor->getName() << "\":" << endl;
        cout << "Direct Co-Actors:" << endl;
        for (int i = 0; i < directCoActors.getLength(); i++) {
            cout << "- " << directCoActors.get(i) << endl;
        }
        cout << "Indirect Co-Actors:" << endl;
        for (int i = 0; i < indirectCoActors.getLength(); i++) {
            cout << "- " << indirectCoActors.get(i) << endl;
        }
    }
}



// ADVANCED

void displayActorRatings(Dictionary<Actor>& actorTable) {
    int id;

    while (true) {
        id = -1;
        cout << endl;
        cout << "ACTOR LIST" << endl << "----------" << endl;
        actorTable.print();
        cout << "0. Return to menu" << endl << endl;
        cout << "Select actor (Enter actor ID): ";
        cin >> id;

        if (cin.fail()) {
            // Handle invalid input
            cin.clear();               // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (id == 0) return;

        cout << endl;

        Actor* actor = actorTable.get(id);

        if (actor != nullptr) {
            cout << actor->getName() << endl;
            actor->displayRatings();
            cout << endl;
        }
        else {
            cout << "Invalid ID. Please try again." << endl;
        }
    }
}

void displayMovieRatings(Dictionary<Movie>& movieTable) {
    int id;

    while (true) {
        id = -1;
        cout << endl;
        cout << "MOVIE LIST" << endl << "----------" << endl;
        movieTable.print();
        cout << "0. Return to menu" << endl << endl;
        cout << "Select movie (Enter movie ID): ";
        cin >> id;

        if (cin.fail()) {
            // Handle invalid input
            cin.clear();               // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (id == 0) return;

        cout << endl;

        Movie* movie = movieTable.get(id);

        if (movie != nullptr) {
            cout << movie->getTitle() << endl;
            movie->displayRatings();
            cout << endl;
        }
        else {
            cout << "Invalid ID. Please try again." << endl;
        }
    }
}

void rateActor(Dictionary<Actor>& actorTable) {
    int id;

    while (true) {
        id = -1;
        cout << endl;
        cout << "ACTOR LIST" << endl << "----------" << endl;
        actorTable.print();
        cout << "0. Return to menu" << endl << endl;
        cout << "Select actor (Enter actor ID): ";
        cin >> id;

        if (cin.fail()) {
            // Handle invalid input
            cin.clear();               // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (id == 0) return;

        cout << endl;

        Actor* actor = actorTable.get(id);

        if (actor != nullptr) {
            float rating;
            while (true) {
                rating = -1;
                cout << "Enter a rating between 1-5 (or 0 to return to actor select): ";
                cin >> rating;

                if (cin.fail()) {
                    // Handle invalid input
                    cin.clear();               // Clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl << "Invalid rating. Please try again." << endl << endl;
                    continue;
                }

                if (rating == 0) break;

                if (rating < 1 || rating > 5) {
                    cout << endl << "Invalid rating. Please enter a number between 1-5." << endl << endl;
                    continue;
                }

                actor->addRating(rating);
                updateActorRatingsCSV(actorTable);
                return;
            }
        }
        else {
            cout << "Invalid ID. Please try again." << endl;
        }
    }
}

void rateMovie(Dictionary<Movie>& movieTable) {
    int id;

    while (true) {
        id = -1;
        cout << endl;
        cout << "MOVIE LIST" << endl << "----------" << endl;
        movieTable.print();
        cout << "0. Return to menu" << endl << endl;
        cout << "Select movie (Enter movie ID): ";
        cin >> id;

        if (cin.fail()) {
            // Handle invalid input
            cin.clear();               // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid ID. Please try again." << endl;
            continue;
        }

        if (id == 0) return;

        cout << endl;

        Movie* movie = movieTable.get(id);

        if (movie != nullptr) {
            float rating;
            while (true) {
                rating = -1;
                cout << "Enter a rating between 1-5 (or 0 to return to movie select): ";
                cin >> rating;

                if (cin.fail()) {
                    // Handle invalid input
                    cin.clear();               // Clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl << "Invalid rating. Please try again." << endl << endl;
                    continue;
                }

                if (rating == 0) break;

                if (rating < 1 || rating > 5) {
                    cout << endl << "Invalid rating. Please enter a number between 1-5." << endl << endl;
                    continue;
                }

                movie->addRating(rating);
                updateMovieRatingsCSV(movieTable);
                return;
            }
        }
        else {

            cout << "Invalid ID. Please try again." << endl;
        }
    }
}

// movies by minimum rating
void insertionSortMovies(Movie* arr[], int n) {
    for (int i = 1; i < n; i++) {
        Movie* key = arr[i];
        int j = i - 1;

        // Sort in descending order of rating
        while (j >= 0 && arr[j]->getAverageRating() < key->getAverageRating()) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void displayMoviesByMinimumRating(const Dictionary<Movie>& movieTable) {
    while (true) {
        float minRating;

        // Input validation for minimum rating
        while (true) {
            cout << "Enter the minimum rating (1-5, or 0 to exit): ";
            cin >> minRating;

            if (cin.fail() || minRating < 0 || minRating > 5) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid rating. Please enter a number between 1 and 5, or 0 to exit." << endl;
                continue;
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
            if (movie->getAverageRating() >= minRating) {
                movieArr[index++] = movie;
            }
        }

        if (index > 0) {
            // Sort movies by rating using Insertion Sort
            insertionSortMovies(movieArr, index);

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

// actors by minimum rating
void insertionSortActors(Actor* arr[], int n) {
    for (int i = 1; i < n; i++) {
        Actor* key = arr[i];
        int j = i - 1;

        // Sort in descending order of rating
        while (j >= 0 && arr[j]->getAverageRating() < key->getAverageRating()) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void displayActorsByMinimumRating(const Dictionary<Actor>& actorTable) {
    while (true) {
        float minRating;

        // Input validation for minimum rating
        while (true) {
            cout << "Enter the minimum rating (1-5, or 0 to exit): ";
            cin >> minRating;

            if (cin.fail() || minRating < 0 || minRating > 5) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid rating. Please enter a number between 1 and 5, or 0 to exit." << endl;
                continue;
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
            if (actor->getAverageRating() >= minRating) {
                actorArr[index++] = actor;
            }
        }

        if (index > 0) {
            // Sort actors by rating using Insertion Sort
            insertionSortActors(actorArr, index);

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

// Parse actor ratings
void parseActorRatings(const string& filename, Dictionary<Actor>& actorTable) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int actorID;
        float rating;
        ss >> actorID;
        ss.ignore();
        ss >> rating;

        Actor* actor = actorTable.get(actorID);

        if (actor) {
            actor->addRating(rating);
        }
    }
    file.close();
}

// Parse movie ratings
void parseMovieRatings(const string& filename, Dictionary<Movie>& movieTable) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int movieID;
        float rating;
        ss >> movieID;
        ss.ignore();
        ss >> rating;

        Movie* movie = movieTable.get(movieID);

        if (movie) {
            movie->addRating(rating);
        }
    }
    file.close();
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