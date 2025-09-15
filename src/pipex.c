/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:25:04 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/15 15:40:26 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_kill(t_pipex *pipex)
{
	if (close(pipex->file1) == -1)
		return (-1);
	if (close(pipex->file2) == -1)
		return (-1);
	if (close(pipex->fd[0]) == -1)
		return (-1);
	if (close(pipex->fd[1]) == -1)
		return (-1);
	return (0);
}

int	pipex_close(t_pipex *pipex, t_gc *gc, int flag, int num)
{
	if (flag == 0)
		perror("Pipex error: ");
	else if (flag == 1)
		ft_putstr_fd("Pipex error: not enough arguments.\n", 2);
	if (pipex != NULL)
	{
		if (pipex_kill(pipex) == -1)
		{
			perror("Pipex error: ");
			gc_free_all(gc);
			return (5);
		}
	}
	gc_free_all(gc);
	return (num);
}

int	pipex_fork(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		return (-1);
	if (pipex->pid1 != 0)
	{
		pipex->pid2 = fork();
		if (pipex->pid2 == -1)
			return (-1);
	}
	return (0);
}

t_pipex *pipex_start(char **av, char **env, t_gc *gc)
{
	t_pipex *pipex;

	pipex = gc_malloc(sizeof(t_pipex), gc, GC_DEFAULT);
	if (!pipex)
		return (NULL);
	if (pipe(pipex->fd) == -1)
			return (NULL);
	pipex->env = get_env(env, gc);
	if (!pipex->env || !*pipex->env)
		return (NULL);
	pipex->cmd1 = get_cmd(av[2], gc);
	pipex->cmd2 = get_cmd(av[3], gc);
	pipex->path[0] = get_path(av[1], pipex->env, gc);
	pipex->path[1] = get_path(pipex->cmd1[0], pipex->env, gc);
	pipex->path[2] = get_path(pipex->cmd2[0], pipex->env, gc);
	pipex->path[3] = get_path(av[4], pipex->env, gc);
	pipex->file1 = open(pipex->path[0], O_RDONLY);
	pipex->file2 = open(pipex->path[3], O_CREAT | O_TRUNC | O_WRONLY);
	if (pipex->file1 == -1 || pipex->file2 == -1)
		return (NULL);
	if (pipex_fork(pipex) == -1)
		return (NULL);
	return (pipex);
}
