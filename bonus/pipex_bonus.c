/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:04:55 by kedemiro          #+#    #+#             */
/*   Updated: 2025/11/06 19:53:02 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_list	data;
	int		i;

	i = 0;
	if (create_data(&data, ac, av, envp) < 0)
	{
		if (ac >= 5)
			all_free(data.commands);
		return (0);
	}
	else
		mother_process(&data, i);
	all_free(data.commands);
}
