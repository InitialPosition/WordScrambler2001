#include "stdafx.h"
#include "ScrambleFuncts.h"
#include <algorithm>

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
			break;
		}
	}
	//fuk
	//(comment preserved for historic significance)

	digest = alphabetB.at((letterVal + currentOffset) % alphabetB.length());
	addOffset(shiftValue);

	return digest;
}

/*
	Decrypts the given character, increments the letter offset
	and returns the decrypted character
*/
char Scrambler::decryptLetter(char letter) {
	char digest;
	int shiftChar = 0;
	int letterVal = 0;

	for (int i = 0; i < alphabetB.length(); i++) {
		if (letter == alphabetB.at(i)) {
			letterVal = i;
			break;
		}
	}

	shiftChar = letterVal - currentOffset;
	while (shiftChar < 0) {
		shiftChar += alphabetA.length();
	}

	digest = alphabetA.at(shiftChar);
	addOffset(shiftValue);

	return digest;
}

/*
	Sets the cipher key.
*/
void Scrambler::setKey(std::string key) {
	this->alphabetB = key;
}

/*
	Sets the cipher key to a random key
*/
std::string Scrambler::getRandomKey() {
	std::string randomKey = alphabetA;
	random_shuffle(randomKey.begin(), randomKey.end());

	return randomKey;
}

/*
	Adds n to the current offset (works with negative numbers)
*/
void Scrambler::addOffset(int n) {
	this->currentOffset += n;

	if (this->currentOffset < 0) {
		this->currentOffset += alphabetA.length();
	}
}

/*
Sets the current offset to n
*/
void Scrambler::setOffset(int n) {
	this->currentOffset = n;
}

/*
Sets the shift value to n
*/
void Scrambler::setShiftValue(int n) {
	this->shiftValue = n;
}