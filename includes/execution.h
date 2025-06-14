/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:24:33 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 16:55:57 by chrleroy         ###   ########.fr       */
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
char	**get_command_and_arguments(t_shell *minishell, t_tokn *list);

//modify_token_types.c
void	modify_token_types(t_tokn **expanded, t_tokn **redirections);

//expand.c
bool	expand(t_shell *minishell, t_tokn **list);

//
bool	split_list(t_tokn *current, t_tokn **assignations, t_tokn **expansions);

//
t_exec	*prepare_for_exec(t_shell **minishell, t_tokn *tokens);

//traverse_ast.c
void	execute_pipeline(t_shell **minishell, t_exec *execute);
int		traverse_ast(t_shell **minishell, t_tree *ast);

//subshells.c
int		handle_subshell(t_shell *minishell, t_tree *ast);

//word_splitting.c
bool	word_splitting(t_shell *minishell, t_tokn **current);

//globing.c
bool	match_pattern(char *pattern, char *current);
bool	valid_star_expansion(char *pattern, char *current);
bool	globing(t_tokn **list, const char *path, int *count);

//key_management.c
bool	get_expanded(t_shell *minishell, char *token, char **value, int *index);

//redirections
bool	handle_redirection_list(t_shell *minishell, t_tokn **list);
bool	handle_here_doc(t_shell *minishell, t_tokn *redirections);

void	execute_command(char **command, char **envp);
//void	execute_builtin(t_shell *minishell, char **command, char **envp);

t_exec	*create_execution_node(t_shell **minishell, t_tree *ast);

//create_process.c
int		execute_command_in_child(t_shell **minishell, t_exec *node, int index);
int		create_child_process(t_shell *minishell, t_exec **execution);

//wait_module.c
int		wait_module(t_shell *minishell, pid_t *pids, int count, int ret);

//handle_pipeline.c
t_exec	*build_command_node(t_shell **minishell, t_tokn *tokens, int *count);
int		execute_commands(t_shell **minishell, t_exec *execution, int count);
void	insert_heredoc_in_list(t_tokn **head, t_tokn **tail, t_tokn *current);
void	handle_assignations(t_shell **minishell, t_tokn **source);
bool	open_here_doc(t_shell *minishell, t_tokn **source);

//get_env.c
char	**get_env(t_shell *minishell);

//redirections.c
void	open_all_redirections(t_shell *minishell, t_exec *node);

//handle_standard_redirections.c
int		open_infile(t_tokn *redirections);
int		open_outfile(t_tokn *redirections);
int		open_outfile_append(t_tokn *redirections);

//handle_here_doc_helper.c
void	setup_heredoc_signals(void);
bool	rewind_heredoc(t_tokn *redirections);
char	*limiter_handler(char *limiter, bool *expansions);
bool	init_heredoc(t_tokn *redirections, bool *expansions, char **limiter, \
		int *len);

void	add_key_to_local(t_shell **minishell, t_tokn *assignations);

//inter_process_communications.c
int		stdin_management(t_exec *node, int pipefd[][2], int index);
int		stdout_management(t_exec *node, int pipefd[][2], int index);
int		my_dup(int source);
int		my_dup2(int oldfs, int newfd);
void	get_or_restore_stds(int fds[2], bool set);
void	redirections_in_parent(t_exec *node, int pipe[][2], int index);
int		setup_redirections_in_child(t_shell *minishell, t_exec *node, \
		int pipefd[][2], int index);

//modify_redirections_nodes.c
void	modify_redirections_nodes(t_tokn **source);

//execution_cleanup.c
void	close_command_redirs(t_exec *node);
void	close_pipes(int (*pipefd)[2], int count);
void	child_cleanup(t_shell **minishell, t_exec *node, int cmd);

//setup_redirections_for_builtins.c
void	setup_redirections_for_builtin(t_exec *node, bool set);

//execute_builtins.c
int		execute_simple_builtin(t_exec *current,	t_shell **minishell);
pid_t	execute_builtin(t_exec *current, int pipefd[][2], int index, \
		t_shell **minishell);

//redirections_helper.c
void	close_and_unlink(t_tokn **heredoc, int *fd, int newfd);
void	append_redirs_value(t_exec *node, int last_in, int last_out);
bool	check_validity_and_append_fd(t_tokn *redirections, int *last_in, \
		int *last_out, bool valid_command);

//quote_removal.c
bool	quote_removal(t_tokn *list);
void	quote_removal_helper(char *token, char *removed);

bool	parse_command_line(t_tokn **current, t_pars *parser);
bool	build_prompt(char **prompt, t_tree *branch);
bool	build_prompt_helper(char **prompt, t_tree *branch);

void	handle_sigint_in_here_doc(t_shell *minishell);
void	handle_sigquit_in_here_doc(t_shell *minishell, char *limiter);

#endif
