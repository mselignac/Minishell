/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:22:50 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:22:50 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	env_error(t_data *data, char *str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	data->last_ret = 127;
}

int	ft_env(t_data *data, char **args)
{
	int	i;

	data->last_ret = 0;
	if (args[1] != NULL)
	{
		env_error(data, args[1]);
		return (data->last_ret);
	}
	i = 0;
	while (data->envp[i])
		printf("%s\n", data->envp[i++]);
	return (data->last_ret);
}
