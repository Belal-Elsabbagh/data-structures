//
//  HashTable.hpp
//  HashTable
//
//  Created by Ashraf AbdelRaouf on 12/4/19.
//  Copyright © 2019 Ashraf AbdelRaouf. All rights reserved.
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
class MyHashTable
{
private:
	class Node
	{
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
	MyHashTable();
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
ostream& operator<< (ostream& out, MyHashTable aHash);

int MyHashTable::hash(string ID)
{
	int sum = 0;
	for (int i = 0; i < ID.length(); i++)
	{
		sum += int(ID.at(i));
	}
	return sum % TableSize;
}

int MyHashTable::GetQuadLoc(int Ndx, int& Sign)
{
	int index;

	if (Sign < 0)
	{
		Sign = Sign * -1;
		index = (Ndx - (Sign * Sign));
		Sign++;
		if (index < 0)
			index = TableSize - index;
	}
}

int MyHashTable::GetDubLoc(string ID, int Val = DoubleHashVal, int Cnt = 0)
{
	return hash(ID) % Val;
}

MyHashTable::MyHashTable() :numberOfElements(0) {}

void MyHashTable::insertDouble(string studentID, string studentName)
{
	if (numberOfElements == TableSize)
	{
		cerr << "The hash table is full.\n";
		return;
	}

	int index = hash(studentID);
	while (!((table[index].key == -1) || (table[index].key == -2)))
		index += GetDubLoc(studentID) % TableSize;

	table[index].key = 0;
	table[index].ID = studentID;
	table[index].value = studentName;
	numberOfElements++;
}

void MyHashTable::removeDouble(string studentID)
{
	int index = searchDouble(studentID);
	if (index == -1)
	{
		cerr << "Item not found";
		return;
	}

	table[index].key = -2;
	table[index].ID = "";
	table[index].value = "";
	numberOfElements--;
}

int MyHashTable::searchDouble(string studentID)
{
	int index = hash(studentID);

	while (!((table[index].key == -1) || (table[index].key == -2)))
	{
		index += GetDubLoc(studentID) % TableSize;
		if (table[index].ID == studentID)
			return index;
	}
	return -1;
}

void MyHashTable::display(ostream& out)
{
	out << "Key\tID\t\tName\n";
	for (int i = 0; i < TableSize; i++)
	{
		out << table[i].key << "\t" << table[i].ID << "\t" << table[i].value << "\n";
	}
}

#endif /* HashTable_h */