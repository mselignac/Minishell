/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:49:37 by elouchez          #+#    #+#             */
/*   Updated: 2022/03/08 15:49:37 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execution_ve(t_data *data, t_token *actual, char *bin)
{
	int	ret;

	ret = execve(bin, actual->args, data->envp);
	if (ret == -1)
	{
		if (errno == 2)
		{
			print_error("command not found: ");
			if (actual->args[0])
				ft_putstr_fd(actual->args[0], STDERR);
			ft_putstr_fd("\n", STDERR);
			ret = 127;
		}
		else
			perror("minishell");
	}
	return (ret);
}

static int	child(t_data *data, t_token *actual)
{
	char	*bin;
	int		ret;

	if (actual->prev_in || actual->prev_out || actual->prev_d_out)
		redirection(actual);
	if (actual->prev_pipe && !actual->next_in
		&& !actual->prev_in && to_prev_command(actual))
		dup2(to_prev_command(actual)->pipes[0], STDIN);
	if (actual->next_pipe && !actual->next_in
		&& !actual->next_out && !actual->next_d_out)
		child_pipe(actual);
	else if (actual->next_out || actual->next_d_out || actual->next_in)
		redirection2(actual);
	bin = get_bin_path(data, actual->args[0]);
	if (bin == NULL)
		bin = ft_strdup(actual->args[0]);
	ret = check_built_in(data, actual->args);
	if (ret == 1000)
		ret = execution_ve(data, actual, bin);
	free(bin);
	minifree(data);
	if (data->envp)
		free_tab(data->envp);
	free (data->pid);
	exit (ret);
}

static int	parent(t_data *data, t_token *actual)
{
	int	i;
	int	ret;
	int	status;

	ret = 0;
	i = 0;
	status = 0;
	if (actual->prev_pipe && to_prev_command(actual))
		close(to_prev_command(actual)->pipes[0]);
	if (actual->next_pipe || actual->prev_pipe)
		close(actual->pipes[1]);
	if (actual->id == data->nb_command - 1)
	{
		while (i < data->nb_command)
		{
			waitpid(data->pid[i], &status, 0);
			ret = ret_status(data, status, i);
			i++;
		}
	}
	return (ret);
}

int	exe_pipe(t_data *data, t_token *actual, int i)
{
	int		error;
	int		ret;

	error = 0;
	ret = 0;
	if (actual->next_pipe || actual->prev_pipe)
		error = pipe(actual->pipes);
	if (error != 0)
		return (1);
	data->pid[i] = fork();
	g_pid = data->pid[i];
	if (data->pid[i] == 0)
		child(data, actual);
	else
		ret = parent(data, actual);
	return (ret);
}

int	execution(t_data *data)
{
	data->actual = data->first;
	if (data->actual->type != COMMAND)
		data->actual = to_next_command(data->actual);
	while (data->command_nb < data->nb_command)
	{
		pre_check_builtins(data, data->actual, data->command_nb);
		data->command_nb++;
		data->actual = to_next_command(data->actual);
		if (!data->actual)
			break ;
	}
	free(data->pid);
	return (0);
}
