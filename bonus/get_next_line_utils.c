/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:53:42 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/21 10:16:15 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin_and_free(const char *buffer, ssize_t	len_buffer, \
										char *temp, size_t *num_line_read)
{
	size_t	len_temp;
	char	*result;
	ssize_t	i;

	i = 0;
	len_temp = 0;
	while (temp != NULL && temp[len_temp])
		len_temp++;
	while (i < len_buffer)
	{
		if (buffer[i++] == '\n')
			(*num_line_read)++;
	}
	result = malloc(sizeof(char) * (len_temp + len_buffer + 1));
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	ft_cat(result, temp, len_temp);
	ft_cat(result, buffer, len_buffer);
	free(temp);
	return (result);
}

char	*create_result(char *temp, char **buff_static, size_t *line_read, \
														ssize_t num_read)
{
	size_t	size_temp;
	size_t	index;
	char	*result;

	if (num_read == -1)
	{
		my_free(buff_static);
		return (NULL);
	}
	index = 0;
	if (temp != NULL)
		while (temp[index] && temp[index] != '\n')
			index++;
	size_temp = index + 1;
	index = 0;
	while (buff_static[0][index] && buff_static[0][index] != '\n')
		index++;
	result = malloc(sizeof(char) * (size_temp + index + 2));
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	ft_cat(result, buff_static[0], index + 1);
	ft_cat(result, temp, size_temp);
	ft_update_rest_and_temp(temp, buff_static[0], line_read);
	return (result);
}

void	ft_update_rest_and_temp(char *temp, char *buff_static, \
												size_t *num_line_read)
{
	size_t	index;
	size_t	i_rest;

	index = 0;
	i_rest = 0;
	if (temp != NULL)
	{
		while (temp[index] && temp[index] != '\n')
			index++;
		while (temp[index] && temp[index + 1])
			buff_static[i_rest++] = temp[index++ + 1];
		buff_static[i_rest] = '\0';
	}
	else
	{
		while (buff_static[index] && buff_static[index] != '\n')
			index++;
		while (buff_static[index] && buff_static[index + 1])
			buff_static[i_rest++] = buff_static[index++ + 1];
		buff_static[i_rest] = '\0';
	}
	(*num_line_read) = count_newline(buff_static);
	free(temp);
}

size_t	count_newline(const char *str)
{
	size_t	num_newline;
	size_t	i;

	num_newline = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			num_newline++;
		i++;
	}
	return (num_newline);
}

void	ft_cat(char *dst, const char *src, size_t len_src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!dst || !src)
		return ;
	while (dst[i])
		i++;
	while (j < len_src)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}
