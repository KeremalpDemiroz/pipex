/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:06:47 by kedemiro          #+#    #+#             */
/*   Updated: 2025/11/06 20:15:07 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files(t_list *data)
{
	int	file_res;

	file_res = access(data->av[1], F_OK | R_OK);
	if (file_res < 0)
	{
		perror(data->av[1]);
		(data->file_err) += 1;
	}
	if (data->file_err == 0 && data->cmd_err == 0)
	{
		data->outfile_fd = open(data->av[(data->ac) - 1], O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
		if (data->outfile_fd < 0)
		{
			perror(data->av[(data->ac) - 1]);
			(data->file_err) += 1;
		}
	}
	if ((data->file_err) > 0)
		return (-1);
	else
		return (0);
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
		ft_putendl_fd("PATH doesn't exist", 2);
		return ;
	}
	while (i <= (data->ac) - 2)
	{
		combine = path_and_cmd(data, i, path);
		if (!combine)
			data->cmd_err += 1;
		else
			is_cmd(data, i, combine);
		i++;
	}
}

void	check_commands(t_list *data)
{
	data->commands = ft_calloc(1, (data->ac) - 2);
	if (!(data->commands))
	{
		data->cmd_err += 1;
		ft_printf("%d error occured\n", data->cmd_err);
		exit(EXIT_FAILURE);
	}
	command_with_path(data);
}

int	is_args_ok(t_list *data)
{
	if (data->ac < 5)
	{
		ft_printf("%d or more arguments must be entered\n", 5 - data->ac);
		ft_printf("1 error occured\n");
		return (-1);
	}
	check_files(data);
	check_commands(data);
	if (data->file_err > 0)
	{
		ft_printf("%d errors occured\n", data->file_err);
		return (-1);
	}
	return (0);
}
