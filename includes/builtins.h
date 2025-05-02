#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
void	cd(t_shel *minishell, char *path);

//echo.c
void	echo(const char **arguments, bool flag);

//env.c
void	env(t_shel *minishell);

//export.c
void	my_export(void);

//exit.c
void	my_exit(t_shel *minishell);

//pwd.c
void	pwd(char *current_dir);

//unsset.v
void	unset(void);

#endif
