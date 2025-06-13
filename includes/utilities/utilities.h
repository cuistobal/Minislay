/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:23:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 12:24:31 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

//tokenizer_bools_1.c:
bool	is_amp_pipe(char c);
bool	is_whitespace(char c);
bool	is_var_wild(char c);
bool	is_redir(char c);
bool	is_quote(char c);

//tokenizer_bools_2.c:
bool	is_paren(char c);
bool	is_squotes(char c);
bool	is_dquotes(char c);
bool	is_iredir(char c);
bool	is_oredir(char c);

//state_management.c:
bool	set_state(int *state, int flag);
bool	unset_state(int *state, int flag);
bool	is_state_active(int state, int flag);

//my_strtok_r.c:
char	*my_strtok_r(char *str, const char *delim, char **saveptr);

//tokens_utils1.c:
void	free_tokens(t_tokn *tokens);
void	free_tokens_adress(t_tokn **tokens);

//parsing_utils.c:
void	delete_links(t_pars *parser);
bool	consume_token(t_tokn **current, t_pars *parser);
bool	valid_lexeme(t_tokn *current, int min, int max);

//parser_utils.c:
bool	append_token_tab(t_tokn *tab[], t_tokn *pointer, int token_type);
bool	reset_parser(t_pars *parser, t_tokn *token, int i, t_tree **branch);
t_pars	*define_parser(t_tree **ast, t_tokn *tokens);

//env_node.c
bool	insert_env_node(t_env **head, t_env **tail, t_env *new);

//ft_strjoin.c
char	*ft_strjoin(const char *s1, const char *s2);

//misc.c
bool	move_pointer(t_tokn **pointer);
bool	move_env_pointer(t_env **pointer);
bool	move_list_pointer(t_tokn **pointer, t_tokn **save);

//find_key.c
bool	find_key(t_shell *minishell, char **value, char *key);

//get_merged.c
char	*get_merged(char **merged, char **temp, char **expanded);

//mem_utils.c
void	*resize_array(void *array, int array_type, int *size);
void	reset_array(char **array, int start, int end);

//messages.c
bool	error_message(char *message);

//tests
void	free_tree(t_tree *ast);
void	free_minishell(t_shell *minishell);
void	free_array(char **array, int count);
void	free_execution_node(t_exec *execution);

//update_key_value.c
int		update_key_value(t_shell *minishell, char *key, char *new_value);
char	*ft_itoa(int num);

//inline_utilities.c
void	set_error_code(t_shell **minishell, int error_code);

//linked_lists_utils1.c
t_tokn	*copy_token(t_tokn *source);
t_tokn	*create_token_sub_list(t_tokn **list, int ttype);

//linked_lists_utils.c
void	remove_node(t_tokn **head, t_tokn **current, t_tokn **prev);
t_tokn	*duplicate_token_list(t_tokn *source);
t_tokn	*get_tail_node(t_tokn **list);
void	append_token_list(t_tokn **head, t_tokn **tail, t_tokn *new);
void	append_exec_list(t_exec **head, t_exec **tail, t_exec *new);

//bool	handle_here_doc(t_shell *minishell, t_tokn **redirections);

//environement_utils.c 
bool	is_standard_key(t_shell *minishell, char **value, char *key);

//linked_lists_utils2.c
t_env	*get_env_tail_node(t_env *list);
t_env	*get_env_node(t_shell *minishell, char *key);
t_env	*find_special_env_variable(t_shell *minishell, int index);
void	free_token_nodes(t_tokn *tokens);

//find_keys.c
bool	find_key_in_command(t_env *command, char **value, char *key);
bool	find_key_in_local(t_env *local, char **value, char *key);
bool	find_key(t_shell *minishell, char **value, char *key);
void	append_exit_code(t_shell *minishell, int code);
bool	find_key_in_env(t_env *command, char **value, char *key);
t_env	*sort_env_list(t_env *list);
void	free_env_list(t_env *list);
void	sort_token_list(t_tokn **list);

//free
void	free_array(char **array, int count);

bool	input_is_space(char *input);

#endif
