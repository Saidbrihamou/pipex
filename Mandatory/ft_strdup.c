/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:25:06 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/18 21:17:59 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	size_s1;

	size_s1 = (ft_strlen(s1) + 1);
	str = (char *)malloc(sizeof(char) * size_s1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, size_s1);
	return (str);
}
