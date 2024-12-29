/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrihamo <sbrihamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:21:47 by sbrihamo          #+#    #+#             */
/*   Updated: 2024/12/27 12:36:11 by sbrihamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin_three(char *s1_aloc, char *s2, char *s3)
{
	char	*res;
	char	*temp;

	res = ft_strjoin(s1_aloc, s2);
	if (res == NULL)
	{
		free(s1_aloc);
		return (NULL);
	}
	temp = res;
	res = ft_strjoin(res, s3);
	if (res == NULL)
	{
		free(s1_aloc);
		free(temp);
		return (NULL);
	}
	free(temp);
	free(s1_aloc);
	return (res);
}

char	**get_list_of_path(char *name_cmd, char *envp[])
{
	char	*path;
	char	**allpath;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			path = envp[i];
		i++;
	}
	i = -1;
	if (path == NULL)
		return (NULL);
	allpath = ft_split(path + 5, ':');
	if (allpath == NULL)
		return (NULL);
	while (allpath[++i])
	{
		allpath[i] = ft_strjoin_three(allpath[i], "/", name_cmd);
		if (allpath[i] == NULL)
			return (free_tab(allpath), NULL);
	}
	return (allpath);
}

void	free_tab(char **tab)
{
	int	index;

	index = 0;
	while (tab[index])
	{
		free(tab[index]);
		index++;
	}
	free(tab);
}

char	*get_cmd_path(char *cmd_name, t_data *data)
{
	char	**allpath;
	char	*res;
	int		i;

	if (cmd_name == NULL)
		return (NULL);
	if (access(cmd_name, F_OK | X_OK) == 0)
		return (ft_strdup(cmd_name));
	allpath = get_list_of_path(cmd_name, data->envp);
	if (allpath == NULL)
		return (NULL);
	i = 0;
	while (allpath[i])
	{
		if (access(allpath[i], F_OK | X_OK) == 0)
		{
			res = ft_strdup(allpath[i]);
			free_tab(allpath);
			return (res);
		}
		i++;
	}
	free_tab(allpath);
	return (NULL);
}
