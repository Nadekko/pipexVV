/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:05:57 by andjenna          #+#    #+#             */
/*   Updated: 2024/03/13 12:36:04 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include "../libft/libft.h"

typedef struct s_pipe
{
	// char	**cmd;
	char **env;
	char **cmd_path;
	char **cmd;
	char ***cmd_tab;
	char **av;
	int ac;
	int infile;
	int outfile;
	int num_cmd;
	int *child;
	int **fds; // fd[0] = in, fd[1] = out, chaque processe a 2 pipes, chaque processe a 4 fd
	// read(fd[i][0]), write(fd[i][1])
} t_pipe;

/*			utils.c			*/
char **get_cmd(int ac, char **cmd_path, char ***cmd_tab);
char ***get_cmd_tab(char **av, int ac);
char **get_env_path(char **envp);
char *join_env_path(char **cmd_path, char *cmd_tab);

/*			init.c			*/
t_pipe clean_init(void);
t_pipe init_pipex(int ac, char **av, char **envp);

/*			hendle_free.c			*/
void free_tab(char **tab);
void free_tab_char(char ***tab);
void free_tab_int(int **tab);
void free_pipex(t_pipe *pipex);

#endif