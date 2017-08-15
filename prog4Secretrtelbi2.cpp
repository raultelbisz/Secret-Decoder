// prog4Secretrtelbi2.cpp
//
// Author: Raul Telbisz
// Program: #4, Secret
// TA: Moumita Samanta, Tues 11
// March 9, 2017
//
// Secret is a a program used to find secret messages known as scytale's
// from a  cipher file. You can use it to display all contents in a file in an
// m x n format where m is the characters per row specified by the user
// and m is the number of rows displayed by the cipher. The program uses a keys 
// file to search for the keywords in the cipher text.
//
/*
A runthrough of the program looks like this:


		Welcome to the decoding program, where hidden messages
		are found inside of a text file.

		Author: Raul Telbisz
		Program: #4, Secret
		TA: Moumita Samanta, Tues 11
		March 9, 2017

		Read in 4 keyWords which are :
		quick
		get
		going

		Read in 388 Cipher text characters

		Choose from the following options:
		1. Display a particular sized table
		2. Find all matching key word phrases
		X. Exit the program
		Enter your choice ->
		1
		Enter a size for each row of letters(13 - 132): 15
		oo fggo pbuzbbb
		y gmjekjnbi son
		cc ppptyewx rbt
		l mbbx  gadhcg
		hcwhz alcjq  ma
		vj vnpd aamy zn
		qy dt znq sjv g
		h pjq fxtozhvq
		dft eqw qkj  pt
		rka puk nih ps
		a nkb yiu oxm r
		t rwnyvgcykel n
		i w vc ydgpbg f
		hz ccfy cdrz yr
		oxednco ulkd ou
		gg  sfc dvsgpc
		zpl shbc iwkc j
		fyd te  z sv nv
		xwz ugskm uutix
		knkzdf  kyab p
		cm wioqvfpltv h
		jp hdjj emcwczu
		ibfc clyxs  igd
		opqqrx vo xf y
		dedqa bnclqgf f
		troaom chhnaz

		Press any key to continue . . .
*/
#include <cstdio>
#include <cstdlib>
#include <cctype> // Used for toupper()

#define MAX_FILE_SIZE 17424 // This is the maximum number of characters we
                            // can expect to encounter in any cipher.

//----------------------------------------------------------------------------
void programInformation()
{
	printf("Welcome to the decoding program, where hidden messages\n");
	printf("are found inside of a text file.                      \n");
	printf("                                                      \n");
	printf("Author: Raul Telbisz                                  \n");
	printf("Program: #4, Secret                                   \n");
	printf("TA: Moumita Samanta, Tues 11                          \n");
	printf("March 9, 2017                                         \n");
	printf("                                                      \n");
}// end of programInformation()


//----------------------------------------------------------------------------
// Function that loops through the stored keyWords & prints them in a 2D array
// The keyWords argument is the array in which the keys are stored
void printKeys(char keyWords[20][25]) 
{
	int row = 0;
	int column = 0;

	while (keyWords[row][column] != '\0') {

		// When the loop reaches end of row, we move to next column
		if (keyWords[row][column] != ' ') {
			printf("%c", keyWords[row][column]);
			column++;
		}
		// If we encounter a space, we move on to the next letter in sequence
		else if (keyWords[row][column] == ' ') {
			printf("\n");
			row++;
			column = 0; // We reset the column back to 0 to loop from the start
		}
	}
}// end of printKeys()


//----------------------------------------------------------------------------
// Open the keys.txt file and read its contents into an array
// If we encounter any error message with a missing file an exit code appears 
void openAndReadKeys(char keyWords[20][25])
{
	FILE *fKeys;    // Pointer to the file we will use
	char inputChar; // Characters we will scan in from the file 1 at a time
	int row    = 0;
	int column = 0;
	int keyCounter = 1; // Counts how many keys we have read and stored

	fKeys = fopen("keys.txt", "rb"); // Storing the contents of the file in *fKeys

	// If the file is not where it should be this message is displayed
	if (fKeys == NULL) {
		printf("Input file open error. Verify it is in the right location\n");
		exit(-1);
	}

	// Scan until all contents have been read until the end of the file
	while (fscanf(fKeys, "%c", &inputChar) != EOF) {

		// Storing the characters of the keys in a 2D array 
		keyWords[row][column] = inputChar;
		column++; // As we reach the end of the row we move to next column

		// If we encounter a space we move on to the next letter
		if (inputChar == ' ') {
			keyWords[row][column] = '\0';
			row++;
			column = 0;
			keyCounter++; 
		}
	}
	keyWords[row][column] = '\0'; // Making sure to close of the array to
	                              // avoid any 'dangling' characters
	
	printf("Read in %d keyWords which are :\n", keyCounter);
	printKeys(keyWords); // Prints each key on its own line as a 2D array
	printf("\n");
}


