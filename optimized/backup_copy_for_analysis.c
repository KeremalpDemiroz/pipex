#include "../pipex.h"
#include <string.h> /* DÜZELTME: choose_envp içinde strncmp/strlen kullanmak için eklendi */

int	check_files(t_list *data)
{
	int	file_res;
	file_res = access(data->av[1], F_OK | R_OK);
	if (file_res < 0)
	{
		perror(data->av[1]);
		(data->file_err) += 1;
	}
	/* DÜZELTME: outfile her durumda açılacak; access kontrolüne bakılmaksızın open çağrısı yap */
	data->outfile_fd = open(data->av[(data->ac) -1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
	{
		perror(data->av[(data->ac) -1]);
		(data->file_err) += 1;
	}
	if ((data->file_err) > 0)
		return (-1);
	else
		return (0);
}
char	*choose_envp(t_list *data, const char *wanted)
{
	/* DÜZELTME: strncmp ile basitleştirilmiş ve düzeltilmiş implementasyon */
	size_t wl = strlen(wanted); /* DÜZELTME: 'wanted' uzunluğunu bir kere hesapla */
	int i = 0;

	if (!data->envp)
		return (NULL); /* DÜZELTME: NULL koruması eklendi */
	while (data->envp[i])
	{
		if (strncmp(data->envp[i], wanted, wl) == 0)
		{
			fprintf(stderr, "DEBUG: choose_envp found: %s\n", data->envp[i]); /* DEBUG */
			return (data->envp[i] + wl); /* DÜZELTME: return pointer after prefix */
		}
		i++;
	}
	return (NULL);
}

static void	all_free(char **split)
{
	int	a;
	if (!split)
		return; /* DÜZELTME: NULL ise çık */
	a = 0;
	while (split[a])
	{
		free(split[a]);
		a++;
	}
	free(split);
}

char	**path_and_cmd(t_list *data, int i, char *path)
{
	char	**combined_path;
	char	**splited_cmd;
	char	*joined;
	int		j;

	j = 0;
	splited_cmd = ft_split(data->av[i], ' ');
	combined_path = ft_split(path, ':');
	if (!combined_path || !splited_cmd)
	{
		data->cmd_err += 1;
		return (NULL);
	}
	while (combined_path[j])
	{
		joined = ft_strjoin(combined_path[j], "/");
		free(combined_path[j]);
		combined_path[j] = ft_strjoin(joined, splited_cmd[0]);
	fprintf(stderr, "DEBUG: path_and_cmd: trying %s\n", combined_path[j]); /* DEBUG */
		free(joined);
		j++;
	}
	all_free(splited_cmd);
	return (combined_path);
}
void	is_cmd(t_list *data, int i, char **cmd_path)
{
	int		j;

	if (!cmd_path) /* DÜZELTME: NULL argüman kontrolü eklendi */
	{
		data->cmd_err += 1; /* DÜZELTME: hata sayaçını artır */
		return;
	}
	j = 0;
	while (cmd_path[j])
	{
		fprintf(stderr, "DEBUG: is_cmd checking: %s\n", cmd_path[j]); /* DEBUG */
		if (access(cmd_path[j], F_OK | X_OK) == 0)
		{
			data->commands[i -2] = ft_strdup(cmd_path[j]);
			fprintf(stderr, "DEBUG: is_cmd selected: %s for av[%d]=%s\n", cmd_path[j], i, data->av[i]); /* DEBUG */
			break ;
		}
		j++;
	}
	/* DÜZELTME: global cmd_err'e göre free yapan hatalı mantık kaldırıldı; strdup başarısızsa NULL olarak bırak */
	if (data->commands[i -2] == NULL && cmd_path[j])
	{
		/* strdup başarısız ya da atanmamış, NULL bırak */
		data->commands[i -2] = NULL;
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
		ft_printf("PATH doesn't exist\n");
		return ;
	}
	while (i <= (data->ac) -2)
	{
		combine = path_and_cmd(data, i, path);
		if (!combine) /* DÜZELTME: kullanmadan önce NULL kontrolü */
		{
			data->cmd_err += 1; /* DÜZELTME: hatayı yukarı taşı */
			i++;
			continue;
		}
		is_cmd(data, i, combine);
		i++;
	}
}


int	check_commands(t_list *data)
{
	int	i;

	i = 0;
	/* DÜZELTME: komut sayısını hesapla ve NULL terminatör için yer ayır */
	int n_cmds = data->ac - 3; /* DÜZELTME: ac = prog infile cmd... outfile => komut sayısı = ac-3 */
	data->commands = malloc(sizeof(char *) * (n_cmds + 1)); /* DÜZELTME: parantez ve +1 (NULL için) */
	if (!(data->commands))
	{
		data->cmd_err += 1;
		return (-1);
	}
	while (i <= n_cmds)
	{
		data->commands[i] = NULL; /* DÜZELTME: tüm girişleri başlat, terminator dahil */
		i++;
	}
	command_with_path(data);
	if (data->cmd_err > 0)
	{
		all_free(data->commands);
		return (-1);
	}
	return(0);
}

int	is_args_ok(t_list *data)
{
	if (data->ac < 5)
	{
		ft_printf("At least %d or more arguments must be entered\n", 5 - data->ac);
		ft_printf("1 error occured\n");

		return (-1);
	}
	check_files(data);
	check_commands(data);
	if (data->cmd_err + data->file_err > 0)
	{
		ft_printf("%d errors occured\n", data->cmd_err + data->file_err);
		return (-1);
	}
	return (0);
}

int	create_data(t_list *data, int ac, char **av, char **envp)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
	data->stdin_backup = dup(0);
	data->stdout_backup = dup(1);
	data->file_err = 0;
	data->cmd_err = 0;
	data->outfile_fd = -1; /* DÜZELTME: outfile fd'yi başlat */
	if (is_args_ok(data) == 0)
	{
		data->infile_fd = open(data->av[1], O_RDONLY);
		return (0);
	}
	else
		return (-1);
}


void	fd_table(t_list *data,int old_pipe_in, int pipe_fd[], int i)
{
	if (i == 0)
	{
	fprintf(stderr, "DEBUG: fd_table i==0 infile_fd=%d pipe_fd[1]=%d\n", data->infile_fd, pipe_fd[1]); /* DEBUG */
		dup2(data->infile_fd, 0);
		dup2(pipe_fd[1], 1);
		close(data->infile_fd);
	}
	else if (i == data->ac -4) /* DÜZELTME: son komut indeksi kontrolü (ac-4 olacak) */
	{
	fprintf(stderr, "DEBUG: fd_table last i=%d old_pipe_in=%d outfile_fd=%d\n", i, old_pipe_in, data->outfile_fd); /* DEBUG */
		if (old_pipe_in >= 0) /* FIX: only dup2 if valid */
			dup2(old_pipe_in, 0);
		dup2(data->outfile_fd, 1);
		close(data->outfile_fd);
	}
	else
	{
	fprintf(stderr, "DEBUG: fd_table middle i=%d old_pipe_in=%d pipe_fd[1]=%d\n", i, old_pipe_in, pipe_fd[1]); /* DEBUG */
		if (old_pipe_in >= 0) /* FIX: only dup2 if valid */
			dup2(old_pipe_in, 0);
		dup2(pipe_fd[1], 1);
	}
	if (old_pipe_in >= 0) /* FIX: avoid closing invalid fd */
		close(old_pipe_in);
	if (pipe_fd[1] >= 0)
		close(pipe_fd[1]);
}

void	child_process(t_list *data, int i, char **arg_array) /* FIX: changed to void */
{
	fprintf(stderr, "DEBUG: child_process execve: %s args[0]=%s\n", data->commands[i], arg_array ? arg_array[0] : "(null)"); /* DEBUG */
	execve(data->commands[i], arg_array, data->envp);
	perror("execve failure");
	exit(EXIT_FAILURE);
}

void	mother_process(t_list *data,int i)
{
	int		pipe_fd[2];
	int		old_pipe_in;
	pid_t	p1;
	char	**arg_array;

	i = 0;
	old_pipe_in = -1; /* DÜZELTME: geçersiz fd ile başlat */
	while (data->commands[i])
	{
	if (pipe(pipe_fd) == -1) { perror("pipe"); return; } /* DÜZELTME: pipe dönüşü kontrol edildi */
	fprintf(stderr, "DEBUG: mother_process before fork i=%d old_pipe_in=%d pipe_fd[0]=%d pipe_fd[1]=%d\n", i, old_pipe_in, pipe_fd[0], pipe_fd[1]); /* DEBUG */
		p1 = fork();
	if (p1 == -1) { perror("fork"); return; } /* DÜZELTME: fork dönüşü kontrol edildi */
		if (p1 == 0)
		{
			arg_array = ft_split(data->av[i+2], ' ');
			if (!arg_array)
				return ;
			fd_table(data,old_pipe_in, pipe_fd, i);
			child_process(data, i ,arg_array);
			all_free(arg_array);
		}
		/* Parent: close write end to avoid hanging and set up next read end */
		if (pipe_fd[1] >= 0)
			close(pipe_fd[1]); /* DÜZELTME: parent'da kullanılmayan yazma ucunu kapat */
	fprintf(stderr, "DEBUG: mother_process parent after fork i=%d new old_pipe_in=%d\n", i, pipe_fd[0]); /* DEBUG */
		old_pipe_in = pipe_fd[0];
		i++;
	}
	while (--i >= 0)
		wait(NULL);
}

int main(int ac, char **av, char **envp)
{
	t_list	data;
	int		i;

	i = 0;
	if (create_data(&data, ac, av,envp) < 0)
	{
		return (0);
	}
	else
		mother_process(&data, i);
	all_free(data.commands);
}
