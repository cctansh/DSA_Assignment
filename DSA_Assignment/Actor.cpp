#include "Actor.h"

Actor::Actor(const string& name, int birthYear) : name(name), birthYear(birthYear) {}

void Actor::setName(const string& newName) {
    name = newName;
}

string Actor::getName() const {
    return name;
}

void Actor::setBirthYear(int year) {
    birthYear = year;
}

int Actor::getBirthYear() const {
    return birthYear;
}

void Actor::addMovie(int movieID) {
    movies.add(movieID);
}

const List<int>& Actor::getMovies() const {
    return movies;
}

void Actor::addRating(float rating) {
    ratings.add(rating);
}

const List<float>& Actor::getRatings() const {
    return ratings;
}

float Actor::getAverageRating() const {
    if (!ratings.isEmpty()) {
        float total = 0;
        for (int i = 0; i < ratings.getLength(); ++i)
            total += ratings.get(i);
        float average = total / ratings.getLength();
        return round(average * 10) / 10; 
    }
    return 0;
}

void Actor::displayRatings() {
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

void Actor::print() {
    cout << setw(20) << left << name << " | "
        << setw(4) << birthYear << " | "
        << setw(4) << fixed << setprecision(1) << getAverageRating() << "/5"
        << endl;
}

// Sort actor names alphabetically using Insertion Sort
void Actor::insertionSortNames(string arr[], int n) {
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

// Sort actors by age using Merge Sort
void Actor::mergeSortByAge(Actor* arr[], int left, int right, int currentYear) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Recursive calls to sort the left and right halves
    mergeSortByAge(arr, left, mid, currentYear);
    mergeSortByAge(arr, mid + 1, right, currentYear);

    // Merge the two sorted halves
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

// Sort actors by rating in descending order using Merge Sort
void Actor::sortActorsByRatingDescending(Actor* arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Recursive calls to sort the left and right halves
    sortActorsByRatingDescending(arr, left, mid);
    sortActorsByRatingDescending(arr, mid + 1, right);

    // Merge the two sorted halves
    int size = right - left + 1;
    Actor** temp = new Actor * [size];
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
