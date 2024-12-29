/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:41:04 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/26 16:01:35 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct s_data
{
	char	**envp;
	pid_t	lastpid;
	char	**argv;
	char	*path_cmd;
	char	**arg_and_cmd;
	int		fd_f1;
	int		fd_f2;
	int		stdin_fd;
	int		stdout_fd;
	int		p_fd[2];
}	t_data;

char	*get_cmd_path(char *cmd_name, t_data *data);
void	put_file_in_pipe(char *filename, int *fdf1);
void	new_fork(int pfd[2], pid_t pid, int fdf1);
void	management_first(t_data data);
void	print_error_and_exit(t_data *data, int file);
void	run_cmd(t_data *data);
void	management_lsat(t_data *data);
void	write_pipe_in_file(int fd_f2, int p_fdwrite[2]);
void	free_tab(char **tab);

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif