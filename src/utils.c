/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:43:13 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/13 21:25:28 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	func_error(int num, t_gc *gc)
{
	perror("Pipex error: ");
	gc_free_all(gc);
	return (num)
}

char	**get_path(char **env, t_gc *gc)
{
	char	*path;

	path = NULL;
	while (*env)
	{
		if (!ft_strncmp("PATH=", *env, 5))
			break;
		env++;
	}
	if (*env)
	{
		path = ft_split(env + 5, ':');
		if (!gc_addptr(path, gc, GC_DEFAULT))
			return (NULL);
	}
	return (path);
}

char	*set_path(char *s, char **env, t_gc *gc)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	path = NULL;
	if (ft_strchr(s, '/'))
		return (s);
	else
	{
		while (env[i])
		{
			tmp = ft_strjoin("/", s);
			path = ft_strjoin(env[i], tmp);
			if (!access(path, F_OK))
				break;
			i++;
		}
	}
	return (path);
}

t_pipex *pipex_start(char **av, char **env, t_gc *gc)
{
	t_pipex *pipex;

	pipex = gc_malloc(sizeof(t_pipex), gc, GC_DEFAULT);
	if (!pipex)
		return (NULL);
	pipex->pid1 = 0;
	pipex->pid2 = 0;
	pipex->cmd1 = 0;
	pipex->cmd2 = 0;
	pipex->file1 = 0;
	pipex->file2 = 0;
	if (pipe(pipex->fd) == -1)
			return (func_error(0));
	pipex->p_env = get_path(env, gc);
	if (!pipex->p_env || !*pipex->p_env)
		return (NULL);
	pipex->p_file1 = set_path(av[1], pipex->p_env, gc);
	pipex->p_cmd1 = set_path(av[1], pipex->p_env, gc);
	pipex->p_cmd2 = set_path(av[1], pipex->p_env, gc);
	pipex->p_file2 = set_path(av[1], pipex->p_env, gc);
	return (pipex);
}

