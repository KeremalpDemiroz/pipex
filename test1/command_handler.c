/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:06:33 by kedemiro          #+#    #+#             */
/*   Updated: 2025/11/06 21:50:36 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_table(t_list *data, int old_pipe_in, int pipe_fd[], int i)
{
	if (i == 2)
	{
		dup2(data->infile_fd, 0);
		dup2(pipe_fd[1], 1);
		close(data->infile_fd);
	}
	else if (i == data->ac -2)
	{
		dup2(old_pipe_in, 0);
		dup2(data->outfile_fd, 1);
		close(data->outfile_fd);
	}
	else
	{
		dup2(old_pipe_in, 0);
		dup2(pipe_fd[1], 1);
	}
	if (old_pipe_in > -1)
		close(old_pipe_in);
	close(pipe_fd[1]);
}

int	execute_command(t_list *data, int i)
{
	data->cmd_split = ft_split(data->av[i], ' ');
	if (!data->cmd_split)
	{
		all_free(data->commands);
		exit (EXIT_FAILURE);
	}
	// write(data->stdout_backup, "split:\n", 7);
	// ft_putendl_fd(data->cmd_split[0], data->stdout_backup);
	// write(data->stdout_backup, "=====\n", 6);
	// ft_putendl_fd(data->commands[i], data->stdout_backup);
	execve(data->commands[i-2], data->cmd_split, data->envp);
	if (i == data->ac - 2)
	{
		perror("execve failure");
		all_free(data->cmd_split);
		all_free(data->commands);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_FAILURE);
}

/*
	a.out infile cmd cmd outfile
	cmd cmd NULL;

*/

void	child_process(t_list *data, int i, int old_pipe_in, int pipe_fd[])
{
	fd_table(data, old_pipe_in, pipe_fd, i);
	execute_command(data, i);
	all_free(data->cmd_split);
}

void	mother_process(t_list *data, int i)
{
	int		pipe_fd[2];
	int		old_pipe_in;
	pid_t	pid;

	i = 2;
	old_pipe_in = -1;
	while (i <= (data->ac) - 2)
	{

		if (pipe(pipe_fd) == -1)
			return (perror ("pipe error"));
		pid = fork();
		if (pid == -1)
			return (pid_error(pipe_fd));
		if (pid == 0)
			child_process(data, i, old_pipe_in, pipe_fd);
		close(pipe_fd[1]);
		old_pipe_in = pipe_fd[0];
		i++;
	}
	while (--i >= 2)
		wait(NULL);
	close(pipe_fd[0]);
}
