#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum for different character groups
typedef enum e_char_group
{
    GROUP_PAREN,       // [( )]
    GROUP_AMP_PIPE,    // [& |]
    GROUP_IREDIR,      // <
    GROUP_OREDIR,      // >
    GROUP_SQUOTES,     // '
    GROUP_DQUOTES,     // "
    GROUP_VAR_WILD,    // [$ *]
    GROUP_WHITESPACE,  // [\t \n \v \f \r <space>]
    GROUP_OTHER        // Default for non-special characters
} t_char_group;

// Function prototypes for checking character groups
int is_amp_pipe(char c);
int is_squotes(char c);
int is_dquotes(char c);
int is_whitespace(char c);
int is_iredir(char c);
int is_oredir(char c);
int is_paren(char c);
int is_var_wild(char c);

// Function pointer array
int (*group_functions[])(char) = {
    is_paren,
    is_amp_pipe,
    is_iredir,
    is_oredir,
    is_squotes,
    is_dquotes,
    is_var_wild,
    is_whitespace
};

// Check functions
int is_amp_pipe(char c) { return (c == '&' || c == '|'); }
int is_squotes(char c) { return (c == '\''); }
int is_dquotes(char c) { return (c == '"'); }
int is_whitespace(char c) { return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' '); }
int is_iredir(char c) { return (c == '<'); }
int is_oredir(char c) { return (c == '>'); }
int is_paren(char c) { return (c == '(' || c == ')'); }
int is_var_wild(char c) { return (c == '$' || c == '*'); }

// Determine the group of a character
int get_group(char c)
{
    int index;
    
    index = 0;
    while (index < GROUP_OTHER)
    {
        if (group_functions[index](c))
            return index;
        index++;
    }
    return GROUP_OTHER; // Default if not found
}

// Hashing function that returns values between 0-9
int *hash_input(char *user_prompt, int len)
{
    int *input;
    int index;

    input = NULL;
    if (user_prompt)
    {
        input = (int *)malloc(sizeof(int) * len);
        if (!input)
            return NULL;

        index = 0;
        while (index < len)
        {
            input[index] = get_group(user_prompt[index]);
            index++;
        }
    }
    return input;
}

int main(int argc, char **argv)
{
    int len;
    int *input;
    int index;

    if (argc == 2)
    {
        len = strlen(argv[1]);
        input = hash_input(argv[1], len);
        if (input)
        {
            index = 0;
            while (index < len)
            {
                printf("%d", input[index]);
                index++;
            }
            printf("\n");
            free(input);
            printf("%s\n", argv[1]);
        }
    }
    return 0;
}
