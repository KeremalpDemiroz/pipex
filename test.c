
// /*

// error = access("path/file", f_ok | w_ok | r_ok) 
// if (error < 0)
// 	perror(error)
// 	return(0)
// --------
// fd1 = open("file1", o_rd);
// fd2 = open("file2", o_wr);
// n_stdo = dup(1);
// p1 = fork();
// if (p1 == 0)

// s_list list_fd
// {
	// 	int file1;
	// 	int file2;
	// 	int n_stdo;
	
	// 	void *next;
	// }t_list;
	
	
	// */
	// char **get_path()
	// {
		// 	char *path;
		// 	char **path_split;
		
		// 	path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
		// 	path_split = ft_split(path, ':'); 
		// 	return (path_split);
		// }
		
		// int	cmd_check(int ac, char **files)//henüz files için ayarlı ama bunu komutlar için kullanabiliriz
		// {
			// 	char **cmds;
			// 	int	error;
			// 	int	i;
			// 	int	j;
			
			
			// 	i = 2;
			// 	while (i < ac-1)
			// 	{
				// 		j = 0;
				// 		cmds = ft_split(files[i], ' ');
				// 		error = access("/usr/bin/ls", F_OK);
				// 		if (error < 0)
				// 		{
					// 			perror(files[i]);
					// 			return  (-1);	
					// 		}
					// 		while (cmds[j] != NULL)
					// 		{
						// 			ft_printf("{%s} , ", cmds[j]);
						// 			free(cmds[j]);
						// 			j++;
						// 		}
						// 		free(cmds);
						// 		i++;
						// 	}
						// 	return (0);
// }


// int main(int ac,char **av)
// {
	// 	(void)**av;
	// 	if (ac == 5)
	// 	{
		// 		// ft_printf("En az 5 arguman olmalı");
		// 		if (cmd_check(ac, av) < 0)
		// 			return(0);
		// 	}
		// 	return (0);
		// }
		
#include "pipex.h"

int	path_finder(char **big, char *little)
{
	int	i;
	int	j;
	int	k;
	
	i = 0;
	while (big[i][k])
	{
		k = 0;
		while (big[i][k])
		{
			j = 0;
			while (little[j] && big[i][k + j] && big[i][k + j] == little[j])
				j++;
			if (!little[j])
				return (i);
			k++;
		}
		i++;
	}
	return (-1);
}

char	**cmd_path(char *envp, char *av)
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

int main(int ac, char **av, char **envp)
{
	int i;
	int j;
	char **paths;
	
	j = 0;
	i = 0;
	if (ac < 5)
		return (0);
	i = path_finder(envp, "PATH");
	paths = cmd_path(envp[i], "ls");
	while (paths[j])
	{
		ft_printf("%s\n", paths[j]);
		free(paths[j]);
		j++;
	}
	free(paths);
	return 0;
}
// void	check_cmds(int ac, int *err, char **av, char **envp)
// {
// 	char	**cmd;
// 	char	**path;
// 	int		j;

// 	j = 2;
// 	while (j < ac -1)
// 	{
// 		cmd = ft_split(av[j], ' ');
// 		path = path_finder(envp, "PATH", cmd[0]);
// 		all_free(cmd);
// 		while (*path)
// 		{
// 			if (access(*path, F_OK | X_OK) == 0)
// 				break ;
// 			path++;
// 		}
// 		if (!(*path))
// 		{
// 			ft_printf("%s: command is not found.\n", av[j]);
// 			(*err) += 1;
// 		}
// 		j++;
// 	}
// }