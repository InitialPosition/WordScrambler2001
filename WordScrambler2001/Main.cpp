#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ScrambleFuncts.h"
#include "base64.h"

void mainFunc(Scrambler scrambler, int shiftValue, int initShift, int mode, int b64, bool showKey, std::string message, std::string key, bool cmdMode) {
	std::string output = "";

	//set scrambler parameters
	scrambler.setOffset(initShift);
	scrambler.setShiftValue(shiftValue);
	scrambler.addOffset(shiftValue);

	//generate key if no key was given
	if (key == "") {
		showKey = true;
		key = scrambler.getRandomKey();
	}

	if (b64 == 1 && showKey == false) {
		scrambler.setKey(base64_decode(key));
	}
	else {
		scrambler.setKey(key);
	}
	std::cout << std::endl;

	//OUTPUT
	if (!cmdMode) {
		std::cout << "################################" << std::endl << std::endl;

		if (showKey) {
			if (b64 == 1) {
				std::cout << "KEY: " << base64_encode(key) << std::endl;
			}
			else {
				std::cout << "KEY: " << key << std::endl;
			}
		}
		std::cout << "OUTPUT: ";
	}
	else {
		if (showKey) {
			if (b64 == 1) {
				std::cout << base64_encode(key) << "|";
			}
			else {
				std::cout << key << "|";
			}
		}
	}

	//encrypt / decrypt
	if (mode == 0) {
		for (int i = 0; i < message.length(); i++) {
			output += scrambler.encryptLetter(message.at(i));
		}

		if (b64 == 1) {
			output = base64_encode(output);
		}
	}
	else if (mode == 1) {
		if (b64 == 1) {
			message = base64_decode(message);
		}

		for (int i = 0; i < message.length(); i++) {
			output += scrambler.decryptLetter(message.at(i));
		}
	}
	else {
		std::cerr << "Unrecognized mode parameter, aborting" << std::endl;
	}

	std::cout << output << std::endl << std::endl;
}

void showHelp() {
	std::cout << std::endl << "                           WordScrambler2001 Help" << std::endl
		<< "------------------------------------------------------------------------------" << std::endl
		<< "Syntax: WordScrambler2001.exe <parameters>" << std::endl
		<< "-e		| --encrypt				Encryption Mode" << std::endl
		<< "-d		| --decrypt				Decryption Mode" << std::endl
		<< "-m		| --message				The message to en-/decrypt" << std::endl
		<< "-k		| --key					The cipher key (Optional)" << std::endl
		<< "-i		| --initial-shift			The initial cipher shift" << std::endl
		<< "-s		| --shift-value				The shift value applied after every letter" << std::endl
		<< "-b64		| --base64				If the input/output is in Base64 (Optional)" << std::endl;
}

int main(int argc, char* argv[])
{
	//seed the randomizer
	std::srand(std::time(nullptr));

	//initialize variables and instances
	Scrambler scrambler;
	int shiftValue, initShift, mode, b64;
	bool showKey = false;
	std::string message, key, line;
	std::string version = "1.4.2";

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

		mainFunc(scrambler, shiftValue, initShift, mode, b64, showKey, message, key, false);

		system("PAUSE");
	}
	else {
		//read in given parameters
		if (argc < 9) {
			//help
			if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
				showHelp();
				return 0;
			}
			else {
				std::cerr << "Invalid parameters. Use --help or -h to show help.";
				return 1;
			}
		}
		else {
			b64 = 0;
			for (int i = 1; i < argc; i++) {
				//determine user mode
				if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--encrypt") == 0) {
					mode = 0;
				}
				if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decrypt") == 0) {
					mode = 1;
				}

				//get message
				if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--message") == 0) {
					message = argv[i + 1];
					i++;
				}

				//get key
				if (strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--key") == 0) {
					key = argv[i + 1];
					i++;
				}

				//get shift values
				if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--initial-shift") == 0) {
					initShift = atoi(argv[i + 1]);
					i++;
				}
				if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--shift-value") == 0) {
					shiftValue = atoi(argv[i + 1]);
					i++;
				}

				//toggle base64 mode
				if (strcmp(argv[i], "-b64") == 0 || strcmp(argv[i], "--base64") == 0) {
					b64 = 1;
				}
			}

			mainFunc(scrambler, shiftValue, initShift, mode, b64, showKey, message, key, true);
		}
	}

    return 0;
}