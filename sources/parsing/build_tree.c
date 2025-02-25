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
	if (!*((*parser)->ast))
		*((*parser)->ast) = create_tree_node(NULL);
	if (*((*parser)->ast))
	{
		branch = *((*parser)->ast);
		delete_links(*parser);
		save = (*parser)->tab[TTNEXT];
		branch->tokens = (*parser)->tab[TTCURR];
		reset_token_tab(*parser, (*parser)->tab[TTHEAD], TTHEAD, &branch->left);

		/*
		if (parse_script(&parser->ast, parser))
		{
			reset_token_tab(parser, save, TTHEAD, branch->right);
			return (parse_script(&(*ast)->right, parser));
		}
		*/
		if (parse_script(parser))
		{
			reset_token_tab(*parser, save, TTHEAD, &branch->right);
			return (parse_script(parser));
		}
	}
	return (branch);
}
