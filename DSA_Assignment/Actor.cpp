#include "Actor.h"
Actor::Actor(string n, int y) {
	name = n;
	birthYear = y;
	movies = List();
}
void Actor::setName(string n) {
	name = n;
}
string Actor::getName() {
	return name;
}
void Actor::setBirthYear(int y) {
	birthYear = y;
}
int Actor::getBirthYear() {
	return birthYear;
}
void Actor::setMovies(List m) {
	movies = m;
}
List Actor::getMovies() {
	return movies;
}
void Actor::addMovie(int* movieId) {
	movies.add(movieId);
}
void Actor::print() {
	std::cout << name << ", " << birthYear << endl;
}