#ifndef STRUCTURES_H
# define STRUCTURES_H

//Tokens structure
typedef struct tokens
{
	int				type;
	char			*value;
	struct tokens	*next;
}	t_tokn;

//AST structure
typedef	struct	tree
{
	struct tokens	*tokens;
	struct tree		*left;
	struct tree		*right;
}	t_tree;

//Parsers structure
typedef struct parser
{
	int				state;
	struct tokens	*tab[TTSIZE];
	struct tree		**ast;
}	t_pars;

//AVL tree's structure


#endif
