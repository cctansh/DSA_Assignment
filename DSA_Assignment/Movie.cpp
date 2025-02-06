/*
DSA T02
Group 7
Tan Si Huei Chloe S10260078
Ng Joe Yi S10262850
*/
#include "Movie.h"

// Constructor to initialize movie with id, title, plot, and release year
Movie::Movie(int id, const string& title, const string& plot, int year)
    : id(id), title(title), plot(plot), year(year) {}

// Sets the ID of the movie
void Movie::setId(int Id) {
    id = Id;
}

// Gets the ID of the movie
int Movie::getId() const {
    return id;
}

// Sets the title of the movie
void Movie::setTitle(const string& newTitle) {
    title = newTitle;
}

// Gets the title of the movie
string Movie::getTitle() const {
    return title;
}

// Sets the plot of the movie
void Movie::setPlot(const string& newPlot) {
    plot = newPlot;
}

// Gets the plot of the movie
string Movie::getPlot() const {
    return plot;
}

// Sets the release year of the movie
void Movie::setYear(int newYear) {
    year = newYear;
}

// Gets the release year of the movie
int Movie::getYear() const {
    return year;
}

// Adds an actor ID to the movie's list of actors
void Movie::addActor(int actorID) {
    actors.add(actorID);
}

// Returns the list of actors in the movie
const List<int>& Movie::getActors() const {
    return actors;
}

// Adds a rating to the movie's list of ratings
void Movie::addRating(float rating) {
    ratings.add(rating);
}

// Returns the list of ratings for the movie
const List<float>& Movie::getRatings() const {
    return ratings;
}

// Calculates and returns the average rating of the movie
float Movie::getAverageRating() const {
    if (!ratings.isEmpty()) {
        float total = 0;
        for (int i = 0; i < ratings.getLength(); ++i)
            total += ratings.get(i);  // Sum all ratings
        float average = total / ratings.getLength();  // Calculate average
        return round(average * 10) / 10;  // Round to 1 decimal place
    }
    return 0;  // Return 0 if no ratings
}

// Displays all ratings for the movie
void Movie::displayRatings() {
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

// Prints the movie's title, release year, and average rating
void Movie::print() {
    cout << setw(20) << left << title << " | "  // Align title to the left
        << setw(4) << year << " | "            // Display release year
        << setw(4) << fixed << setprecision(1) << getAverageRating() << "/5"
        << endl;
}

// Prints full details of the movie including plot
void Movie::printFullDetails() {
    cout << setw(20) << left << title << " | "  // Align title to the left
        << setw(4) << year << " | "            // Display release year
        << setw(4) << fixed << setprecision(1) << getAverageRating() << "/5"
        << endl
        << plot  // Display movie plot
        << endl;
}

// Sorts movie titles alphabetically using Insertion Sort
void Movie::insertionSortTitles(string arr[], int n) {
    for (int i = 1; i < n; i++) {
        string key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  // Shift larger titles to the right
            j--;
        }
        arr[j + 1] = key;  // Insert key at the correct position
    }
}

// Sorts movies by release year using Merge Sort
void Movie::mergeSortByYear(Movie* arr[], int left, int right) {
    if (left >= right) return;  // Base case: single element

    int mid = left + (right - left) / 2;

    // Recursive calls to sort the left and right halves
    mergeSortByYear(arr, left, mid);
    mergeSortByYear(arr, mid + 1, right);

    // Merge the two sorted halves
    int size = right - left + 1;
    Movie** temp = new Movie * [size];  // Temporary array for merging
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i]->getYear() <= arr[j]->getYear()) {
            temp[k++] = arr[i++];  // Add movie with earlier release year first
        }
        else {
            temp[k++] = arr[j++];  // Add movie with later release year first
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

// Sorts movies by rating in descending order using Merge Sort
void Movie::sortMoviesByRatingDescending(Movie* arr[], int left, int right) {
    if (left >= right) return;  // Base case: single element

    int mid = left + (right - left) / 2;

    // Recursive calls to sort the left and right halves
    sortMoviesByRatingDescending(arr, left, mid);
    sortMoviesByRatingDescending(arr, mid + 1, right);

    // Merge the two sorted halves
    int size = right - left + 1;
    Movie** temp = new Movie * [size];  // Temporary array for merging
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i]->getAverageRating() >= arr[j]->getAverageRating()) {
            temp[k++] = arr[i++];  // Add movie with higher rating first
        }
        else {
            temp[k++] = arr[j++];  // Add movie with lower rating next
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
