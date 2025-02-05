/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:51:57 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/04 14:13:18 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum s_type 
{
	OPAR,
	SQTE,
	DQTE,
	CPAR,
	MISC,
}	t_type;

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									PARSER									 //
//																			 //

//We use this enum to track the parser's state
enum parser_state
{
    STATE_NORML,
	STATE_SQUOT,
	STATE_DQUOT,
	STATE_SREDI,
	STATE_HREDI,
	STATE_SSHEL,
	STATE_ERROR,
};

typedef struct parser
{
	char	*input;
	char	*stack;
	char	syntax[4];
    char	state;
}   t_pars;

bool	set_state(t_parser *parser, int flag);
bool	unset_state(t_parser *parser, int flag);
bool	is_state_active(t_parser *parser, int flag);

// Enum for different character groups
typedef enum e_char_group
{
    GROUP_PAREN,
	GROUP_AMP_PIPE,
	GROUP_IREDIR,
	GROUP_OREDIR,
	GROUP_SQUOTES,
	GROUP_DQUOTES,
	GROUP_VAR_WILD,
	GROUP_WHITESPACE,
	GROUP_OTHER
}	t_char_group;

//Pas besoin
typedef enum
{
    SSTATE,
    USTATE,
    GSTATE,
    CMD_COUNT
}	state_manager;

#endif
