/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_prooses_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:06:31 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/27 11:21:50 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_error_and_free_pipe(t_data *data)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(data->arg_and_cmd[0], 2);
	ft_putstr_fd("\n", 2);
	free_tab(data->arg_and_cmd);
	close(data->p_fd[1][1]);
	close(data->p_fd[1][0]);
	close(data->p_fd[0][1]);
	close(data->p_fd[0][0]);
	exit(127);
}

void	free_argv_and_path(t_data *data)
{
	free_tab(data->arg_and_cmd);
	free(data->path_cmd);
}

void	run_cmd_multiple(t_data *data)
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

void	management_multiple(t_data data, int argv_i)
{
	pid_t	p_idlast;

	p_idlast = fork();
	if (p_idlast > 0)
		return ;
	else if (p_idlast == -1)
		exit(1);
	data.arg_and_cmd = ft_split(data.argv[argv_i], ' ');
	if (data.arg_and_cmd == NULL)
	{
		close(data.p_fd[1][0]);
		close(data.p_fd[1][1]);
		close(data.p_fd[0][1]);
		close(data.p_fd[0][0]);
		exit(1);
	}
	data.path_cmd = get_cmd_path(data.arg_and_cmd[0], &data);
	if (data.path_cmd == NULL)
		print_error_and_free_pipe(&data);
	close(data.p_fd[0][1]);
	close(data.p_fd[1][0]);
	data.stdin_fd = data.p_fd[0][0];
	data.stdout_fd = data.p_fd[1][1];
	run_cmd_multiple(&data);
	exit(0);
}
