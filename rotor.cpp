//	name:	rotor.cpp
//	author:	Ethan Dy Tioco
//	desc:	Implementing the functions for the Rotor class

#include <iostream>
#include <string>
#include <algorithm>		// <-- remove whitespace functionality. also, swap()
#include "rotor.h"
using namespace std;

// Constructor - default
// rotor is a 2D array that's flattened to 1D. it's 26 sets of {int, int}. row major order.
Rotor::Rotor(): name(""), abcMapping(""), rotor(new int[26*3]), indexTurnover(new int[2]){}


// Constructor- with params
Rotor::Rotor(string name, string mapping, int indexTurnover1, int indexTurnover2): name(name), abcMapping(mapping), rotor(new int[26*3]), indexTurnover(new int[2]){
	this->indexTurnover[0] = indexTurnover1;
	this->indexTurnover[1] = indexTurnover2;
	
	// e.g. string mapping = EKMFLGDQVZNTOWYHXUSPAIBRCJ
	// 		to lower ->      ekmflgdqvzntowyhxuspaibrcj
	// 		numeric:         4,10,12,5,11,6,3,...
	int numericEquiv;
	int numericInRange;
	for (int i = 0; i < abcMapping.length(); i++){
		abcMapping[i] = tolower(abcMapping[i]);
		numericEquiv = int(abcMapping[i]) - int('a');
		
		rotor[i*3 + 0] = i;
		rotor[i*3 + 1] = numericEquiv;
		rotor[i*3 + 2] = 0;		// initialize turnover value at 0 (false)
	}
	
	// if indexTurnover has a non-negative value, use it as an index
	// to the rotor array, and set that turnover value ([...][2]) at 1 (true)
	if (indexTurnover[0] > 0)
		rotor[indexTurnover[0]*3 + 2] = 1;
	if (indexTurnover[1] > 0)
		rotor[indexTurnover[1]*3 + 2] = 1;
}


// Copy Constructor
Rotor::Rotor(const Rotor& orig): name(orig.name), abcMapping(orig.abcMapping), rotor(new int[26*3]), indexTurnover(new int[2]){
	memcpy(rotor, orig.rotor, 26*3*sizeof(int));
	memcpy(indexTurnover, orig.indexTurnover, 2*sizeof(int));
}


// Move Constructor
Rotor::Rotor(Rotor&& orig): name(orig.name), abcMapping(orig.abcMapping), rotor(orig.rotor), indexTurnover(orig.indexTurnover){
	orig.rotor = nullptr;
	orig.indexTurnover = nullptr;
}


// Destructor - very needed, since we're making new int []'s
Rotor::~Rotor(){
	delete [] rotor;
	delete [] indexTurnover;
}


// = Operator using the copy-and-swap method
Rotor& Rotor::operator = (Rotor copy){
	name = copy.name;
	abcMapping = copy.abcMapping;
	swap(rotor, copy.rotor);
	swap(indexTurnover, copy.indexTurnover);
	return *this;	// returns pointer to the object that we're writing into
}




// GET methods, because the object data is private
string Rotor::getName(){
	return name;
}

string Rotor::getStringMapping(){
	return abcMapping;
}

int Rotor::getIndexTurnover1(){
	return indexTurnover[0];
}

int Rotor::getIndexTurnover2(){
	return indexTurnover[1];
}

int Rotor::getFirstPassResult(int n){
	// forces n to be in range [0-26]
	if (n >= 26)
		n = n % 26;
	while (n < 0)
		n += 26;
	
	return rotor[n*3 + 1] - rotor[n*3 + 0]; // e.g. {A -> E} = 4 - 0 = +4
}

int Rotor::getSecondPassResult(int n){
	// forces n to be in range [0-26]
	if (n >= 26)
		n = n % 26;
	while (n < 0)
		n += 26;
	return rotor[n*3 + 0] - rotor[n*3 + 1]; // e.g. {A <- E} = 0 - 4 = -4
}

int Rotor::getInputAt(int n){
	// forces n to be in range [0-26]
	if (n >= 26)
		n = n % 26;
	while (n < 0)
		n += 26;
	return rotor[n*3 + 0];
}

