/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:59:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 05:49:27 by ynyamets         ###   ########.fr       */
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
int	export(t_shel *minishell, char **args);

//exit.c
int	my_exit(t_shel *minishell, char **args);

//pwd.c
int		pwd(t_shel *minishell);

//unsset.v
int	unset(t_shel *minishell, char **args);
/* réimplementation des builtin*/
int		is_builtin(char *cmd);
//dispatcher unique qui route chaque commande vers sa fonction dedier
int		exec_builtin(char **argv, char **env, t_shel *minishell);
int		builtin_echo(char **argv);

#endif
