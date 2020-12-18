//	name:	rotor.cpp
//	author:	Ethan Dy Tioco
//	desc:	Implementing the functions for the Rotor class

#include <iostream>
#include <string>
#include <algorithm>		// <-- remove whitespace functionality. also, swap()
#include "rotor.h"
using namespace std;

// .h file holds the declarations.
// .cpp file holds the implementation, like this:

/*
	return_type ClassName::function(...){
		// type out what's inside the code
	}
*/

// Constructor - default
Rotor::Rotor(){
	this->indexTurnover[0] = 0;
	this->indexTurnover[1] = 0;
	this->name = "";
}


// Constructor- with params
Rotor::Rotor(string name, string mapping, int indexTurnover1, int indexTurnover2){
	this->indexTurnover[0] = indexTurnover1;
	this->indexTurnover[1] = indexTurnover2;
	this->name = name;
	
	// e.g. string mapping = EKMFLGDQVZNTOWYHXUSPAIBRCJ
	// 		to lower ->      ekmflgdqvzntowyhxuspaibrcj
	// 		numeric:         4,9,10,2,7,1,23,9,13,16,3,8,2,9,10,18,7,3,0,22,6,13,5,20,4,10
	int numericEquiv;
	for (int i = 0; i < mapping.length(); i++){
		mapping[i] = tolower(mapping[i]);
		numericEquiv = int(mapping[i]);
		rotor[i][0] = i;
		rotor[i][1] = int(mapping[i]) - int('a' + i);
	}
}


// Copy Constructor
Rotor::Rotor(const Rotor& orig){
	memcpy(this->indexTurnover, orig.indexTurnover, 2*sizeof(int));
	memcpy(this->rotor, orig.rotor, 26*2*sizeof(int));
	this->name = orig.name;
}


// Move Constructor
Rotor::Rotor(Rotor&& orig){
	this->name = orig.name;
	this-indexTurnover
}





// = Operator using memcpy
Rotor& Rotor::operator = (const Rotor& orig){
	if (this != &orig){
		this->name = orig.name;
		memcpy(this->indexTurnover, orig.indexTurnover, 2*sizeof(int));
		memcpy(this->rotor, orig.rotor, 26*2*sizeof(int));
	}
	
	return *this;	// returns pointer to the object that we're writing into
}




// GET methods, because the object data is private
string Rotor::getName(){
	return name;
}


int Rotor::getIndexTurnover1(){
	return indexTurnover[0];
}


int Rotor::getIndexTurnover2(){
	return indexTurnover[1];
}


int Rotor::getInputAt(int n){
	return rotor[n][0];
}


int Rotor::getOutputAt(int n){
	return rotor[n][1];
}




// Rotates by left-shifting n spaces. n range: [0, +]
void Rotor::rotateBy(int n){
	// if n >= 26 (1 or more full rotations),
	// bring it down to an equivalent value that's less than 1 full rotation
	if (n >= 26)
		n = n % 26;
	
	int temp[26][2];
	memcpy(temp, rotor, 26*2*sizeof(int));
	
	for (int i = 0; i < 26-n; i++){
		for (int j = 0; j < 2; j++)
			rotor[i][j] = temp[i+n][j];
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < 2; j++)
			rotor[26-n+i][j] = temp[i][j];
	}
}




void Rotor::printRotor(){
	cout << "----------------------------------------\n";
	cout << "Rotor: " << name << '\n';
	cout << "Turnover starts at: " << char(indexTurnover[0] + 'a') << '\n';
	cout << "Initial char:\t";
	for (int i = 0; i < 26; i++){
		cout << char(rotor[i][0] + 'a');
	}
	cout << "\nMapped to:\t";
	for (int i = 0; i < 26; i++){
		cout << char(rotor[i][0] + rotor[i][1] + 'a');
	}
	cout << "\n----------------------------------------\n";
}