//----------------------------------------------------------------------------
// Read in all the contents of the cipher.txt file saving them in a 1d array
// called cipherText[]. Also keeps track of the number of characters read in.
// It returns an integer which is a value of cipher characters, which becomes 
// valuable for later functions in the program and loop iterations.
int openAndReadCipher(char cipherText[])
{
	FILE *fCipher;       // Our pointer to the cipher file
	int column = 0;      // Used to increment each column of our 1d array
	char inputChar;      // We store the characters using this variable
	int numOfChars = 0;; // Count how many characters we read in from the cipher

	fCipher = fopen("cipher.txt", "rb");

	// If the file is misplaced, this error is triggered
	if (fCipher == NULL) {
		printf("Input file open error. Verify it is in the right location\n");
		exit(-1);
	}

	// We scan until the end of the file is reached
	while (fscanf(fCipher, "%c", &inputChar) != EOF) {
		cipherText[column] = inputChar; // As we scan we store the characters
		column++;                       // in a 1-d cipher all while increasing
		numOfChars++;                   // each array "location" or column
	}
	cipherText[column] = '\0'; // Makes sure we close off the end of the array
	
	printf("Read in %d Cipher text characters\n", numOfChars);
	printf("\n");

	return numOfChars; // We will use the number of cipher characters for
	                   // other loops where its value will be useful
}// end of openAndReadCipher()


//----------------------------------------------------------------------------
// Displays Menu options that the user can decide which to perform
// Returns a value with which we decide what actions to perform
int programMenu()
{
	int userInput; // Variable to store the user's input

	printf("Choose from the following options:       \n");
	printf("   1. Display a particular sized table   \n");
	printf("   2. Find all matching key word phrases \n");
	printf("   X. Exit the program                   \n");
	printf("Enter your choice ->                     \n");

	scanf("%d", &userInput);

	// If the user does not enter a 1 or 2, the program assumes the user
	// wants to exit
	if ((userInput != 1) && (userInput != 2)) {
		printf("Exiting program...\n");
		system("pause");
		exit(-1);
	}
	else if (userInput == 1) {
		return 1;
	}
	else if (userInput == 2) {
		return 2;
	}

	return 0;
} // end of programMenu()


//----------------------------------------------------------------------------
// Gets the length of any word passed through
int length(char word[]) {
	int i = 0; // i is just used as a variable to count through letters
	int letterCounter = 0; // used to counter the number of letters

	for (i = 0; word[i] != '\0'; i++) {
		letterCounter++;
	}
	return letterCounter; //Returns the number of letters, or length of word
}


//----------------------------------------------------------------------------
// Displays the array in a specified format based on what the user chooses
// i.e. if the user chooses rowSize to be 15, we display the contents
// of the cipher with a maximum of 15 characters per row
// cipherText is our 1D cipher array. keyWords is our 2D keys array
// alteredCipher will be the newly altered Cipher to display according to 
// the user-specified row
// rowSize is the variable used to determine what our row size will be
// numofChars is the number of Characters in our cipher or "length" of it
void alterCipher(char cipherText[MAX_FILE_SIZE], char keyWords[20][25],
	             char alteredCipher[MAX_FILE_SIZE / 13][132],
	             int rowSize, int numOfChars)
{
	int originalRow    = 0; // Placeholder for row of original cipher
	int originalColumn = 0; // Placeholder for column of original cipher
	int newColumn      = 0; // Placeholder for column of new cipher
	int newRow         = 0; // Placeholder for row of new ciper

	int cipherLength = length(cipherText); // Gets the length of the cipher

	// This populates our 2D cipher with the cipherTexts characters
	// We loop through each spot in the original cipher and copy that character
	// Into the new cipher's row and column
	for (originalRow = 0; originalRow < ((numOfChars / rowSize) + 1); originalRow++) {
		for (newColumn = 0; newColumn < rowSize; newColumn++) {
			alteredCipher[newRow][newColumn] = cipherText[originalColumn];
			originalColumn++;
		}
		// If we've reached the ended of the column we move on to the next row
		if (newColumn == rowSize) {
			alteredCipher[newRow][newColumn] = '\0';
			newRow++;
			newColumn = 0;
		}
	}
	// This was added in case our cipher is huge. If it wasn't it would print all
	// 16000+ characters and it would take a long time to do that.
	if (numOfChars > 15000) { 
		numOfChars = (numOfChars / rowSize);
	}

	// This displays the contents of our newly altered 2D cipher
	for (originalColumn = 0; originalColumn < (numOfChars / rowSize) + 1; originalColumn++) {
		printf("%.*s", rowSize, alteredCipher[originalColumn]);
		printf("\n");
	}
}// end of alteredCipher()


