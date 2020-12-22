//	name:	rotor.h
//	author:	Ethan Dy Tioco
//	desc:	Contains declarations for the Rotor class, to be used for the Enigma project
//			12.19.2020 object has: string name, abcMapping; int* rotor, indexTurnover;
#ifndef Rotor_H
#define Rotor_H

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class Rotor{
private:
	string name, abcMapping;
	int* rotor;
	int* indexTurnover;
	
public:
	// Constructors
	Rotor();
	Rotor(string name, string mapping, int indexTurnover1, int indexTurnover2);
	Rotor(const Rotor& orig);	// copy constructor
	Rotor(Rotor&& orig);		// move constructor
	~Rotor();					// destructor
	Rotor& operator = (Rotor copy);
	
	// GET methods
	string getName();
	string getStringMapping();
	int getIndexTurnover1();
	int getIndexTurnover2();
	int getFirstPassResult(int n);
	int getSecondPassResult(int n);
	int getInputAt(int n);
	int getOutputAt(int n);
	int getTurnoverValueAt(int n);
	
	// SET methods
	void setInput(char value, int n);
	void setOutput(char value, int n);
	
	// Functionalities
	void rotateBy(int n);
	void ringstellung(int n);
	void printRotor();
	void diagnostic();
};

#endif