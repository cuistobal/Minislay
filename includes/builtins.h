#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
void	cd(t_shel *minishell, char *path);

//echo.c
void	echo(const char **arguments, bool flag);

//env.c
void	env(t_shel *minishell);

//exit.c
void	my_exit(void);

//pwd.c
void	pwd(char *current_dir);

#endif
