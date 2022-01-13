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

const int TableSize = 11;
const int DoubleHashVal = 7;
class ModelHashTable
{
private:
	class Node
	{
	public:
		int key;
		std::string ID; // Student ID
		std::string value; // Student name

		Node(int K = -1, std::string id = "", std::string val = "")
		{
			key = K; ID = id; value = val;
		}
	};

	int numberOfElements;
	Node table[TableSize];

	int hash(std::string ID);
	int GetQuadLoc(int Ndx, int& Sign);
	int GetDubLoc(std::string ID, int Val, int Cnt);
	void DeleteNodeAtIndex(int index);

public:
	ModelHashTable();
	// Linear Probing
	void insertLinear(std::string studentID, std::string studentName);
	void removeLinear(std::string studentID);
	int searchLinear(std::string studentID);

	// Quadratic Probing
	void insertQuadratic(std::string studentID, std::string studentName);
	void removeQuadratic(std::string studentID);
	int searchQuadratic(std::string studentID);

	// Double Hashing
	void insertDouble(std::string studentID, std::string studentName);
	void removeDouble(std::string studentID);
	int searchDouble(std::string studentID);

	void display(std::ostream& out);


};
std::ostream& operator<< (std::ostream& out, ModelHashTable aHash);

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
int ModelHashTable::hash(std::string ID)
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

void ModelHashTable::DeleteNodeAtIndex(int index)
{
	table[index].key = -2; // marks as deleted
	table[index].ID = ""; // empties data
	table[index].value = ""; // emptied data
	numberOfElements--; // decrement the number of elements
}

