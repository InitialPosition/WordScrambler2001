#include "stdafx.h"
#include <iostream>
#include "ScrambleFuncts.h"


int main()
{
	Scrambler scrambler;

	int shiftValue, initShift;
	std::string message, key;
	int mode;

	//read parameters
	std::cout << "#########################" << std::endl << "### WordScrambler2001 ###" << std::endl << "#########################" << std::endl << std::endl << "MESSAGE: ";
	std::cin >> message;
	std::cout << "KEY: ";
	std::cin >> key;
	std::cout << "INITIAL SHIFT: ";
	std::cin >> initShift;
	std::cout << "SHIFT VALUE: ";
	std::cin >> shiftValue;
	std::cout << "MODE (0: Encrypt, 1: Decrypt): ";
	std::cin >> mode;

	//set parameters
	scrambler.setOffset(initShift);
	scrambler.setShiftValue(shiftValue);

	scrambler.addOffset(shiftValue);

	if (key != "DEFAULT") {
		scrambler.setKey(key);
	}

	system("cls");

	//OUTPUT
	std::cout	<< "########## PARAMETERS ##########" << std::endl
				<< "MESSAGE:       " << message << std::endl
				<< "KEY:           " << key << std::endl
				<< "INITIAL SHIFT: " << initShift << std::endl
				<< "SHIFT VALUE:   " << shiftValue << std::endl;

	if (mode == 0) {
		std::cout << "MODE:          ENCRYPTION";
	}
	else if (mode == 1) {
		std::cout << "MODE:          DECRYPTION";
	}

	std::cout << std::endl << std::endl << "OUTPUT: ";

	//encrypt / decrypt
	if (mode == 0) {
		for (int i = 0; i < message.length(); i++) {
			std::cout << scrambler.encryptLetter(message.at(i));
		}
	}
	else if (mode == 1) {
		for (int i = 0; i < message.length(); i++) {
			std::cout << scrambler.decryptLetter(message.at(i));
		}
	}
	else {
		std::cout << "Unrecognized mode parameter, aborting" << std::endl;
	}
	

	std::cout << std::endl << std::endl;

	system("PAUSE");

    return 0;
}