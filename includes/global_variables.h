/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:39:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/06 12:25:44 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_VARIABLES_H
# define GLOBAL_VARIABLES_H

# define MINISLAY "minislay > "

/*
//Not used anymore
//Various states of the parser
# define STATE_NORML 0b00000000
# define STATE_SQUOT 0b00000001
# define STATE_DQUOT 0b00000010
# define STATE_SSHEL 0b00000100
# define STATE_IREDI 0b00001000
# define STATE_OREDI 0b00010000
# define STATE_ERROR 0b00100000
//

//Those status need to be reworked
# define TOKEN_WORD          0
# define TOKEN_ASSIGNMENT    1
# define TOKEN_REDIR_IN      2
# define TOKEN_REDIR_OUT     3
# define TOKEN_APPEND        4
# define TOKEN_HEREDOC       5
# define TOKEN_PIPE          6
# define TOKEN_SINGLE_QUOTE  7
# define TOKEN_DOUBLE_QUOTE  8
# define TOKEN_DOLLAR        9
# define TOKEN_NEWLINE       10
# define TOKEN_EOF           11
# define TOKEN_AND_IF        12
# define TOKEN_OR_IF         13
# define TOKEN_PAREN_OPEN    14
# define TOKEN_PAREN_CLOSE   15
# define TOKEN_WILDCARD      16
*/

//Tokens definition by list

//Used
# define GRAMMAR "()|&><$=*\""
# define SPECIAL "()|&><"

//Not sure if used
# define IAE "$=*"

//Not used yet
# define QUOTES "\"'"


//Masks for terminal tokens

# define INIT 0b0000000000000000
# define OPAR 0b0000000000000001
# define CPAR 0b0000000000000010

# define PIPE 0b0000000000000100

# define LAND 0b0000000000001000
# define LORR 0b0000000000010000

# define WORD 0b0000000000100000

# define IRED 0b0000000001000000
# define HDOC 0b0000000010000000
# define ORED 0b0000000100000000
# define ARED 0b0000001000000000

# define STAR 0b0000100000000000
# define EQUL 0b0001000000000000

# define DQTE 0b0010000000000000

# define DOLL 0b0100000000000000

# define SQTE 0b1000000000000000

# define XXXX 0b1000000000000000

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

/*
//Masks for the parser status

#define State START
#define State 
#define State 2
#define State 3
#define State 4
#define State 5
#define State 6
#define State 7
#define State 8
#define State 9
#define State 10
#define State 11
#define State 12
#define State 13
#define State 14
#define State 15
#define State 16
#define State 17
#define State 18
#define State 19
#define State 20
#define State 21
#define State 22
#define State 23
#define State 24
#define State 25
#define State 26
#define State 27
#define State 28
#define State 29
#define State 30
#define State 31
#define State 32
#define State 33
#define State 34
#define State 35
#define State 36
*/

//Others
# define STACK_SIZE 2

//TT Stands for Token Tab
# define TTSIZE 4

# define TTHEAD 0
# define TTPREV 1
# define TTCURR 2
# define TTNEXT 3

/*	OLD	->	CONFLICT WITH CURRENTLY USED MASKS

# define DELIMITERS 9

//Subshells
# define OPAR '('
# define CPAR ')'

//Grammar
# define PIPE '|'
# define AMPR '&'

//Redirections
# define IRDR '<'
# define ORDR '>'

//Assignations
# define EQUL '='

//Expansions
# define DOLL '$'
# define STAR '*'

enum
{
	OPAR,
	CPAR,
	PIPE,
	AMPR,
	IRDR,
	ORDR,
	EQUL,
	DOLL,
	STAR
};

//Quotes
# define SQTE '\''
# define DQTE '"'
*/

# define BCNT 7

# define BCDD "cd"
# define BPWD "pwd"
# define BENV "env"
# define BECO "echo"
# define BEXT "exit"
# define BUST "unset"
# define BEXP "export"

#endif
