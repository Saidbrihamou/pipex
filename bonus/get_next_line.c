/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:53:44 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/21 10:16:03 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_allocat(char **buffer)
{
	if (*buffer != NULL)
		return (1);
	if (BUFFER_SIZE > INT_MAX || BUFFER_SIZE <= 0)
		return (0);
	*buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return (0);
	buffer[0][0] = '\0';
	return (1);
}

int	my_free(char **p)
{
	free(*p);
	*p = NULL;
	return (1);
}

int	check_isnothing_and_free(char **buffer, char *temp, char **buff_static)
{
	return (my_free(buffer) && temp == NULL && buff_static[0][0] == '\0' \
												&& my_free(buff_static));
}

char	*get_next_line(int fd)
{
	static char		*buff_static = NULL;
	static size_t	num_line_read = 0;
	ssize_t			num_read;
	char			*buffer;
	char			*temp;

	temp = NULL;
	num_read = 0;
	buffer = NULL;
	if (!ft_allocat(&buff_static) || !ft_allocat(&buffer))
		return (NULL);
	while (1)
	{
		if (num_line_read > 0 && read(fd, NULL, 0) == 0)
			break ;
		num_read = read(fd, buffer, BUFFER_SIZE);
		if (num_read == 0 || num_read == -1)
			break ;
		temp = ft_strjoin_and_free(buffer, num_read, temp, &num_line_read);
		if (temp == NULL && my_free(&buffer))
			return (NULL);
	}
	if (check_isnothing_and_free(&buffer, temp, &buff_static))
		return (NULL);
	return (create_result(temp, &buff_static, &num_line_read, num_read));
}
