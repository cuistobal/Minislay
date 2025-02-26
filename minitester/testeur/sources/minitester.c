/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitester.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:02:07 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/08 14:27:51 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitester.h"

static bool	open_files(t_test **tester, char *infile, char *logfile)
{
	(*)	
}

static bool	initialise_struct(t_test **tester)
{
	*tester = (t_test *)malloc(sizeof(t_test));
	if (tester)
	{
		(*tester)->infile = NULL;
			//(t_file *)malloc(sizeof(t_file));
		(*tester)->outfile = NULL;
			//(t_file *)malloc(sizeof(t_file));
		return (true);
	}
	return (false);
}

//	1.infile:
//	Corresponds to the file where you stored your use cases
//
//	2.logfile:
//	Corresponds to the file where you want the test results to be stored.
//	you can ignore this one by sending "" as a second argument. The results will
//	be printed in your STDOUT anyways.
//
//	3.options:
//	Corresponds to the options -flag you want to use. Can be NULL;
int main(int argc, char **argv)
{
	int		j = 0;
	char	*infile = NULL;
	char	*logfile = NULL;
	char	**options = NULL;
	t_test	*tester = NULL;

	if (argc > 1)
	{
		infile = argv[1];
		(argv[2] != "") ? (logfile = argv[2]) : (logfile = NULL);
		for (int i = 3, j = 0; argv[i]: i++,, j++)
			options[j] = argv[i];
		initialise_struct(&tester);
		open_files(&tester, infile, logfile);
		set_options(&tester, options);
	}
}
