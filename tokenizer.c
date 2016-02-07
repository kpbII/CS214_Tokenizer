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



typedef enum tokenType_ {DEFAULT, WORD, DECIMAL, HEX, OCTAL, FLOATP, CONTROL, BADTOKEN, SPACE, SPECIAL, OPERATOR} tokenType;

typedef struct Token_ {
	char *token;
	tokenType tType;
}Token;

typedef struct TokenizerT_ {
	char *tokenstring;
	int length;
	int index;
	Token *current_token;
}TokenizerT;

char* cOperators[42] = 	{"(", ")", "[", "]", "~", "?", ":", ".", ",", 
					"*", "&", "-", "!", "+", "/", "%", ">", "<",
					"=", "^", "|", "*=", "&&", "--", "!=", "++", "/=",
					"%=", ">>", "<<", "==", "^=", "||", "&=", "-=", "+=",
					">=", "<=", "|=", "->", ">>=", "<<="};




Token* tokenize( TokenizerT * tk );

/*
* Function to match up enum values with strings to fix the print issue
*
*
*/
char* getVals(tokenType type)
{
	switch(type)
	{
		case DEFAULT:
			return "Default";

		case WORD:
			return "Word";

		case DECIMAL:
			return "Decimal";
			break;

		case HEX:
			return "Hexadecimal";
			break;

		case OCTAL:
			return "Octal";
			break;

		case FLOATP:
			return "Float";
			break;

		case CONTROL:
			return "Control Code";
			break;

		case BADTOKEN:
			return "Bad Token";
			break;

		case SPACE:
			return "Space";
			break;

		case OPERATOR:
			return "Operator";
			break;

		case SPECIAL:
			return "Special character";
			break;

		default:
			//return temp_token;
			break;
	}
}





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
	tk->current_token = tokenize(tk);
	tk->index += strlen(tk->current_token->token);
	return tk->current_token->token;
}

int isSpecialCharacter(char c){
  switch(c)
  {
    case '\n': return 1; break;
    case '\t': return 1; break;
    case '\v': return 1; break;
    case '\b': return 1; break;
    case '\r': return 1; break;
    case '\f': return 1; break;
    case '\a': return 1; break;
    case '\\': return 1; break;
    case '\"': return 1; break;
    default:
    	return 0;
  }
}

int isOperator(char * c)
{
	int i = 0;
	int length = sizeof(cOperators);
	for(i = 0; i < length; i++)
	{
		if(!strcmp(c,cOperators[i]))
			return 1;
	}

	return 0;
}



/*
* state-getter, getter of simple states
* will only make generalizations, ie number, letter, control, punctuation
* more fine-grained decision making should be done in tokenize i think
* the "x" in hex is a problem right now, however
*/
tokenType getSimpleState( char input )
{
	char c = input;
	if(isdigit(c))
	{
		return DECIMAL;
	}
	else if(isspace(c))
	{
		return SPACE;
	}

	else if(isSpecialCharacter(c))
	{
		return SPECIAL;
	}

	// else if(isOperator(c))
	// {
	// 	return OPERATOR;
	// }

	else if(ispunct(c))
	{
		return BADTOKEN;
	}

	else if(iscntrl(c))
	{
		return CONTROL;
	}

	else if(isalpha(c))
	{
		return WORD;
	}

	else
	{
		return DEFAULT;
	}

	return DEFAULT;

}


Token* tokenize( TokenizerT * tk )
{
	//initialize size of result array
	int length = strlen(tk->tokenstring);
	int i = 0;
	char *input = tk->tokenstring;
	char *temp = (char*)calloc((length),sizeof(char));
	
	Token *temp_token = (Token*)calloc(1, sizeof(Token));
	temp_token->tType = DEFAULT;
	if(temp_token==NULL)
	{
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}

	int start = input[tk->index];
	temp_token->tType = getSimpleState(start);

	for(i = tk->index; input[i] != '\0' && i <= length; i++)
	{
		char cur = temp[strlen(temp) - 1];
		char next = input[i];

		//tokenType cType = getSimpleState(cur);
		tokenType nType = getSimpleState(next);

		if(temp_token->tType == SPACE)
		{
			tk->index++;
			break;
		}
		//append if they match, regardless of type

		//float
		else if(next == '.' && temp_token->tType == DECIMAL)
		{
			temp_token->tType = FLOATP;
			temp[strlen(temp)] = next;
		}
		else if((temp_token->tType == DECIMAL || temp_token->tType == FLOATP) && next == 'e')
		{
			temp_token->tType = FLOATP;
			temp[strlen(temp)] = next;
		}
		else if(temp_token->tType == FLOATP && cur == 'e')
		{
			if(next == '+' || next == '-' || isdigit(next))
				temp[strlen(temp)] = next;
		}
		else if(temp_token->tType == FLOATP && isdigit(next))
		{
			temp[strlen(temp)] = next;
		}

		//hex
		else if(start == '0' && (next == 'x' || next == 'x'))
		{
			temp_token->tType = HEX;
			temp[strlen(temp)] = next;
		}
		else if(temp_token->tType == HEX)
		{
			if(isxdigit(next))
				temp[strlen(temp)] = next;
			else if(strlen(temp) > 2)
				break;
			else if(strlen(temp) == 2)
			{
				temp_token->tType = BADTOKEN;
				break;
			}
		}

		else if(temp_token -> tType == OCTAL)
		{
			if(!isdigit(cur))
			{
				break;
			}
			else if(cur < 8)
			{
				temp[strlen(temp)] = next;
			}
		}

		//
		else if(temp_token->tType == nType)
		{
			temp[strlen(temp)] = next;
		}
		else
		{
			break;
		}

	
	}

	//add null terminator and put string into token
	temp[strlen(temp)] = '\0';
	temp_token->token = temp;
	return temp_token;
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

	TokenizerT * TT = TKCreate(argv[1]);
	printf("Tokenizer string is: %s\n", TT->tokenstring);
	int x = 0;
	while(TT->index < TT->length){
		char* tok = TKGetNextToken(TT);
		if(strlen(tok) == 0)
		{
			x++;
		}
		else
		{
			char* enumVal = getVals(TT->current_token->tType);
			printf("%s: %s \n",enumVal,tok);//printing an enum gets its number not string
			free(tok);
			free(TT->current_token);
			x++;
		}


	}
	TKDestroy(TT);


	return 0;
}
