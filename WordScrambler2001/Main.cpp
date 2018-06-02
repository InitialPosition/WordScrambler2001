#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ScrambleFuncts.h"
#include "base64.h"

void mainFunc(Scrambler scrambler, int shiftValue, int initShift, int mode, int b64, bool showKey, std::string message, std::string key, bool cmdMode, bool VERBOSE_LOGGING) {
	std::string output = "";

	if (VERBOSE_LOGGING) {
		if (mode == 0) {
			std::cout << std::endl << "MODE: ENCRYPTION" << std::endl;
		}
		if (mode == 1) {
			std::cout << std::endl << "MODE: DECRYPTION" << std::endl;
		}
	}

	//set scrambler parameters
	scrambler.setOffset(initShift);
	scrambler.setShiftValue(shiftValue);
	scrambler.addOffset(shiftValue);
	if (VERBOSE_LOGGING) {
		std::cout << "Initialized Parameters: INITIAL OFFSET: " << initShift << ", SHIFT VALUE: " << shiftValue << std::endl;
	}

	//generate key if no key was given
	if (key == "") {
		showKey = true;
		key = scrambler.getRandomKey();
		if (VERBOSE_LOGGING) {
			std::cout << "No key given, generating random key..." << std::endl;
		}
	}

	if (b64 == 1 && showKey == false) {
		if (VERBOSE_LOGGING) {
			std::cout << "Key is Base64, decoding..." << std::endl;
		}
		key = base64_decode(key);
	}
	scrambler.setKey(key);
	if (VERBOSE_LOGGING) {
		std::cout << "Key set to " << key << std::endl;
	}

	//encrypt / decrypt
	if (mode == 0) {
		message = base64_encode(message);

		if (VERBOSE_LOGGING) {
			std::cout << "Message encoded, " << message.length() << " characters..." << std::endl;
			
		}
		
		for (int i = 0; i < message.length(); i++) {
			output += scrambler.encryptLetter(message.at(i));
		}

		if (b64 == 1) {
			if (VERBOSE_LOGGING) {
				std::cout << "Final Base64 mode requested, encoding..." << std::endl;
			}
			output = base64_encode(output);
		}
	}
	else if (mode == 1) {
		if (b64 == 1) {
			if (VERBOSE_LOGGING) {
				std::cout << "Message given in Base64, decoding..." << std::endl;
			}
			message = base64_decode(message);
		}

		for (int i = 0; i < message.length(); i++) {
			output += scrambler.decryptLetter(message.at(i));
		}

		if (VERBOSE_LOGGING) {
			std::cout << "Decoding final digest from Base64..." << std::endl;
		}
		output = base64_decode(output);
	}
	else {
		std::cerr << "Unrecognized mode parameter, aborting" << std::endl;
	}

	std::cout << std::endl;

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

	int shiftValue	= 0;
	int initShift	= 1;
	int mode		= 0;
	int b64			= 0;

	bool showKey			= false;
	bool VERBOSE_LOGGING	= false;

	std::string message, key, line;

	//read parameters
	if (argc <= 1) {
		std::string version = "1.6";
		const int SPLASH_AMOUNT = 43;
		const char* splashs[SPLASH_AMOUNT] = { "This is a splash message!",
												"Completely random output!",
												"97% Bug Free!",
												"Magic inside!",
												"mov	ax,'00'",
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
												"Help my boss forces me to write splash texts",
												"Half Life 3 confirmed!",
												"AEIOU.",
												"Shoutouts to SimpleFlips",
												"[ REDACTED ]",
												"Fork me on GitHub!",
												"Encryption? Where we're going, we won't need encryption!",
												"This statement is true!",
												"This statement is false!",
												"Only uses one color!",
												"The best Open-Source encryption on the market!",
												"Sorry, I don't speak polish.",
												"Now with Base64!",
												"Better than MD5!",
												"Finally supports full ASCII!",
												"output(random_text);",
												"Conke or Bepis, that is the question",
												"Can I pwease haww a better encwiption :3333",
												"P = NP", 
												"P != NP",
												"Very very good encryption (very)!", 
												"Very small overhead!", 
												"Organically grown!"};
		std::string chosenSplash = splashs[rand() % SPLASH_AMOUNT];

		//run in standalone mode
		std::cout << " __        __            _ ____                           _     _          ____   ___   ___  _ " << std::endl <<
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
		std::cout << "VERBOSE LOGGING (0: No, 1: Yes): ";
		std::cin >> VERBOSE_LOGGING;

		mainFunc(scrambler, shiftValue, initShift, mode, b64, showKey, message, key, false, VERBOSE_LOGGING);

		system("PAUSE");
	}
	else {
		//read in given parameters
		bool hasMode = false;
		bool hasMessage = false;
		bool hasInit = false;
		bool hasShift = false;

		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
			showHelp();
			return 0;
		}

		b64 = 0;
		for (int i = 1; i < argc; i++) {
			//determine user mode
			if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--encrypt") == 0) {
				hasMode = true;
				mode = 0;
			}
			if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decrypt") == 0) {
				hasMode = true;
				mode = 1;
			}

			//get message
			if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--message") == 0) {
				hasMessage = true;
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
				hasInit = true;
				initShift = atoi(argv[i + 1]);
				i++;
			}
			if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--shift-value") == 0) {
				hasShift = true;
				shiftValue = atoi(argv[i + 1]);
				i++;
			}

			//toggle base64 mode
			if (strcmp(argv[i], "-b64") == 0 || strcmp(argv[i], "--base64") == 0) {
				b64 = 1;
			}

			//toggle verbose mode
			if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
				VERBOSE_LOGGING = true;
			}
		}

		if (hasMode && hasMessage && hasInit && hasShift) {
			mainFunc(scrambler, shiftValue, initShift, mode, b64, showKey, message, key, true, VERBOSE_LOGGING);
		}
		else {
			std::cerr << "Invalid parameters. Use --help or -h to show help.";
			return 1;
		}
	}

	return 0;
}