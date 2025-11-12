#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./sources/libft.h"

typedef struct s_list
{
	int		stdin_backup;
	int		stdout_backup;
	int		infile_fd;
	int		outfile_fd;
	char	**av;
	char	**envp;
	int		ac;
	char	**commands;
	char	**cmd_split;
	int		file_err;
	int		cmd_err;
}	t_list;

char	*choose_envp(t_list *data, const char *wanted);
char	**path_and_cmd(t_list *data, int i, char *path);
int		check_files(t_list *data);
int		check_commands(t_list *data);
int		is_args_ok(t_list *data);
int		create_data(t_list *data, int ac, char **av, char **envp);
int		execute_command(t_list *data, int i);
void	all_free(char **split);
void	is_cmd(t_list *data, int i, char **cmd_path);
void	command_with_path(t_list *data);
void	fd_table(t_list *data, int old_pipe_in, int pipe_fd[], int i);
void	child_process(t_list *data, int i, int old_pipe_in, int pipe_fd[]);
void	pid_error(int pipe_fd[]);
void	mother_process(t_list *data, int i);

#endif
