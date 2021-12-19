//
//  HashTable.hpp
//  HashTable
//
//  Created by Ashraf AbdelRaouf on 12/4/19.
//  Copyright � 2019 Ashraf AbdelRaouf. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
//#include <iterator>
using namespace std;

const int TableSize = 11;
const int DoubleHashVal = 7;
class HTable
{
private:
    class Node {
    public:
        int key;
        string ID; // Student ID
        string value; // Student name
        Node(int K = -1, string id = "", string val = "") {
            key = K; ID = id; value = val;
        }
    };

    int numberOfElements;
    Node table[TableSize];
    int hash(string ID);
    int GetQuadLoc(int Ndx, int& Sign);
    int GetDubLoc(string ID, int Val, int Cnt);

public:
    HTable();
    // Linear Probing
    void insertLinear(string studentID, string studentName);
    void removeLinear(string studentID);
    int searchLinear(string studentID);

    // Quadratic Probing
    void insertQuadratic(string studentID, string studentName);
    void removeQuadratic(string studentID);
    int searchQuadratic(string studentID);

    // Double Hashing
    void insertDouble(string studentID, string studentName);
    void removeDouble(string studentID);
    int searchDouble(string studentID);

    void display(ostream& out);


};
ostream& operator<< (ostream& out, HTable aHash);

#endif /* HashTable_h */
