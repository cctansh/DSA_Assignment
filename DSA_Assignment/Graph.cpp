#include "Graph.h"
#include <iostream>
using namespace std;

// Constructor
Graph::Graph() {
    // No special initialization needed since Dictionary handles its own setup
}

// Add connection between actor and movie
void Graph::addActorMovieEdge(int actorID, int movieID) {
    // Retrieve the actor's current list of movies
    List<int>* movies = actorToMovies.get(actorID);
    if (!movies) {
        // If no movie list exists, create a new one
        movies = new List<int>();
        actorToMovies.add(actorID, movies); // Movies actor has starred in
    }
    movies->add(movieID);

    // Retrieve the movie's current list of actors
    List<int>* actors = movieToActors.get(movieID);
    if (!actors) {
        // If no actor list exists, create a new one
        actors = new List<int>();
        movieToActors.add(movieID, actors);
    }
    actors->add(actorID);
}

// Build the graph from the actor data in actorTable
void Graph::buildGraph(Dictionary<Actor>& actorTable) {
    List<KeyValue<int, Actor>> allActors = actorTable.getAllItemsWithKeys();

    for (int i = 0; i < allActors.getLength(); i++) {
        Actor* actor = allActors.get(i).value;
        int actorID = actor->getId();

        const List<int>& movies = actor->getMovies();
        for (int j = 0; j < movies.getLength(); j++) {
            int movieID = movies.get(j);
            addActorMovieEdge(actorID, movieID);  // Create connections in the graph
        }
    }
}

// Find and display direct and indirect co-actors using BFS
void Graph::findCoActors(int actorID, Dictionary<Actor>& actorTable) {
    Actor* startActor = actorTable.get(actorID);
    if (!startActor) {
        cout << "Invalid Actor ID." << endl;
        return;
    }

    bool visitedActors[MAX_ACTORS] = { false };
    bool visitedMovies[MAX_MOVIES] = { false };

    List<string> directCoActors;
    List<string> indirectCoActors;

    // Dynamic allocation to avoid stack overflow for large datasets
    int* queue = new int[2 * MAX_ACTORS];
    int* levelQueue = new int[2 * MAX_ACTORS];
    int front = 0, rear = 0;

    // Initialize BFS with the starting actor
    queue[rear] = actorID;
    levelQueue[rear] = 0;
    rear++;
    visitedActors[actorID % MAX_ACTORS] = true;

    while (front < rear) {
        int currentActorID = queue[front];
        int level = levelQueue[front];
        front++;

        // Retrieve the list of movies for the current actor
        List<int>* movieIDs = actorToMovies.get(currentActorID);
        if (!movieIDs) continue;

        for (int i = 0; i < movieIDs->getLength(); i++) {
            int movieID = movieIDs->get(i);

            if (visitedMovies[movieID % MAX_MOVIES]) continue;
            visitedMovies[movieID % MAX_MOVIES] = true;

            // Retrieve the list of actors in this movie
            List<int>* coActorIDs = movieToActors.get(movieID);
            if (!coActorIDs) continue;

            for (int j = 0; j < coActorIDs->getLength(); j++) {
                int coActorID = coActorIDs->get(j);

                if (coActorID == actorID || visitedActors[coActorID % MAX_ACTORS]) continue;

                Actor* coActor = actorTable.get(coActorID);
                if (coActor) {
                    if (level == 0 && !directCoActors.contains(coActor->getName())) {
                        directCoActors.add(coActor->getName());
                    }
                    else if (level == 1 &&
                        !directCoActors.contains(coActor->getName()) &&
                        !indirectCoActors.contains(coActor->getName())) {
                        indirectCoActors.add(coActor->getName());
                    }

                    // Mark co-actor as visited and enqueue
                    visitedActors[coActorID % MAX_ACTORS] = true;
                    queue[rear] = coActorID;
                    levelQueue[rear] = level + 1;
                    rear++;
                }
            }
        }
    }

    // Clean up dynamically allocated memory
    delete[] queue;
    delete[] levelQueue;

    // Display Results
    cout << "\nActors known by \"" << startActor->getName() << "\":" << endl;

    cout << "Direct Co-Actors:" << endl;
    if (directCoActors.isEmpty()) {
        cout << "No direct co-actors found." << endl;
    }
    else {
        for (int i = 0; i < directCoActors.getLength(); i++) {
            cout << "- " << directCoActors.get(i) << endl;
        }
    }

    cout << "Indirect Co-Actors:" << endl;
    if (indirectCoActors.isEmpty()) {
        cout << "No indirect co-actors found." << endl;
    }
    else {
        for (int i = 0; i < indirectCoActors.getLength(); i++) {
            cout << "- " << indirectCoActors.get(i) << endl;
        }
    }
}
