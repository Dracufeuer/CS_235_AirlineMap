//
//  airline.cpp
//  PR-5
//
//  Created by Marcus Shaw on 12/10/23.
//

#include "airline.hpp"
#include "Graph.hpp"
#include <iostream>
using namespace std;
PathVertexInfo::PathVertexInfo(Vertex* vertex ) {
    this->vertex = vertex;
    distance = numeric_limits<double>::infinity();
    predecessor = nullptr;
}
PathVertexInfo* PathVertexInfo::RemoveMid(vector<PathVertexInfo*> &items) {
    if( 0 == items.size()) {
        return nullptr;
    }
    int minIndex = 0;
    for(int i = 1; i < items.size(); i++) {
        if(items[i]->distance < items[minIndex]->distance) {
            minIndex = 1;
        }
    }
    PathVertexInfo* infoWithMinDistance = items[minIndex];
    
    items.erase(items.begin() + minIndex);
    return infoWithMinDistance;
}
bool airline::input(string fName) {
    ifstream fin;
    ofstream fout;
    string inString;
    int inInt, count=0, iter =0; // This is the input for in, the counter for the for loop and to keep track of the iterations of the while loop
    fin.open(fName);
    
    if(fin.fail()) {
        cout << "Cannot open " << fName << '\n';
        exit(1);
        return false;
    }
    getline(fin, inString);
    
    
    while(!fin.eof()) { // this is to get the input from the file and store it into the object
        
        cities.push_back(inString);
        iter++;
        if(airlineMap.GetVertex(iter) == nullptr) { // this is to see if the vertex already exists before creating it as the for loop creates vertices as well
            airlineMap.AddVertex(iter);
        }
        
        
        fin >> inInt;
        
        count = inInt;
        for(int i = 0; i < count; i++) {
            fin >> inInt;
            
            if(airlineMap.GetVertex(inInt) != nullptr) {
                airlineMap.AddDirectedEdge(airlineMap.GetVertex(iter), airlineMap.GetVertex(inInt));
               
            }
            else{
                airlineMap.AddVertex(inInt);
                airlineMap.AddDirectedEdge(airlineMap.GetVertex(iter), airlineMap.GetVertex(inInt));
               
            }
            
        }
        getline(fin, inString);
        getline(fin, inString);
        inInt = 0;
        count = 0;
    }
    cout << "Representation: " << '\n';
    
    for(int i = 0; i < cities.size(); i++) { // this is the representation of the data that was input
        cout << i+1 << ": " << cities.at(i) << "--";
        for( int k = 0; k < airlineMap.GetEdgesFrom(airlineMap.GetVertex(i+1))->size(); k++) {
            cout << airlineMap.GetEdgesFrom(airlineMap.GetVertex(i+1))->at(k)->toVertex->label << " ";
        }
        
        cout << '\n';
    }
     
    fin.close();
    return true;
}
void airline::ShortestPath(int start, int end) {
    unordered_map<Vertex*, PathVertexInfo*> info;
    Vertex* startVertex = airlineMap.GetVertex(start);
    Vertex* endVertex = airlineMap.GetVertex(end);
    vector<PathVertexInfo*> unvisited;
    for ( Vertex* vertex : airlineMap.GetVetices()) {
        PathVertexInfo* vertexInfo = new PathVertexInfo(vertex);
        unvisited.push_back(vertexInfo);
        info[vertex] = vertexInfo;
    }
    
    info[startVertex]->distance = 0.0;
    
    while(unvisited.size() > 0)  {
        PathVertexInfo* currentInfo =PathVertexInfo::RemoveMid(unvisited);
        
        for(Edge* edge : *airlineMap.GetEdgesFrom(currentInfo->vertex)) {
            Vertex* adjacentVertex = edge->toVertex;
            double alternativePathDistance = currentInfo->distance + edge->weight;
            
            PathVertexInfo* adjacentInfo = info[adjacentVertex];
            if (alternativePathDistance < adjacentInfo->distance) {
                adjacentInfo->distance = alternativePathDistance;
                adjacentInfo->predecessor = currentInfo->vertex;
            }
        }
        
    }
    getShortestPath(startVertex, endVertex, info);
}

void airline::getShortestPath(Vertex *startVertex, Vertex *endVertex, unordered_map<Vertex *, PathVertexInfo *> infoMap) {
    Vertex* currentVertex = endVertex;
    vector<int> v1;
    while (currentVertex != startVertex) {
        v1.push_back(currentVertex->label);
        currentVertex = infoMap[currentVertex]->predecessor;    
    }
    v1.push_back(startVertex->label);
    for(int i = v1.size()- 1; 0 < i; i--) {
        cout << v1.at(i) << " " << cities.at(v1.at(i) - 1)<< '\n' << "   |" << '\n' << "   v" << '\n';
    }
    cout << v1.at(0) << " " << cities.at(v1.at(0) - 1) << '\n';
}
