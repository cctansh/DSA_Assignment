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

void Actor::print() {
	cout << name << ", " << birthYear << endl;
}