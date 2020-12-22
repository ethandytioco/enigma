//	name:	enigma.cpp
//	author:	Ethan Dy Tioco
//	desc:	Implementing the functions for the Enigma class

#include <iostream>
#include <string>
#include <cstring>			// <-- memcpy(destination*, source*, sizeInBytes)
#include <cctype>			// <-- isupper(char), tolower(char)
#include <unordered_map>	// <-- for dictionary/labels to be outputted based on a numeric key
#include <algorithm>		// <-- .erase(), .remove(), for removing whitespace

#include "enigma.h"			// <-- class definition for enigma
#include "rotor.h"			// <-- need this to incorporate rotors
using namespace std;

Enigma::Enigma(){
	// If the user doesn't configure the enigma machine before using it, I'll set the default settings to:
	// reflector:						UKW-B
	// rotors (left, center, right):	III, II, I
	// ringstellung(L, C, R):			A,   A,  A		<-- ring offset (right shift: a = 0)
	// grundstelllung (L, C, R):		A,   A,  Z		<-- starting visible position
	// steckering:						no steckering
	//
	// I'm also setting rotorBank to have rotors I-VIII, UKW-A, UKW-B, and a stecker-board
	rotorBank.emplace(1, Rotor("I",		"EKMFLGDQVZNTOWYHXUSPAIBRCJ", 16,	-1));	// <-- turnover at Q
	rotorBank.emplace(2, Rotor("II",	"AJDKSIRUXBLHWTMCQGZNPYFVOE", 4,	-1));	// <-- turnover at E
	rotorBank.emplace(3, Rotor("III",	"BDFHJLCPRTXVZNYEIWGAKMUSQO", 21,	-1));	// <-- turnover at V
	rotorBank.emplace(4, Rotor("IV",	"ESOVPZJAYQUIRHXLNFTGKDCMWB", 9,	-1));	// <-- turnover at J
	rotorBank.emplace(5, Rotor("V",		"VZBRGITYUPSDNHLXAWMJQOFECK", 25,	-1));	// <-- turnover at Z
	rotorBank.emplace(6, Rotor("VI",	"JPGVOUMFYQBENHZRDKASXLICTW", 25,	12));	// <-- turnovers at Z and M
	rotorBank.emplace(7, Rotor("VII",	"NZJHGRCXMYSWBOUFAIVLPEKQDT", 25,	12));	// <-- turnovers at Z and M
	rotorBank.emplace(8, Rotor("VIII",	"FKQHTLXOCBJSPDZRAMEWNIUYGV", 25,	12));	// <-- turnovers at Z and M
	
	rotorBank.emplace(9, Rotor("UKW-A",			"EJMZALYXVBWFCRQUONTSPIKHGD", -1,	-1));
	rotorBank.emplace(10, Rotor("UKW-B",		"YRUHQSLDPXNGOKMIEBFZCWVJAT", -1,	-1));
	rotorBank.emplace(11, Rotor("Steckerbrett",	"ABCDEFGHIJKLMNOPQRSTUVWXYZ", -1,	-1));
	
	reflector	= rotorBank.at(10);	// <-- UKW-B
	left		= rotorBank.at(3);	// <-- III
	center		= rotorBank.at(2);	// <-- II
	right		= rotorBank.at(1);	// <-- I
	plugboard	= rotorBank.at(11);	// <-- Steckerbrett. initially has no plugs. will be set in configure()
	
	ringsetting_l = 'a';
	ringsetting_c = 'a';
	ringsetting_r = 'a';
	
	groundsetting_l = 'a';
	groundsetting_c = 'd';
	groundsetting_r = 'q';
	
	ringstellung(ringsetting_l, ringsetting_c, ringsetting_r);
	grundstellung(groundsetting_l, groundsetting_c, groundsetting_r);
}

