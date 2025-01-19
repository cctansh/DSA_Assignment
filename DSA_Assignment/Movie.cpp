#include "Movie.h"
void Movie::setTitle(string t) {
	title = t;
}
string Movie::getTitle() {
	return title;
}
void Movie::setPlot(string p) {
	plot = p;
}
string Movie::getPlot() {
	return plot;
}
void Movie::setYear(int y) {
	year = y;
}
int Movie::getYear() {
	return year;
}
void Movie::setActors(List a) {
	actors = a;
}
List Movie::getActors() {
	return actors;
}
void Movie::print() {
	std::cout << title << ", " << year << endl;
}