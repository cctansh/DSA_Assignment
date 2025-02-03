#pragma once
#include "list.h"
#include "Dictionary.h"
#include <string>

const int MAX_ACTORS = 17000;
const int MAX_MOVIES = 17000;

class Graph {
private:
    Dictionary<List<int>> actorToMovies;  // Actor ID -> List of Movie IDs
    Dictionary<List<int>> movieToActors;  // Movie ID -> List of Actor IDs

public:
    // Constructor
    Graph();

    // Add connections between actor and movie
    void addActorMovieEdge(int actorID, int movieID);

    // Build the graph from actor data
    void buildGraph(Dictionary<Actor>& actorTable);

    // Find and display direct and indirect co-actors
    void findCoActors(int actorID, Dictionary<Actor>& actorTable);
};
