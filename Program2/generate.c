#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/****************************************************************
	Function declarations.
*************************************************************** */

void generateSpellings  (char [], int);
void convert (char phone[], int* phone_int);
void print_if_good (int, char[], int[]);
int isvowel (char);

/****************************************************************
main( )
input
	Character array that is used to store user input.
	Its size is greater than two characters in order to 
	accommodate responses such as yes/no and possibly
	other unpredictable user responses. (See a tutor for
	an explanation.)
phone
	Character array used to store the actual phone number
	entered by the user.  Space is allocated for seven
	digits and the corresponding carriage return.
maxNumConsonant
	User-entered value that filters out those
	numbers with too many consonants.
goahead
	true/false flag that determines whether or not
	the user wants to test another number.
*************************************************************** */

int main ( ) {
	int maxNumConsonant;
	int goahead;
	char input[8];
	char phone[8];
	
	goahead = true;
	while (goahead) {
	/* This part of the code gathers user data.  The use of puts and gets is illustrated here.  
	puts sends its char array to standard output followed by a carriage return.  gets puts 
	everything in the standard input up to the carriage return into a character array.  In place 
	of the carriage return, puts has a '\0' to signify the end of the string. */
		puts ("This program finds words associated with phone numbers.\n\n");
		puts ("phone numbers\n\n");
		puts("What is the maximum number of consonants you would like");
		puts("the generated word to possess?");
		puts ("(note: 0's and 1's are considered consonants)");
                scanf ("%7s", input);
		
		/* Each digit read in as a character needs to be converted to a number for comparison pur-
		poses later.  The difference between the ASCII value of the user input and the ASCII value 
		of '0' will return the appropriate numeric value for the character. */
		maxNumConsonant = input[0] - '0';
		puts ("Please enter a 7-digit phone number with dashes removed");
		scanf ("%7s", phone);
		/* The generateSpellings function does most of the work. */
		generateSpellings (phone, maxNumConsonant);
		putchar ('\n');
		putchar ('\n');
		puts ("Would you like to try another number? (Y/N)");
		scanf ("%7s", input);
		if ((input[0] == 'Y') || (input[0] == 'y')) {
			goahead = true;
		} else {
			goahead = false;
		}
	}
	return 0;
}

/*****************************************************************
generateSpellings (char*, int)
phone_int
	The characters '1', '2', '3', ... are converted to
	1, 2, 3, ... and stored appropriately in this 
	numeric representation of the user's phone number.
level
	This variable is used to make the printouts nice.  
	It is passed using the "address of" operator, as described in House
	in section 5.2.1. Passing a variable using the "address of" operator
	in this way is a technique that allows a function to 
	change its contents in such a way that the changes
	are recognized in the calling program.
	Note that level should really be a local variable in
	generateSpellings; it is used as a parameter here for
	illustrative purposes.
a-g
	Index variables used to keep track of for loops.
word
	A candidate "word" that is then passed on to
	print_if_good, which prints the word if it meets
	the minimum requirements for consonants.  The
	representation is again an array of characters
	terminated by a NULL ('\0').
dial
	A two-dimensional array.  For each dial [i][j], i represents
	the actual number on the key pad (a value between 1 and 10)
	and j indicates a choice of letter that the key pad could represent.  
	So, for example, dial[2][3] would represent the 
	third letter on button #2 of the keypad, namely the letter "c".
	Similarly, dial[2][2] == 'b', dial [3][3] = 'f', etc.  
	Confused? Pick up your phone and take a look!  
	Some letters aren't mapped the way they should be. 
	Note that the letters "q" and "z" have been removed.  
	The numbers 0 and 1 have no associated letters and so 
	the program simply returns a "1" or a "0" in those
	circumstances.
*************************************************************** */

void generateSpellings (char* phone, int maxNumConsonant) {
	int phone_int[7];
	int a, b, c, d, e, f, g;
	char word[8];
	int level;
	char* dial[10] = {"000", "111", "abc", "def", "ghi", "jkl",
		"mno", "prs", "tuv", "wxy"};
	/* Each ASCII character stored in phone is converted to its appropriate number. */
	level = 0;
	convert (phone, phone_int);
	/* The following for loop works as follows: for each of the seven digits in the phone number, we 
	generate all the different possible letters each letter can take on by considering each digit in 
	turn until all values are exhausted. */
	for (a = 0; a < 3; a++) {
		for (b = 0; b < 3; b++) {
			for (c = 0; c < 3; c++) {
				for (d = 0; d < 3; d++) {
					for (e = 0; e < 3; e++) {
						for (f = 0; f < 3; f++) {
							for (g = 0; g < 3; g++) {
								/* The candidate word is built here.  Starting with the first letter of 
								the word we assign a candidate translation dial[][a] based on 
								the original number's value. */
								word[0] = dial[phone_int[0]][a];
								word[1] = dial[phone_int[1]][b];
								word[2] = dial[phone_int[2]][c];
								word[3] = dial[phone_int[3]][d];
								word[4] = dial[phone_int[4]][e];
								word[5] = dial[phone_int[5]][f];
								word[6] = dial[phone_int[6]][g];
								word[7] = '\0';
								/* print_if_good prints the word if it meets the minimum 
								requirements. */
								print_if_good (maxNumConsonant, word, &level);
							}
						}
					}
				}
			}
		}
	}
}

/* This function prints the word if it has maxNumConsonant or fewer consonants. */
void print_if_good (int maxNumConsonant, char* word, int *level) {
	int i;
	int numVowel = 0;
	/* This loop counts the number of vowels. */
	for (i = 0; i < 7; i++) {
		if (isvowel(word[i])) {
			numVowel++;
		}
	}
	
	/* This loop prints the word if there is maxNumConsonant or fewer consonants. */
	if ((7 - numVowel) <= maxNumConsonant) {
		printf ("%s  ",word);
		/* Every time we print a word, we add 1 to the value of level. */
		*level = *level + 1;
		/* Every seventh word we print, we add a carriage return to make the format nice. */
		if ((*level)%7 == 0) {
			putchar ('\n');
		}
	}
}

/* This function checks to see if the letter in question is "a", "e", "i", "o", or "u". */
int isvowel (char x) {
	return ((x == 'a') || (x == 'e') || (x == 'i') || (x == 'o') || (x == 'u'));
}

/* This function converts the character array into numbers and places its contents into 
	the array phone_int. */
void convert (char* phone, int* phone_int) {
	int i;
	for (i = 0; i < 7; i++) {
		phone_int[i] = phone[i] - '0';
	}
}
