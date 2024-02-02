//
//  Graph.cpp
//  PR-5
//
//  Created by Marcus Shaw on 12/9/23.
//

#include "Graph.hpp"
using namespace std;

Vertex::Vertex(const int& vertexLabel) {
    label = vertexLabel;
}

Edge::Edge(Vertex* from, Vertex* to, double edgeWeight){
    fromVertex = from;
    toVertex = to;
    weight = edgeWeight;
}

const vector<Edge*>* Graph::GetEdgesFrom(Vertex *fromVertex) const {
    return fromEdges.at(fromVertex);
}
const vector<Edge*>* Graph::GetEdgesTo(Vertex *toVertex) const {
    return toEdges.at(toVertex);
}

Vertex* Graph::GetVertex(const int &vertexLabel) {
    for(auto& keyvalue : fromEdges) {
        Vertex* vertex = keyvalue.first;
        if(vertex->label == vertexLabel) {
            return keyvalue.first;
        }
    }
    return nullptr;
}
vector<Vertex*> Graph::GetVetices() const {
    vector<Vertex*> vertices;
    for(auto& keyValue : fromEdges) {
        vertices.push_back(keyValue.first);
    }
    return vertices;
}
Graph::~Graph() { // destructing the graph maps
    unordered_set<Vertex*> distinctVertices;
    unordered_set<Edge*> distinctEdges;
    
    for(auto& keyvalue : fromEdges) {
        distinctVertices.insert(keyvalue.first);
        for(Edge* edge : *keyvalue.second) {
            distinctEdges.insert(edge);
        }
        
        delete keyvalue.second;
    }
    fromEdges.clear();
    toEdges.clear();
    
    for(Edge* edge : distinctEdges) {
        delete edge;
    }
    for(Vertex* vertex : distinctVertices) {
        delete vertex;
    }
    
}

Vertex* Graph::AddVertex(const int &vertexLabel) {
    Vertex* vertex = new Vertex(vertexLabel);
    
    fromEdges[vertex] = new vector<Edge*>();
    toEdges[vertex] = new vector<Edge*>();
    
    return vertex;
}

Edge* Graph::AddDirectedEdge(Vertex *fromVertex, Vertex *toVertex, double weight ) {
    if(HasEdge(fromVertex, toVertex)) {
        return nullptr;
    }
    Edge* edge = new Edge(fromVertex, toVertex, weight);
    
    fromEdges[fromVertex]->push_back(edge);
    toEdges[toVertex]->push_back(edge);
    
    return edge;
}

bool Graph::HasEdge(Vertex *fromVertex, Vertex *toVertex) {
    if ( 0 == fromEdges.count(fromVertex)) {
        return false;
    }
    
    vector<Edge*>& edges = *fromEdges.at(fromVertex);
    for (Edge* edge : edges) {
        if(edge->toVertex == toVertex) {
            return true;
        }
    }
    return false;
}
