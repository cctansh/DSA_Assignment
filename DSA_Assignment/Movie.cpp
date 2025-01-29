#include "Movie.h"
Movie::Movie(const string& title, const string& plot, int year)
    : title(title), plot(plot), year(year) {}

void Movie::setTitle(const string& newTitle) {
    title = newTitle;
}

string Movie::getTitle() const {
    return title;
}

void Movie::setPlot(const string& newPlot) {
    plot = newPlot;
}

string Movie::getPlot() const {
    return plot;
}

void Movie::setYear(int newYear) {
    year = newYear;
}

int Movie::getYear() const {
    return year;
}

void Movie::addActor(int actorID) {
    actors.add(actorID);
}

const List<int>& Movie::getActors() const {
    return actors;
}

void Movie::addRating(float rating) {
    ratings.add(rating);
}

const List<float>& Movie::getRatings() const {
    return ratings;
}

float Movie::getAverageRating() const {
    if (!ratings.isEmpty()) {
        float total = 0;
        for (int i = 0; i < ratings.getLength(); ++i)
            total += ratings.get(i);
        float average = total / ratings.getLength();
        return round(average * 10) / 10;
    }
    return 0;
}

void Movie::displayRatings() {
    if (!ratings.isEmpty()) {
        cout << "Ratings: ";
        for (int i = 0; i < ratings.getLength(); ++i) {
            cout << ratings.get(i);
            if (i < ratings.getLength() - 1)
                cout << ", ";
        }

    }
    else {
        cout << "No ratings found.";
    }

}

void Movie::print() {

    cout << setw(20) << left << title << " | "
        << setw(4) << year << " | "
        << setw(4) << fixed << setprecision(1) << getAverageRating() << "/5"
        << endl;
}

void Movie::printFullDetails() {
    cout << setw(20) << left << title << " | "
        << setw(4) << year << " | "
        << setw(4) << fixed << setprecision(1) << getAverageRating() << "/5"
        << endl
        << plot
        << endl;
}

// Sort movie titles alphabetically using Insertion Sort
void Movie::insertionSortTitles(string arr[], int n) {
    for (int i = 1; i < n; i++) {
        string key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Sort movies by year using Merge Sort
void Movie::mergeSortByYear(Movie* arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Recursive calls to sort the left and right halves
    mergeSortByYear(arr, left, mid);
    mergeSortByYear(arr, mid + 1, right);

    // Merge the two sorted halves
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

// Sort movies by rating in descending order using Merge Sort
void Movie::sortMoviesByRatingDescending(Movie* arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Recursive calls to sort the left and right halves
    sortMoviesByRatingDescending(arr, left, mid);
    sortMoviesByRatingDescending(arr, mid + 1, right);

    // Merge the two sorted halves
    int size = right - left + 1;
    Movie** temp = new Movie * [size];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i]->getAverageRating() >= arr[j]->getAverageRating()) {
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
