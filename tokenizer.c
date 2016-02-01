/*
* tokenizer.c
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
* Tokenizer type.  You need to fill in the type as part of your implementation.
*/

struct TokenizerT_ {
	char *token;
	tokenType_ type;
	int length;
	int index;
};

typedef struct TokenizerT_ TokenizerT;
typedef enum {WORD, DECIMAL, HEX, OCTAL, FLOATP, KEYWORD} tokenType_;

/*
* TKCreate creates a new TokenizerT object for a given token stream
* (given as a string).
* 
* TKCreate should copy the arguments so that it is not dependent on
* them staying immutable after returning.  (In the future, this may change
* to increase efficiency.)
*
* If the function succeeds, it returns a non-NULL TokenizerT.
* Else it returns NULL.
*
* You need to fill in this function as part of your implementation.
*/

TokenizerT *TKCreate( char * ts ) {
	//error checking
	if(ts == NULL | strlen(ts) <= 0) return NULL;

	//allocate memory
	TokenizerT * token = (TokenizerT*)malloc(sizeof(TokenizerT));

	return NULL;
}

/*
* TKDestroy destroys a TokenizerT object.  It should free all dynamically
* allocated memory that is part of the object being destroyed.
*
* You need to fill in this function as part of your implementation.
*/

void TKDestroy( TokenizerT * tk ) {
}

/*
* TKGetNextToken returns the next token from the token stream as a
* character string.  Space for the returned token should be dynamically
* allocated.  The caller is responsible for freeing the space once it is
* no longer needed.
*
* If the function succeeds, it returns a C string (delimited by '\0')
* containing the token.  Else it returns 0.
*
* You need to fill in this function as part of your implementation.
*/

char *TKGetNextToken( TokenizerT * tk ) {

	return NULL;
}

char* tokenize(char *input)
{
	//initialize size of result array
	int i = 0;
	int index = 0;
	int length = strlen(input);
	char *temp = (char*)malloc((len)*sizeof(char));

	for(i = 0; input[i] != '\0' && i < len; i++)
	{
		if(isalpha(input[i]))
	}
}

/*
* main will have a string argument (in argv[1]).
* The string argument contains the tokens.
* Print out the tokens in the second string in left-to-right order.
* Each token should be printed on a separate line.
*/

int main(int argc, char **argv) {
	//check if valid number of arguments
	if(argc != 2)
	{
		printf("Incorrect number of arguments \n");
		exit(11);
	}
	

	//empty string check
	if(strlen(argv[1]) == 0)
	{
		printf("empty string passed, nothing to parse \n");
		exit(0);
	}

	print_chars(argv[1]);




	return 0;
}