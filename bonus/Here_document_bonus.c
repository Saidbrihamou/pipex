/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Here_document_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:13:45 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/27 12:37:37 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	put_in_buffer(t_data *data)
{
	int		pid;

	pid = fork();
	if (pid > 0)
		return ;
	close(data->p_fd[0][0]);
	if (data->buffer == NULL)
	{
		close(data->p_fd[0][1]);
		exit(0);
	}
	write(data->p_fd[0][1], data->buffer, ft_strlen(data->buffer));
	close(data->p_fd[0][1]);
	free(data->buffer);
	exit(0);
}

void	free_and_exit(t_data *data, char *temp_cmp)
{
	close(data->p_fd[0][0]);
	close(data->p_fd[0][1]);
	free(data->buffer);
	free(temp_cmp);
	exit(1);
}

void	read_doc_and_put_in_buffer(t_data *data)
{
	char	*line;
	char	*temp;
	char	*temp_cmp;

	data->buffer = NULL;
	temp_cmp = ft_strjoin(data->argv[2], "\n");
	if (temp_cmp == NULL)
		free_and_exit(data, temp_cmp);
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (line == NULL)
			free_and_exit(data, temp_cmp);
		if (ft_strncmp(line, temp_cmp, ft_strlen(data->argv[2]) + 2) == 0)
			break ;
		temp = data->buffer;
		data->buffer = ft_strjoin(data->buffer, line);
		free(temp);
		free(line);
		if (data->buffer == NULL)
			free_and_exit(data, temp_cmp);
	}
	free(line);
	free(temp_cmp);
}

void	management_lsat_doc(t_data *data)
{
	pid_t	p_idlast;

	p_idlast = fork();
	data->lastpid = p_idlast;
	if (p_idlast > 0)
		return ;
	else if (p_idlast == -1)
		exit(1);
	data->fd_f2 = open_file_is_existe_append(data->argv[5], data);
	data->arg_and_cmd = ft_split(data->argv[4], ' ');
	if (data->arg_and_cmd == NULL)
	{
		close(data->p_fd[1][1]);
		close(data->p_fd[1][0]);
		close(data->fd_f2);
		exit(1);
	}
	data->path_cmd = get_cmd_path(data->arg_and_cmd[0], data);
	if (data->path_cmd == NULL)
		print_error_and_exit(data, data->fd_f2);
	data->stdout_fd = data->fd_f2;
	data->stdin_fd = data->p_fd[1][0];
	close(data->p_fd[1][1]);
	run_cmd_multiple(data);
	exit(0);
}

void	here_document(t_data *data)
{
	if (pipe(data->p_fd[0]) == -1)
		exit(1);
	read_doc_and_put_in_buffer(data);
	put_in_buffer(data);
	free(data->buffer);
	if (pipe(data->p_fd[1]) == -1)
		exit(1);
	management_multiple(*data, 3);
	close(data->p_fd[0][1]);
	close(data->p_fd[0][0]);
	management_lsat_doc(data);
	close(data->p_fd[1][1]);
	close(data->p_fd[1][0]);
}
