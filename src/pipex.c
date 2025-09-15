#include "pipex.h"

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
	pipex->file1 = 0;
	pipex->file2 = 0;
	if (pipe(pipex->fd) == -1)
			return (func_error(0));
	pipex->env = get_env(env, gc);
	if (!pipex->env || !*pipex->env)
		return (NULL);
	pipex->cmd1 = get_cmd(av[2], gc);
	pipex->cmd2 = get_cmd(av[3], gc);
	pipex->paths[0] = get_path(av[1], pipex->env, gc);
	pipex->paths[1] = get_path(pipex->cmd1[0], pipex->env, gc);
	pipex->paths[2] = get_path(pipex->cmd2[0], pipex->env, gc);
	pipex->paths[3] = get_path(av[4], pipex->env, gc);
	if (pipex_fork(pipex) == -1)
		return (NULL);
	return (pipex);
}