void Enigma::menu(){
	int menuChoice = 0;
	while(true){
		cout << "\n======= Enigma Machine 0.1: Menu =======\n\n";
		cout << "[1] - Configure Enigma   <-- do this first\n";
		cout << "[2] - View Configuration\n";
		cout << "[3] - Encrypt/Decrypt\n";
		cout << "[4] - Exit\n";
		cout << "[5] - Rotor diagnostic (dev)\n";
		cout << "entry: ";
		cin >> menuChoice;
		
		switch(menuChoice){
			case 1:
				cout << ".\n.\n.\n.\n.\n.\n.\n.\n";
				configure();
				cout << ".\n.\n.\n.\n.\n.\n.\n.\n";
				break;
			case 2:
				cout << ".\n.\n.\n.\n.\n.\n.\n.\n";
				viewConfiguration();
				cout << ".\n.\n.\n.\n.\n.\n.\n.\n";
				break;
			case 3:
				cout << ".\n.\n.\n.\n.\n.\n.\n.\n";
				useEnigma();
				cout << ".\n.\n.\n.\n.\n.\n.\n.\n";
				break;
			case 4:
				cout << ".\n.\n.\n.\n.\n.\n.\n";
				cout << "\n...exiting\n";
				return;
				break;
			case 5:
				cout << ".\n.\n.\n.\n.\n.\n.\n";
				diagnostic();
				cout << ".\n.\n.\n.\n.\n.\n.\n.\n";
				break;
			default:
				cin.ignore();
				cout << ".\n.\n.\n.\n.\n.\n.\n.\n";
				cout << "\n[error] unrecognized entry\n";
				cout << ".\n.\n.\n.\n.\n.\n.\n.\n";
				break;
		}
	}
}

void Enigma::configure(){
	int selectRotor;
	string steckerPairs;
	cout << "========= Enigma Configuration =========\n\n";
	cout << "-------------- Walzenlage --------------\n";
	cout << "Supported rotors. Enter the number corr-\n";
	cout << "esponding to the rotor you want to use.\n";
	cout << "[1]  - I\n";
	cout << "[2]  - II\n";
	cout << "[3]  - III\n";
	cout << "[4]  - IV\n";
	cout << "[5]  - V\n";
	cout << "[6]  - VI\n";
	cout << "[7]  - VII\n";
	cout << "[8]  - VIII\n";
	cout << "----------------------------------------\n";		// <-- 40 dashes.
	cout << "Left Rotor\t(e.g. 3): ";
	cin >> selectRotor;
	left = rotorBank.at(selectRotor);
	
	cout << "Center Rotor\t(e.g. 2): ";
	cin >> selectRotor;
	center = rotorBank.at(selectRotor);
	
	cout << "Right Rotor\t(e.g. 1): ";
	cin >> selectRotor;
	right = rotorBank.at(selectRotor);
	
	cout << "\n\n";
	
	cout << "------------- Ringstellung -------------\n";
	cout << "Enter the ring settings as letters.\n";
	cout << "Left Rotor\t(e.g. a): ";
	cin >> ringsetting_l;
	cout << "Center Rotor\t(e.g. a): ";
	cin >> ringsetting_c;
	cout << "Right Rotor\t(e.g. a): ";
	cin >> ringsetting_r;
	
	ringstellung(ringsetting_l, ringsetting_c, ringsetting_r);
	
	cout << "\n\n";
	
	cout << "------------- Grundstellung ------------\n";
	cout << "Enter the starting positions as letters.\n";
	cout << "Left Rotor\t(e.g. a): ";
	cin >> groundsetting_l;
	cout << "Center Rotor\t(e.g. a): ";
	cin >> groundsetting_c;
	cout << "Right Rotor\t(e.g. z): ";
	cin >> groundsetting_r;
	
	grundstellung(groundsetting_l, groundsetting_c, groundsetting_r);
	
	cout << "\n\n";
	
	cout << "---------- Steckerverbindungen ---------\n";
	cout << "Write your plugboard letters in pairs,\n";
	cout << "with spaces in between. TEN letter pairs\n";
	cout << "maximum.\n\n";
	cout << "Letter pairs: ";
	cin.ignore();
	getline(cin, steckerPairs);
	
	steckerPairs = scrubInput(steckerPairs);
	if (steckerPairs.length() % 2 != 0)
		cout << "[ERROR]: odd-number of letters. Stecker input ignored.\n";
	else
		steckerbrett(steckerPairs);
}

