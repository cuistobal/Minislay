#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100

// Define the token structure
typedef struct t_tokn {
    char *value;
    int type;
    struct t_tokn *next;
} t_tokn;

// Function prototypes
static void in_quotes(int *inQuotes, char *currentQuote, char inputChar, char *buffer, int *bufferIndex);
static void handle_whitespace(char *buffer, int *bufferIndex, t_tokn **tokenList);
void initial_tokenization(const char *input, t_tokn **tokenList);
void free_tokens(t_tokn *tokenList);

static void in_quotes(int *inQuotes, char *currentQuote, char inputChar, char *buffer, int *bufferIndex)
{
    if (*inQuotes && *currentQuote == inputChar)
    {
        *inQuotes = 0;
    }
    else if (!*inQuotes)
    {
        *inQuotes = 1;
        *currentQuote = inputChar;
        if (*bufferIndex > 0 && buffer[*bufferIndex - 1] != ' ')
        {
            buffer[(*bufferIndex)++] = ' ';
        }
    }
}

static void handle_whitespace(char *buffer, int *bufferIndex, t_tokn **tokenList)
{
    if (*bufferIndex > 0)
    {
        // Trim trailing whitespace
        while (*bufferIndex > 0 && isspace(buffer[*bufferIndex - 1]))
        {
            (*bufferIndex)--;
        }

        if (*bufferIndex > 0)
        {
            buffer[*bufferIndex] = '\0';
            t_tokn *newToken = (t_tokn *)malloc(sizeof(t_tokn));
            newToken->value = strdup(buffer);
            newToken->type = 1;
            newToken->next = *tokenList;
            *tokenList = newToken;
            *bufferIndex = 0;
        }
    }
}

void initial_tokenization(const char *input, t_tokn **tokenList)
{
    int i, bufferIndex = 0;
    int inQuotes = 0;
    char currentQuote = '\0';
    char buffer[MAX_TOKEN_LENGTH];

    for (i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
            in_quotes(&inQuotes, &currentQuote, input[i], buffer, &bufferIndex);
        }
        else if (isspace(input[i]) && !inQuotes)
        {
            handle_whitespace(buffer, &bufferIndex, tokenList);
        }
        else
        {
            buffer[bufferIndex++] = input[i];
        }
    }
    handle_whitespace(buffer, &bufferIndex, tokenList);
}

void free_tokens(t_tokn *tokenList)
{
    t_tokn *current = tokenList;
    while (current != NULL)
    {
        t_tokn *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <input_string>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    t_tokn *tokenList = NULL;

    initial_tokenization(input, &tokenList);

    printf("Tokens:\n");
    t_tokn *current = tokenList;
    while (current != NULL)
    {
        printf("Value: %s, Type: %d\n", current->value, current->type);
        current = current->next;
    }

    free_tokens(tokenList);

    return 0;
}


