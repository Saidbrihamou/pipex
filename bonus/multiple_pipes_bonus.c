/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:53:01 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/27 12:39:47 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		close(data->p_fd[1][0]);
		close(data->p_fd[1][1]);
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
	data->fd_f2 = open_file_is_existe(data->argv[data->argc - 1], data);
	data->arg_and_cmd = ft_split(data->argv[data->argc - 2], ' ');
	if (data->arg_and_cmd == NULL)
	{
		close(data->p_fd[1][0]);
		close(data->p_fd[1][1]);
		close(data->fd_f2);
		exit(1);
	}
	data->path_cmd = get_cmd_path(data->arg_and_cmd[0], data);
	if (data->path_cmd == NULL)
		print_error_and_exit(data, data->fd_f2);
	data->stdout_fd = data->fd_f2;
	data->stdin_fd = data->p_fd[1][0];
	run_cmd_multiple(data);
	exit(0);
}

void	close_pipe_and_exit(t_data *data)
{
	close(data->p_fd[1][0]);
	close(data->p_fd[1][1]);
	exit(1);
}

void	multiple_pipes(t_data *data)
{
	int		temp_fd[2];
	int		i;

	i = 3;
	if (pipe(data->p_fd[1]) == -1)
		exit(1);
	management_first(*data);
	while (data->argc - 2 > i)
	{
		if (pipe(temp_fd) == -1)
			close_pipe_and_exit(data);
		data->p_fd[0][0] = data->p_fd[1][0];
		data->p_fd[0][1] = data->p_fd[1][1];
		data->p_fd[1][0] = temp_fd[0];
		data->p_fd[1][1] = temp_fd[1];
		management_multiple(*data, i);
		close(data->p_fd[0][1]);
		close(data->p_fd[0][0]);
		i++;
	}
	close(data->p_fd[1][1]);
	management_lsat(data);
	close(data->p_fd[1][0]);
}
