#ifndef __SCRAMBLE_H
#define __SCRAMBLE_H

#include <string>

class Scrambler {
public:
	char encryptLetter(char letter);
	char decryptLetter(char letter);

	void setKey(std::string key);

	void addOffset(int n);
	void setOffset(int n);
	
	void setShiftValue(int n);
private:
	std::string alphabetA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string alphabetB = "";

	int currentOffset = 0;
	int shiftValue = 1;
};

#endif