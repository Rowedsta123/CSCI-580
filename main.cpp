#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<vector>
#include"matrix.h"
#include"robot.h"
using namespace std;

input str_to_enum(string sensor);

int main(int argc, char* argv[]) 
{ 
	if(argc < 4)
	{
		cout << "Too few arguments. input:: executable file.txt \%error sensor_input" << endl; 
		//return 1;
	}
	input obs[argc - 3];
	int NItt = 0;
	//Get array of Inputs from comand line.
	for(int i = 3, j = 0; i < argc; ++i, ++j)
	{
		string str = argv[i];
		obs[j] = str_to_enum(str);
		++NItt;
	}
	//get map info;
	vector<input> sensor_input;	
	string temp = argv[2];
	double error = atof(temp.c_str());
	
	int n_states = 0;
	int numLines = 0;
	ifstream mapFile;
	mapFile.open(argv[1]);
	string output;
	if (mapFile.is_open()) 
	{
		while(mapFile.peek() != EOF) 
		{
		 	mapFile >> output;
			if(mapFile.peek() != EOF)
			{
    		sensor_input.push_back(str_to_enum(output));
				++n_states;
			}
			if(mapFile.peek() == '\n')
			{
				++numLines;
			}
		}
	}
	mapFile.close();
	input* map_array = new input[n_states];
	for(int i = 0; i < n_states; ++i)
	{
		map_array[i] = sensor_input[i];	
	}
	long double estimation_probability;
	Robot Steve(n_states/numLines, numLines, map_array, error);
	for(int i = 0; i < NItt; ++i)
	{
		//Steve.print();
		Matrix* temp = Steve.CalcJointPredictProb();
		temp->print();
		Steve.MakeObservation(obs[i]);
		//Steve.print();
		Steve.CalcJointProb(temp);
		Steve.print();
		estimation_probability = Steve.CalcEstProb();
		//Steve.print();
		cout << std::showpoint << std::fixed << setprecision(12) << estimation_probability<<" ";
		Steve.printlikelystates(estimation_probability);
	}
	
	
	delete map_array;
	return 0;
}


input str_to_enum(string sensor)
{
	if(sensor == "0")
	{
		return NONE;
	}
	if(sensor == "E" 
|| sensor == "1")
	{
		return E;
	}
	if(sensor == "W" || sensor == "2")
	{
		return W;
	}
	if(sensor == "WE" || sensor == "3")
	{
		return WE;
	}
	if(sensor == "S" || sensor == "4")
	{
		return S;
	}
	if(sensor == "SE" || sensor == "5")
	{
		return SE;
	}
	if(sensor == "SW" || sensor == "6")
	{
		return SW;
	}
	if(sensor == "SWE" || sensor == "7")
	{
		return SWE;
	}
	if(sensor == "N" || sensor == "8")
	{
		return N;
	}
	if(sensor == "NE" || sensor == "9")
	{
		return NE;
	}
	if(sensor == "NW" || sensor == "10")
	{
		return NW;
	}
	if(sensor == "NWE" || sensor == "11")
	{
		return NWE;
	}
	if(sensor == "NS" || sensor == "12")
	{
		return NS;
	}
	if(sensor == "NSE" || sensor == "13")
	{
		return NSE;
	}
	if(sensor == "NSW" || sensor == "14")
	{
		return NSW;
	}
	if(sensor == "NSWE" || sensor == "15")
	{
		return NSWE;
	}	
}
