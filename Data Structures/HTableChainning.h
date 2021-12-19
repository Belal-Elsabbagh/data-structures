
//
//  HTable.hpp
//  HashTable
//
//  Created by Ashraf AbdelRaouf on 25/11/2021.
//

#ifndef HTable_hpp
#define HTable_hpp

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

const int TableSize = 11;

class HTableChainning
{
private:
    class Node {
    public:
        string key; // Student ID
        string value; // Student name
        Node* next;
    };

    int numberOfElements;
    Node* table[TableSize];
    int hash(string key);
public:
    HTableChainning();
    void insert(string studentID, string studentName);
    void remove(string studentID);
    void print();
};

#endif /* HTable_hpp */
