#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

//Checking if we have a pipe or amp token
bool	is_pipe(char c)
{
	return (c == '|');
}

bool	is_amp(char c)
{
	return (c == '&');
}

//Checking if we have a whitespace token
bool	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' )
		return (true);
	return (c == '\f' || c == '\r' || c == ' ');
}

//Checking if we have a expansion token
bool	is_var_wild(char c)
{
	return (c == '$' || c == '*' || c == '=');
}

//Checking if we have an opening or closing parenthesis
bool	is_paren(char c)
{
	return (c == '(' || c == ')');
}

//Checking if we have a single quote
bool	is_squotes(char c)
{
	return (c == '\'');
}

//Checking if we have a double quote
bool	is_dquotes(char c)
{
	return (c == '"');
}

//Checking if we have a input redirection
bool	is_iredir(char c)
{
	return (c == '<');
}

//Checking if we have an outpute redirection
bool	is_oredir(char c)
{
	return (c == '>');
}

static int get_group(bool (*group_functions[])(char), char c)
{
    int 	index;

    index = 0;
    while (index < 9 && group_functions[index])
    {
        if (group_functions[index](c))
            return (index);
        index++;
    }
    return (9);
}

//Initialises the array of function pointers.
static void	initialise_check_type(bool (*group_functions[])(char))
{
    group_functions[0] = is_paren;
    group_functions[1] = is_pipe;
    group_functions[2] = is_amp;
    group_functions[3] = is_iredir;
    group_functions[4] = is_oredir;
    group_functions[5] = is_squotes;
    group_functions[6] = is_dquotes;
    group_functions[7] = is_var_wild;
    group_functions[8] = is_whitespace;
}

//Hashing function that turns the user's input into a chain of digits rannging
//from 0 to 9 included.
//We use this array to identify tokens and construct our execution tree.
int is_valid_transition(int from, int to)
{
    static const int precedence[10][10] = 
	{
	//	{ () |  &  <  >  '  " $=*' ' M }
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, //	0	PAREN
        { 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 }, //	1	PIPE
        { 1, 0, 1, 0, 0, 0, 0, 0, 1, 1 }, //	2	AMP
        { 0, 0, 0, 2, 0, 0, 0, 1, 1, 1 }, //	3	IREDIR
        { 0, 0, 0, 0, 2, 0, 0, 1, 1, 1 }, //	4	OREDIR
        { 0, 0, 0, 0, 0, 1, 2, 1, 1, 1 }, //	5	SQUOTES
        { 0, 0, 0, 0, 0, 2, 1, 1, 1, 1 }, //	6	DQUOTES
        { 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 }, //	7	VAR_WILD
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, //	8	WHITESPACE
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }  //	9	OTHER
    };
    return precedence[from][to];
}

uint8_t	*hash_input(char *user_prompt, int len)
{
    int 	index;
    uint8_t	*input;
	bool	(*check_type[9])(char);

    input = NULL;
    if (user_prompt)
    {
        input = (uint8_t *)malloc(sizeof(uint8_t) * len);
        if (input)
		{
			index = 0;
			initialise_check_type(check_type);
        	while (index < len)
        	{
        	    input[index] = get_group(check_type, user_prompt[index]);
				int test = is_valid_transition(input[index - 1], input[index]);
				if (test == 0)
					printf("error:	\n%d	&&	%d\n%c	&&	%c\n", input[index -1], input[index], user_prompt[index - 1], user_prompt[index]);
				else if (test == 2)
					printf("warning:\n%d	&&	%d\n%c	&&	%c\n", input[index -1], input[index], user_prompt[index - 1], user_prompt[index]);
				index++;
        	}
			return (input);
		}
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    int len;
    int index;
    uint8_t	*input;

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
