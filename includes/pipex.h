/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:12:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/16 18:02:39 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// External include
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <stdlib.h>

// Local includes
# include "libft.h"

// Structs
typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		file1;
	int		file2;
	int		fd[2];
	char	*path[2];
	char	**cmd1;
	char	**cmd2;
	char	**env;
}	t_pipex;

//Prototypes
t_pipex	*pipex_start(char **av, char **env, t_gc *gc);
char	**get_env(char **env, t_gc *gc);
char	*get_path(char *s, char **env, t_gc *gc);
char	**get_cmd(char *s, t_gc *gc);
int		pipex_process(t_pipex *pipex);
int		pipex_kill(t_pipex *pipex);
int		pipex_close(t_pipex *pipex, t_gc *gc, int flag, int num);
int		pipex_fork(t_pipex *pipex);

#endif
