/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 05:49:57 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

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