// I think ringstellung does a right-shift on rotor[], but not the notches
void Enigma::ringstellung(char l, char c, char r){
	// rotateBy(int n) performs a left-shift.
	// to perform a rightshift, we're calling rotateBy(array size - n)
	// and our rotors are [26][3], so we'll hard-code array size as 26
	
	// NOTE: the turnover index must not change
	
	left.ringstellung(26 - int(l - 'a'));
	center.ringstellung(26 - int(c - 'a'));
	right.ringstellung(26 - int(r - 'a'));
}

// and grundstelling does a left-shift on the rotor[]
void Enigma::grundstellung(char l, char c, char r){
	left.rotateBy(int(l - 'a'));
	center.rotateBy(int(c - 'a'));
	right.rotateBy(int(r - 'a'));
}

// configuring Rotor plugboard here. string pairs should be all lower case, no spaces, even amt of characters
void Enigma::steckerbrett(string pairs){
	char first, second;
	for (int i = 0; i < pairs.length(); i += 2){
		first = pairs[i];
		second = pairs[i+1];
	}
}

void Enigma::viewConfigurationLite(){
	cout << "Rotors (left, center, right):\t" << this->left.getName() << ", " << this->center.getName() << ", " << this->right.getName() << '\n';
	cout << "Ringstellung (L, C, R):\t\t" << char(toupper(ringsetting_l)) << ", " << char(toupper(ringsetting_c)) << ", " << char(toupper(ringsetting_r)) << '\n';
	cout << "Grundstellung (L, C, R):\t" << char(toupper(groundsetting_l)) << ", " << char(toupper(groundsetting_c)) << ", " << char(toupper(groundsetting_r)) << '\n';
	cout << "Steckerbrett:\t\t\t" << "." << endl;
}

void Enigma::viewConfiguration(){
	cout << "========= Current Configuration ========\n";
	viewConfigurationLite();
	
	//this->left.printRotor();
	//this->center.printRotor();
	//this->right.printRotor();
}

