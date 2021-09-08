#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h> 
#include <cmath>
#include "random_tree.h"
using namespace std;

void Car::adddetails(string input)
{ // need to break up string into parts
	istringstream ss(input);
	string token;
	getline(ss, token, ',');
	buying = token;
	getline(ss, token, ',');
	maint = token;
	getline(ss, token, ',');
	doors = token;
	getline(ss, token, ',');
	persons = token;
	getline(ss, token, ',');
	lug_boot = token;
	getline(ss, token, ',');
	safety = token;
	getline(ss, token, ',');
	result = token;
}

string Car::getresult()
{
	return result;
}

string Car::getwritedata()
{
	string temp;
	temp = buying;
	temp += ",";
	temp += maint;
	temp += ",";
	temp += doors;
	temp += ",";
	temp += persons;
	temp += ",";
	temp += lug_boot;
	temp += ",";
	temp += safety;
	temp += ",";
	temp += result;
	temp += ",";
	return temp;
}

void Car::display()
{
	cout << buying << " " << maint << " " << doors << " " << persons << " " << lug_boot << " " << safety << " " << result << endl;
}

Car::~Car()
{
}




carlist::carlist(int x)
{
	dataarray = new Car[x];
	length = 0;
	size = x;
}
carlist::carlist(const carlist& rhs)
{ // copy constructor
	if (this != &rhs)
	{
		length = rhs.length;
		size = rhs.size;
		dataarray = new Car[size];
		for (int i = 0; i < length; i++)
		{
			dataarray[i] = rhs.dataarray[i];
		}
		// Deallocate, allocate new space, copy values...
	}
}
void carlist::MakeEmpty()
{
	length = 0;
}
bool carlist::IsFull()
{
	return (length == size);
}
int carlist::GetLength()
{
	return length;
}
void carlist::InsertItem(string item) // insert data line by line from input file
{
	if (IsFull()) {
		Car* ptr = new Car[size + 5];
		for (int i = 0; i < size; i++)
		{
			ptr[i] = dataarray[i];
		}
		delete[] dataarray;
		dataarray = ptr;
		size = size + 5;
		dataarray[length].adddetails(item);
		length++;
	}
	else 
	{
		dataarray[length].adddetails(item);
		length++;
	}
}
void carlist::InsertItem(Car item) // copy items
{ 
	if (IsFull())
	{
		Car* ptr = new Car[size + 5];
		for (int i = 0; i < size; i++)
		{
			ptr[i] = dataarray[i];
		}
		delete[] dataarray;
		dataarray = ptr;
		size = size + 5;
		dataarray[length] = item;
		length++;
	}
	else 
	{
		dataarray[length] = item;
		length++;
	}
}
Car carlist::getitem(int index)// array like access
{ 
	Car temp;
	if ((index >= 0) && (index < length))
	{
		temp = dataarray[index];
	}
	return temp;
}
void carlist::DeleteItem(int index) 
{
	for (int j = index; j < length - 1; j++) 
	{
		dataarray[j] = dataarray[j + 1];
	}
	length--;
}
void carlist::Show() 
{
	for (int i = 0; i < length; i++) 
	{
		dataarray[i].display();
	}
}
void carlist::ShowSize()
{
	cout << "size is " << length;
}
void carlist::copylistattributes(int column, int quality, carlist& input) 
{// breaks list into sub parts column is atribute and quality is type ( high low med etc)
	this->MakeEmpty();
	int run = input.GetLength();
	if (run != 0)
	{
		switch (column) 
		{
		case 1: //buying
			if (quality == 1) 
			{// low med high vhigh (1,2,3,4)
				for (int i = 0; i < run; i++)
				{
					if (input.dataarray[i].buying == "low")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 2) 
			{// low med high vhigh (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].buying == "med")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 3) 
			{// low med high vhigh (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].buying == "high")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 4) {// low med high vhigh (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].buying == "vhigh")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else 
			{ 
				cout << " out of function bounds buying\n"; 
			}
			break;
		case 2:// maint
			if (quality == 1) {// low med high vhigh (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].maint == "low")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 2) {// low med high vhigh (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].maint == "med")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 3) {// low med high vhigh (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].maint == "high")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 4) {// low med high vhigh (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].maint == "vhigh")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else 
			{ 
				cout << " out of function bounds maintiance \n"; 
			}
			break;
		case 3:// doors
			if (quality == 1) 
			{// two three four 5more (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].doors == "2")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 2) {// two three four 5more (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].doors == "3")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 3) 
			{// two three four 5more (1,2,3,4)
				for (int i = 0; i < run; i++)
				{
					if (input.dataarray[i].doors == "4")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 4) 
			{// two three four 5more (1,2,3,4)
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].doors == "5more")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else 
			{ 
				cout << " out of function bounds doors\n"; 
			}
			break;
		case 4:// persons
			if (quality == 1) 
			{// two four more 1,2,3
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].persons == "2")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 2) {// two four more 1,2,3
				for (int i = 0; i < run; i++)
				{
					if (input.dataarray[i].persons == "4")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 3)
			{// two four more 1,2,3
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].persons == "more")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else 
			{ 
				cout << " out of function bounds persons\n"; 
			}
			break;
		case 5:// luggage
			if (quality == 1) 
			{// small med big 1,2,3
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].lug_boot == "small")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 2) 
			{// small med big 1,2,3
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].lug_boot == "med")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 3) 
			{// small med big 1,2,3
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].lug_boot == "big")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else 
			{ 
				cout << " out of function bounds luggage\n"; 
			}
			break;
		case 6:// safety
			if (quality == 1)
			{// low med high 1,2,3
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].safety == "low")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 2) 
			{// low med high 1,2,3
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].safety == "med")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else if (quality == 3) 
			{// low med high 1,2,3
				for (int i = 0; i < run; i++) 
				{
					if (input.dataarray[i].safety == "high")
						this->InsertItem(input.dataarray[i]);
				}
			}
			else 
			{ 
				cout << " out of function bounds luggage\n"; 
			}
			break;
		}
	}
	else 
	{
		cout << "emply list reached split function \n";
	}
}
float carlist::findentrophy()// calculates total entrophy wrt outcome
{
	float unaccept = 0, accept = 0, good = 0, vgood = 0, total = 0, entrophy = 0, pu = 0, pa = 0, pg = 0, pv = 0;
	for (int i = 0; i < length; i++)
	{
		if (dataarray[i].result == "unacc")
		{
			unaccept++;
		}
		else if (dataarray[i].result == "acc")
		{
			accept++;
		}
		else if (dataarray[i].result == "good")
		{
			good++;
		}
		else
		{
			vgood++;
		}
	}// put checks to elimnate elements which are zero
	total = unaccept + accept + good + vgood;
	if (unaccept != 0) 
	{
		pu = unaccept / total;
		pu = pu * (log2(pu));
	}
	if (accept != 0) 
	{
		pa = accept / total;
		pa = pa * (log2(pa));
	}
	if (good != 0) 
	{
		pg = good / total;
		pg = pg * (log2(pg));
	}
	if (vgood != 0) 
	{
		pv = vgood / total;
		pv = pv * (log2(pv));
	}
	entrophy = -1 * (pu + pa + pg + pv);
	return entrophy;
}
bool carlist::checkcoveredallcases(Car list) 
{
	if ((list.buying == "covered") && (list.maint == "covered") && (list.doors == "covered") && (list.persons == "covered") && (list.lug_boot == "covered") && (list.safety == "covered"))
	{
		return true;
	}
	return false;
}
bool carlist::checkpuresubset(carlist& input)
{
	float x = input.findentrophy();
	if (x == 0)
	{
		return true;
	}
	return false;
}
carlist& carlist::operator=(const carlist& rhs)
{// Only do assignment if RHS is a different object from this.
	if (this != &rhs) {
		delete[] dataarray;
		length = rhs.length;
		size = rhs.size;
		dataarray = new Car[size];
		for (int i = 0; i < length; i++) 
		{
			dataarray[i] = rhs.dataarray[i];
		}// Deallocate, allocate new space, copy values...
	}
	return *this;
}
carlist::~carlist() 
{// had to comment this out due to segmentation fault errors (should have stuck to pointers)
	delete[] dataarray;
}




