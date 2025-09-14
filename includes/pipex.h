/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:12:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/13 21:26:03 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
#define SETUP_H

// External include
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <stdlib.h>

// Local includes
# include "libft.h"

// Structs
typedef struct s_pipex
{
	int		pid1;
	int		pid2;
	int		cmd1;
	int 	cmd2;
	int 	file1;
	int 	file2;
	int 	fd[2];
	char	*p_cmd1;
	char	*p_cmd2;
	char	*p_file1;
	char	*p_file2;
	char	**p_env;
}	t_pipex;	
	
// Macros


//Prototypes


#endif
