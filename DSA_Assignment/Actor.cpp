/*
DSA T02
Group 7
Tan Si Huei Chloe S10260078
Ng Joe Yi S10262850
*/
#include "Actor.h"

// Constructor to initialize actor with id, name, and birth year
Actor::Actor(int id, const string& name, int birthYear) : id(id), name(name), birthYear(birthYear) {}

// Sets the ID of the actor
void Actor::setId(int Id) {
    id = Id;
}

// Gets the ID of the actor
int Actor::getId() const {
    return id;
}

// Sets the name of the actor
void Actor::setName(const string& newName) {
    name = newName;
}

// Gets the name of the actor
string Actor::getName() const {
    return name;
}

// Sets the birth year of the actor
void Actor::setBirthYear(int year) {
    birthYear = year;
}

// Gets the birth year of the actor
int Actor::getBirthYear() const {
    return birthYear;
}

// Adds a movie ID to the actor's list of movies
void Actor::addMovie(int movieID) {
    movies.add(movieID);
}

// Returns the list of movies the actor has participated in
const List<int>& Actor::getMovies() const {
    return movies;
}

// Adds a rating to the actor's list of ratings
void Actor::addRating(float rating) {
    ratings.add(rating);
}

// Returns the list of ratings for the actor
const List<float>& Actor::getRatings() const {
    return ratings;
}

// Calculates and returns the average rating of the actor
float Actor::getAverageRating() const {
    if (!ratings.isEmpty()) {
        float total = 0;
        for (int i = 0; i < ratings.getLength(); ++i)
            total += ratings.get(i);  // Sum all ratings
        float average = total / ratings.getLength();  // Calculate average
        return round(average * 10) / 10;  // Round to 1 decimal place
    }
    return 0;  // Return 0 if no ratings
}

// Displays all ratings for the actor
void Actor::displayRatings() {
    if (!ratings.isEmpty()) {
        cout << "Ratings: ";
        for (int i = 0; i < ratings.getLength(); ++i) {
            cout << ratings.get(i);
            if (i < ratings.getLength() - 1)
                cout << ", ";  // Add comma between ratings
        }
    }
    else {
        cout << "No ratings found.";  // Message if no ratings
    }
}

// Prints the actor's name, birth year, and average rating
void Actor::print() {
    cout << setw(20) << left << name << " | "  // Align name to the left
        << setw(4) << birthYear << " | "      // Display birth year
        << setw(4) << fixed << setprecision(1) << getAverageRating() << "/5"  // Display average rating
        << endl;
}

// Sorts actor names alphabetically using Insertion Sort
void Actor::insertionSortNames(string arr[], int n) {
    for (int i = 1; i < n; i++) {
        string key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  // Shift larger elements to the right
            j--;
        }
        arr[j + 1] = key;  // Insert key at the correct position
    }
}

// Sorts actors by age using Merge Sort
void Actor::mergeSortByAge(Actor* arr[], int left, int right, int currentYear) {
    if (left >= right) return;  // Base case: single element

    int mid = left + (right - left) / 2;

    // Recursive calls to sort the left and right halves
    mergeSortByAge(arr, left, mid, currentYear);
    mergeSortByAge(arr, mid + 1, right, currentYear);

    // Merge the two sorted halves
    int size = right - left + 1;
    Actor** temp = new Actor * [size];  // Temporary array for merging
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        int ageLeft = currentYear - arr[i]->getBirthYear();
        int ageRight = currentYear - arr[j]->getBirthYear();
        if (ageLeft <= ageRight) {
            temp[k++] = arr[i++];  // Add younger actor first
        }
        else {
            temp[k++] = arr[j++];  // Add older actor first
        }
    }

    // Copy remaining elements from left half
    while (i <= mid) temp[k++] = arr[i++];
    // Copy remaining elements from right half
    while (j <= right) temp[k++] = arr[j++];

    // Copy sorted elements back to original array
    for (int m = 0; m < size; m++) arr[left + m] = temp[m];

    delete[] temp;  // Free dynamically allocated memory
}

// Sorts actors by rating in descending order using Merge Sort
void Actor::sortActorsByRatingDescending(Actor* arr[], int left, int right) {
    if (left >= right) return;  // Base case: single element

    int mid = left + (right - left) / 2;

    // Recursive calls to sort the left and right halves
    sortActorsByRatingDescending(arr, left, mid);
    sortActorsByRatingDescending(arr, mid + 1, right);

    // Merge the two sorted halves
    int size = right - left + 1;
    Actor** temp = new Actor * [size];  // Temporary array for merging
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i]->getAverageRating() >= arr[j]->getAverageRating()) {
            temp[k++] = arr[i++];  // Add actor with higher rating first
        }
        else {
            temp[k++] = arr[j++];  // Add actor with lower rating next
        }
    }

    // Copy remaining elements from left half
    while (i <= mid) temp[k++] = arr[i++];
    // Copy remaining elements from right half
    while (j <= right) temp[k++] = arr[j++];

    // Copy sorted elements back to original array
    for (int m = 0; m < size; m++) arr[left + m] = temp[m];

    delete[] temp;  // Free dynamically allocated memory
}
