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



typedef enum tokenType {WORD, DECIMAL, HEX, OCTAL, FLOATP, KEYWORD} tokenType_;

typedef struct TokenizerT_ {
	char *tokenstring;
	int length;
	int index;
}TokenizerT;

typedef struct Token_ {
	char *token;
	int length;
	enum tokenType tType;

}Token;
char* tokenize(char *input);

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
	if(ts == 0 | strlen(ts) <= 0) return 0;

	//allocate memory

	TokenizerT *tizer = (TokenizerT*)malloc(sizeof(TokenizerT));
	if(tizer == NULL)
	{
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
	tizer->tokenstring=strdup(ts);
	if(tizer->tokenstring==NULL){//this is a secret malloc, free later
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
	tizer->index=0;
	tizer->length = strlen(tizer->tokenstring);


	return tizer;

}


/*
* TKDestroy destroys a TokenizerT object.  It should free all dynamically
* allocated memory that is part of the object being destroyed.
*
* You need to fill in this function as part of your implementation.
*/

void TKDestroy( TokenizerT * tk ) {
	if(tk == 0)  return;
    free(tk->tokenstring);
	free(tk);
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
	char *thistoken = tokenize(tk->tokenstring+tk->index);
	tk->index += strlen(thistoken)+1;
	return thistoken;
}
/*given a string, tokenize will chomp identify what kind
 * and go until it gets to the next new token
 */
char* tokenize(char *input){
	//initialize size of result array
	int i = 0;
	int index = 0;
	int length = strlen(input);
	char *temp = (char*)malloc((length)*sizeof(char));

	for(i = 0; input[i] != '\0' && i < length; i++)
	{
		char c = input[i];
		if(isalpha(c)){
			temp[i]=c;
		}
		else if(isdigit(c)){
			//go to the number branch
		}
		else if(isspace(c)){
			temp[i] = '\0';
			return temp;
		}
	}
	return temp;
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

	printf("This is your string: %s\n",argv[1]);
	TokenizerT * TT = TKCreate(argv[1]);
	printf("Create Successful\nTokenizer string is: %s\n", TT->tokenstring);
	int x = 0;
	while(TT->index < TT->length){
		char* tok = TKGetNextToken(TT);
		printf("Token: %s\n",tok);
		free(tok);
		x++;
	}
	TKDestroy(TT);


	return 0;
}
