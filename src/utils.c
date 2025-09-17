/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:43:13 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/17 00:09:44 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		cmd_error(void)
{
	ft_putstr_fd("Pipex error: command not found\n", 2);
	return (-1);
}

char	**get_env(char **env, t_gc *gc)
{
	char	**path;

	path = NULL;
	while (*env)
	{
		if (!ft_strncmp("PATH=", *env, 5))
			break ;
		env++;
	}
	if (*env)
	{
		path = ft_split(*env + 5, ':');
		if (!gc_addmtx(path, gc, GC_DEFAULT))
			return (NULL);
	}
	return (path);
}

char	*get_path(char *s, char **env, t_gc *gc)
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
			free(tmp);
			if (!gc_addptr(path, gc, GC_DEFAULT))
				return (NULL);
			if (!access(path, F_OK))
				break ;
			path = NULL;
			i++;
		}
	}
	return (path);
}

char	**get_cmd(char *s, t_gc *gc)
{
	char	**split;
	char	*add;

	split = ft_split(s, ' ');
	add = gc_addmtx(split, gc, GC_DEFAULT);
	if (!add)
		return (NULL);
	return (split);
}