void dtree::destroysubtree(dtnode*& nodePtr)
{// set this leaf to null before calling this function to prevent segmentation fault errors
	dtnode* first, * second, * third, * fourth;
	if (nodePtr)
	{
		first = nodePtr->array[0];
		second = nodePtr->array[1];
		third = nodePtr->array[2];
		fourth = nodePtr->array[3];
		delete nodePtr;
		destroysubtree(first);
		destroysubtree(second);
		destroysubtree(third);
		destroysubtree(fourth);
	}
}
bool dtree::checkindividualcase(int x, Car list)
{ // 1-6 for atributes
	switch (x) 
	{
	case 1:
		if (list.buying == "covered")
			return true;
		return false;
		break;
	case 2:
		if (list.maint == "covered")
			return true;
		return false;
		break;
	case 3:
		if (list.doors == "covered")
			return true;
		return false;
		break;
	case 4:
		if (list.persons == "covered")
			return true;
		return false;
		break;
	case 5:
		if (list.lug_boot == "covered")
			return true;
		return false;
		break;
	case 6:
		if (list.safety == "covered")
			return true;
		return false;
		break;
	default:
		cout << "out of function designed scope\n";
		return false;
	}
}
void dtree::countoutcomes(int& unaccept, int& accept, int& good, int& vgood, carlist& input)
{// counts all outputs used at node divisions
	int length = input.GetLength();
	unaccept = accept = good = vgood = 0;
	for (int i = 0; i < length; i++) 
	{
		if (input.dataarray[i].result == "unacc")
			unaccept++;
		else if (input.dataarray[i].result == "acc")
			accept++;
		else if (input.dataarray[i].result == "good")
			good++;
		else
			vgood++;
	}
}
int dtree::findmaximumgain(carlist& input, Car list) // returns a int (1-6 and zero for pureclass and 7 for covering all attributes) which denotes a quality that best divides data avoids already bucketed terms
{
	if (input.checkpuresubset(input))// if return True
	{
		return 0;
	}
	else if (input.checkcoveredallcases(list))
	{
		return 7;
	}
	else {// calculate gain of all atributes find max if not already covered and return indicator
		float oldent, array[6], newent, max, run = input.GetLength();
		carlist temp1(3), temp2(3), temp3(3), temp4(3);
		int slot;
		oldent = input.findentrophy(); //initial entrophy
		for (int i = 1; i < 7; i++) {// 1-6 attributes
			if (!checkindividualcase(i, list)) 
			{ // push each into own list and calulate new entrophys and number of terms
				switch (i) {
				case 1: //buying
					temp1.copylistattributes(1, 1, input); // low
					temp2.copylistattributes(1, 2, input); // med
					temp3.copylistattributes(1, 3, input); // high	
					temp4.copylistattributes(1, 4, input); // vhigh
					newent = (temp1.GetLength()) * (temp1.findentrophy()) + (temp2.GetLength()) * (temp2.findentrophy()) + (temp3.GetLength()) * (temp3.findentrophy()) + (temp4.GetLength()) * (temp4.findentrophy());
					newent = newent / run;
					array[0] = oldent - newent;// gain saved in array 
					break;
				case 2: //maintainence
					temp1.copylistattributes(2, 1, input); // low
					temp2.copylistattributes(2, 2, input); // med
					temp3.copylistattributes(2, 3, input); // high	
					temp4.copylistattributes(2, 4, input); // vhigh
					newent = (temp1.GetLength()) * (temp1.findentrophy()) + (temp2.GetLength()) * (temp2.findentrophy()) + (temp3.GetLength()) * (temp3.findentrophy()) + (temp4.GetLength()) * (temp4.findentrophy());
					newent = newent / run;
					array[1] = oldent - newent;// gain saved in array 
					break;
				case 3: // doors
					temp1.copylistattributes(3, 1, input); // 2
					temp2.copylistattributes(3, 2, input); // 3
					temp3.copylistattributes(3, 3, input); // 4	
					temp4.copylistattributes(3, 4, input); // 5more
					newent = (temp1.GetLength()) * (temp1.findentrophy()) + (temp2.GetLength()) * (temp2.findentrophy()) + (temp3.GetLength()) * (temp3.findentrophy()) + (temp4.GetLength()) * (temp4.findentrophy());
					newent = newent / run;
					array[2] = oldent - newent;// gain saved in array 		
					break;
				case 4: //persons
					temp1.copylistattributes(4, 1, input); // 2
					temp2.copylistattributes(4, 2, input); // 4
					temp3.copylistattributes(4, 3, input); // more	
					newent = (temp1.GetLength()) * (temp1.findentrophy()) + (temp2.GetLength()) * (temp2.findentrophy()) + (temp3.GetLength()) * (temp3.findentrophy());
					newent = newent / run;
					array[3] = oldent - newent;// gain saved in array 
					break;
				case 5: //luggage
					temp1.copylistattributes(5, 1, input); // small
					temp2.copylistattributes(5, 2, input); // medium
					temp3.copylistattributes(5, 3, input); // big
					newent = (temp1.GetLength()) * (temp1.findentrophy()) + (temp2.GetLength()) * (temp2.findentrophy()) + (temp3.GetLength()) * (temp3.findentrophy());
					newent = newent / run;
					array[4] = oldent - newent;// gain saved in array 
					break;
				case 6: //safety
					temp1.copylistattributes(6, 1, input); // low
					temp2.copylistattributes(6, 2, input); // med 
					temp3.copylistattributes(6, 3, input); // high	
					newent = (temp1.GetLength()) * (temp1.findentrophy()) + (temp2.GetLength()) * (temp2.findentrophy()) + (temp3.GetLength()) * (temp3.findentrophy());
					newent = newent / run;
					array[5] = oldent - newent;// gain saved in array 
					break;
				}
			}
			else
			{
				array[i - 1] = 0;  // make this lower to prevent repeats if they occur
			}
		}
		max = array[0];
		slot = 0;
		for (int j = 0; j < 6; j++) 
		{
			if (max < array[j]) 
			{
				max = array[j];
				slot = j;
			}
		}
		slot++;
		return slot;
	}
}
void dtree::constructtree(carlist input, dtnode*& node, Car list) // recursive dtree builder base case 
{
	// check if all atributes have been covered 
	int x = findmaximumgain(input, list);
	carlist temp(3);
	switch (x) 
	{
	case 0: // pure class stop here
		node = new dtnode;
		node->atribute = "pureset";
		node->numofchild = 0;
		countoutcomes(node->unacceptable, node->acceptable, node->good, node->verygood, input);
		for (int i = 0; i < 4; i++) 
		{
			node->array[i] = NULL;
		}
		break;
	case 1: //buying
		node = new dtnode;
		node->atribute = "buying";
		node->numofchild = 4;
		list.buying = "covered";// denotes an split on buying in ancestors
		countoutcomes(node->unacceptable, node->acceptable, node->good, node->verygood, input);// calculates decendents of node
		for (int i = 1; i < 5; i++) 
		{
			temp.copylistattributes(1, i, input);
			constructtree(temp, node->array[i - 1], list);// build tree downwards				
		}
		break;
	case 2: //maintainence
		node = new dtnode;
		node->atribute = "maintenance";
		node->numofchild = 4;
		list.maint = "covered";// denotes an split on maintenance in ancestors
		countoutcomes(node->unacceptable, node->acceptable, node->good, node->verygood, input);// calculates decendents of node
		for (int i = 1; i < 5; i++) 
		{
			temp.copylistattributes(2, i, input);
			constructtree(temp, node->array[i - 1], list);// build tree downwards				
		}
		break;
	case 3: // doors
		node = new dtnode;
		node->atribute = "doors";
		node->numofchild = 4;
		list.doors = "covered";// denotes an split on doors in ancestors
		countoutcomes(node->unacceptable, node->acceptable, node->good, node->verygood, input);// calculates decendents of node
		for (int i = 1; i < 5; i++) 
		{
			temp.copylistattributes(3, i, input);
			constructtree(temp, node->array[i - 1], list);// build tree downwards				
		}
		break;
	case 4: //persons
		node = new dtnode;
		node->atribute = "persons";
		node->numofchild = 3;
		list.persons = "covered";// denotes an split on persons in ancestors
		countoutcomes(node->unacceptable, node->acceptable, node->good, node->verygood, input);// calculates decendents of node
		for (int i = 1; i < 4; i++) 
		{
			temp.copylistattributes(4, i, input);
			constructtree(temp, node->array[i - 1], list);// build tree downwards				
		}
		break;
	case 5: //luggage
		node = new dtnode;
		node->atribute = "luggage";
		node->numofchild = 3;
		list.lug_boot = "covered";// denotes an split on luggage in ancestors
		countoutcomes(node->unacceptable, node->acceptable, node->good, node->verygood, input);// calculates decendents of node
		for (int i = 1; i < 4; i++) 
		{
			temp.copylistattributes(5, i, input);
			constructtree(temp, node->array[i - 1], list);// build tree downwards				
		}
		break;
	case 6: //safety
		node = new dtnode;
		node->atribute = "safety";
		node->numofchild = 3;
		list.safety = "covered";// denotes an split on safety in ancestors
		countoutcomes(node->unacceptable, node->acceptable, node->good, node->verygood, input);// calculates decendents of node
		for (int i = 1; i < 4; i++) 
		{
			temp.copylistattributes(6, i, input);
			constructtree(temp, node->array[i - 1], list);// build tree downwards				
		}
		break;
	case 7: // all attributes have been covered but no pure subset
		node = new dtnode;
		node->atribute = "leafnode";
		node->numofchild = 0;
		countoutcomes(node->unacceptable, node->acceptable, node->good, node->verygood, input);
		for (int i = 0; i < 4; i++) 
		{
			node->array[i] = NULL;
		}
		break;
	default:
		cout << " error in gain calculation \n";
	}
}
int dtree::determineindex(string input, int row)// row is atribute and input is what the car object has stored. returns a index to which child of the node to go to next
{ 
	switch (row) 
	{
	case 1:
	case 2: // 4 posibilities for buying and maintanence
		if (input == "low")
			return 0;
		else if (input == "med")
			return 1;
		else if (input == "high")
			return 2;
		else if (input == "vhigh")
			return 3;
		break;
	case 3: // 4 posibilities doors
		if (input == "2")
			return 0;
		else if (input == "3")
			return 1;
		else if (input == "4")
			return 2;
		else if (input == "5more")
			return 3;
		break;
	case 4:
		if (input == "2")
			return 0;
		else if (input == "4")
			return 1;
		else if (input == "more")
			return 2;
		break;
	case 5:
		if (input == "small")
			return 0;
		else if (input == "med")
			return 1;
		else if (input == "big")
			return 2;
		break;
	case 6:
		if (input == "low")
			return 0;
		else if (input == "med")
			return 1;
		else if (input == "high")
			return 2;
		break;
	}
}

