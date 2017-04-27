
#include<stdio.h>
#include<string.h>
// Zhuneng Jiang 2016-09-26

// check if a char is a vowel
int isVowel(char a){
	if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u'){
		return 1;
	}else{
		return 0;
	}
}

// check if a char is a vowel or y
int isVowelorY(char a){
	if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u' || a == 'y'){
		return 1;
	}else{
		return 0;
	}
}

// move first char of a string to the end
char *swap_last(char *str){

	int len = strlen(str);
	char first = str[0];
	for (int i = 0; i < len-1; i++){
		str[i] = str[i+1];
	}
	str[len-1] = first;
	str[len] = '\0';
	return str;
}

// method where problem logic is implemented
char* process(char *input){
	int count = 0;
	if(isVowel(input[0])){
		return strcat(input, "yay"); 
	}
	while(count < strlen(input)-1){
		if(count == 0){
			if (isVowel(input[0]) == 0){
				if(input[0] == 'q'){
					input = swap_last(input);
				}
				input = swap_last(input);
			}
		}else{
			if (isVowelorY(input[0]) == 0){
				if(input[0] == 'q'){
					input = swap_last(input);
				}
				input = swap_last(input);
			}
		}
		count++;

	}
	return strcat(input, "ay");
}


int main()
{
	while(1){
		char *str;
		printf("Enter a word: "); 
		scanf("%s", str); 
		printf("%s", process(str));
		printf("\n");
	}

}