//----------------------------------------------------------------------------
//Extracts the keyWords out of the 2D keyWords array and puts them in their
// own separate 1D arrays. This makes searching for the keyWords much easier
// We have room enough for 4 words (if 4 exist) and if we only have 3 words
// we store them in arrays word1, word2, word3 respectively.
void extractWords(char word1[25], char word2[25], char word3[25],
	              char word4[25], char keyWords[20][25])
{
	int keysRow      = 0; // Keeps track of the keyWord's row
	int keysColumn   = 0; // Keeps track of the keyWord's column
	int charLocation = 0; // Keeps track of each letter's location in a word

	// Until we have reached the end of our row we populate word1 with the key
	while (keyWords[keysRow][keysColumn] != '\0') {
		word1[charLocation] = keyWords[keysRow][keysColumn];
		keysColumn++;
		charLocation++;
	}

	// We reset the variables and close off the last array with a null
	// then continue to populate the next word array with the next keyWord
	word1[charLocation] = '\0'; keysColumn = 0; keysRow = 1; charLocation = 0;
	
	while (keyWords[keysRow][keysColumn] != '\0') {
		word2[charLocation] = keyWords[keysRow][keysColumn];
		keysColumn++;
		charLocation++;
	}

	// We reset the variables and close off the last array with a null
	// then continue to populate the next word array with the next keyWord
	word2[charLocation] = '\0'; keysColumn = 0; keysRow = 2; charLocation = 0;
	
	while (keyWords[keysRow][keysColumn] != '\0') {
		word3[charLocation] = keyWords[keysRow][keysColumn];
		keysColumn++;
		charLocation++;
	}

	// We reset the variables and close off the last array with a null
	// then continue to populate the next word array with the next keyWord
	
	word3[charLocation] = '\0';
	keysRow = 0; keysColumn = 0; charLocation = 0;

	// Checks if a fourth word exists or not
	if (keyWords[3][keysColumn] == '\0') {
		keysColumn = 0; charLocation = 0;
		while (keyWords[keysRow][keysColumn] != '\0') {
			word4[charLocation] = keyWords[keysRow][keysColumn];
			keysColumn++;
			charLocation++;
		}
	}
}// end of extractWords()


//----------------------------------------------------------------------------
// Extracts any "hidden" messages from our cipherText array. Using keyWord
// as a guideline for searching, we can pass through any word to see if it 
// exists, and so we pass through our previously extracted keyWords.
// Any messages we find are stored in our message array. The rowSize is used
// to figure out how long we must loop through our arrays.
// The function returns 2 if we find a word, and 0 if we do not.
int extractMessage(char keyWord[25], char cipherText[17424],
	               int rowSize, char message[388]) 
{
	int keyColumn    = 0; // Keeps track of the columns in the keys
	int cipherColumn = 0; // Keeps track of the columns in the Cipher
	int offset       = 1; // Offset used to displace letters
	int nextWord     = 1; // Stores the location of the next word

	int lengthOfWord   = 0; // Stores the length of the key word
	int lengthOfCipher = 0; // Stores the length of the cipher

	lengthOfWord = length(keyWord);
	lengthOfCipher = length(cipherText);

	// We loop through the cipher column till the first letter matches the keyword's
	while (keyWord[keyColumn] != cipherText[cipherColumn]) {
		cipherColumn++;
		// If we find a match, we check the next letter too, if they do not match
		// We go on to find the next letter that matches the first letter in our keyword
		if (keyWord[keyColumn + offset] != cipherText[cipherColumn + (rowSize*nextWord) + nextWord]) {
			cipherColumn++;
			continue;
		}
	}
	// Once we've found our match, we go on to store the message into a new array
	if (keyWord[keyColumn + offset] == cipherText[cipherColumn + (rowSize*nextWord) + nextWord]) {
		message[keyColumn] = (cipherText[cipherColumn]);
		// As long as we do not reach the end of array, we continue to store words
		for (keyColumn = 1; keyColumn < (rowSize + lengthOfWord - 1); keyColumn++) {
			message[keyColumn] = cipherText[cipherColumn + (rowSize*nextWord) + nextWord];
			nextWord++;
		}
	}

	// If we do not find any matches for our keyword, we return 0
	if (keyWord[2] != cipherText[cipherColumn + (rowSize * 2) + 2]) {
		return 0;
	}

	// We append a null character to the end of the string to prevent issues
	message[keyColumn] = '\0';

	// This was only added because the 16000 cipherText would also give us
	// unwanted characters in our message at the end. This just makes the output
	// look much cleaner.
	message[23] = '\0';

	printf("%s", message); // Prints any messages we have found

	return 2; // If we have found a message we return 2
}


