#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STATE_NORMAL       0
#define STATE_SINGLE_QUOTE (1 << 0)  // '
#define STATE_DOUBLE_QUOTE (1 << 1)  // "
#define STATE_SUBSHELL     (1 << 2)  // ()
#define STATE_ERROR        (1 << 3)  // Error flag

# define OPAR '('
# define SQTE 39
# define DQTE '"'
# define CPAR ')'

typedef struct s_parser 
{
    int state;   // Bitwise tracking of the current state
    char *stack; // Stack for parenthesis matching
    int top;
}	t_parser;

// ---- STACK OPERATIONS ----
void push(t_parser *parser, char c) 
{
    if (parser->top < 255)
        parser->stack[parser->top++] = c;
}

char pop(t_parser *parser) 
{
    if (parser->top > 0)
        return parser->stack[--parser->top];
    return '\0';
}

char peek(t_parser *parser)
{
    if (parser->top > 0)
        return parser->stack[parser->top - 1];
	return '\0';
}

// ---- STATE MANAGEMENT ----
void set_state(t_parser *parser, int flag) { parser->state |= flag; }
void unset_state(t_parser *parser, int flag) { parser->state &= ~flag; }
bool is_state_active(t_parser *parser, int flag) { return parser->state & flag; }

// ---- MAIN CHARACTER HANDLING ----
bool handle_char(t_parser *parser, char c) 
{
    if (c == SQTE) 
	{
        if (is_state_active(parser, STATE_SINGLE_QUOTE))
            unset_state(parser, STATE_SINGLE_QUOTE);
		else if (!is_state_active(parser, STATE_DOUBLE_QUOTE))
            set_state(parser, STATE_SINGLE_QUOTE);
	}
    else if (c == DQTE) 
	{
        if (is_state_active(parser, STATE_DOUBLE_QUOTE))
            unset_state(parser, STATE_DOUBLE_QUOTE);
		else if (!is_state_active(parser, STATE_SINGLE_QUOTE))
            set_state(parser, STATE_DOUBLE_QUOTE);
	}
    else if (c == OPAR) 
	{
        if (!is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE))
		{
            set_state(parser, STATE_SUBSHELL);
            push(parser, '(');
		}
    }
    else if (c == CPAR) 
	{
        if (!is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE))
		{
            if (peek(parser) == '(') 
			{
                pop(parser);
                if (parser->top == 0)
					unset_state(parser, STATE_SUBSHELL);
            } 
			else 
                return (set_state(parser, STATE_ERROR), false);
        }
    }
	printf("state %d for %c\n", parser->state ,c);
    return true;
}

// ---- PARSE FUNCTION ----
bool parse_input(const char *input) 
{
    t_parser parser = {STATE_NORMAL, "", 0};

    for (int i = 0; input[i]; i++) 
	{
        if (!handle_char(&parser, input[i]))
		{
            printf("❌ Syntax Error: Unmatched parentheses\n");
            return false;
        }
    }

    if (is_state_active(&parser, STATE_SINGLE_QUOTE)) {
        printf("❌ Syntax Error: Unclosed '\n");
        return false;
    }
    if (is_state_active(&parser, STATE_DOUBLE_QUOTE)) {
        printf("❌ Syntax Error: Unclosed \"\n");
        return false;
    }
    if (is_state_active(&parser, STATE_SUBSHELL)) {
        printf("❌ Syntax Error: Unclosed (\n");
        return false;
    }

    printf("✅ Valid Input\n");
    return true;
}

int	main()
{
    char *test_cases[] = {
        "echo \"hello (world)\" 'test'",         
		"echo 'single ( inside'",
        "echo \"hello (world\"",
		"echo 'hello \"world",
		"echo (echo hello",
		"echo 'test (hello)'",
		"echo 'test \"(hello)'",
		"((('$' && '\"')))",
		NULL};

    	for (int i = 1; test_cases[i]; i++) 
		{
			printf("\nTesting: %s\n", test_cases[i]);
    		parse_input(test_cases[i]);
		}
	return 0;
}

/*
// ---- TEST CASES ----
int main(int argc, char **argv) 
{
	if (argc > 1)
	{
    	for (int i = 1; argv[i]; i++) 
		{
        	printf("\nTesting: %s\n", argv[i]);
        	parse_input(argv[i]);
    	}
	}
    return 0;
}*/
