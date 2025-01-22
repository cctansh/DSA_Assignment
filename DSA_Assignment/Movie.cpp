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

void Movie::print() {
	cout << title << ", " << year << endl;
}

bool Movie::operator<(const Movie& other) const {
    return year < other.year; // Sort by ascending release year
}