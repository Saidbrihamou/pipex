/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_prooses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:06:31 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/26 16:01:52 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_file_is_existe(char *filename, t_data *data)
{
	int	fdf2;

	fdf2 = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (0 != access(filename, W_OK) || fdf2 == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
		close(data->p_fd[0]);
		close(data->p_fd[1]);
		exit(1);
	}
	return (fdf2);
}

void	management_lsat(t_data *data)
{
	pid_t	p_idlast;

	p_idlast = fork();
	data->lastpid = p_idlast;
	if (p_idlast > 0)
		return ;
	else if (p_idlast == -1)
		exit(1);
	data->fd_f2 = open_file_is_existe(data->argv[4], data);
	data->arg_and_cmd = ft_split(data->argv[3], ' ');
	if (data->arg_and_cmd == NULL)
	{
		close(data->p_fd[0]);
		close(data->p_fd[1]);
		close(data->fd_f2);
		exit(1);
	}
	data->path_cmd = get_cmd_path(data->arg_and_cmd[0], data);
	if (data->path_cmd == NULL)
		print_error_and_exit(data, data->fd_f2);
	close(data->p_fd[1]);
	data->stdout_fd = data->fd_f2;
	data->stdin_fd = data->p_fd[0];
	run_cmd(data);
	exit(0);
}
