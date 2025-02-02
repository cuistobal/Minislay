#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TOKEN_SIZE 256

typedef struct s_token
{
    char *value;
    struct s_token *next;
} t_token;

typedef struct s_state
{
    int single_quote;
    int double_quote;
    int paren_count;
} t_state;

// Helper function to create a new token
t_token *new_token(char *value)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

// Adds a token to the token list
void add_token(t_token **head, char *value)
{
    t_token *new = new_token(value);
    if (!new)
        return;
    if (!*head)
        *head = new;
    else
    {
        t_token *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

// Handles unclosed quotes or parentheses
int check_errors(t_state *state)
{
    if (state->single_quote)
    {
        printf("Error: Unclosed single quote.\n");
        return 1;
    }
    if (state->double_quote)
    {
        printf("Error: Unclosed double quote.\n");
        return 1;
    }
    if (state->paren_count != 0)
    {
        printf("Error: Unmatched parentheses.\n");
        return 1;
    }
    return 0;
}

// Tokenizer function
t_token *tokenize(const char *input)
{
    t_token *tokens = NULL;
    t_state state = {0, 0, 0};
    char buffer[TOKEN_SIZE];
    int i = 0, j = 0;

    while (input[i])
    {
        if (input[i] == '\'' && !state.double_quote)
        {
            state.single_quote = !state.single_quote;
        }
        else if (input[i] == '\"' && !state.single_quote)
        {
            state.double_quote = !state.double_quote;
        }
        else if (input[i] == '(' && !state.single_quote && !state.double_quote)
        {
            state.paren_count++;
            add_token(&tokens, "(");
        }
        else if (input[i] == ')' && !state.single_quote && !state.double_quote)
        {
            state.paren_count--;
            if (state.paren_count < 0) // Error case: closing more than opening
            {
                printf("Error: Unmatched closing parenthesis.\n");
                return NULL;
            }
            add_token(&tokens, ")");
        }
        else if (isspace(input[i]) && !state.single_quote && !state.double_quote)
        {
            if (j > 0)
            {
                buffer[j] = '\0';
                add_token(&tokens, buffer);
                j = 0;
            }
        }
        else
        {
            buffer[j++] = input[i];
        }

        i++;
    }

    if (j > 0) // Last token
    {
        buffer[j] = '\0';
        add_token(&tokens, buffer);
    }

    if (check_errors(&state)) // Check unclosed quotes/parentheses
        return NULL;

    return tokens;
}

// Prints the token list
void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        printf("Token: [%s]\n", tokens->value);
        tokens = tokens->next;
    }
}

// Free the token list
void free_tokens(t_token *tokens)
{
    t_token *tmp;
    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}

// Test the tokenizer
int main(int argc, char **argv)
{

    t_token *tokens = tokenize(argv[1]);
    if (tokens)
    {
        print_tokens(tokens);
        free_tokens(tokens);
    }
    return 0;
}
