#ifndef STRUCTURES_H
# define STRUCTURES_H

//Sell's main structure, holding env etc
typedef struct shell
{
	struct  env		*envp;
	struct	env		*local;
	struct	avltree	*expt;
}	t_shel;

//Basic environement node
typedef struct env
{
	char		*var[2];
	struct  env *next;
}   t_env;

typedef struct	avltree
{
	int				height;
	char			*data[2];
	struct avltree	*left;
	struct avltree	*right;
}	t_avlt;

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
