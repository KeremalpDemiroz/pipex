#include "pipex.h"

int	fd_to_data(t_list *data)
{
	int	err;

	err = 0;
	data->infile_fd = open((data->av)[1], O_WRONLY);
	if (data->infile_fd == -1)
	{
		perror((data->av)[1]);
		err++;
	}
	data->outfile_fd = open((data->av)[(data->ac) -1], O_RDONLY);
	if (data->outfile_fd == -1)
	{
		perror((data->av)[(data->ac) -1]);
		err++;
	}
	data->stdin_backup = dup(0);
	data->stdout_backup = dup(1);
	if (data->stdin_backup == -1 || data->stdout_backup == -1)
	{
		ft_printf("error about file descriptors\n");
		err++;
	}
	return (err);
}

char	**join_path_and_cmd(char *envp, char *av)
{
	char	*join;
	char	**paths;
	int		i;

	i = 0;
	while (*envp != '/')
		envp++;
	paths = ft_split(envp, ':');
	while (paths[i])
	{
		join = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(join, av);
		free(join);
		i++;
	}
	return (paths);
}
char	**path_finder(char **envp, char *path, char *cmd)
{
	int	i;
	int	j;
	int	k;
	
	i = 0;
	while (envp[i])
	{
		k = 0;
		while (envp[i][k])
		{
			j = 0;
			while (path[j] && envp[i][k + j] && envp[i][k + j] == path[j])
				j++;
			if (path[j] == '\0')
				return (join_path_and_cmd(envp[i], cmd));
			k++;
		}
		i++;
	}
	return (NULL);
}

void	check_files(t_list *data, int *err)
{
	if ((data->ac) < 5)
	{
		ft_printf("you need %d more arguments.\n", 5-(data->ac));
		*err += 1;
	}
	else
	{
		if ((access((data->av)[1], F_OK | R_OK)) < 0)
		{
			perror((data->av)[1]);
			*err += 1;
		}
		if ((access((data->av)[(data->ac) -1], F_OK | W_OK)) < 0)
		{
			perror((data->av)[(data->ac) -1]);
			*err += 1;
		}
	}
}
void	all_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free (split[i++]);
	free (split);
}

char	**get_path_of_cmds(int *j, t_list *data)
{
	char	**cmd;
	char	**path_of_cmds;

	cmd = ft_split((data->av)[*j], ' ');
	path_of_cmds = path_finder((data->envp), "PATH=", cmd[0]);
	all_free(cmd);
	return(path_of_cmds);
}

char	**cmd_to_list(char *path_of_cmd, t_list data)
{
	char	**result;
	int		i;

	i = 0;
	while (data.commands[i])
		i++;
	result = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (data.commands[i])
	{
		result[i] = data.commands[i];
		i++;
	}
	result[i] = path_of_cmd;
	i++;
	result[i] = NULL;//free gerekebilir
	return (result);
}

void	check_cmds(t_list *data, int *err)
{
	char	**path_of_cmd;
	int		j;
	int		i;

	j = 2;
	data->commands = NULL;
	while (j < data->ac -1)
	{
		path_of_cmd = get_path_of_cmds(&j, data);
		while (*path_of_cmd)
		{
			if (access(*path_of_cmd, F_OK | X_OK) == 0)
			{
				(data->commands) = cmd_to_list(*path_of_cmd, *data);
				break ;
			}
			path_of_cmd++;
		}
		if (!(*path_of_cmd))
		{
			ft_printf("%s: command is not found.\n", (data->av)[j]);
			(*err) += 1;
		}
		j++;
	}
}

int	arg_checker(t_list *data)
{
	int err;

	err = 0;
	check_files(data, &err);
	check_cmds(data, &err);
	if (err > 0)
		return (err);
	else
		err += fd_to_data(data);
	return (err);
}
void	add_args_to_list(t_list *data, int ac, char **av, char **envp)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
}

int	main(int ac, char **av, char **envp)
{
	int		err;
	t_list	data;
	add_args_to_list(&data, ac, av, envp);
	err = arg_checker(&data);
	if ( err > 0)
	{
		ft_printf("%d error occured.\n", err);
		return (0);
	}
	// main_process(data, ac, av, envp);
	return (0);
}


/*
	pipe(int pipefd[input, output]);

	t_list data = fill_list(ac, av, envp);

	fill_list(int ac, char **av, char **envp)
	{

	}

*/