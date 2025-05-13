/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:59:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 09:59:05 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
int		cd(t_shel *minishell, char *path);

//echo.c
void	echo(const char **arguments, bool flag);

//env.c
void	env(t_shel *minishell);

//export.c
void	my_export(void);

//exit.c
void	my_exit(void);

//pwd.c
void	pwd(char *current_dir);

//unsset.v
void	unset(void);
/* réimplementation des builtin*/
int is_builtin(char *cmd);
//dispatcher unique qui route chaque commande vers sa fonction dedier
int exec_builtin(char **argv, t_shel *minishell);
int builtin_echo(char **argv);

#endif
