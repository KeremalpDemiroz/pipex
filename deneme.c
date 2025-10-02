#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_list
{
	int	infile;
	int	outfile;
	int	n_stdin;
	int n_stdout;

}t_list;

// int	check_files(int ac, char **av)
// {
// 	int	error;
// 	int	range;

// 	range = ac -1;
// 	while (ac -1 >= 0)
// 	{
// 		error = access(av[ac -1], F_OK | W_OK | R_OK);
// 		if (error < 0)
// 		{
// 			perror(av[ac-1]);
// 			return (-1);
// 		}
// 		ac -= range - 1;
// 	}
// 	return (0);
// }

int	check_files(int ac, char **av, int *error_count)
{
	int error;

	if (ac < 5)
	{
		*error_count += 1;
		ft_printf("%d arguments: Argument counts must be greater than 5\n", ac);
	}
	error = access(av[ac -1], F_OK | W_OK | R_OK);
	if (error < 0 && ac != 2)
	{
		perror(av[ac -1]);
		*error_count += 1;
	}
	error = access(av[1], F_OK | W_OK | R_OK);
	if (error < 0)
	{
		perror(av[1]);
		*error_count += 1;
	}
	return (*error_count);
}


/*
	minus = ac -1; (4);
------------------------------------
	ac(5) >= 0
	ac(5) -= minus; -> ac == 1;
	ac (1) >= 0;
	ac(1) -= minus;

*/

int	create_data_list(t_list *pipex_data,int *error_count, int ac, char **av)
{
	(*pipex_data).infile = open(av[1], O_RDWR);
	(*pipex_data).outfile = open(av[ac-1], O_RDWR);
	if ((*pipex_data).infile == -1 || (*pipex_data).outfile == -1)//hata kontrolüne tekrar bak perror için
	{
		error_count += 1;
		return (perror(""), -1);
	}
	return (0);
}
int	main(int ac, char **av, char **envp)
{
	int	error_count;

	error_count = 0;
	int i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	if (check_files(ac, av, &error_count) != 0)
		return (ft_printf("%d error occured.", error_count), 0);
	t_list pipex_data;
	if (create_data_list(&pipex_data, &error_count, ac, av) == -1)
		return (ft_printf("%d error occured.", error_count), 0);

	close (pipex_data.infile);
	close (pipex_data.outfile);
	return 0;
}
