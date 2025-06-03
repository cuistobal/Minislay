/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:59:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/03 11:34:41 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
int		cd(t_shell *minishell, char **arguments);

//echo.c
void	echo(const char **arguments, bool flag);

//env.c
int		env(t_shell *minishell, char **arguments);

//export.c
int	    export(t_shell **minishell, char **args);

//exit.c
int	    my_exit(t_shell *minishell, char **args);

//pwd.c
int		pwd(t_shell *minishell);

//unsset.v
int	    unset(t_shell *minishell, char **args);
/* réimplementation des builtin*/
int		is_builtin(char *cmd);
//dispatcher unique qui route chaque commande vers sa fonction dedier
int		exec_builtin(char **argv, char **env, t_shell **minishell);
int		builtin_echo(char **argv);

#endif
