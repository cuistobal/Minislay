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
	
	if (!*((*parser)->ast))
		*((*parser)->ast) = create_tree_node(NULL);
	if (*((*parser)->ast))
	{
		branch = *((*parser)->ast);

		delete_links(*parser);

		save = (*parser)->tab[TTNEXT];
		
//		delete_links(*parser);

		if ((*parser)->tab[TTCURR] && is_amp_pipe(*(*parser)->tab[TTCURR]->value))
		{

			branch->tokens = (*parser)->tab[TTCURR];

		//	(*(*parser)->ast)->left;
		//	(*(*parser)->ast)->right;
			
		//	(*(*parser)->ast)->left = create_tree_node(NULL);
			
			reset_token_tab(*parser, (*parser)->tab[TTHEAD], TTHEAD, &branch->left);
			
			//reset_token_tab(parser, (*parser)->tab[TTHEAD], TTHEAD, &(*(*parser)->ast)->left);

		/*	OLD
		if (parse_script(&parser->ast, parser))
		{
			reset_token_tab(parser, save, TTHEAD, branch->right);
			return (parse_script(&(*ast)->right, parser));
		}
		*/
		
			if (parse_script(parser))
			{
				
		//		(*(*parser)->ast)->right = create_tree_node(NULL);
			
				reset_token_tab(*parser, save, TTHEAD, &branch->right);
				
				//reset_token_tab(parser, save, TTHEAD, &(*(*parser)->ast)->right);
				
				return (parse_script(parser));
			}
			return (false);
		}
		
		branch->tokens = (*parser)->tab[TTHEAD];

		//print_ast(branch, "", "", 10000000);
	}
	return (branch);
}
