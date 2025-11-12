/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:04:55 by kedemiro          #+#    #+#             */
/*   Updated: 2025/11/12 19:06:18 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	n_free(char **ptr, int nptr)
{
	if (!ptr)
		return ;
	while (nptr >= 0)
	{
		free(ptr[nptr]);
		nptr--;
	}
	free(ptr);
}

int	main(int ac, char **av, char **envp)
{
	t_list	data;
	int		i;

	i = 0;
	if (ac <= 5)
	{
		ft_putendl_fd("the number of arguments must be more than 5", 2);
		exit(EXIT_FAILURE);
	}
	create_data(&data, ac, av, envp);
	mother_process(&data, i);
	n_free(data.commands, ac -4);
	if (data.cmd_err + data.file_err > 0)
	{
		ft_putnbr_fd(data.cmd_err + data.file_err, 2);
		ft_putendl_fd(" error occured", 2);
	}
}
