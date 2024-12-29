/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:24:04 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/20 17:04:05 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static size_t	countline(char const *s, char c, \
					size_t *setzero1, size_t *setzero2)
{
	size_t	count;
	size_t	i;
	int		isinline;

	i = 0;
	*setzero1 = 0;
	*setzero2 = 0;
	count = 0;
	isinline = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!isinline)
			{
				count++;
				isinline = 1;
			}
		}
		else
			isinline = 0;
		i++;
	}
	return (count);
}

static size_t	countsize_charinline(char const *s, char c, size_t	*lastindex)
{
	size_t	size;

	size = 0;
	while (s[*lastindex] && s[*lastindex] != c)
	{
		size++;
		(*lastindex)++;
	}
	return (size);
}

static char	*strdup_and_skip(char const *s, char c, size_t	*lastindex)
{
	size_t	size;
	char	*str;

	while (s[*lastindex] && s[*lastindex] == c)
	{
		(*lastindex)++;
	}
	size = countsize_charinline(s, c, lastindex) + 1;
	str = (char *)malloc(size * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s + (*lastindex - size + 1), size - 1);
	str[size - 1] = '\0';
	return (str);
}

static void	freeifdone(char **add, int index)
{
	while (index >= 0)
	{
		free(add[index]);
		index--;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	lastindex;
	size_t	sizeline;
	size_t	i;
	char	**res;

	if (!s)
		return (NULL);
	sizeline = countline(s, c, &i, &lastindex) + 1;
	res = (char **)malloc(sizeline * sizeof(char *));
	if (!res)
		return (NULL);
	while (sizeline - 1 > i)
	{
		res[i] = strdup_and_skip(s, c, &lastindex);
		if (res[i] == NULL)
		{
			freeifdone(res, i);
			free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
