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
class ModelHashTable
{
private:
    class Node 
    {
    public:
        int key;
        string ID; // Student ID
        string value; // Student name
        
        Node(int K = -1, string id = "", string val = "") 
        {
            key = K; ID = id; value = val;
        }
    };

    int numberOfElements;
    Node table[TableSize];
    int hash(string ID);
    int GetQuadLoc(int Ndx, int& Sign);
    int GetDubLoc(string ID, int Val, int Cnt);

public:
    ModelHashTable();
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
ostream& operator<< (ostream& out, ModelHashTable aHash);

ModelHashTable::ModelHashTable()
{
    numberOfElements = 0;

    // initialize the table with default values
    for (int i = 0; i < TableSize; i++) 
    {
        table[i].key = -1;
        table[i].ID = "";
        table[i].value = "";
    }
}

//------------------------ Hash function ----------------------------------------
int ModelHashTable::hash(string ID)
{
    /*---------------------------------------------------
     Takes the sum of ascii codes of characters in ID
     and returns its remainder when divided by TableSize
     ---------------------------------------------------*/ 

    int sum = 0;
    for (int i = 0; i < ID.length(); i++)
        sum += ID[i];
    return sum % TableSize;
}

//----------------- insert Linear probing ---------------------------------------
void ModelHashTable::insertLinear(string studentID, string studentName)
{
    int index = hash(studentID); // saves the index specified by the hash
    int loc;
    Node newNode(index, studentID, studentName); // creates a new node with the index as key

    if (table[index].ID == studentID) // checks if the index already contains the ID
    {
        cout << "Student with ID: " << studentID 
             << " and name: " << studentName 
             << " already exists." << endl;
        return;
    }

    if (!(table[index].key == -1) && !(table[index].key == -2)) // checks if there's collision
    {
        for (int i = 1; i < TableSize; i++) // iterates over the table
        {
            loc = (i + index) % TableSize; // initializes the new index by linear probing
            
            if (table[loc].ID == studentID) // checks if the index already contains the ID
            {
                cout << "Student with ID: " << studentID
                     << " and name: " << studentName
                     << " already exists." << endl;
                return;
            }

            if (table[loc].key == -1 || table[loc].key == -2) //add node in loc in the case of no collision
            {
                table[loc] = newNode;
                newNode.key = loc;
                numberOfElements++;
                return;
            }
        }
    }

    // adds the node to the table in the case of no collision
    table[index] = newNode;
    numberOfElements++;
}

//----------------- remove Linear probing ---------------------------------------
void ModelHashTable::removeLinear(string studentID) 
{
    int index = hash(studentID); //get index in table by ID
    int loc;
    
    if (table[index].ID == studentID) // checks if the ID exists
    {
        table[index].key = -2; // marks as deleted
        table[index].ID = ""; // empties data
        table[index].value = ""; // emptied data
        numberOfElements--; // decrement the number of elements
        return;
    }

    for (int i = 1; i < TableSize; i++) // iterates over table
    {
        loc = (i + index) % TableSize; // initializes the new index by linear probing

        if (table[loc].key == -1) // if an empty node is encountered
        {
            cout << "Student with ID: " << studentID << " NOT exists." << endl;
            return;
        }
        if (table[loc].ID == studentID) // if the required node is encountered
        {
            table[loc].key = -2; // mark as deleted
            table[loc].ID = ""; // empty data
            table[loc].value = ""; // empty data
            numberOfElements--; // decrement number of elements
            return;
        }
    }
}

//----------------- search Linear probing ---------------------------------------
int ModelHashTable::searchLinear(string studentID) 
{
    int index = hash(studentID);
    int loc;
    if (table[index].ID == studentID) 
    {
        cout << "Student with ID: " << studentID << " exists." << endl;
        cout << setw(2) << index << ": " << setw(2) << table[index].key
             << ": " << setw(3) << table[index].ID << ": " << setw(10) << table[index].value << endl;
        return index;
    }

    for (int i = 1; i < TableSize; i++) // iterate over table
    {
        loc = (i + index) % TableSize;
        if (table[loc].key == -1) // if an empty node was found
        {
            cout << "Student with ID: " << studentID << "does NOT exists." << endl;
            return -1; // indicates that this ID does not found
        }
        if (table[loc].ID == studentID) // found ID
        {
            cout << "Student with ID: " << studentID << " exists." << endl;
            
            // display the Node data
            cout << setw(2) << loc << ": " << setw(2) << table[loc].key
                 << ": " << setw(3) << table[loc].ID << ": " << setw(10) << table[loc].value << endl;
            return loc; // return index
        }
    }
    return -1;
}

//------------------- Get Quadratic Location ------------------------------------
int GetQuadLoc(int Ndx, int& Sign) 
{
    int loc;
    if (Sign > 0) 
    {
        loc = (Ndx + (Sign * Sign)) % TableSize;
        Sign = Sign * -1;
        return loc;
    }
    Sign = Sign * -1;
    loc = (Ndx - (Sign * Sign));
    Sign++;
    if (loc < 0)
        loc = TableSize - loc;
    return loc;
}

//----------------- insert Quadratic probing ------------------------------------
void ModelHashTable::insertQuadratic(string studentID, string studentName)
{
    int index = hash(studentID);
    int loc, i = 1;
    Node n(index, studentID, studentName);

    if (table[index].ID == studentID) {
        cout << "Student with ID: " << studentID << " and name: " << studentName << " already exists." << endl;
        return;
    }

    if (table[index].key == -1 || table[index].key == -2) { // No collision
        table[index] = n;
        numberOfElements++;
    }
    else { // Collision
        while (true) {
            loc = GetQuadLoc(index, i);
            if (table[loc].ID == studentID) {
                cout << "Student with ID: " << studentID << " and name: " << studentName << " already exists." << endl;
                return;
            }
            if (table[loc].key == -1 || table[loc].key == -2) { // No collision
                table[loc] = n;
                n.key = loc;
                numberOfElements++;
                return;
            }
            if (abs(i) > TableSize / 2) {
                cout << "Hash Table is full, Can't insert" << endl;
                return;
            }
        }
    }
}

//----------------- remove Quadratic probing ------------------------------------
void ModelHashTable::removeQuadratic(string studentID) {
    int index = hash(studentID);
    int loc, i = 1;
    if (table[index].ID == studentID) {
        table[index].key = -2;
        table[index].ID = "";
        table[index].value = "";
        numberOfElements--;
        return;
    }
    else {
        while (true) {
            loc = GetQuadLoc(index, i);
            if (table[loc].key == -1) {
                cout << "Student with ID: " << studentID << " NOT exists." << endl;
                return;
            }
            if (table[loc].ID == studentID) {
                table[loc].key = -2;
                table[loc].ID = "";
                table[loc].value = "";
                numberOfElements--;
                return;
            }
        }
    }
}

//------------ search Quadratic probing ------------------------------------
int ModelHashTable::searchQuadratic(string studentID) {
    int index = hash(studentID);
    int loc, i = 0;
    if (table[index].ID == studentID) {
        cout << "Student with ID: " << studentID << " exists." << endl;
        cout << setw(2) << index << ": " << setw(2) << table[index].key
            << ": " << setw(3) << table[index].ID << ": " << setw(10) << table[index].value << endl;

        return index;
    }
    else {
        while (true) {
            loc = GetQuadLoc(index, i);
            if (table[loc].key == -1) {
                cout << "Student with ID: " << studentID << " NOT exists." << endl;
                return -1;
            }
            if (table[loc].ID == studentID) {
                cout << "Student with ID: " << studentID << " exists." << endl;
                cout << setw(2) << loc << ": " << setw(2) << table[loc].key
                    << ": " << setw(3) << table[loc].ID << ": " << setw(10) << table[loc].value << endl;
                return loc;
            }
            if (abs(i) > TableSize / 2) {
                cout << "Item doesn't exists" << endl;
                return -1;
            }
        }
    }
    return -1;
}

//----------------- Get Double Hashing Location ---------------------------------
int GetDubLoc(string ID, int Val, int Cnt) {
    int sum = 0, h1, h2;
    for (int i = 0; i < ID.length(); i++)
        sum += ID[i];
    h1 = sum % TableSize;
    h2 = Val - (sum % Val);
    return((h1 + (Cnt * h2)) % TableSize);
}
//----------------- insert Double Hashing ------------------------------------
void ModelHashTable::insertDouble(string studentID, string studentName)
{
    int index = hash(studentID);
    int loc;
    Node n(index, studentID, studentName);

    if (table[index].ID == studentID) {
        cout << "Student with ID: " << studentID << " and name: " << studentName << " already exists." << endl;
        return;
    }

    if (table[index].key == -1 || table[index].key == -2) { // No collision
        table[index] = n;
        numberOfElements++;
    }
    else { // Collision
        for (int i = 1; i < TableSize; i++) {
            loc = GetDubLoc(studentID, DoubleHashVal, i);
            if (table[loc].ID == studentID) {
                cout << "Student with ID: " << studentID << " and name: " << studentName << " already exists." << endl;
                return;
            }
            if (table[loc].key == -1 || table[loc].key == -2) { // No collision
                table[loc] = n;
                n.key = loc;
                numberOfElements++;
                return;
            }
        }
        cout << "Hash Table is full, Can't insert" << endl;
        return;
    }
}
//----------------- remove Double probing ------------------------------------
void ModelHashTable::removeDouble(string studentID) {
    int index = hash(studentID);
    int loc;
    if (table[index].ID == studentID) {
        table[index].key = -2;
        table[index].ID = "";
        table[index].value = "";
        numberOfElements--;
        return;
    }
    else {
        for (int i = 1; i < TableSize; i++) {
            loc = GetDubLoc(studentID, DoubleHashVal, i);
            if (table[loc].key == -1) {
                cout << "Student with ID: " << studentID << " NOT exists." << endl;
                return;
            }
            if (table[loc].ID == studentID) {
                table[loc].key = -2;
                table[loc].ID = "";
                table[loc].value = "";
                numberOfElements--;
                return;
            }
        }
    }
}

//------------ search Double probing ------------------------------------
int ModelHashTable::searchDouble(string studentID) {
    int index = hash(studentID);
    int loc;
    if (table[index].ID == studentID) {
        cout << "Student with ID: " << studentID << " exists." << endl;
        cout << setw(2) << index << ": " << setw(2) << table[index].key
            << ": " << setw(3) << table[index].ID << ": " << setw(10) << table[index].value << endl;
        return index;
    }
    else {
        for (int i = 1; i < TableSize; i++) {
            loc = GetDubLoc(studentID, DoubleHashVal, i);
            if (table[loc].key == -1) {
                cout << "Student with ID: " << studentID << " NOT exists." << endl;
                return -1;
            }
            if (table[loc].ID == studentID) {
                cout << "Student with ID: " << studentID << " exists." << endl;
                cout << setw(2) << loc << ": " << setw(2) << table[loc].key
                    << ": " << setw(3) << table[loc].ID << ": " << setw(10) << table[loc].value << endl;
                return loc;
            }
            if (abs(i) > TableSize / 2) {
                cout << "Item doesn't exists" << endl;
                return -1;
            }
        }
        cout << "Item doesn't exists" << endl;
        return -1;
    }
}

//------------------- Display Hash Table ------------------------------------
void ModelHashTable::display(ostream& out) {
    for (int i = 0; i < TableSize; i++) {
        if (table[i].key == -1 || table[i].key == -2)
            continue;
        out << setw(2) << i << ": " << setw(2) << table[i].key << ": " << setw(3) << table[i].ID << ": "
            << setw(10) << table[i].value << endl;
    }
}

//--------------- Overloading output << operator --------------------------------
ostream& operator<< (ostream& out, ModelHashTable aHash) {
    aHash.display(out);
    return out;
}

#endif /* HashTable_h */
