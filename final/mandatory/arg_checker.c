/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:06:47 by kedemiro          #+#    #+#             */
/*   Updated: 2025/11/12 18:59:09 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_files(t_list *data)
{
	int	file_res;

	file_res = access(data->av[1], F_OK | R_OK);
	if (file_res < 0)
	{
		perror(data->av[1]);
		data->infile_fd = open("/dev/null", O_RDONLY);
		(data->file_err) += 1;
	}
	else
		data->infile_fd = open(data->av[1], O_RDONLY);
	data->outfile_fd = open(data->av[(data->ac) - 1], O_CREAT
			| O_WRONLY | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
	{
		perror(data->av[(data->ac) - 1]);
		(data->file_err) += 1;
		exit (EXIT_FAILURE);
	}
}

void	is_cmd(t_list *data, int i, char **cmd_path)
{
	int		j;

	j = 0;
	if (!cmd_path)
	{
		ft_putstr_fd(data->av[i], 2);
		ft_putendl_fd(": Command is not found", 2);
		return ;
	}
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
		ft_putstr_fd(data->av[i], 2);
		ft_putendl_fd(": Command is not found", 2);
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
		is_cmd(data, i, combine);
		i++;
	}
}

void	check_commands(t_list *data)
{
	data->commands = ft_calloc((data->ac) - 2, sizeof(char *));
	if (!(data->commands))
	{
		data->cmd_err += 1;
		ft_putnbr_fd(data->cmd_err, 2);
		ft_putendl_fd(" error occured", 2);
		exit(EXIT_FAILURE);
	}
	command_with_path(data);
}

int	is_args_ok(t_list *data)
{
	if (data->ac < 5)
	{
		ft_putnbr_fd(5 - data->ac, 2);
		ft_putendl_fd(" or more arguments must be entered\n1 error occured", 2);
		return (-1);
	}
	check_files(data);
	check_commands(data);
	if (data->file_err > 0)
		return (-1);
	return (0);
}
