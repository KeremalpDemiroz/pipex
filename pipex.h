#ifndef PIPEX
# define PIPEX

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./sources/libft.h"

typedef struct s_list
{
	int		stdin_backup;	// dup(0);
	int		stdout_backup;	// dup(1);
	int		infile_fd;		// open(av[1], o_RDONLY)
	int		outfile_fd;		// open(av[ac -1], o_WRONLY)
	char	**av;
	char	**envp;
	int		ac;
	char	**commands;
	int		file_err;
	int		cmd_err;
}t_list;

#endif

/*

	(dup2(0,infile_fd)) ->execve(get_path, av[2], envp) -> (0, NULL)_pipe_(NULL, 1)-> execve -> outfile_fd
*/