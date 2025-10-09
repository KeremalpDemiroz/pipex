#include "../pipex.h"

void	check_files(t_list *data)
{
	int	file_res;

	file_res = access(data->av[1], F_OK | R_OK);
	if (file_res < 0)
	{
		perror(data->av[1]);
		(data->err) += 1;
	}
	file_res = access(data->av[(data->ac)-1], F_OK | W_OK);
	if (file_res < 0)
	{
		perror(data->av[(data->ac) -1]);
		(data->err) += 1;
	}
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
		while (data->envp[i][j])
		{
			k = 0;
			while (data->envp[i][j+ k] && wanted[k] 
					&& data->envp[i][j + k] == wanted[k])
				k++;
			if (!wanted[k])
				return (data->envp[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	*all_free(char **split)
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
	splited_cmd = ft_split(data->av[i], " ");
	combined_path = ft_split(path, ":");
	while (combined_path[j])
	{
		joined = ft_strjoin(combined_path[j], "/");
		free(combined_path[j]);
		combined_path[j] = ft_strjoin(joined, splited_cmd[0]);
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
		if (access(cmd_path[j], F_OK | X_OK))
		{
			data->commands[i -2] = cmd_path[j];
		}
		j++;
	}
	if (!cmd_path[j])
	{
		ft_printf("command %s is not found.\n", data->av[i]);
		data->err += 1;
	}
}

void	command_with_path(t_list *data)
{
	char	*path;
	char	**combine;
	int		i;
	int		j;

	i = 2;
	path = choose_envp(data, "PATH=");
	if (path == NULL)
	{
		data->err += 1;
		ft_printf("PATH doesn't exist.\n");
		return ;
	}
	while (i < (data->ac)-1)
	{
		combine =path_and_cmd(data, i, path);
		is_cmd(data, i, combine);
		i++;
	}
}


void	check_commands(t_list *data, int *err)
{
	char	*cmd;

	data->commands = malloc(sizeof(char *) * (data->ac) -2);
	if (!(data->commands))
		return (NULL);
	data->commands[(data->ac) -2] = NULL;
	command_with_path(data);
	//access();
	//command_to_list(data, "if'den gelen");
}

void	is_args_ok(t_list *data)
{

	check_files(data);
	check_commands(data);
}

void	create_data(t_list *data, int ac, char **av, char **envp)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
	data->err = 0;
	is_args_ok(data);
}

int main(int ac, char **av, char **envp)
{
	t_list data;

	create_data(&data, ac, av,envp);
}