/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:32:39 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/15 15:38:49 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ./pipex file1 cmd1 cmd2 file2
* bash: < file1 cmd1 | cmd2 > file2
* The pipex program mimics the behavior of command from line 2
* The command firstly redirects stdin to file1's FD, cmd 1 reads from stdin, which became file1's FD
* then stdout is redirected to cmd2's stdin and then cmd2's stdout is redirected to file2's FD
*
* Observations.:
* 1 - I need to fork twice, once for each process and use execve on them to run each command.
* 2 - I need to always close both ends of every process' pipe 
* 3 - I should use the access function to see if I can access an FD or if it even exists
* 4 - Always check for errors on functions such as write, read, whatever
* 5 - Use the damn GC for the path
* 6 - I need to provide the full path of the executable to execve
*/

#include "pipex.h"

int	pipex_process(t_pipex *pipex)
{
	if (pipex->pid1 == 0)
	{
		if (dup2(pipex->file1, 0) == -1)
			return (-1);
		if (dup2(pipex->fd[1], 1) == -1)
			return (-1);
		if (pipex_kill(pipex) == -1)
			return (-1);
		if (execve(pipex->path[1], pipex->cmd1 + 1, pipex->env) == -1)
			return (-1);
	}
	else if (pipex->pid2 == 0)
	{
		if (dup2(pipex->fd[0], 0) == -1)
			return (-1);
		if (dup2(pipex->file2, 1) == -1)
			return (-1);
		if (pipex_kill(pipex) == -1)
			return (-1);
		if (execve(pipex->path[2], pipex->cmd2 + 1, pipex->env) == -1)
			return (-1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_gc 	*gc;
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
		if(!pipex)
			return (pipex_close(pipex, gc, 0, 3));
		if (pipex_process(pipex) == -1)
			return (pipex_close(pipex, gc, 0, 4));
	}
	if (pipex_close(pipex, gc, -1, 0) == 5)
		return (5);
	return (0);
}
