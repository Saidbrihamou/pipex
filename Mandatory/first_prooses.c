/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_prooses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:19:07 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/27 12:40:24 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error_and_exit(t_data *data, int file)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(data->arg_and_cmd[0], 2);
	ft_putstr_fd("\n", 2);
	free_tab(data->arg_and_cmd);
	close(data->p_fd[0]);
	close(data->p_fd[1]);
	close(file);
	exit(127);
}

static void	open_file_is_existe(char *filename, t_data *data)
{
	if (0 != access(filename, R_OK))
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
		close(data->p_fd[1]);
		close(data->p_fd[0]);
		exit(1);
	}
	data->fd_f1 = open(filename, O_RDONLY);
	if (data->fd_f1 == -1)
	{
		close(data->p_fd[1]);
		close(data->p_fd[0]);
		exit(1);
	}
	data->stdin_fd = data->fd_f1;
}

void	free_argv_and_path(t_data *data)
{
	free_tab(data->arg_and_cmd);
	free(data->path_cmd);
}

void	run_cmd(t_data *data)
{
	if (dup2(data->stdin_fd, STDIN_FILENO) == -1)
	{
		free_argv_and_path(data);
		close(data->stdin_fd);
		close(data->stdout_fd);
		exit(errno);
	}
	if (dup2(data->stdout_fd, STDOUT_FILENO) == -1)
	{
		free_argv_and_path(data);
		close(STDIN_FILENO);
		close(data->stdin_fd);
		close(data->stdout_fd);
		exit(errno);
	}
	close(data->stdin_fd);
	close(data->stdout_fd);
	if (execve(data->path_cmd, data->arg_and_cmd, data->envp) == -1)
	{
		free_argv_and_path(data);
		close(data->stdin_fd);
		close(data->stdout_fd);
		exit(errno);
	}
}

void	management_first(t_data data)
{
	pid_t	p_idfirst;

	p_idfirst = fork();
	if (p_idfirst > 0)
		return ;
	else if (p_idfirst == -1)
		exit(1);
	open_file_is_existe(data.argv[1], &data);
	data.arg_and_cmd = ft_split(data.argv[2], ' ');
	if (data.arg_and_cmd == NULL)
	{
		close(data.p_fd[0]);
		close(data.p_fd[1]);
		close(data.fd_f1);
		exit(1);
	}
	data.path_cmd = get_cmd_path(data.arg_and_cmd[0], &data);
	if (data.path_cmd == NULL)
		print_error_and_exit(&data, data.fd_f1);
	data.stdout_fd = data.p_fd[1];
	close(data.p_fd[0]);
	run_cmd(&data);
	exit(0);
}
