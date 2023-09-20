/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:43:35 by elouchez          #+#    #+#             */
/*   Updated: 2022/03/08 15:43:35 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_bis(t_data *data)
{
	data->first = NULL;
	data->actual = NULL;
	data->error = 0;
	data->nb_pipe = 0;
	data->splitted_args = NULL;
	data->buffer = "";
	data->quote_type = '\0';
	data->export.args = NULL;
	data->export.valid_args = 0;
	data->export.check = 0;
	data->export.equal = 0;
	data->envp_i = 0;
	data->command_nb = 0;
	data->ret = 0;
	data->last_ret = 0;
}

void	init(t_data *data)
{
	init_bis(data);
	g_pid = 0;
	data->tmpin = 0;
	data->tmpout = 0;
	data->unset.is_unset = 0;
	data->unset.check = 0;
	data->unset.valid_args = 0;
	data->unset.args = NULL;
	data->cd.home = NULL;
	data->nb_infiles = 0;
	data->heredoc = 0;
	data->nb_outfiles = 0;
	data->last_out = 0;
	data->tmp_var = NULL;
	data->nb_command = 0;
	data->heredoc_nb = 0;
}

static void	reset2(t_data *data)
{
	data->tmpin = 0;
	data->tmpout = 0;
	data->unset.is_unset = 0;
	data->unset.check = 0;
	data->unset.valid_args = 0;
	data->unset.args = NULL;
	data->nb_infiles = 0;
	data->nb_outfiles = 0;
	data->last_out = 0;
	data->tmp_var = NULL;
	data->heredoc_nb = 0;
	data->last_ret = 0;
}

void	reset_bis(t_data *data)
{
	data->first = NULL;
	data->actual = NULL;
	data->error = 0;
	data->nb_pipe = 0;
	data->splitted_args = NULL;
	data->buffer = "";
	data->quote_type = '\0';
	data->export.args = NULL;
	data->export.valid_args = 0;
	data->export.check = 0;
	data->export.equal = 0;
	data->envp_i = 0;
	data->command_nb = 0;
	data->nb_command = 0;
}

void	reset(t_data *data)
{
	reset_bis(data);
	g_pid = 0;
	reset2(data);
}