//----------------------------------------------------------------------------
// Searches through the different variations of the cipher scanning through 
// the specified rowSize  and  also every iteration of rows to see if the
// keyWords exist. The searchType argument triggers the searching of all rows
// if the user chooses option 2 at the program Menu.
void searchCipher(char cipherText[17424], char keyWords[20][25],
	              int rowSize, int searchType)
{
	char word1[25], word2[25], word3[25], word4[25]; // Keywords

	char message[388]; // Messages will be stores in here

	int sizeTestedAlready = rowSize; // Keeps track of the row sizes already tested
	int testMessage =  0;  // Stores whether or not a message was found using a keyword
	int testRowSizes = 13; // The beginning of the allowed "rows"

	// We begin by extracting the keywords and storing them in their
	// respective arrays
	extractWords(word1, word2, word3, word4, keyWords);

	// We then send each word through our function extractMessage to find the
	// existence of a message in the cipher. Any found messages are printed
	extractMessage(word1, cipherText, rowSize, message);
	extractMessage(word2, cipherText, rowSize, message);
	extractMessage(word3, cipherText, rowSize, message);
	
	// This only triggers if a fourth word exists. Searches using that word
	if (keyWords[3][0] == '\0') {
		extractMessage(word4, cipherText, rowSize, message);
	}

	// If the user selects option 2 in the menu, the following block of code
	// will search ALL "rows" of the cipher beginning at 13 and ending at 132
	if (searchType == 2) {
		printf("All secret messages found are:\n");

		while (testRowSizes < 133) {

			rowSize = testRowSizes;
			// If the size has been tested already, we increment
			if (rowSize == sizeTestedAlready) {
				testRowSizes++;
			}
			rowSize = testRowSizes;

			// Extract any messages if we find them. When and if they are found
			// We print out the message, print out which keyword was used to find
			// that message, and then print out in which row size we found it
			testMessage = extractMessage(word1, cipherText, rowSize, message);
			if (testMessage == 2) {
				printf("\nFound '%s' diagonally with table size %d",
					word1, testRowSizes);
				break;
			}
			testMessage = extractMessage(word2, cipherText, rowSize, message);
			if (testMessage == 2) {
				printf("\nFound '%s' diagonally with table size %d",
					word2, testRowSizes);
				break;
			}
			testMessage = extractMessage(word3, cipherText, rowSize, message);
			if (testMessage == 2) {
				printf("\nFound '%s' diagonally with table size %d",
					word3, testRowSizes);
				break;
			}
			if (keyWords[3][0] == '\0') { // Only if a fourth word exists
				testMessage = extractMessage(
					word4, cipherText, rowSize, message);
				if (testMessage == 2) {
					printf("\nFound '%s' diagonally with table size %d",
						word4, testRowSizes);
					break;
				}
			}
			testRowSizes++; // Increments on to the next row (table)
		} // end of while loop
	} // end of if statement checking all rows
}// end of searchCipher



//----------------------------------------------------------------------------
int main() {

	char keyWords[20][25]; // Used to store our key words
	char cipherText[MAX_FILE_SIZE]; // Used to store the contents of our cipher
	char alteredCipher[MAX_FILE_SIZE / 13][132]; // Used to create the 2D cipher

	int userInput = 0;  // User input to decide which menu option to run
	int rowSize = 0;    // Row size the user specifies
	int numOfChars = 0; // Counts the number of characters in our cipher or keys

	programInformation(); // Display program Info
	openAndReadKeys(keyWords); // We read in the keys from the keys file
	printf("\n");
	numOfChars = openAndReadCipher(cipherText); // We read in the cipher

	userInput = programMenu(); // We print out the menu and get users feedback

	// Display a table size specified by the user
	if (userInput == 1) {
		printf("Enter a size for each row of letters(13 - 132): ");
		scanf("%d", &rowSize);

		// Call our function to alter and create our 2d Cipher
		alterCipher(cipherText, keyWords, alteredCipher, rowSize, numOfChars);
	}

	// Search for all hidden messages
	if (userInput == 2) {
		searchCipher(cipherText, keyWords, rowSize, 2);
	}

	printf("\n");
	system("pause");

	return 0;
}