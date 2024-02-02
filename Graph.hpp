//
//  Graph.hpp
//  PR-5
//
//  Created by Marcus Shaw on 12/9/23.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
// most if not all the functions are from the chapter 11 zybooks graph class. I am writing before completing the code fully so I may need to add more functions here I am unsure

using namespace std;
class Vertex { // this class is used by the graph class to make vector labels
public:
    int label;
    
    Vertex(const int& vertexLabel); //this is to assign the label to the vertex
};
class Edge { // this is to keep track of the edges to the vertex. The weights will be 1 for each as they are unweughted
public:
    Vertex* fromVertex;
    Vertex* toVertex;
    double weight;
    
    Edge(Vertex* from, Vertex* to, double edgeWeight = 1); // this is to set the edges of the vertex
};
class Graph {
private:
    unordered_map<Vertex*, vector<Edge*>*> fromEdges; // this is a map of all the edges that come from a vertex
    unordered_map<Vertex*, vector<Edge*>*> toEdges; // this is a map of all the edges that go to a vertex
public:
    const vector<Edge*>* GetEdgesFrom(Vertex* fromVertex) const; // this returns the edges that come FROM a vertex in a vector
    const vector<Edge*>* GetEdgesTo(Vertex* toVertex) const; // this returns the edges that go TO a specificed vertex in the form a vector
    
    Vertex* GetVertex(const int& vertexLabel); // this returns the vectors label or a null ptr if it does not exist
    vector<Vertex*> GetVetices() const; 
    virtual ~Graph(); // this is used to delete the maps
    
    Vertex* AddVertex(const int& vertexLabel); // this is to add a new vertex to the map
    
    Edge* AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex, double weight = 1); // this is to add a directed edge to a vertex
    bool HasEdge(Vertex* fromVertex, Vertex* toVertex); // this is to say if the edge already exists 
    
    
    
    
    
    
};

#endif /* Graph_hpp */
