#ifndef EXECUTION_H
# define EXECUTION_H

//traverse_ast.c
void    traverse_ast(t_shel *minishell, t_tree *ast);

//subshells.c
bool    handle_subshell(t_shel *minishell, t_tree *ast);

#endif
