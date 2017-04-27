
#include<stdio.h>
#include<string.h>
// Zhuneng Jiang 2016-09-26

// check if a char is a vowel



// int main()
// {
// 	int n = 80;
// 	printf("%d%% usually\nmeans \"excellent\"\n", n);

// 	int k;
// 	k = getchar ();
// 	printf ("%d", k);

// }

int main ( ) {
		char c;
		for (c='a'; c<'g'; ++c) {
			switch (c) {
				case 'a':	c += 2;
				case 'c':	c += 1;
				case 'g':	++c;
						printf ("%c\n" , c-- );
				default:	++c;
			}
			printf ("*** %c\n" , c);
		}
		return 0;
	}
	