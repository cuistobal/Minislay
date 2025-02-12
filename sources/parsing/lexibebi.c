#include "minislay.h"

// Main parsing function with backtracking
bool parse_script(t_tokn *tokens) {
    t_tokn *current = tokens;
    if (tokens) 
	{
        printf("%s\t@\t%s\n", tokens->value, __func__);
	//	return parse_command_list(&current);
		parse_command_list(&current);
    }
	(current) ? printf("%s\n", current->value) : printf("NULL\n");
    return (current == NULL);
}

// CommandList → Command ('&&' | '||') CommandList | Command
bool parse_command_list(t_tokn **current) {
    t_tokn *initial_node = *current;
    if (*current) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        if (parse_command(current)) {
            while (*current && ((*current)->type == LAND || (*current)->type == LORR)) {
                *current = (*current)->next;
                if (!parse_command(current)) {
                    return false;
                }
            }
            return true;
        }
        *current = initial_node;
    }
    return false;
}

// Determine if it's a simple command, compound command, or pipeline
bool parse_command(t_tokn **current)
{
    t_tokn *initial_node;
    
	if (*current)
	{
    	printf("%s\t@\t%s\n", (*current)->value, __func__);
		initial_node = *current;
        if ((*current)->type == OPAR) {
            return parse_compound_command(current);
        } else if (parse_simple_command(current)) {
            return true;
        } else 
		{
			*current = initial_node;
            return parse_pipeline(current);
        }
    }
    return false;
}

// SimpleCommand → Assignment* WORD (Argument | Redirection)*
bool parse_simple_command(t_tokn **current) {
    if (*current) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        while ((*current)->type == WORD && (*current)->next && (*current)->next->type == EQUL) {
            if (!parse_assignment(current)) {
                return false;
            }
        }
        if ((*current)->type == WORD) {
            *current = (*current)->next;
            while (*current && ((*current)->type >= WORD && (*current)->type <= ARED)) {
                if ((*current)->type == WORD) {
                    if (!parse_argument(current)) {
                        return false;
                    }
                } else {
                    if (!parse_redirection(current)) {
                        return false;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

// Pipeline → Command ('|' Command)*
bool parse_pipeline(t_tokn **current) {
    if (*current) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        if (parse_command(current)) {
            while (*current && (*current)->type == PIPE) {
                *current = (*current)->next;
                if (!parse_command(current)) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

// CompoundCommand → '(' CommandList ')'
bool parse_compound_command(t_tokn **current) {
    if (*current && (*current)->type == OPAR) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        *current = (*current)->next;
        if (parse_command_list(current)) {
            if ((*current)->type == CPAR) {
                *current = (*current)->next;
                return true;
            }
        }
    }
    return false;
}

// Assignment → WORD '=' Expression
bool parse_assignment(t_tokn **current) {
    if (*current && (*current)->next) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        if ((*current)->type == WORD && (*current)->next->type == EQUL) {
            *current = (*current)->next->next;
            return parse_expression(current);
        }
    }
    return false;
}

// Argument → WORD
bool parse_argument(t_tokn **current) {
    if (*current && (*current)->type == WORD) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        *current = (*current)->next;
        return true;
    }
    return false;
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
bool parse_redirection(t_tokn **current) {
    if (*current && ((*current)->type >= IRED && (*current)->type <= ARED)) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        *current = (*current)->next;
        if ((*current)->type == WORD) {
            *current = (*current)->next;
            return true;
        }
    }
    return false;
}

// Expression → '$' WORD | WORD
bool parse_expression(t_tokn **current) {
    if (*current) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        if ((*current)->type == DOLL) {
            *current = (*current)->next;
        }
        return parse_argument(current);
    }
    return false;
}
