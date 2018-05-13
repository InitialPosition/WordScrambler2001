#include "stdafx.h"
#include "ScrambleFuncts.h"
//#include <iostream>

//bool debug = false;
/*
Encrypts the given character, increments the letter offset
and returns the encrypted character
*/
char Scrambler::encryptLetter(char letter) {
	char digest;
	int letterVal = 0;

	for (int i = 0; i < alphabetA.length(); i++) {
		if (letter == alphabetA.at(i)) {
			letterVal = i;
			continue;
		}
	}
	//std::cout << "ENC: Letter found at position " << letterVal << std::endl;
	//std::cout << "ENC: Output letter: " << (letterVal + currentOffset) % alphabetB.length() << std::endl;
	//fuk

	digest = alphabetB.at((letterVal + currentOffset) % alphabetB.length());
	addOffset(shiftValue);

	return digest;
}

char Scrambler::decryptLetter(char letter) {
	char digest;
	int shiftChar = 0;
	int letterVal = 0;

	for (int i = 0; i < alphabetB.length(); i++) {
		if (letter == alphabetB.at(i)) {
			letterVal = i;
			continue;
		}
	}

	shiftChar = letterVal - currentOffset;
	while (shiftChar < 0) {
		shiftChar += alphabetA.length();
	}

	//std::cout << std::endl << "DEC: " << shiftChar << std::endl;

	digest = alphabetA.at(shiftChar);
	addOffset(shiftValue);

	return digest;
}

void Scrambler::setKey(std::string key) {
	//std::cout << "Key set to " << key << std::endl;

	this->alphabetB = key;
}

/*
Adds n to the current offset (works with negative numbers)
*/
void Scrambler::addOffset(int n) {
	this->currentOffset += n;

	if (this->currentOffset < 0) {
		this->currentOffset += alphabetA.length();
	}

	//std::cout << "ADDOFFSET: Offset is now " << currentOffset << std::endl;
}

/*
Sets the current offset to n
*/
void Scrambler::setOffset(int n) {
	this->currentOffset = n;
	/*
	if (mode == 1) {
	this->currentOffset = alphabetB.find(firstChar);
	}
	*/
	//std::cout << "SETOFFSET: Offset is now " << currentOffset << std::endl;
}

/*
Sets the shift value to n
*/
void Scrambler::setShiftValue(int n) {
	this->shiftValue = n;

	//std::cout << "Setting Shift Value to " << n << std::endl;
}