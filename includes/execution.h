/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:24:33 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 12:37:21 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

//command_type.c
bool	is_builtin_bool(char *command);
bool	is_absolute(char *command);
bool	is_executable(char *command);

//retrieve_path.c
bool	retrieve_path(t_shell *minishell, char **command);

//get_command_and_arguments.c
char    **get_command_and_arguments(t_shell *minishell, t_tokn *list, int count);

//is_builtin.c
//bool    is_builtin(char *command);

//modify_token_types.c
void    modify_token_types(t_tokn **expanded, t_tokn **redirections, int *count);

//expand.c
bool    expand(t_shell *minishell, t_tokn **list, int *count);

//
bool	split_list(t_tokn *current, t_tokn **assignations, t_tokn **expansions);

//
//bool	prepare_for_exec(t_shel **minishell, t_tree *ast);
//char	**prepare_for_exec(t_shel *minishell, t_tree *ast, int *size);
t_exec	*prepare_for_exec(t_shell **minishell, t_tree *ast, t_tokn **redirections);

//traverse_ast.c
void	execute_pipeline(t_shell **minishell, t_exec *execute);
void	traverse_ast(t_shell **minishell, t_tree *ast);

//subshells.c
bool    handle_subshell(t_shell *minishell, t_tree *ast);

//word_splitting.c
//bool	word_splitting(t_shel *minishell, t_tokn **current, char *expanded);
bool	word_splitting(t_shell *minishell, t_tokn **current);

//globing.c
void	free_array(char **array, int count);
bool	match_pattern(char **patterns, char *current, int *i);
char	**identify_globing_patterns(char *globing);
bool	globing(t_tokn **list, const char *path, int *count);

//key_management.c
bool	get_expanded(t_shell *minishell, char *token, char **value, int *index);

//redirections
bool	handle_redirection_list(t_shell *minishell, t_tokn **list);
bool	handle_here_doc(t_shell *minishell, t_tokn **redirections);

void	execute_command(char **command, char **envp);
void	execute_builtin(t_shell *minishell, char **command, char **envp);


t_exec	*create_execution_node(t_shell **minishell, t_tree *ast);

//int		create_child_process(t_shel *minishell, t_exec *execution);

//create_process.c
int		execute_command_in_child(char **command, char **env);
int		create_child_process(t_shell *minishell, t_exec **execution);

//wait_module.c
int		wait_module(pid_t *pids, int count);

//ipc_module.c
int		handle_communication_in_child(t_exec **node);
int		handle_communication_in_parent(t_exec **node);
int		handle_redirections(t_exec **execution, int original_stds[2]);


//handle_pipeline.c
t_exec	*build_command_node(t_shell **minishell, t_tree *ast, int *count);

int		execute_commands(t_shell **minishell, t_exec *execution, int *count);

int	setup_redirections_in_child(t_shell **minishell, t_exec **node, int pipe[][2], int cmd);

#endif
