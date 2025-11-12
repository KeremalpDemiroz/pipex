/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:06:44 by kedemiro          #+#    #+#             */
/*   Updated: 2025/11/06 17:58:05 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	all_free(char **split)
{
	int	a;

	a = 0;
	if (!split)
		return ;
	while (split[a])
		free (split[a++]);
	free (split);
}

char	**path_and_cmd(t_list *data, int i, char *path)
{
	char	**combined_path;
	char	**splited_cmd;
	char	*joined;
	int		j;

	j = 0;
	splited_cmd = ft_split(data->av[i], ' ');
	combined_path = ft_split(path, ':');
	if (!combined_path || !splited_cmd[0])
	{
		ft_printf("%s: Command is not found\n", data->av[i]);
		all_free(splited_cmd);
		all_free(combined_path);
		return (NULL);
	}
	while (combined_path[j])
	{
		joined = ft_strjoin(combined_path[j], "/");
		free(combined_path[j]);
		combined_path[j] = ft_strjoin(joined, splited_cmd[0]);
		free(joined);
		j++;
	}
	all_free(splited_cmd);
	return (combined_path);
}

char	*choose_envp(t_list *data, const char *wanted)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (!data->envp)
		return (NULL);
	while (data->envp[i])
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (data->envp[i][j + k] && wanted[k]
					&& data->envp[i][j + k] == wanted[k])
				k++;
			if (!wanted[k])
				return (&(data->envp[i][5]));
			j++;
		}
		i++;
	}
	return (NULL);
}

void	pid_error(int pipe_fd[])
{
	perror("fork error");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	create_data(t_list *data, int ac, char **av, char **envp)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
	data->stdin_backup = dup(0);
	data->stdout_backup = dup(1);
	data->file_err = 0;
	data->cmd_err = 0;
	data->cmd_split = NULL;
	if (is_args_ok(data) == 0)
	{
		data->infile_fd = open(data->av[1], O_RDONLY);
		return (0);
	}
	else
		return (-1);
}
