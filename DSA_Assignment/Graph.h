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

	// Adds a connection between an actor and a movie
	// Parameters: int actorID - actor's ID, int movieID - movie's ID
	// Pre : actorID and movieID should be valid
	// Post: actorID is linked to movieID and vice versa in the graph
	void addActorMovieEdge(int actorID, int movieID);

	// Builds the graph using actor data from a dictionary
	// Parameter: Dictionary<Actor>& actorTable - dictionary of actors
	// Pre : actorTable should be initialized with actor data
	// Post: Graph is populated with actor-movie connections
	void buildGraph(Dictionary<Actor>& actorTable);

	// Finds and displays direct and indirect co-actors of a given actor
	// Parameters: int actorID - actor's ID, Dictionary<Actor>& actorTable - dictionary of actors
	// Pre : actorID should exist in actorTable
	// Post: Co-actors are displayed
	void findCoActors(int actorID, Dictionary<Actor>& actorTable);
};
