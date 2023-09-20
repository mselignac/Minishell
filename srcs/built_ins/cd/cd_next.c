/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_next.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:21:44 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:21:44 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	change_pwd_vars(t_data *data, char *oldpwd, char *pwd)
{
	int		i;
	int		checkpwd;
	int		old;

	i = 0;
	checkpwd = 0;
	old = 0;
	while (data->envp[i])
	{
		if (strncmp(data->envp[i], "PWD", 3) == 0)
		{
			data->envp[i] = join_arg(data->envp[i], pwd);
			checkpwd = 1;
		}
		if (strncmp(data->envp[i], "OLDPWD", 6) == 0)
		{
			data->envp[i] = join_arg(data->envp[i], oldpwd);
			old = i;
		}
		i++;
	}
	if (checkpwd == 0)
		data->envp[old] = join_arg(data->envp[old], "=");
}

char	*cd_join(char *dir, char *arg, char *new_dir)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (!new_dir)
		return (NULL);
	if (dir[0] == '/' && dir[1] == '\0')
		i++;
	while (dir[i])
		new_dir[k++] = dir[i++];
	i = 0;
	if (arg[0] != '~')
		new_dir[k++] = '/';
	else
		i = 1;
	if (arg[0] == '/')
		i = 1;
	while (arg[i])
		new_dir[k++] = arg[i++];
	new_dir[k] = '\0';
	return (new_dir);
}

char	*if_tilde(t_data *data, char *arg)
{
	char	*new_dir;

	if (ft_strlen(arg) == 1 || (arg[0] == 'c' && arg[1] == 'd'))
		return (data->cd.home);
	new_dir = malloc(ft_strlen(data->cd.home) + ft_strlen(arg));
	if (!new_dir)
		alloc_error(data, "cd");
	new_dir = cd_join(data->cd.home, arg, new_dir);
	return (new_dir);
}
