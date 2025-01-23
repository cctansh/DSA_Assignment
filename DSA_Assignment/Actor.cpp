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

bool Actor::operator<(const Actor& other) const {
    if (birthYear == other.birthYear) {
        return name < other.name; // Secondary sort by name
    }
    return birthYear < other.birthYear; // Primary sort by birth year
}
// Overload << operator
ostream& operator<<(ostream& os, const Actor& actor) {
    os << "Name: " << actor.name << ", Birth Year: " << actor.birthYear;
    return os;
}