int Rotor::getOutputAt(int n){
	// forces n to be in range [0-26]
	if (n >= 26)
		n = n % 26;
	while (n < 0)
		n += 26;
	return rotor[n*3 + 1];
}

int Rotor::getTurnoverValueAt(int n){
	// forces n to be in range [0-26]
	if (n >= 26)
		n = n % 26;
	while (n < 0)
		n += 26;
	return rotor[n*3 + 2];
}

void Rotor::setInput(char value, int n){
	// forces n to be in range [0-26]
	if (n >= 26)
		n = n % 26;
	while (n < 0)
		n += 26;
	
	rotor[n*3 + 0] = int(value - 'a');
}

void Rotor::setOutput(char value, int n){
	// forces n to be in range [0-26]
	if (n >= 26)
		n = n % 26;
	while (n < 0)
		n += 26;
		
	rotor[n*3 + 1] = int(value - 'a');
}




// Rotates by left-shifting n spaces. n range: [0, +]
void Rotor::rotateBy(int n){
	// if n >= 26 (1 or more full rotations),
	// bring it down to an equivalent value that's less than 1 full rotation
	if (n >= 26)
		n = n % 26;
	
	int temp[26*3];
	memcpy(temp, rotor, 26*3*sizeof(int));
	
	for (int i = 0; i < 26-n; i++){
		for (int j = 0; j < 3; j++)
			rotor[i*3 + j] = temp[(i+n)*3 + j];
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < 3; j++)
			rotor[(26-n+i)*3 + j] = temp[i*3 + j];
	}
}




void Rotor::ringstellung(int n){
	// if n >= 26 (1 or more full rotations),
	// bring it down to an equivalent value that's less than 1 full rotation
	if (n >= 26)
		n = n % 26;
	
	int temp[26*3];
	memcpy(temp, rotor, 26*3*sizeof(int));
	
	for (int i = 0; i < 26-n; i++){
		for (int j = 0; j < 2; j++)
			rotor[i*3 + j] = temp[(i+n)*3 + j];
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < 2; j++)
			rotor[(26-n+i)*3 + j] = temp[i*3 + j];
	}
}



void Rotor::printRotor(){
	cout << "----------------------------------------\n";
	cout << "Rotor: " << name << '\n';
	cout << "Turnover starts at: ";
	
	if (indexTurnover[0] > 0)
		cout << char(indexTurnover[0] + 'a');
	if (indexTurnover[1] > 0)
		cout << ", and " << char(indexTurnover[1] + 'a');
	cout << '\n';
	
	cout << "Initial mapping:\n";
	cout << "input:\t\tabcdefghijklmnopqrstuvwxyz\n";
	cout << "map:\t\t" << abcMapping;
	
	cout << "\n\n";
	
	cout << "Current mapping:\n";
	cout << "input:\t\t";
	for (int i = 0; i < 26; i++){
		cout << char(rotor[i*3 + 0] + 'a');
	}
	cout << "\noutput:\t\t";
	for (int i = 0; i < 26; i++){
		cout << char(rotor[i*3 + 1] + 'a');
	}
	cout << "\nturnover:\t";
	for (int i = 0; i < 26; i++){
		if (rotor[i*3 + 2] < 1)
			cout << ' ';
		else
			cout << '^';
	}
	cout << "\n----------------------------------------\n";
}

void Rotor::diagnostic(){
	cout << "input\t\t";
	for (int i = 0; i < 26; i++){
		cout << rotor[i*3 + 0] << '\t';
	}
	cout << "\n\t\t";
	for (int i = 0; i < 26; i++){
		cout << char(rotor[i*3 + 0] + 'a') << '\t';
	}
	cout << "\noutput:\t\t";
	for (int i = 0; i < 26; i++){
		cout << rotor[i*3 + 1] << '\t';
	}
	cout << "\n\t\t";
	for (int i = 0; i < 26; i++){
		cout << char(rotor[i*3 + 1] + 'a') << '\t';
	}
	cout << "\nturnover:\t";
	for (int i = 0; i < 26; i++){
		cout << rotor[i*3 + 2] << '\t';
	}
	cout << '\n';
}

