/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:03:44 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 14:44:40 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
//void	cd(t_shel *minishell, char *path);
void	cd(void *p1, void *p2);

//pwd.c
//void	pwd(char *current_dir);
void	pwd(void *p1, void *p2);

//env.c
//void	env(t_shel *minishell);
void	env(void *p1, void  *p2);

//echo.c
//void	echo(const char **arguments, bool flag);
void	echo(void *p1, void *p2);

//exit.c
//void	my_exit(void);
void	my_exit(void *p1, void *p2);

//unset.c
//void	unset(void);
void	unset(void *p1, void *p2);

//export.c
//void	my_export(void);
void	export(void *p1, void *p2);

//unset.c
void	unset(void *p1, void *p2);

#endif
