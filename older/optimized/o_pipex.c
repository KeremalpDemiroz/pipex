#include "../pipex.h"

int	check_files(t_list *data)
{
	int	file_res;
	file_res = access(data->av[1], F_OK | R_OK);
	if (file_res < 0)
	{
		perror(data->av[1]);
		(data->file_err) += 1;
	}
	file_res = access(data->av[(data->ac)-1], F_OK | W_OK);
	if (file_res < 0)
	{
		data->outfile_fd = open(data->av[(data->ac) -1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->outfile_fd < 0)
		{
			perror(data->av[(data->ac) -1]);
			(data->file_err) += 1;
		}
		
	}
	if ((data->file_err) > 0)
		return (-1);
	else
		return (0);
}
char	*choose_envp(t_list *data, const char *wanted)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (data->envp[i])
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (data->envp[i][j+ k] && wanted[k] && data->envp[i][j + k] == wanted[k])
			{
				k++;
			}
			if (!wanted[k])
				return (&(data->envp[i][5]));
			j++;
		}
		i++;
	}
	return (NULL);
}

static void	all_free(char **split)
{
	int	a;

	a = 0;
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
	if (!combined_path || !splited_cmd)
	{
		data->cmd_err += 1;
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
void	is_cmd(t_list *data, int i, char **cmd_path)
{
	int		j;

	j = 0;
	while (cmd_path[j])
	{
		if (access(cmd_path[j], F_OK | X_OK) == 0)
		{
			data->commands[i -2] = ft_strdup(cmd_path[j]);
			break ;
		}
		j++;
	}
	if (data->cmd_err > 0)
	{
		free(data->commands[i -2]);
		data->commands[i -2] = NULL;
	}
	if (!cmd_path[j])
	{
		ft_printf("%s: Command is not found\n", data->av[i]);
		data->cmd_err += 1;
	}
	all_free(cmd_path);
}

void	command_with_path(t_list *data)
{
	char	*path;
	char	**combine;
	int		i;
	
	i = 2;
	path = choose_envp(data, "PATH=");
	if (path == NULL)
	{
		data->cmd_err += 1;
		ft_printf("PATH doesn't exist\n");
		return ;
	}
	while (i <= (data->ac) -2)
	{
		combine = path_and_cmd(data, i, path);
		is_cmd(data, i, combine);
		i++;
	}
}


int	check_commands(t_list *data)
{
	int	i;

	i = 0;
	data->commands = malloc(sizeof(char *) * (data->ac) -2);
	if (!(data->commands))
	{
		data->cmd_err += 1;
		return (-1);
	}
	while(i <= (data->ac) -2)
	{
		data->commands[i] = NULL;
		i++;
	}
	command_with_path(data);
	if (data->cmd_err > 0)
	{
		all_free(data->commands);
		return (-1);
	}
	return(0);
}

int	is_args_ok(t_list *data)
{
	if (data->ac < 5)
	{
		ft_printf("At least %d or more arguments must be entered\n", 5 - data->ac);
		ft_printf("1 error occured\n");

		return (-1);
	}
	check_files(data);
	check_commands(data);
	if (data->cmd_err + data->file_err > 0)
	{
		ft_printf("%d errors occured\n", data->cmd_err + data->file_err);
		return (-1);
	}
	return (0);
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
	if (is_args_ok(data) < 0)
		return (-1);
	else
		return (0);
}

void	execute_command(char *path, char **argv, char **envp)
{
	execve(path, **argv, **envp);

}

int	child_process_a(t_list *data, int *pipe_fd)
{
	char	**arg_array;
	int		i;

	i = 0;
	if(dup2(1, pipe_fd[1]) < 0)
	{
		perror("");
		return (-1);
	}
	data->infile_fd = open(data->av[1], O_RDONLY);
	arg_array = ft_split(data->av[i + 2], " ");
	execute_command();


}

void	mother_process(t_list *data)
{
	int		pipe_fd[2];
	pid_t	p1;
	pid_t	p2;

	pipe(pipe_fd);
	p1 = fork();
	if (p1 == 0)
		child_process_a(&data, *pipe_fd);
	p2 = fork();
	if (p2 == 0)
		child_process_b(&data, *pipe_fd);
	waitpid(p1, );
	
		
}

int main(int ac, char **av, char **envp)
{
	t_list data;

	if (create_data(&data, ac, av,envp) < 0)
	{
		return (0);
	}
	else
		mother_process(&data);
	all_free(data.commands);
}
