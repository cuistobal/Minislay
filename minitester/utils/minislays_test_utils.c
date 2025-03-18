#include "minislay.h"

void	print_env(t_env *environement)
{
	t_env	*current;

	if (environement)
	{
		printf("environement\n");
		current = environement;
		while (current)
		{
			printf("%s	->	%s\n", current->var[KEY], current->var[VALUE]);
			current = current->next;
		}
	}
}

//Printing tokens
void	print_tokens(t_tokn *current)
{
	while (current)
	{
		printf("%s %d	", current->value, current->type);
		current = current->next;
	}
	printf("\n");
}

//Printing AST
void	print_ast(t_tree *ast, char *origin, char *destination, int lvl)
{
	if (ast)
	{
	//	print_ast(ast->left, destination, "LEFT", lvl + 1);
		
		printf("%s	->	%s	@	%d\n", origin, destination, lvl);
		while (ast->tokens)
		{
			printf("%s ", ast->tokens->value);
			ast->tokens = ast->tokens->next;
		}
		printf("\n");
		
		print_ast(ast->left, destination, "LEFT", lvl + 1);
		
		print_ast(ast->right, destination, "RIGHT", lvl + 1);

		return ;
	}

//	printf("%s	->	%s	@	%d\n", origin, destination, lvl);
//	printf("LEAF\n");
}

//
void	print_ast_BFS(t_tree *ast)
{
    int front = 0, rear = 0;
    t_tree **queue, *current;

	current = NULL;
	if (ast)
	{
   		queue = (t_tree **)malloc(1000 * sizeof(t_tree*)); // Taille fixe pour simplifier
    	queue[rear++] = ast;
	    while (front < rear)
		{
    		current = queue[front++];
        	printf("%s ", current->tokens->value);
        	if (current->left)
            	queue[rear++] = current->left;
        	if (current->right)
            	queue[rear++] = current->right;
    	}
    	free(queue);
	}
}

//
void	print_ast_DFS(t_tree *ast, int lvl, char *c, char *s)
{
	if (ast)
	{
		printf("\n%s	%d	%s\n", c, lvl, s);
		while (ast->tokens)
		{
			printf("%s ", ast->tokens->value);
			ast->tokens = ast->tokens->next;
		}
		printf("\n");

		print_ast_DFS(ast->left, lvl + 1, "left", c);

		print_ast_DFS(ast->right, lvl + 1, "right", c);
	}
}

//
void	print_parser(t_pars *parser)
{

	if (parser)
	{
		printf("%s\n\n", __func__);

		//parser->tokens ? print_tokens(parser->tokens) : printf("No tokens\n");

		if (parser->tab)
		{
			for (int i = 0; i < TTSIZE; i++)
				parser->tab[i] ? printf("parser->tab[%d]	->	%s\n", i, parser->tab[i]->value) : printf("parser->tab[%d]	->	NULL\n", i);
		}

		printf("state		->	%d\n", parser->state);

		parser->ast? print_ast_DFS(*(parser)->ast, 0, "root", "root") : printf("No AST\n");
	}
}

void	print_exec(t_tokn *assignations, t_tokn *expansions, t_tokn *redirections, char **execution)
{
	printf("ASSIGNATIONS:\n");
	print_tokens(assignations);
	printf("EXPANSIONS:\n");
	print_tokens(expansions);
	printf("REDIRECTIONS:\n");
	print_tokens(redirections);
	printf("EXECUTION:\n");
	if (execution)
	{
		while (*execution)
		{
			printf("%s ", *execution);
			execution++;
		}
	}
	printf("\n");
}
