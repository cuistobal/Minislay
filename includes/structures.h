/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:25:19 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 09:09:50 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

//	NEEDS FURTHER THINKING	->	USE THIS BAD BOI FOR SIGNALS ?
//
//Sell's main structure, holding environement variables and misc informations:
//
//	1.	envp	->	Linked list holding the env variable. Newly exported 
//					variables are appended at the end of the list.
//	2.	local	->	Linked list holding local variables, accessible only from
//					this instance -No inheritance for subshells-.
//	3.	command	->	Linkled list holding variable accessible for the command
//					only -happens when you get an assignation list && a command
//					list-. Gets reset for each command block.
//	4.	expt	->	AVL Tree holding environement variables. Used for export &&
//					quick access.
typedef struct shell
{
	struct	avltree	*expt;
	struct  env		*envp;
	struct	env		*local;
	struct	env		*command;
	char			*special[10];
}	t_shell;

//Basic environement node
typedef struct env
{/*
46
//AVL Tree's structuroe
47
typedef struct  avltree
48
{
49
  int       height;
50
  char      *data[2];
51
  struct avltree  *left;
52
  struct avltree  *right;
53
} t_avlt;
54
*/
	char		*var[2];
	struct  env *next;
}   t_env;

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

typedef struct exec
{
	pid_t		pid;
	int			pipe[2];
	int			redirections[2];
	char		**command;
	char		**environ;
	struct exec	*next;
}	t_exec;

#endif
