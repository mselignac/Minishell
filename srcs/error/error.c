/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:20:52 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:20:52 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *error_str)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(error_str, STDERR);
}

static int	syntax_check(t_data *data)
{
	t_token	*actual;

	actual = data->first;
	while (actual)
	{
		if (actual->next && actual->type == PIPE && actual->next->type == PIPE)
		{
			print_error("syntax error near `|\'\n");
			data->ret = 2;
			return (2);
		}
		if (actual->next && is_arrow(actual->content) == 1
			&& is_arrow(actual->next->content) == 1)
		{
			print_error("syntax error near redirection\n");
			data->ret = 2;
			return (2);
		}
		actual = actual->next;
	}
	return (0);
}

int	last_check(t_data *data)
{
	t_token	*actual;
	int		ret;

	ret = syntax_check(data);
	if (ret > 0)
		return (ret);
	actual = data->first;
	if (actual->content && actual->content[0] == '\0')
		actual->content = NULL;
	while (actual->next)
		actual = actual->next;
	if (actual->type == PIPE)
	{
		print_error("nothing next to last pipe\n");
		data->ret = 2;
		return (2);
	}
	if (is_arrow(actual->content) == 1)
	{
		print_error("nothing next to last redirection\n");
		data->ret = 2;
		return (2);
	}
	return (0);
}
