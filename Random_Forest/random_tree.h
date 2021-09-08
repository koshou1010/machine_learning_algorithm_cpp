#pragma once
#ifndef RANDOM_TREE_H 
#define RANDOM_TREE_H

#include <iostream>

using namespace std;

class Car
{
	friend class carlist;
	friend class dtree;
protected:
	string buying;
	string maint;
	string doors;
	string persons;
	string lug_boot;
	string safety;
	string result;
public:
	Car() {	}
	void adddetails(string input);
	string getresult();
	string getwritedata();
	void display();
	~Car();
};

class carlist
{
	friend class dtree;
protected:
	Car* dataarray;
	int length; //numberof elements
	int size;// amount of allocated space
public:
	carlist(int x);
	carlist(const carlist& rhs);
	void MakeEmpty();
	bool IsFull();
	int GetLength();
	void InsertItem(string item); // insert data line by line from input file
	void InsertItem(Car item);
	Car getitem(int index);
	void DeleteItem(int index); 
	void Show();
	void ShowSize();
	void copylistattributes(int column, int quality, carlist& input);
	float findentrophy();
	bool checkcoveredallcases(Car list);
	bool checkpuresubset(carlist& input);
	carlist& operator=(const carlist& rhs);
	~carlist();
};

struct dtnode
{
	string atribute;
	int unacceptable, acceptable, good, verygood, numofchild;
	dtnode* array[4];
	dtnode()
	{
		array[0] = NULL;
		array[1] = NULL;
		array[2] = NULL;
		array[3] = NULL;
	}
};

class dtree
{
private:
	dtnode* root;
	void destroysubtree(dtnode*& nodePtr);
	bool checkindividualcase(int x, Car list);
	void countoutcomes(int& unaccept, int& accept, int& good, int& vgood, carlist& input);
	int findmaximumgain(carlist& input, Car list);
	void constructtree(carlist input, dtnode*& node, Car list);
	int determineindex(string input, int row);
public:
	dtree();
	void builddtree(carlist& input);
	string getresult(Car input);
	~dtree();
};


#endif // !
