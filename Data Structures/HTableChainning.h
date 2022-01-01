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
	class Node
	{
	public:
		string key; // Student ID
		string value; // Student name
		Node* next;

		Node(string id = "", string val = "", Node* nxt = 0)
		{
			key = id; val = value; next = nxt;
		}
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

int HTableChainning::hash(string key)
{
	int sum = 0;
	for (int i = 0; i < key.length(); i++)
	{
		sum += int(key.at(i));
	}
	return sum % TableSize;
}

HTableChainning::HTableChainning() : numberOfElements(0)
{
	for (int i = 0; i < TableSize; i++)
	{
		table[i]->key = "";
		table[i]->value = "";
		table[i]->next = NULL;
		table[i] = NULL;
	}
}

void HTableChainning::insert(string studentID, string studentName)
{
	int index = hash(studentID);
	Node* newNode;
	if (table[index])
	{
		table[index] = new Node(studentID, studentName, table[index]);
	}

	numberOfElements++;
}

void HTableChainning::remove(string studentID)
{
	int index = hash(studentID);
	Node* previous = table[index];
	Node* trash = previous;

	while (trash->next)
	{
		if (trash->key != studentID)
		{
			previous = trash;
			trash = trash->next;
		}

		previous->next = trash->next;
		delete trash;
		numberOfElements--;
		return;
	}
}

void HTableChainning::print()
{
	for (int i = 0; i < TableSize; i++)
	{
		Node* ptr = table[i];

		while (ptr->next)
		{
			cout << ptr->key << " -> ";
		}
		cout << "\n";
	}
}
#endif /* HTable_hpp */