//----------------- insert Linear probing ---------------------------------------
void ModelHashTable::insertLinear(std::string studentID, std::string studentName)
{
	int index = hash(studentID); // saves the index specified by the hash
	int loc;
	Node newNode(index, studentID, studentName); // creates a new node with the index as key

	if (table[index].ID == studentID) // checks if the index already contains the ID
	{
		std::cout << "Student with ID: " << studentID
			<< " and name: " << studentName
			<< " already exists." << "\n";
		return;
	}

	if (!(table[index].key == -1) && !(table[index].key == -2)) // checks if there's collision
	{
		for (int i = 1; i < TableSize; i++) // iterates over the table
		{
			loc = (i + index) % TableSize; // initializes the new index by linear probing

			if (table[loc].ID == studentID) // checks if the index already contains the ID
			{
				std::cout << "Student with ID: " << studentID
					 << " and name: " << studentName
					 << " already exists." << "\n";
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
void ModelHashTable::removeLinear(std::string studentID)
{
	int index = hash(studentID); //get index in table by ID
	int loc;

	if (table[index].ID == studentID) // checks if the ID exists
	{
		DeleteNodeAtIndex(index);
		return;
	}

	for (int i = 1; i < TableSize; i++) // iterates over table
	{
		loc = (i + index) % TableSize; // initializes the new index by linear probing

		if (table[loc].key == -1) // if an empty node is encountered
		{
			std::cout << "Student with ID: " << studentID << " NOT exists." << "\n";
			return;
		}
		if (table[loc].ID == studentID) // if the required node is encountered
		{
			DeleteNodeAtIndex(loc);
			return;
		}
	}
}

//----------------- search Linear probing ---------------------------------------
int ModelHashTable::searchLinear(std::string studentID)
{
	int index = hash(studentID);
	int loc;
	if (table[index].ID == studentID)
	{
		std::cout << "Student with ID: " << studentID << " exists." << "\n";
		std::cout << std::setw(2) << index << ": " << std::setw(2) << table[index].key
			<< ": " << std::setw(3) << table[index].ID << ": " << std::setw(10) << table[index].value << "\n";
		return index;
	}

	for (int i = 1; i < TableSize; i++) // iterate over table
	{
		loc = (i + index) % TableSize;
		if (table[loc].key == -1) // if an empty node was found
		{
			std::cout << "Student with ID: " << studentID << "does NOT exists." << "\n";
			return -1; // indicates that this ID does not found
		}
		if (table[loc].ID == studentID) // found ID
		{
			std::cout << "Student with ID: " << studentID << " exists." << "\n";

			// display the Node data
			std::cout << std::setw(2) << loc << ": " << std::setw(2) << table[loc].key
				<< ": " << std::setw(3) << table[loc].ID << ": " << std::setw(10) << table[loc].value << "\n";
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
void ModelHashTable::insertQuadratic(std::string studentID, std::string studentName)
{
	int index = hash(studentID);
	int loc, i = 1;
	Node n(index, studentID, studentName);

	if (table[index].ID == studentID)
	{
		std::cout << "Student with ID: " << studentID << " and name: " << studentName << " already exists." << "\n";
		return;
	}

	if (table[index].key == -1 || table[index].key == -2)
	{ // No collision
		table[index] = n;
		numberOfElements++;
	}
	// Collision
	while (true)
	{
		loc = GetQuadLoc(index, i);
		if (table[loc].ID == studentID)
		{
			std::cout << "Student with ID: " << studentID << " and name: " << studentName << " already exists." << "\n";
			return;
		}
		if (table[loc].key == -1 || table[loc].key == -2)
		{ // No collision
			table[loc] = n;
			n.key = loc;
			numberOfElements++;
			return;
		}
		if (abs(i) > TableSize / 2)
		{
			std::cout << "Hash Table is full, Can't insert" << "\n";
			return;
		}
	}
}

//----------------- remove Quadratic probing ------------------------------------
void ModelHashTable::removeQuadratic(std::string studentID)
{
	int index = hash(studentID);
	int loc, i = 1;
	if (table[index].ID == studentID)
	{
		DeleteNodeAtIndex(index);
		return;
	}

	while (true)
	{
		loc = GetQuadLoc(index, i);
		if (table[loc].key == -1)
		{
			std::cout << "Student with ID: " << studentID << " NOT exists." << "\n";
			return;
		}
		if (table[loc].ID == studentID)
		{
			DeleteNodeAtIndex(loc);
			return;
		}
	}
}

//------------ search Quadratic probing ------------------------------------
int ModelHashTable::searchQuadratic(std::string studentID)
{
	int index = hash(studentID);
	int loc, i = 0;
	if (table[index].ID == studentID)
	{
		std::cout << "Student with ID: " << studentID << " exists." << "\n";
		std::cout << std::setw(2) << index << ": " << std::setw(2) << table[index].key
			<< ": " << std::setw(3) << table[index].ID << ": " << std::setw(10) << table[index].value << "\n";

		return index;
	}
	while (true)
	{
		loc = GetQuadLoc(index, i);
		if (table[loc].key == -1)
		{
			std::cout << "Student with ID: " << studentID << " NOT exists." << "\n";
			return -1;
		}
		if (table[loc].ID == studentID)
		{
			std::cout << "Student with ID: " << studentID << " exists." << "\n";
			std::cout << std::setw(2) << loc << ": " << std::setw(2) << table[loc].key
				<< ": " << std::setw(3) << table[loc].ID << ": " << std::setw(10) << table[loc].value << "\n";
			return loc;
		}
		if (abs(i) > TableSize / 2)
		{
			std::cout << "Item doesn't exists" << "\n";
			return -1;
		}
	}
	return -1;
}

//----------------- Get Double Hashing Location ---------------------------------
int GetDubLoc(std::string ID, int Val, int Cnt)
{
	int sum = 0, h1, h2;
	for (int i = 0; i < ID.length(); i++)
		sum += ID[i];
	h1 = sum % TableSize;
	h2 = Val - (sum % Val);
	return((h1 + (Cnt * h2)) % TableSize);
}
//----------------- insert Double Hashing ------------------------------------
void ModelHashTable::insertDouble(std::string studentID, std::string studentName)
{
	int index = hash(studentID);
	int loc;
	Node n(index, studentID, studentName);

	if (table[index].ID == studentID)
	{
		std::cout << "Student with ID: " << studentID << " and name: " << studentName << " already exists." << "\n";
		return;
	}

	if (table[index].key == -1 || table[index].key == -2)
	{ // No collision
		table[index] = n;
		numberOfElements++;
		return;
	}
	// in case of collision
	for (int i = 1; i < TableSize; i++)
	{
		loc = GetDubLoc(studentID, DoubleHashVal, i);
		if (table[loc].ID == studentID)
		{
			std::cout << "Student with ID: " << studentID << " and name: " << studentName << " already exists." << "\n";
			return;
		}
		if (table[loc].key == -1 || table[loc].key == -2)
		{ // No collision
			table[loc] = n;
			n.key = loc;
			numberOfElements++;
			return;
		}
	}
	std::cout << "Hash Table is full, Can't insert" << "\n";
	return;
}
//----------------- remove Double probing ------------------------------------
void ModelHashTable::removeDouble(std::string studentID)
{
	int index = hash(studentID);
	int loc;
	if (table[index].ID == studentID)
	{
		DeleteNodeAtIndex(index);
		return;
	}

	for (int i = 1; i < TableSize; i++)
	{
		loc = GetDubLoc(studentID, DoubleHashVal, i);
		if (table[loc].key == -1)
		{
			std::cout << "Student with ID: " << studentID << " NOT exists." << "\n";
			return;
		}
		if (table[loc].ID == studentID)
		{
			DeleteNodeAtIndex(loc);
			return;
		}
	}
}

//------------ search Double probing ------------------------------------
int ModelHashTable::searchDouble(std::string studentID)
{
	int index = hash(studentID);
	int loc;
	if (table[index].ID == studentID)
	{
		std::cout << "Student with ID: " << studentID << " exists." << "\n";
		std::cout << std::setw(2) << index << ": " << std::setw(2) << table[index].key
			<< ": " << std::setw(3) << table[index].ID << ": " << std::setw(10) << table[index].value << "\n";
		return index;
	}

	for (int i = 1; i < TableSize; i++)
	{
		loc = GetDubLoc(studentID, DoubleHashVal, i);
		if (table[loc].key == -1)
		{
			std::cout << "Student with ID: " << studentID << " NOT exists." << "\n";
			return -1;
		}
		if (table[loc].ID == studentID)
		{
			std::cout << "Student with ID: " << studentID << " exists." << "\n";
			std::cout << std::setw(2) << loc << ": " << std::setw(2) << table[loc].key
				<< ": " << std::setw(3) << table[loc].ID << ": " << std::setw(10) << table[loc].value << "\n";
			return loc;
		}
		if (abs(i) > TableSize / 2)
		{
			std::cout << "Item doesn't exists" << "\n";
			return -1;
		}
	}
	std::cout << "Item doesn't exists" << "\n";
	return -1;
}

//------------------- Display Hash Table ------------------------------------
void ModelHashTable::display(std::ostream& out)
{
	for (int i = 0; i < TableSize; i++)
	{
		if (table[i].key == -1 || table[i].key == -2)
			continue;
		out << std::setw(2) << i << ": " << std::setw(2) << table[i].key << ": " << std::setw(3) << table[i].ID << ": "
			<< std::setw(10) << table[i].value << "\n";
	}
}

//--------------- Overloading output << operator --------------------------------
std::ostream& operator<< (std::ostream& out, ModelHashTable aHash)
{
	aHash.display(out);
	return out;
}

#endif /* HashTable_h */
