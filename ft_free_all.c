/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:54:13 by cmarteau          #+#    #+#             */
/*   Updated: 2021/11/15 15:54:16 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_table(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	ft_free_all(t_arg *args)
{
	if (args->cmd1)
		free(args->cmd1);
	if (args->cmd2)
		free(args->cmd2);
	if (args->arg1)
		ft_free_table(args->arg1);
	if (args->arg2)
		ft_free_table(args->arg2);
	if (args->outfile)
		free(args->outfile);
	if (args->infile)
		free(args->infile);
}

void	ft_close_if_error(int *pdes)
{
	close(pdes[0]);
	close(pdes[1]);
	perror("error");
}
