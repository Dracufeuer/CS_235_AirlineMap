//
//  airline.hpp
//  PR-5
//
//  Created by Marcus Shaw on 12/10/23.
//

#ifndef airline_hpp
#define airline_hpp

#include <stdio.h>

#include "Graph.hpp"
#include <fstream>
class PathVertexInfo {
public:
    Vertex* vertex; // this holds the vertex
    double distance; // this holds the distance of the path
    Vertex* predecessor; // this holds information of the previous vertex visited
    
    PathVertexInfo(Vertex* vertex = nullptr); // default constructor
    static PathVertexInfo* RemoveMid(vector<PathVertexInfo*>& items); // this is to remove and return the PathVertexInfo that has the min distance
    
};
class airline {
private:
    Graph airlineMap;
    vector <string> cities;
public:
    void getShortestPath(Vertex* startVertex, Vertex* endVertex, unordered_map<Vertex*, PathVertexInfo*> infoMap); // this finds the shortest path and output it
    bool input(string fName); // this takes in the file name to get the input information
    void ShortestPath(int start, int end);
};


#endif /* airline_hpp */
