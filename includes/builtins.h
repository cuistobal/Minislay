/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:59:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 10:13:39 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
int		cd(t_shel *minishell, char **arguments);

//echo.c
void	echo(const char **arguments, bool flag);

//env.c
int		env(t_shel *minishell, char **arguments);

//export.c
void	my_export(void);

//exit.c
void	my_exit(t_shel **minishell, t_exec **execution);

//pwd.c
int		pwd(t_shel *minishell);

//unsset.v
void	unset(void);
/* réimplementation des builtin*/
int		is_builtin(char *cmd);
//dispatcher unique qui route chaque commande vers sa fonction dedier
int		exec_builtin(t_shel **minishell, t_exec **execution);
int		builtin_echo(char **argv);

#endif
