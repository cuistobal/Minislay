#ifndef EXECUTION_H
# define EXECUTION_H

//get_command_and_arguments.c
char    **get_command_and_arguments(t_tokn *list, int count);

//is_builtin.c
bool    is_builtin(char *command);

//modify_token_types.c
void    modify_token_types(t_tokn **expanded, t_tokn **redirections, int *count);

//expand.c
bool    expand(t_shel *minishell, t_tokn **list);

//
bool	split_list(t_tokn *current, t_tokn **assignations, t_tokn **expansions);

//
bool	prepare_for_exec(t_shel **minishell, t_tree *ast);

//traverse_ast.c
void    traverse_ast(t_shel **minishell, t_tree *ast);

//subshells.c
bool    handle_subshell(t_shel *minishell, t_tree *ast);

//word_splitting.c
bool	word_splitting(t_shel *minishell, t_tokn **current, char *expanded);

//globing.c
void	free_array(char **array, int count);
bool	match_pattern(char **patterns, char *current);
char	**identify_globing_patterns(char *globing);
bool	globing(t_tokn **list, const char *path);

//key_management.c
bool	get_expanded(t_shel *minishell, t_tokn **token, char **value, int *index);




#endif
