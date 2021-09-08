// this program uses the first 1600 data entries to build dtrees and the the remaining 100 entries to test . it calculates the percentage and outputs to file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h> 
#include <cmath>
#include "random_tree.h"
using namespace std;



int main()
{
	carlist file2mem(3),treedata(3);
	dtree decisiontree[100]; // forest of 100 trees 
	Car tempv;
	int votes[4]={0,0,0,0},max=0,index=0,percent=0;// unacc, acc, vgood,good
	float totalpercentage=0;
	fstream filereader,filewriter;
	string temp,temp2,temp3;
	int rndv;
	srand(time(0));
	filereader.open("car.csv",ios::in);
	if(!filereader)
	{
		cout<<"error reading input file\n";
	}
	else
	{
		int enteries=0;
		while(1)
		{
				if(filereader.eof())
				{
					break;
				}
				getline(filereader,temp);
				enteries++;
				file2mem.InsertItem(temp);
		}
		cout<<enteries<<" enteries have been succesfully loaded into memory\n";
	}
	filereader.close();
	for(int j=0;j<100;j++)
	{
		treedata.MakeEmpty();// wipe all entries
		for(int i=0;i<340;i++)// randomly selects data for one tree
		{ 
			rndv=rand()%1600;
			treedata.InsertItem(file2mem.getitem(rndv));
		} 
		decisiontree[j].builddtree(treedata);
	}// forest built
	filewriter.open("RFPrediction.csv",ios::out);
	for(int j=1600;j<1700;j++)
	{
		tempv=file2mem.getitem(j);
		temp=tempv.getresult();// store actual value here
		temp3=tempv.getwritedata(); // store origanal content in string and add the predicted one with it
		for (int i = 0; i < 100; i++)
		{

			temp2 = decisiontree[i].getresult(tempv);
			if (temp2 == "unacc")
			{
				votes[0]++;
			}
			else if (temp2 == "acc")
			{
				votes[1]++;
			}
			else if (temp2 == "good")
			{
				votes[2]++;
			}
			else if (temp2 == "vgood")
			{
				votes[3]++;
			}
		}
		if (temp == "unacc")
		{
			percent = votes[0];
		}
		else if (temp == "acc")
		{
			percent = votes[1];
		}
		else if (temp == "good")
		{
			percent = votes[2];
		}
		else if (temp == "vgood")
		{
			percent = votes[3];
		}
		max=votes[0];
		index=0;
		for(int k=0;k<4;k++)
		{
			if(max<votes[k])
			{
				max=votes[k];
				index=k;
			}
		}
		if (index == 0)
		{
			temp3 += "unacc";
		}
		else if (index == 1)
		{
			temp3 += "acc";
		}
		else if (index == 2)
		{
			temp3 += "good";
		}
		else if (index == 3)
		{
			temp3 += "vgood";
		}
		temp3+="\n";
		filewriter<<temp3;// append prediction and write to file
		votes[0]=0;
		votes[1]=0;
		votes[2]=0;
		votes[3]=0;	
		totalpercentage+=percent;
	}
	totalpercentage=totalpercentage/100;
	cout<<"the forest had an accuracy of "<<totalpercentage<<"%\n";
	return 0;
}
