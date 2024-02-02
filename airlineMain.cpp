//
//  airlineMain.cpp
//  PR-5
//  Class: CS 236
//  Semester: Fall 2023
//  Name: Marcus Shaw
//  Created by Marcus Shaw on 12/9/23.
//

#include <iostream>
#include "airline.hpp"
#include "Graph.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
    string userData;
    int x,y; // this is for the starting and ending index
    char check = 'y'; // this is to check if the user wants to continue
    airline a;
    cout << "Enter Name of Network File: ";
    getline(cin, userData);
    a.input(userData);
    while( check == 'Y' || check == 'y') {
        cout << '\n' << "Number of Start City: ";
        cin >> x;
        cout << '\n' << "Number of Destination City: ";
        cin >> y;
        a.ShortestPath(x, y);
        cout << '\n'  << "More (Y or N)?";
        cin >> check;
    }
    return 0;
}
