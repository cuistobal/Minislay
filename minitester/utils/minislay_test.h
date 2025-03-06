#ifndef MINISLAY_TEST_H
# define MINISLAY_TEST_H

//minislays_test_utils.c:
void	print_env(t_env *env);
void	print_tokens(t_tokn *current);
void	print_ast(t_tree *ast, char *origin, char *destination, int lvl);
void	print_ast_BFS(t_tree *ast);
void	print_ast_DFS(t_tree *ast, int lvl, char *c, char *s);
void	print_parser(t_pars *parser);

#endif
