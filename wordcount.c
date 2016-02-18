#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int
cmp(const void *str1, const void *str2) {
	return strcmp(*(char **)str1, *(char **)str2);
}

int
main(int argc, char **argv) {
	
	if (argv[1] == NULL) {					//did not enter a file
		printf("You didn't enter a file\n");
		exit(1);
	}

	char const* const fileName = argv[1];
	FILE* textFile = fopen(fileName, "r");			//taking in the filename
	
	int n = 0;
	int ch;

	if (textFile == '\0') {					//could not open file
		printf("Could not open file\n");
		exit(2);
	}
	
	//char *charArr = (char *)malloc(sizeof(char *) * 4000000);
	
	int prevSpace = 0;					//flag to check if there was already a space
	char charArr[8000000];					//allocate space for the char Array
	while ((ch = fgetc(textFile)) != EOF) {			//read text file and get each character until file ends
		if ((ch >= 'A') && (ch <= 'Z')) {		//if it is upper change to lower
			ch = ch + ('a' - 'A');
			charArr[n] = (char) ch;
//			printf("%c", charArr[n]);
			n++;
			prevSpace = 0;				//flag set to 0
		}
		else if ((ch >= 'a') && (ch <= 'z')) {		//if it is lower, just assign into the char array
			charArr[n] = (char) ch;
//			printf("%c", charArr[n]);
			n++;
			prevSpace = 0;
		}
		else if (((ch == 9) || (ch == 10) || (ch == 32)) && (prevSpace == 0)) {	//if it is a tab, nextline or space
			charArr[n] = (char) 32;			//assign only one space
//			printf("%c", charArr[n]);
			n++;
			prevSpace = 1;				//there has been a space, set flag to 1
		}
	}
	

	char **strArr = (char **)malloc(sizeof(char *) * 1000000);	//create string array and allocate large size
	memset(strArr, 0, sizeof(char *) * 1000000);			//set null to all

	int len = 19;							//maximum length of a word

	int i;
	for (i = 0; i < 1000000; i++) {
		char *str = (char *)malloc(sizeof(char) * (len + 1));	//allocate 20 spaces for each entry in the string array
		memset(str, 0, sizeof(char) * (len + 1));		//set null to all
		strArr[i] = str;
	}

	int charIndex = 0;						//looks at the index in the char array
	int strIndex = 0;						//looks at the index of the Str (maximum it goes up to is 20)
	int strPos = 0;							//looks at the string position
	while (charArr[charIndex] != '\0') {				//this process converts the charArr to a strArr
		if (charArr[charIndex] == ' ') {			//there is a space meaning its the next word. set the strIndex back to 0
			strIndex = 0;
			strPos++;
		}
		else if (charArr[charIndex] >= 'a' || charArr[charIndex] <= 'z'){ //it is a char
			*(strArr[strPos] + strIndex) = charArr[charIndex];	  //add the char to its respective index
			strIndex++;
		}
		charIndex++;
	}
	strArr[strPos] = '\0';						//set strArr to terminate to null

	qsort(strArr, strPos, sizeof(char *), cmp);			//quick sort the str array so everything is in lexicographical order
	
	char **wordArr = (char **)malloc(sizeof(char *) * 1000000);	//create word array and a char array and allocate enough size
	memset(wordArr, 0, sizeof(char *) * 1000000);
	int q;
	for (q = 0; q < 1000000; q++) {
		char *str2 = (char *)malloc(sizeof(char) * len + 1);
		memset(str2, 0, sizeof(char) * (len + 1));
		wordArr[q] = str2;
	}


	int * countArr = (int *)malloc(sizeof(int) * 1000000);
	memset(countArr, 0, sizeof(int) * 1000000);
	int wordCount;							//this counts the number of each word
	int a = 0;
	int b = 0;
	
	while (strArr[a + 1] != '\0'){					//encountered the first character, stop when reach the end
		wordCount = 1;						//there will always be at least one of each word

		while (strcmp(strArr[a], strArr[a + 1]) == 0) {		//continue looping and adding the count when it is the same word
			wordCount++;					
			a++;
		}

		wordArr[b] = strArr[a];					//this will only add one instance of a word and its respective count
		countArr[b] = wordCount;

		b++;							//jump to the next index
		
		a++;
	}
	
	wordArr[b] = '\0';
	countArr[b] = '\0';
	
	char ** words = (char **)malloc(sizeof(char) * 10);		//create an array of words of size 10 (the final set of words we want to select)
	int u;
        for (u = 0; u < 10; u++) {					//allocate each element to be length 20
                char *str2 = (char *)malloc(sizeof(char) * (len + 1));
                memset(str2, 0, sizeof(char) * (len + 1));
                words[u] = str2;
        }

	int * count = (int *)malloc(sizeof(int) * 10);			//this count array corresponds to the wordcount for each word in words Array
	memset(count, 0, sizeof(int) * 10);
	
	int c;
	int index = 0;
	int currentMax = countArr[index];				//keep track of the current Max
	int prevMax = 1000000;						//set the previous max to a large number (larger than the maxmimum count)
	int frequency = 0;						//this frequency is the order of the frequency of numbers (up until 10)
	while (frequency != 10) {
		c = 0;
		while (countArr[c] != '\0') {
			if ((countArr[c] > currentMax) && (countArr[c] < prevMax)) { //we found another word with a greater count
				currentMax = countArr[c];					 //change the current max
				index = c;							//record the index
			}
			c++;
		}
		words[frequency] = wordArr[index];							//set the words and count array to the respective
		count[frequency] = countArr[index];							//index in the wordArr and countArr
		frequency++;
		prevMax = currentMax;									//set the previous max to the current max
		currentMax = 0;										//so that we can find the next largest number
	}

	words[frequency] = '\0';								//set words and count to terminate to null
	count[frequency] = '\0';
	
	int d = 0;
	while (words[d] != '\0') {
		printf("%s: %d\n", words[d], count[d]);						//print each word and its respective count
		d++;
	}
	
	fclose(textFile);										//close the textfile
	return 0;
}
