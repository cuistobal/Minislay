#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STATE_NORMAL       0
#define STATE_SINGLE_QUOTE (1 << 0)  // '
#define STATE_DOUBLE_QUOTE (1 << 1)  // "
#define STATE_SUBSHELL     (1 << 2)  // ()
#define STATE_ERROR        (1 << 3)  // Error flag

#define OPAR '('
#define SQTE 39
#define DQTE '"'
#define CPAR ')'

// ---- STRUCTURE ----
typedef struct s_parser
{
    int state;     // Bitwise tracking of the current state
    int top;       // Stack pointer (index)
    int capacity;  // Stack capacity
    char *stack;   // Stack for parenthesis matching (dynamic allocation)
}	t_parser;

// ---- STACK OPERATIONS ----
void push(t_parser *parser, char c)
{
    char	*new_stack;
    int		new_capacity;

    if (parser->top >= parser->capacity)
	{
        new_capacity = parser->capacity + 1;
        new_stack = realloc(parser->stack, new_capacity); //Remplacer par ft_realloc
        if (!new_stack)
		{
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        parser->capacity = new_capacity;
        parser->stack = new_stack;
    }
    parser->stack[parser->top++] = c;
}

char pop(t_parser *parser) {
    if (parser->top > 0)
        return parser->stack[--parser->top];
    return '\0';
}

char peek(t_parser *parser) {
    if (parser->top > 0)
        return parser->stack[parser->top - 1];
    return '\0';
}

// ---- STATE MANAGEMENT ----
void set_state(t_parser *parser, int flag) { parser->state |= flag; }
void unset_state(t_parser *parser, int flag) { parser->state &= ~flag; }
bool is_state_active(t_parser *parser, int flag) { return parser->state & flag; }

// ---- CHARACTER HANDLING ----
bool handle_quotes(t_parser *parser, char c)
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
    return true;
}

bool handle_parentheses(t_parser *parser, char c)
{
    if (c == OPAR && !is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE)) 
	{
        set_state(parser, STATE_SUBSHELL);
        push(parser, OPAR);
    }
    else if (c == CPAR && !is_state_active(parser, STATE_SINGLE_QUOTE | STATE_DOUBLE_QUOTE)) 
	{
        if (peek(parser) == OPAR) 
		{
            pop(parser);
            if (parser->top == 0)
                unset_state(parser, STATE_SUBSHELL);
        } 
		else 
            return (set_state(parser, STATE_ERROR), false);
    }
    return true;
}

bool handle_char(t_parser *parser, char c)
{
    if (c == SQTE || c == DQTE)
        return handle_quotes(parser, c);
    if (c == OPAR || c == CPAR)
        return handle_parentheses(parser, c);
    return true;
}

// ---- PARSE FUNCTION ----
bool parse_input(const char *input)
{
    t_parser	parser;

    parser.state = STATE_NORMAL;
    parser.top = 0;
    parser.capacity = 1;
	parser.stack = malloc(parser.capacity);
    if (!parser.stack)
	{
        printf("Memory allocation failed\n");
        return false;
    }
	else
		parser.stack[parser.top] = '\0';

    for (int i = 0; input[i]; i++)
	{
        if (!handle_char(&parser, input[i]))
		{
            printf("❌ Syntax Error: Unmatched parentheses\n");
            free(parser.stack);
            return false;
        }
    }

    if (is_state_active(&parser, STATE_SINGLE_QUOTE))
	{
        printf("❌ Syntax Error: Unclosed '\n");
        free(parser.stack);
        return false;
    }
    if (is_state_active(&parser, STATE_DOUBLE_QUOTE)) {
        printf("❌ Syntax Error: Unclosed \"\n");
        free(parser.stack);
        return false;
    }
    if (is_state_active(&parser, STATE_SUBSHELL)) {
        printf("❌ Syntax Error: Unclosed (\n");
        free(parser.stack);
        return false;
    }

    printf("✅ Valid Input\n");
    free(parser.stack);
    return true;
}

// ---- TEST CASES ----
int main()
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
        NULL
    };

    for (int i = 0; test_cases[i]; i++) {
        printf("\nTesting: %s\n", test_cases[i]);
        parse_input(test_cases[i]);
    }

    return 0;
}
