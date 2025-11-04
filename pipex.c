#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_list	data;
	int		i;

	i = 0;
	if (create_data(&data, ac, av, envp) < 0)
	{
		return (0);
	}
	else
		mother_process(&data, i);
	all_free(data.commands);
}
