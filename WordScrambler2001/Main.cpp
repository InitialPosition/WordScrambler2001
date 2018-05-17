#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ScrambleFuncts.h"
#include "base64.h"

#define MODE_ENCRYPT "-e"
#define MODE_DECRYPT "-d"
#define MODE_HELP "-help"
#define MODE_B64 "-base64"


int main(int argc, char* argv[])
{
	//seed the randomizer
	std::srand(std::time(nullptr));

	//initialize variables and instances
	Scrambler scrambler;
	int shiftValue, initShift, mode, b64;
	bool showKey = false;
	std::string message, key, line;
	std::string output = "";
	std::string version = "1.4";

	const int SPLASH_AMOUNT = 40;
	const char* splashs[SPLASH_AMOUNT] = {	"This is a splash message!", 
											"Completely random output!",
											"97% Bug Free!", 
											"Magic inside!", 
											"mov	ax,'00'", 
											"Where is my mind?", 
											"Snake? Snake! SNAAAAAKE!", 
											"Powered by C++!", 
											"Perfectly formatted source code!", 
											"EXTERMINATE!", 
											"This splash message will never appear! Wait... damn.", 
											"Use a better encryption please!", 
											"Hello, World!", 
											"Hi Ryan!", 
											"Hi Chris!", 
											"The most useless waste of HDD space!", 
											"Also try NodeScrambler2001!", 
											"Crazy letter manipulation!", 
											"Uses cstrings!", 
											"Also try DROP!", 
											"Also try Commodore Combat!", 
											"Help I am captivated and forced to write splash texts", 
											"Half Life 3 confirmed!", 
											"AEIOU.", 
											"Shoutouts to SimpleFlips", 
											"[ REDACTED ]", 
											"https://www.youtube.com/watch?v=oHg5SJYRHA0", 
											"Please check out my music!", 
											"Encryption? Where we're going, we won't need encryption!", 
											"This statement is true!", 
											"This statement is false!", 
											"Only uses one color!", 
											"The best Open-Source encryption on the market!", 
											"Dubstep is pretty nice actually", 
											"Listen to MDK!", 
											"Listen to TheFatRat!", 
											"Listen to Waterflame!", 
											"Sorry, I don't speak polish.", 
											"Now with Base64!", 
											"Better than MD5!"};
	std::string chosenSplash = splashs[rand() % SPLASH_AMOUNT];

	//read parameters
	if (argc <= 1) {
		//run in standalone mode
		std::cout <<	" __        __            _ ____                           _     _          ____   ___   ___  _ " << std::endl <<
						" \\ \\      / | _  _ __ __| / ___|  ___ _ __ __ _ _ __ ___ | |__ | | ___ _ _|___ \\ / _ \\ / _ \\/ |" << std::endl <<
						"  \\ \\ /\\ / / _ \\| \'__/ _` \\___ \\ / __| \'__/ _` | \'_ ` _ \\| \'_ \\| |/ _ | \'__|__) | | | | | | | |" << std::endl <<
						"   \\ V  V | (_) | | | (_| |___) | (__| | | (_| | | | | | | |_) | |  __| |  / __/| |_| | |_| | |" << std::endl <<
						"    \\_/\\_/ \\___/|_|  \\__,_|____/ \\___|_|  \\__,_|_| |_| |_|_.__/|_|\\___|_| |_____|\\___/ \\___/|_|" << std::endl << std::endl <<
						"Version " << version << ", (c) 2018 Syrapt0r" << std::endl <<
						chosenSplash << std::endl <<

		//read parameters
		std::endl << "MESSAGE: ";
		getline(std::cin, line);
		message += line;
		std::cout << "KEY (leave blank for random): ";
		getline(std::cin, line);
		key += line;
		std::cout << "INITIAL SHIFT: ";
		std::cin >> initShift;
		std::cout << "SHIFT VALUE: ";
		std::cin >> shiftValue;
		std::cout << "MODE (0: Encrypt, 1: Decrypt): ";
		std::cin >> mode;

		if (mode == 0) {
			std::cout << "CONVERT OUTPUT TO BASE64 (0: No, 1: Yes): ";
		}
		if (mode == 1) {
			std::cout << "IS INPUT BASE64 (0: No, 1: Yes): ";
		}
		std::cin >> b64;

		//set scrambler parameters
		scrambler.setOffset(initShift);
		scrambler.setShiftValue(shiftValue);

		scrambler.addOffset(shiftValue);

		//generate key if no key was given
		if (key == "") {
			showKey = true;
			key = scrambler.getRandomKey();
		}

		scrambler.setKey(key);

		std::cout << std::endl;

		//OUTPUT
		std::cout << "################################" << std::endl << std::endl;

		if (showKey) {
			std::cout << "KEY: " << key << std::endl;
		}
		std::cout << "OUTPUT: ";

		//encrypt / decrypt
		if (mode == 0) {
			//encrypt the message
			for (int i = 0; i < message.length(); i++) {
				output += scrambler.encryptLetter(message.at(i));
			}

			//if wanted, convert final output to base64
			if (b64 == 1) {
				output = base64_encode(output);
			}

			//finally, output the digest
			std::cout << output << std::endl;
		}
		else if (mode == 1) {
			//if input is base64, convert to encrypted string
			if (b64 == 1) {
				message = base64_decode(message);
			}

			//decrypt the string
			for (int i = 0; i < message.length(); i++) {
				output += scrambler.decryptLetter(message.at(i));
			}

			//finally, output the digest
			std::cout << output << std::endl;
		}
		else {
			std::cout << "Unrecognized mode parameter, aborting" << std::endl;
		}


		std::cout << std::endl << std::endl;

		system("PAUSE");
	}
	else {
		//run in parameter mode
		if (argc < 5) {
			if (strcmp(argv[1], MODE_HELP) == 0) {
				//show help
				std::cout << "                           WordScrambler2001 Help" << std::endl
					<< "------------------------------------------------------------------------------" << std::endl
					<< "Syntax: wordscrambler2001 <mode> <message> <key> <initial shift> <shift value>" << std::endl
					<< "-e				Encryption Mode" << std::endl
					<< "-d				Decryption Mode" << std::endl
					<< "key				The key to use for encryption/decryption. Optional." << std::endl
					<< "Initial Shift	The shifting done before the actual shifting. Should be between 0 and 50." << std::endl
					<< "Shift Value		The shifting done every letter. Should be between 0 and 50." << std::endl;
							//<< "-base64			If the output should be base64 encoded / If the input is base64 encoded. Optional." << std::endl;

				return 0;
			}
			else {
				std::cout << "Invalid parameters. Use -help to see help." << std::endl;
				return 1;
			}
		}
		else {
			if (argc == 6) {				//key given
				message = argv[2];
				key = argv[3];
				initShift = atoi(argv[4]);
				shiftValue = atoi(argv[5]);
			}

			if (argc == 5) {				//no key given
				message = argv[2];
				key = "";
				initShift = atoi(argv[3]);
				shiftValue = atoi(argv[4]);
			}

			//set parameters
			scrambler.setOffset(initShift);
			scrambler.setShiftValue(shiftValue);
			scrambler.addOffset(shiftValue);

			if (key == "") {
				key = scrambler.getRandomKey();
				std::cout << key << "|";
			}

			scrambler.setKey(key);

			//encrypt / decrypt
			if (strcmp(argv[1], MODE_ENCRYPT) == 0) {
				for (int i = 0; i < message.length(); i++) {
					std::cout << scrambler.encryptLetter(message.at(i));
				}
			} 
			else if (strcmp(argv[1], MODE_DECRYPT) == 0) {
				for (int i = 0; i < message.length(); i++) {
					std::cout << scrambler.decryptLetter(message.at(i));
				}
			}
			else {
				std::cout << "Unrecognized operation.";
				return 1;
			}
		}
	}

    return 0;
}