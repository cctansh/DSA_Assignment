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