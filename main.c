/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:55:01 by cmarteau          #+#    #+#             */
/*   Updated: 2021/11/16 18:08:10 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

void	run_pipe(t_arg *args)
{
	int			read_end;
	int			write_end;
	pid_t		child;
	int			pdes[2];

	read_end = 0;
	write_end = 1;
	pipe(pdes);
	child = fork();
	if (child == -1)
		ft_close_if_error(pdes);
	else if (child == 0)
	{
		dup2(pdes[write_end], STDOUT_FILENO);
		close(pdes[read_end]);
		execve(args->cmd1, args->arg1, NULL);
	}
	dup2(pdes[read_end], STDIN_FILENO);
	close(pdes[write_end]);
	wait(NULL);
	run_redir_stdout(args);
	return ;
}

void	ft_parsing_args(char **av, t_arg *args, char **envp)
{
	args->arg1 = ft_split(av[2], ' ');
	args->arg2 = ft_split(av[3], ' ');
	if (access(args->arg1[0], F_OK) == 0)
		args->cmd1 = ft_malloc_cpy(args, 1);
	else
		args->cmd1 = ft_find_path(envp, args, 1);
	if (access(args->arg2[0], F_OK) == 0)
		args->cmd2 = ft_malloc_cpy(args, 2);
	else
		args->cmd2 = ft_find_path(envp, args, 2);
	args->outfile = malloc(sizeof(char *) * (ft_strlen(av[4]) + 1));
	if (!args->outfile)
		return ;
	ft_strlcpy(args->outfile, av[4], ft_strlen(av[4]) + 1);
	if (open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644) == -1)
	{
		perror("error");
		ft_free_all(args);
		exit(1);
	}
	args->infile = malloc(sizeof(char *) * (ft_strlen(av[1]) + 1));
	if (!args->infile)
		return ;
	ft_strlcpy(args->infile, av[1], ft_strlen(av[1]) + 1);
}

char	*ft_find_path(char **envp, t_arg *args, int a)
{
	int		i;
	char	**t;
	char	*arg;
	char	*path;

	i = 0;
	if (a == 1)
		arg = args->arg1[0];
	else
		arg = args->arg2[0];
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	t = ft_split(envp[i], ':');
	path = ft_access_path(t, arg);
	ft_free_table(t);
	if (ft_strncmp(path, "hehe", 4) == 0)
	{
		write(1, "error: command not found\n", 25);
		ft_free_all(args);
		if (a == 1)
			exit(0);
		else
			exit(127);
	}
	return (path);
}

char	*ft_access_path(char **t, char *arg)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (t[i])
	{
		tmp = ft_strjoin(t[i], "/");
		path = ft_strjoin(tmp, arg);
		free(tmp);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	if (path)
		return (path);
	else
		return ("hehe");
}

int	main(int ac, char **av, char **envp)
{
	pid_t	child;
	t_arg	args;

	child = -1;
	args = (t_arg){};
	if (ac != 5)
	{
		write(1, "error: wrong number of arguments\n", 33);
		exit(0);
	}
	if (ft_strlen(av[2]) < 2 || ft_strlen(av[3]) < 2)
	{
		write(1, "error: command not found\n", 25);
		if (ft_strlen(av[3]) < 2)
			exit(127);
		exit(0);
	}
	ft_parsing_args(av, &args, envp);
	child = fork();
	if (child == -1)
		perror("error");
	else if (child == 0)
		run_redir_stdin(&args);
	wait(NULL);
	ft_free_all(&args);
}
