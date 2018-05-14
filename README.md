# WordScrambler2001
A (very simple, insecure) monoalphabetic substitution cipher

This cipher works by replacing every letter in a string with the corresponding letter in the key alphabet, adding a changing offset.

## Use cases
- Please no

## Usage
You can use the program in standalone mode or using a command line.
In standalone mode, enter your message, your key, the offset values and the mode.
In command line mode, use "wordscrambler2001 <mode> <message> <key> <initial shift> <shift>" where mode is "-e" for encrypting or "-d" for decrypting.
Your key needs to contain the following characters: ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,!?§$%&/()=-_:;
These are the only characters you can encrypt.

## Roadmap
- Optimize parameter mode
- Allow random key generation
- Simplify usage overall