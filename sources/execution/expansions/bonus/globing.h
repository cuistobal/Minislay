#ifndef GLOBING_H
# define GLOBING_H

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void	free_array(char **array, int count);

bool	match_pattern(char **patterns, char *current);

char	**identify_globing_patterns(const char *globing, int *pindex);

char	**globing(const char *globing, const char *path, int *count);

int		main(int argc, char **argv);

#endif
