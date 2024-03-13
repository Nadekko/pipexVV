/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:06:55 by andjenna          #+#    #+#             */
/*   Updated: 2024/03/13 15:28:50 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

char **get_env_path(char **envp)
{
	int i;
	char **path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

char *get_cmd_path(char *cmd, char **envp)
{
	int i;
	char *path;
	char *tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_strjoin(envp[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

int exec_cmd(int ac, char **av, char **envp)
{
	char	**cmd;
	char	**env;
	char	*path;
	int i;

	i = 2;
	env = get_env_path(envp);
	while (i < ac - 1)
	{
		cmd = ft_split(av[i], ' ');
		path = get_cmd_path(cmd[0], env);
		if (!path)
			printf("Command not found: %s\n", cmd[0]);
		else
		{
			printf("Command found: %s\n", cmd[0]);
			execve(path, cmd, envp);
			free(path);
		}
		free(cmd);
		i++;
	}
	return (0);
}
int	child_process(int pipefd[2], int ac, char **av, char **envp)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exec_cmd(ac, av, envp);
	return (0);
}

int pipex(int ac, char **av, char **envp)
{
	int infile;
	int outfile;
	int pipefd[2];
	pid_t pid;

	infile = open(av[1], O_RDONLY);
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
	{
		perror("Error");
		return (1);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	pipe(pipefd);
	if (pipefd < 0)
	{
		perror("Error");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		return (1);
	}
	if (pid == 0)
		child_process(pipefd, ac, av, envp);
	else
		printf("Parent process\n");
	return (0);
}

int main(int ac, char **av, char **envp)
{
	if (!envp || !*envp)
		return (0);
	if (ac > 4)
	{
		// if (ft_strncmp(av[1], "here_doc", 9) == 0)
		// 	// here_doc(av, envp);
		// else
		pipex(ac, av, envp);
	}
	return (0);
}