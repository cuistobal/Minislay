/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:17:31 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/08 14:20:18 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct file
{
	char	*filename;
	int		fd;
}	t_file;

typedef struct tester
{
	struct file	*infile;
	struct file	*outfile;
	int			options;
}	t_test;

#endif
