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
	ft_strarray_del(&input->pmpt);
	line_del(&input->line);
	line_del(&input->clipb);
}

//file
static void	term_del(t_term *term)
{
	term->termtype = NULL;
	return ;
}

void		shell_del(t_sh *shell)
{
	term_del(&shell->term);
	input_del(&shell->input);
}
