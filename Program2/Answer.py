1. 
	Insert ";" after puts ("phone numbers\n\n")
	Change scanf ("%7s", number); to scanf ("%7s", phone);
	Insert ";" after print_if_good (maxNumConsonant, word, &level)
	Insert Void in front of convert (char* phone, int* phone_int)
2.
	When I choose 4 consonants, and 6937648 for phone number, the output
	looks weird.
3.  gdb commands used: print maxNumConsonant, display maxNumConsonant
	input[0] - '0' returns the appropriate numeric value for the character.
4.
	"6937648", phone is represented as an address because it is a pointer to the first character of the array.
5.
	The for loop works fine, the displayed info: 
	9: phone_int[6] = 8
	8: phone_int[5] = 4
	7: phone_int[4] = 6
	6: phone_int[3] = 7
	5: phone_int[2] = 3
	4: phone_int[1] = 9
	3: phone_int[0] = 6
	2: i = 7
6.
	They work fine. I display the word and values for abcdefg while stepping through the method.
7. 
	The word is "mwdrnit". Command used: display word. It is correct.
8.
	&level is the address that the pointer points at, since print_if_good takes in a pointer argument.
9.
	The value of level did not change (still 0), but the hex address was incremented by 4.
	*level = *level + 1
	No warnings.