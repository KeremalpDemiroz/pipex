int	create_data(t_list *data, int ac, char **av, char **envp)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
	data->stdin_backup = dup(0);
	data->stdout_backup = dup(1);
	data->file_err = 0;
	data->cmd_err = 0;
	if (is_args_ok(data) < 0)
		return (-1);
	else
		return (0);
}
