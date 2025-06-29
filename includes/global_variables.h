/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:39:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 19:43:18 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_VARIABLES_H
# define GLOBAL_VARIABLES_H

# define MINISLAY "minislay > "

//Used
# define GRAMMAR "()|&><$=*\""
# define SPECIAL "()|&><"
# define EXPANDS "$*"

//Masks for terminal tokens

# define INIT 0b0000000000000000	//	initailisation a 0
# define OPAR 0b0000000000000001	//	parenthese ouvrante (
# define CPAR 0b0000000000000010	//	parenthese femante )
# define PIPE 0b0000000000000100	//	operateur pipe |
# define LAND 0b0000000000001000	//	operateur et &&
# define LORR 0b0000000000010000	//	operateur ou ||
# define WORD 0b0000000000100000	//	token de mot WORD
# define HDOC 0b0000000001000000	//	token here_doc <<
# define IRED 0b0000000010000000	//	token de redirection simple d'entree <
# define ORED 0b0000000100000000	//	token de redirection simple de sortie >
# define ARED 0b0000001000000000	//	token de redirection append de sortie >>
# define STAR 0b0000100000000000	//	token d'expansion globing *
# define EQUL 0b0001000000000000	//	token d'assignation de variable =
# define DQTE 0b0010000000000000	//	token d'apostrophe double "
# define DOLL 0b0100000000000000	//	token d'expansion dollar $
# define SQTE 0b1000000000000000	//	token d'apostrophe simple '

//Masks for the parser status
//	If SUBSHELL -> status & ROOTEDD || if status & ROOTED -> not rooted yet
# define INITIAL 0b00000000 //(?) Usefull ? COnfilct with ROOTEDD status ?
# define ROOTEDD 0b00000001 //Gets triggered when finding the first significant 
							//grammar element.
							//How to implement this logic when dealing with 
							//Subshells
							//
							//Make the recursive call inherit the SUBSHELL 
							//status ?
							//
							//	->	Desactivate on the first OPAR, reactivate on
							//		the second if applies.
							//
# define SUBSHEL 0b00000010 //Gets triggered on CMPDCMD
# define CMDLIST 0b00000100 //Gets triggered on LAND || LORR
# define COMMAND 0b00001000 //Gets triggered if !(status & CMDLIST)
# define CMPDCMD 0b00010000 //Gets triggred on OPAR
# define PIPELIN 0b00100000 //Gets triggered on PIPE
# define SIMPCMD 0b01000000 //Gets triggered if nothing else

//To silence the Warning triggered by check status util
//This bad boi nbeeds some reework
# define STATE_ERROR 0b00100000

//TT Stands for Token Tab and refers to the token_tab used within t_pars struct
# define TTSIZE 4	//	taille du tableau de pointeur dans la structrue de 
					//	parsing
# define TTHEAD 0	//	tete de la liste chainee en cours de traitement
# define TTPREV 1	//	adresse du noeud prev
# define TTCURR 2	//	adress du noeud current
# define TTNEXT 3	//	adress du noeud next

//Those macrops refers to the function tab we use for builtins
# define BCNT 7
# define BCDD "cd"
# define BPWD "pwd"
# define BENV "env"
# define BECO "echo"
# define BEXT "exit"
# define BUST "unset"
# define BEXP "export"

//Those identifiers are used within our env nodes
# define KEY 0
# define VALUE 1

//This is an additional grammar element representing the need for a recursive
//call within the AST
# define SUBSHELL "SUBSHELL"
# define EXECTBL 0b00000001
# define ARGUMNT 0b00000010 
# define FILENAM 0b00000100
# define ASSIGNS 0b00001000 
# define BUFFER_SIZE 1024
# define TAB_SIZE 128 
//Shifting operator from token type to exec type
# define CONVERT 3

//test expansions
# define LIMITERS "     *"
# define SPECIALS "$?"
# define CWD "."
# define PATH "PATH"
# define HEREDOC_PREFIX "/tmp/heredoc_"
# define HEREDOC "heredoc"
# define HERE ">"

# define CMD_INPUT 0
# define CMD_OUTPUT 1
# define EXIT_STATUS 32
# define INFILE 0
# define OUTFILE 1
# define READ_END 0
# define WRITE_END 1
# define EXPORT_PROMPT "export "

# define EXIT_MASK 0b1000000000

#endif
