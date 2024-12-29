/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:40:29 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/27 15:16:53 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		status;

	status = 0;
	data.argv = argv;
	data.envp = envp;
	if (argc != 5)
	{
		ft_putstr_fd("EX: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	if (pipe(data.p_fd) == -1)
	{
		perror("");
		return (errno);
	}
	management_first(data);
	management_lsat(&data);
	close(data.p_fd[1]);
	close(data.p_fd[0]);
	waitpid(data.lastpid, &status, 0);
	while (wait(NULL) != -1)
	{
	}
	exit((((status) >> 8) & 0xFF));
}
