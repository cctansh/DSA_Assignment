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
        actorToMovies.add(actorID, movies); // Store movies the actor has starred in
    }
    movies->add(movieID);  // Add the movie to the actor's list

    // Retrieve the movie's current list of actors
    List<int>* actors = movieToActors.get(movieID);
    if (!actors) {
        // If no actor list exists, create a new one
        actors = new List<int>();
        movieToActors.add(movieID, actors); // Store actors in the movie
    }
    actors->add(actorID);  // Add the actor to the movie's list
}

// Build the graph from the actor data in actorTable
void Graph::buildGraph(Dictionary<Actor>& actorTable) {
    List<KeyValue<int, Actor>> allActors = actorTable.getAllItemsWithKeys();  // Get all actors from the dictionary

    for (int i = 0; i < allActors.getLength(); i++) {
        Actor* actor = allActors.get(i).value;  // Retrieve actor object
        int actorID = actor->getId();  // Get actor ID

        const List<int>& movies = actor->getMovies();  // Get list of movies the actor has participated in
        for (int j = 0; j < movies.getLength(); j++) {
            int movieID = movies.get(j);
            addActorMovieEdge(actorID, movieID);  // Create connections between actor and movies
        }
    }
}

// Find and display direct and indirect co-actors using BFS
void Graph::findCoActors(int actorID, Dictionary<Actor>& actorTable) {
    Actor* startActor = actorTable.get(actorID);  // Retrieve the starting actor from the dictionary
    if (!startActor) {
        cout << "Invalid Actor ID." << endl;
        return;
    }

    bool visitedActors[MAX_ACTORS] = { false };  // Track visited actors
    bool visitedMovies[MAX_MOVIES] = { false };  // Track visited movies

    List<string> directCoActors;    // List to store direct co-actors
    List<string> indirectCoActors;  // List to store indirect co-actors

    // Dynamic allocation to avoid stack overflow for large datasets
    int* queue = new int[2 * MAX_ACTORS];       // Queue for BFS traversal
    int* levelQueue = new int[2 * MAX_ACTORS];  // Queue to track levels in BFS
    int front = 0, rear = 0;  // Initialize queue pointers

    // Initialize BFS with the starting actor
    queue[rear] = actorID;         // Enqueue the starting actor
    levelQueue[rear] = 0;          // Level 0 for the starting actor
    rear++;
    visitedActors[actorID % MAX_ACTORS] = true;  // Mark the starting actor as visited

    while (front < rear) {
        int currentActorID = queue[front];  // Get the current actor ID from the queue
        int level = levelQueue[front];      // Get the level of the current actor
        front++;

        // Retrieve the list of movies for the current actor
        List<int>* movieIDs = actorToMovies.get(currentActorID);
        if (!movieIDs) continue;  // Skip if no movies are found

        for (int i = 0; i < movieIDs->getLength(); i++) {
            int movieID = movieIDs->get(i);

            if (visitedMovies[movieID % MAX_MOVIES]) continue;  // Skip if the movie has already been visited
            visitedMovies[movieID % MAX_MOVIES] = true;  // Mark the movie as visited

            // Retrieve the list of actors in this movie
            List<int>* coActorIDs = movieToActors.get(movieID);
            if (!coActorIDs) continue;  // Skip if no actors are found

            for (int j = 0; j < coActorIDs->getLength(); j++) {
                int coActorID = coActorIDs->get(j);

                if (coActorID == actorID || visitedActors[coActorID % MAX_ACTORS]) continue;  // Skip if co-actor is the starting actor or already visited

                Actor* coActor = actorTable.get(coActorID);  // Retrieve co-actor from the dictionary
                if (coActor) {
                    if (level == 0 && !directCoActors.contains(coActor->getName())) {
                        directCoActors.add(coActor->getName());  // Add to direct co-actors if on level 0
                    }
                    else if (level == 1 &&
                        !directCoActors.contains(coActor->getName()) &&
                        !indirectCoActors.contains(coActor->getName())) {
                        indirectCoActors.add(coActor->getName());  // Add to indirect co-actors if on level 1
                    }

                    // Mark co-actor as visited and enqueue
                    visitedActors[coActorID % MAX_ACTORS] = true;
                    queue[rear] = coActorID;       // Enqueue co-actor
                    levelQueue[rear] = level + 1;  // Increment level
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
            cout << "- " << directCoActors.get(i) << endl;  // Display direct co-actors
        }
    }

    cout << "Indirect Co-Actors:" << endl;
    if (indirectCoActors.isEmpty()) {
        cout << "No indirect co-actors found." << endl;
    }
    else {
        for (int i = 0; i < indirectCoActors.getLength(); i++) {
            cout << "- " << indirectCoActors.get(i) << endl;  // Display indirect co-actors
        }
    }
}