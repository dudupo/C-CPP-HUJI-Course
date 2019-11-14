#include <stdio.h>
#include <stdlib.h>

int isDigit( char c )
{
    return ( c <= '9' && c >= '0');
}
int isLetter(char c)
{
	return !isDigit(c);
}

void decode(const char * text)
{
		const char * pointer = text;
		int num = 0;

		while( *pointer )
		{
			while( *pointer && isLetter(*pointer)  )
			{
					printf("%c", *pointer);
					pointer++;
			}
			num = 0;
			while( *pointer && isDigit(*pointer)  )
			{
					num = 10 * num + ( *pointer - '0');
					pointer++;
			}
			for ( int i = 0 ; i < num ; i++ ){
				printf("%c", *pointer);
			}
			pointer++;
		}
}


int main(int argc, char const *argv[]) {
  /* code */
  decode("2a5b7g");

  return 0;
}
