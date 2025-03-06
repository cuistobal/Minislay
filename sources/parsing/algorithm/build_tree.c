#include "minislay.h"

//We use this function to create a new tree_node
t_tree	*create_tree_node(t_tokn *tokens)
{
	t_tree	*new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	if (new_node)
	{
		print_tokens(tokens);
		new_node->tokens = tokens;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	return (new_node);
}

//This function builds the AST
bool	build_ast(t_pars **parser)
{
	t_tokn	*save;
	t_tree	*branch;

	branch = NULL;
	//Ajout check parser && parser->ast
	//if (*parser && !*((*parser)->ast))
	if (!*((*parser)->ast))
		*((*parser)->ast) = create_tree_node(NULL);
	//if (*parser && *((*parser)->ast))
	if (*((*parser)->ast))
	{
		branch = *((*parser)->ast);
		delete_links(*parser);
		save = (*parser)->tab[TTNEXT];

	//	printf("%s\n", (*parser)->tab[TTPREV]->value);
	
		/*
		for (int  i = 0; i < TTSIZE; i++)
		{
			print_tokens((*parser)->tab[i]);
			printf("\n");
		}
		printf("\n");
		*/
		if ((*parser)->tab[TTCURR]) //&& valid_lexeme(, ) 
			//	is_amp_pipe(*(*parser)->tab[TTCURR]->value))
		{
			branch->tokens = (*parser)->tab[TTCURR];
			reset_parser(*parser, (*parser)->tab[TTHEAD], TTHEAD, &branch->left);	
			if (parse_script(parser))
			{
				reset_parser(*parser, save, TTHEAD, &branch->right);	
				return (parse_script(parser));
			}
			return (false);
		}
		branch->tokens = (*parser)->tab[TTHEAD];
	}
	return (branch);
}