void Enigma::useEnigma(){
	string input, output = "";
	int inChannel, outChannel;
	cout << "=========== Encrypt / Decrypt ==========\n";
	viewConfigurationLite();
	cout << "\n";
	cout << "Note: Accepts only letters a-z.\n";
	cout << "      Spaces, numbers, and special char-\n";
	cout << "      acters not allowed.\n\n";
	
	
	
	cout << "Input:\t";
	cin.ignore();
	getline(cin, input);
	input = scrubInput(input);		// <-- input is now all lowercase alphabet. no spaces, no numbers
	
	// ready for char-by-char processing.
	for (int i = 0; i < input.length(); i++){
		// first, do rotation. also, update grundstellung to what's currently showing
		rotation();
		
		// right ring
		inChannel = input[i] - 'a';
		outChannel = inChannel + right.getFirstPassResult(inChannel);
		outChannel = intForceWithinRange(outChannel);
		// cout << "Rotor " << right.getName() << ":\t" << char(inChannel + 'a') << " -> " << char(outChannel + 'a') << '\n';
		
		// center ring
		inChannel = outChannel;
		outChannel = inChannel + center.getFirstPassResult(inChannel);
		outChannel = intForceWithinRange(outChannel);
		// cout << "Rotor " << center.getName() << ":\t" << char(inChannel + 'a') << " -> " << char(outChannel + 'a') << '\n';
		
		// left ring
		inChannel = outChannel;
		outChannel = inChannel + left.getFirstPassResult(inChannel);
		outChannel = intForceWithinRange(outChannel);
		// cout << "Rotor " << left.getName() << ":\t" << char(inChannel + 'a') << " -> " << char(outChannel + 'a') << '\n';
		
		// reflector (btw i'm led to believe that the reflector doesn't rotate)
		inChannel = outChannel;
		outChannel = inChannel + reflector.getFirstPassResult(inChannel);
		outChannel = intForceWithinRange(outChannel);
		// cout << "Reflector:\t" << char(inChannel + 'a') << " -> " << char(outChannel + 'a') << '\n';
		
		// feed back to left ring
		inChannel = outChannel;
		for (int j = 0; j < 26; j++){
			if (intForceWithinRange((j + left.getFirstPassResult(j))) == inChannel){
				outChannel = inChannel + left.getSecondPassResult(j);
				outChannel = intForceWithinRange(outChannel);
				break;
			}
		}
		// cout << "Rotor " << left.getName() << ":\t" << char(inChannel + 'a') << " -> " << char(outChannel + 'a') << '\n';
		
		// feed back to center ring
		inChannel = outChannel;
		for (int j = 0; j < 26; j++){
			if (intForceWithinRange((j + center.getFirstPassResult(j))) == inChannel){
				outChannel = inChannel + center.getSecondPassResult(j);
				outChannel = intForceWithinRange(outChannel);
				break;
			}
		}
		// cout << "Rotor " << center.getName() << ":\t" << char(inChannel + 'a') << " -> " << char(outChannel + 'a') << '\n';
		
		// feed back to right ring
		inChannel = outChannel;
		for (int j = 0; j < 26; j++){
			if (intForceWithinRange((j + right.getFirstPassResult(j))) == inChannel){
				outChannel = inChannel + right.getSecondPassResult(j);
				outChannel = intForceWithinRange(outChannel);
				break;
			}
		}
		// cout << "Rotor " << right.getName() << ":\t" << char(inChannel + 'a') << " -> " << char(outChannel + 'a') << '\n';
		//cout << '\n';
		
		// after 5 letters, put a space in the output
		if ((i != 0) && ((i % 5) == 0))
			output += ' ';
		output += char(outChannel + 'a');
	}
	
	cout << '\n';
	cout << "Output:\t" << output << "\n";
}


// takes in a string input and removes any character that's not a-z
string Enigma::scrubInput(string input){
	for (int i = 0; i < input.length(); i++){
		input[i] = tolower(input[i]);
		if (input[i] < 'a' || input[i] > 'z'){
			input.erase(i, 1);
			i--;
		}
	}
	return input;
}



void Enigma::rotation(){
	// cout << "Rotor position:\t" << char(left.getInputAt(0) + 'a') << char(center.getInputAt(0) + 'a') << char(right.getInputAt(0) + 'a') << " -> ";

	// double step
	if (center.getTurnoverValueAt(0) == 1){			// <-- double step.
		center.rotateBy(1);
		left.rotateBy(1);
	}
	else if (right.getTurnoverValueAt(0) == 1){		// <-- the thing before double-step
		center.rotateBy(1);
	}
	right.rotateBy(1); 								// <-- right rotor always rotates.
	
	// cout << char(left.getInputAt(0) + 'a') << char(center.getInputAt(0) + 'a') << char(right.getInputAt(0) + 'a') << '\n';
	// cout << "Rotate at:\t" << char(left.getIndexTurnover1() + 'a') << char(center.getIndexTurnover1() + 'a') << char(right.getIndexTurnover1() + 'a') << '\n';
}


int Enigma::intForceWithinRange(int n){
	if (n >= 26)
		n = n % 26;
	while (n < 0)
		n += 26;
	
	return n;
}


void Enigma::diagnostic(){
	cout << "==== rotor right ====\n";
	right.diagnostic();
	/*
	for (int i = 0; i < 26; i++){
		right.rotateBy(1);
		right.diagnostic();
	}
	*/
	
	cout << "\n\n==== rotor center ====\n";
	center.diagnostic();
	/*
	for (int i = 0; i < 26; i++){
		right.rotateBy(1);
		right.diagnostic();
	}
	*/
	
	cout << "\n\n==== rotor left ====\n";
	left.diagnostic();
	/*
	for (int i = 0; i < 26; i++){
		right.rotateBy(1);
		right.diagnostic();
	}
	*/
}