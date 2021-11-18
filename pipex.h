/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:53:15 by cmarteau          #+#    #+#             */
/*   Updated: 2021/11/15 15:53:19 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_arg
{
	char	*cmd1;
	char	*cmd2;
	char	**arg1;
	char	**arg2;
	char	*infile;
	char	*outfile;
}				t_arg;

void		ft_parsing_args(char **av, t_arg *args, char **envp);
void		run_pipe(t_arg *args);
void		ft_free_all(t_arg *args);
void		ft_free_table(char **str);
void		run_redir_stdout(t_arg *args);
void		run_redir_stdin(t_arg *args);
void		ft_close_if_error(int *pdes);

char		**ft_split(const char *str, char c);

char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_find_path(char **envp, t_arg *args, int a);
char		*ft_access_path(char **t, char *arg);
char		*fill_tab(const char *str, int i, int size);
char		*ft_malloc_cpy(t_arg *args, int a);

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			is_sep(char c, char b);
int			count_w(const char *str, char c);
int			word_size(const char *str, int i, char c);

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);

#endif
