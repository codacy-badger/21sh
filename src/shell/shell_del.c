/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:37:04 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//file
static void	input_del(t_input *input)
{
	line_del(&input->line);
	line_del(&input->clipb);
}

//file
static void	term_del(t_term *term)
{
	term->termtype = NULL;
	term_reset(&term->orig_term);
	return ;
}

static void	data_del(t_data *data)
{
	ft_strarray_del(&data->prompts);
}

void		shell_del(t_sh *shell)
{
	data_del(&shell->data);
	input_del(&shell->input);
	term_del(&shell->term);
}
