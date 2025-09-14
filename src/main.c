/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:32:39 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/13 21:30:30 by dasimoes         ###   ########.fr       */
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

int	pipex_cmd(t_pipex *pipex)
{
	pipex->file1 = open(pipex->p_file1, O_RDONLY);
	if (pipex->cmd1 == -1)
		return (-1);
	if (dup2(pipex->, 0) == -1)
		return (-1);

}

int	pipex_set(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		return (-1);
	if (pipex->pid1 == 0)
	{
		if (pipex_cmd(av, env, gc) == -1)
			return (-1);
	}
	else
	{
		pipex->pid2 = fork();
		if (pipex->pid2 == -1)
			return (-1);
		if (pipex->pid2 == 0)
		{
			if (pipex_cmd(av, env, gc) == -1)
				return (-1);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_gc 	*gc;
	t_pipex	*pipex;

	gc = gc_init();
	if (!gc)
		return (func_error(1, gc));
	if (ac != 5)
	{
		ft_putstr_fd("Pipex error: not enough arguments.\n", 2);
		gc_free_all(gc);
		return (2);
	}
	else
	{
		if (access(av[1], F_OK | R_OK))
			return (func_error(3, gc));
		pipex = pipex_start(av, env, gc);
		if(!pipex)
			return (func_error(4, gc));
		if (pipex_set(av, env, gc) == -1)
			return (func_error(5, gc));
	}
	return (0);
}
