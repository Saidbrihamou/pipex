/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:37:21 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/27 12:38:39 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file_is_existe_append(char *filename, t_data *data)
{
	int	fdf2;

	fdf2 = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (0 != access(filename, W_OK) || fdf2 == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
		close(data->p_fd[1][0]);
		close(data->p_fd[1][1]);
		exit(1);
	}
	return (fdf2);
}
