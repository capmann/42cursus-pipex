/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:54:31 by cmarteau          #+#    #+#             */
/*   Updated: 2021/11/16 18:01:16 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_redir_stdout(t_arg *args)
{
	int		fd;
	pid_t	child;

	child = -1;
	fd = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	child = fork();
	if (child == -1)
	{
		close(fd);
		perror("error");
	}
	else if (child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(args->cmd2, args->arg2, NULL);
		perror("error");
	}
	close(fd);
	wait(NULL);
}

void	run_redir_stdin(t_arg *args)
{
	int		fd;
	pid_t	child;

	child = -1;
	fd = open(args->infile, O_RDONLY);
	if (fd == -1)
	{
		perror("error");
		ft_free_all(args);
		exit(1);
	}
	child = fork();
	if (child == -1)
	{
		close(fd);
		perror("error");
	}
	else if (child == 0)
	{
		dup2(fd, STDIN_FILENO);
		run_pipe(args);
	}
	close(fd);
	wait(NULL);
}

char	*ft_malloc_cpy(t_arg *args, int a)
{
	char	*cmd;
	char	*arg;

	if (a == 1)
		arg = args->arg1[0];
	else
		arg = args->arg2[0];
	cmd = malloc(sizeof(char *) * (ft_strlen(arg) + 1));
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, arg, ft_strlen(arg) + 1);
	return (cmd);
}
