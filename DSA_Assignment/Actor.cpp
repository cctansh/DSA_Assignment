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