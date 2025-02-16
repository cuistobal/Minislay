#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 100

//This module idetify tokens splited by whitespaces, while conserving spaces within quotes.
//Then, We have to assign a token type.

static void out_quotes()
{

}

static void in_quotes()
{
    if (inQuotes && currentQuote == input[i])
        inQuotes = 0;
    else if (!inQuotes)
    {
        inQuotes = 1;
        currentQuote = input[i];
        if (i > 0 && input[i-1] != ' ')
            tokens[*tokenCount][k++] = ' ';
    }
}

void    initial_tokenization(const char *input, char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH], int *tokenCount)
{
    int i, j = 0, k = 0;
    int inQuotes = 0;
    char currentQuote = '\0';
    int tokenStart = 0;

    *tokenCount = 0;
    for (i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
            in_quotes();
            /*
            if (inQuotes && currentQuote == input[i])
            {
                inQuotes = 0;
            }
            else if (!inQuotes)
            {
                inQuotes = 1;
                currentQuote = input[i];
                if (i > 0 && input[i-1] != ' ')
                {
                    tokens[*tokenCount][k++] = ' ';
                }
            }*/
        }
        else if (isspace(input[i]) && !inQuotes)
        {
            if (k > 0)
            {
                tokens[*tokenCount][k] = '\0';
                (*tokenCount)++;
                k = 0;
            }
            tokenStart = i + 1;
        }
        else
        {
            tokens[*tokenCount][k++] = input[i];
        }
    }
    if (k > 0)
    {
        tokens[*tokenCount][k] = '\0';
        (*tokenCount)++;
    }
}

int main(int argc, char **argv)
{
    char *input = argv[1];
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    int tokenCount = 0;

    initial_tokenization(input, tokens, &tokenCount);

    printf("Tokens:\n");
    for (int i = 0; i < tokenCount; i++) {
        printf("%s\n", tokens[i]);
    }

    return 0;
}
