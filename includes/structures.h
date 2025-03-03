#ifndef STRUCTURES_H
# define STRUCTURES_H

//Sell's main structure, holding env etc
typedef struct shell
{
	struct  envp	*envp;
}	t_shel;

//Env main structure -> Holds a pointer to environremnt variables, local 
//variables and export's AVL tree.
typedef struct envp
{
	struct env	*envp;
	struct env	*local;
	struct tree	*expt;
}   t_envp;

//Basic environement node
typedef struct env
{
	char		*var;
	struct  env *next;
}   t_envn;

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
