/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:32:39 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/17 19:08:16 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_process(t_pipex *pipex)
{
	if (pipex->pid1 == 0)
	{
		if (pipex->path[0] == NULL || pipex->file1 == -1)
			arg_error(pipex);
		if (dup2(pipex->file1, 0) == -1)
			return (-1);
		if (dup2(pipex->fd[1], 1) == -1)
			return (-1);
		if (pipex_kill(pipex) == -1)
			return (-1);
		execve(pipex->path[0], pipex->cmd1, pipex->env);
	}
	else if (pipex->pid2 == 0)
	{
		if (pipex->path[1] == NULL || pipex->file2 == -1)
			arg_error(pipex);
		if (dup2(pipex->fd[0], 0) == -1)
			return (-1);
		if (dup2(pipex->file2, 1) == -1)
			return (-1);
		if (pipex_kill(pipex) == -1)
			return (-1);
		execve(pipex->path[1], pipex->cmd2, pipex->env);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_gc	*gc;
	t_pipex	*pipex;

	pipex = NULL;
	gc = gc_init();
	if (!gc)
		return (pipex_close(pipex, gc, 0, 1));
	if (ac != 5)
		return (pipex_close(pipex, gc, 1, 2));
	else
	{
		pipex = pipex_start(av, env, gc);
		if (!pipex)
			return (pipex_close(pipex, gc, 0, 3));
		if (pipex_process(pipex) == -1)
			return (pipex_close(pipex, gc, 0, 4));
	}
	if (waitpid(pipex->pid1, 0, 0) == -1)
		return (pipex_close(pipex, gc, 0, 5));
	if (waitpid(pipex->pid2, 0, 0) == -1)
		return (pipex_close(pipex, gc, 0, 6));
	if (pipex_close(pipex, gc, -1, 0) == 7)
		return (7);
	return (0);
}
