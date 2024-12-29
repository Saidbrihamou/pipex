/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:40:29 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/27 15:27:07 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_status(t_data *data)
{
	int		status;

	status = 0;
	waitpid(data->lastpid, &status, 0);
	while (wait(NULL) != -1)
	{
	}
	exit((((status) >> 8) & 0xFF));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc < 5)
	{
		ft_putstr_fd("EX: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2", 2);
		exit(1);
	}
	data.argv = argv;
	data.envp = envp;
	data.argc = argc;
	if (ft_strncmp("here_doc", argv[1], 9) != 0)
		multiple_pipes(&data);
	else
	{
		if (argc != 6)
		{
			ft_putstr_fd("EX: ./pipex here_doc LIMITER cmd cmd1 file", 2);
			exit(1);
		}
		here_document(&data);
	}
	exit_status(&data);
}
