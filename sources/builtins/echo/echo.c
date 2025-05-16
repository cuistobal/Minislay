/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 09:56:42 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Echo built-in. Prints the argument followed by a new_line unless the flag is
//spefied.
void	echo(const char **arguments, bool flag)
{
	while (*arguments)
	{
		printf("%s", *arguments);
		if (!flag)
			printf("\n");
		arguments++;
	}
	printf("%s\n", "leon test");
}

/*leon*/
int builtin_echo(char **argv)
{
	int	i;
	bool	newline;
	int	j;

	i = 1;
	newline = true;
	// gérer tous les -n/-nnn
	while (argv[i] && strncmp(argv[i], "-n", 2) == 0) {
		j = 2;
		while (argv[i][j] == 'n') j++;
		if (argv[i][j] != '\0')
			break;
		newline = false;
		i++;
	}
	// afficher le reste
	while (argv[i]) {
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0); // succès = 0
}
