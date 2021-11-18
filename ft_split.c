/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <cmarteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:47:58 by cmarteau          #+#    #+#             */
/*   Updated: 2021/09/09 02:28:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_sep(char c, char b)
{
	if (c == b)
		return (1);
	return (0);
}

int	count_w(const char *str, char c)
{
	int	i;
	int	onoff;
	int	count;

	count = 0;
	onoff = 1;
	i = 0;
	while (str[i])
	{
		if (is_sep(str[i], c) == 1)
			onoff = 1;
		else
		{
			if (onoff == 1)
				count++;
			onoff = 0;
		}
		i++;
	}
	return (count);
}

int	word_size(const char *str, int i, char c)
{
	int	k;

	k = 0;
	while (is_sep(str[i], c) == 0 && str[i])
	{
		i++;
		k++;
	}
	return (k);
}

char	*fill_tab(const char *str, int i, int size)
{
	int		k;
	char	*tab;

	k = 0;
	tab = malloc(sizeof(char) * size + 1);
	if (tab == NULL)
		return (NULL);
	while (size > k)
		tab[k++] = str[i++];
	tab[k] = '\0';
	return (tab);
}

char	**ft_split(const char *str, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * (count_w(str, c) + 2));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		if (is_sep(str[i], c) == 1)
			i++;
		else
		{
			tab[j++] = fill_tab(str, i, word_size(str, i, c));
			i += word_size(str, i, c);
		}
	}
	tab[j] = NULL;
	return (tab);
}
