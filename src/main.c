/* ./pipex file1 cmd1 cmd2 file2
* bash: < file1 cmd1 | cmd2 > file2
* The pipex program mimics the behavior of command from line 2
* The command firstly redirects stdin to file1's FD, cmd 1 reads from stdin, which became file1's FD
* then stdout is redirected to cmd2's stdin and then cmd2's stdout is redirected to file2's FD
*
* Observations.:
* 1 - I need to fork twice for each process and use execve on them to run each command.
* 2 - I need to always close both ends of every process' pipe 
* 3 - I should use the access function to see if I can access an FD or if it even exists
* 4 - Always check for errors on functions such as write, read, whatever
* 5 - No reason to malloc anything nor use my GC
* 6 - I need to provide the full path of the executable to execve
*/

#include "pipex.h"

int	func_error(int num)
{
	perror("Pipex error: ");
	return (num)
}

char	*get_path(char **env)
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
		path = ft_strdup(*env);
	return (path);
}

int	main(int ac, char **av, char **env)
{
	int	cmd1;
	int	cmd2;
	int fd[2];
	int	file1;
	char *path;

	path = get_path(env);

	if (ac != 5)
	{
		ft_putstr_fd("Pipex error: not enough arguments.\n", 2);
		return (1);
	}
	else
	{
		cmd1 = fork();
		if (cmd1 == 0)
		{
			file1 = av[1];
			if (open(file1, O_RDONLY) == -1)
				return (func_error(3));
			if (dup2(file1, 0) == -1)
				return (func_error(4));
			if (pipe(fd) == -1)
				return (func_error(2));
			// run execve?
		}
		else
		{

		}
	}
	return (0);
}