dtree::dtree()
{
	root = NULL;
}
void dtree::builddtree(carlist& input)// build decision tree for a given list of cars
{
	Car list; // empty object to help keep track of qualities used to split at nodes
	constructtree(input, root, list); // calls recursive function to make dtree
}
string dtree::getresult(Car input) // traverses the tree and tells if car is acceptable/not/good/vgood
{
	string temp, div;
	int index;
	dtnode* ptr = root;
	while (1) 
	{
		div = ptr->atribute;
		if (div == "buying") 
		{
			temp = input.buying;
			index = determineindex(temp, 1);
			ptr = ptr->array[index];
		}
		else if (div == "maintenance") 
		{
			temp = input.maint;
			index = determineindex(temp, 2);
			ptr = ptr->array[index];
		}
		else if (div == "doors") 
		{
			temp = input.doors;
			index = determineindex(temp, 3);
			ptr = ptr->array[index];
		}
		else if (div == "persons") 
		{
			temp = input.persons;
			index = determineindex(temp, 4);
			ptr = ptr->array[index];
		}
		else if (div == "luggage") 
		{
			temp = input.lug_boot;
			index = determineindex(temp, 5);
			ptr = ptr->array[index];
		}
		else if (div == "safety") 
		{
			temp = input.safety;
			index = determineindex(temp, 6);
			ptr = ptr->array[index];
		}
		else if (div == "leafnode")
		{
			int array[4], max, slot, dup = -1; // 0 for unaccaptable, 1 acc, 2 good, 3 vgood
			array[0] = ptr->unacceptable;
			array[1] = ptr->acceptable;
			array[2] = ptr->good;
			array[3] = ptr->verygood;
			max = array[0];
			slot = 0;
			//cout<<"unacc "<<array[0]<<" acc "<<array[1]<<endl;
			for (int i = 0; i < 4; i++)
			{ //find max
				if (max < array[i])
				{
					max = array[i];
					slot = i;
				}
			}
			for (int i = 0; i < 4; i++) 
			{ //find duplicate cases only designed for 2 equal entities (eg acc==unacc)
				if ((max == array[i]) && (i != slot)) 
				{
					dup = i;
				}
			}
			if (dup == -1) {// no 50/50
				if (slot == 0) 
				{
					temp = "unacc";
					return temp;
				}
				else if (slot == 1) 
				{
					temp = "acc";
					return temp;
				}
				else if (slot == 2) 
				{
					temp = "good";
					return temp;
				}
				else if (slot == 3) 
				{
					temp = "vgood";
					return temp;
				}
				else 
				{
					temp = "notfound";
					return temp;
				}
			}
			else {
				index = rand() % 2;
				if (index == 0) // random choices for equals
					slot = dup;
				if (slot == 0) 
				{
					temp = "unacc";
					return temp;
				}
				else if (slot == 1) 
				{
					temp = "acc";
					return temp;
				}
				else if (slot == 2)
				{
					temp = "good";
					return temp;
				}
				else if (slot == 3) 
				{
					temp = "vgood";
					return temp;
				}
				else 
				{
					temp = "notfound";
					return temp;
				}
			}
		}
		else if (div == "pureset") 
		{
			index = ptr->unacceptable + ptr->acceptable + ptr->good + ptr->verygood;
			if (index == ptr->unacceptable)
			{
				temp = "unacc";
				return temp;
			}
			else if (index == ptr->acceptable) 
			{
				temp = "acc";
				return temp;
			}
			else if (index == ptr->good) 
			{
				temp = "good";
				return temp;
			}
			else if (index == ptr->verygood) 
			{
				temp = "vgood";
				return temp;
			}
			else 
			{
				temp = "notfound";
				return temp;
			}
		}
	}
	return "notfound";// is something wrong with the tree ?
}
dtree::~dtree()
{
	destroysubtree(root);
}

