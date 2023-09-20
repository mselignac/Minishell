/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:32:08 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 09:32:08 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe(t_token	*actual)
{
	if (actual->next)
		actual = actual->next;
	else
		return (0);
	while (actual && (actual->type == STRING || actual->type == STRING_SIMPLE
			|| actual->type == OPTION))
	{
		if (actual->next == NULL)
			return (0);
		if (actual->next->type == PIPE)
			return (1);
		actual = actual->next;
	}
	return (0);
}

void	check_exit(t_data *data)
{
	t_token	*actual;
	t_token	*tmp;
	int		i;
	int		t;

	actual = data->first;
	i = 0;
	t = 0;
	tmp = NULL;
	while (actual)
	{
		if (actual->type == COMMAND)
		{
			i++;
			if (!ft_strcmp(actual->content, "exit"))
			{
				tmp = actual;
				t = i;
			}
		}
		actual = actual->next;
	}
	if (tmp)
		ft_exit(data, data->splitted_args[t - 1]);
}

static void	check_quotes_bis(char quote, int *len, int *i, char *str)
{
	if (quote)
	{
		(*len)--;
		*i = 1;
	}
	if (str[(*len) - 2] == quote)
		(*len)--;
}

static void	init_quotes(int *i, char *quote, int *len, char *str)
{
	*i = 0;
	*quote = 0;
	*len = ft_strlen(str) + 1;
}

char	*check_quotes(t_data *data, char *str)
{
	int		i;
	int		len;
	char	quote;
	char	*dest;

	if (str[0] == '\"' && str[1] == '\"' && str[2] == '\0')
		return ("");
	init_quotes(&i, &quote, &len, str);
	if (str[0] == '\"')
		quote = '\"';
	else if (str[0] == '\'')
		quote = '\'';
	check_quotes_bis(quote, &len, &i, str);
	dest = mallocer(&dest, sizeof(char) * len);
	if (!dest)
		alloc_error(data, NULL);
	while (i < len - 1)
	{
		dest[i - 1] = str[i];
		i++;
	}
	dest[i - 1] = '\0';
	free(str);
	return (dest);
}
