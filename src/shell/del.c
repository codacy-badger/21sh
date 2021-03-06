/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/25 16:54:19 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	del_input(t_input *input)
{
	while (input->head->next != input->head)
	{
		ft_dstr_del((void *)&input->head->next->data, NULL);
		ft_list_del(input->head->next);
	}
	ft_list_del(input->head);
	ft_dstr_del((void **)&input->line, NULL);
	ft_dstr_del((void **)&input->clip, NULL);
}

static void	del_term(t_term *term)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->oldterm);
	return ;
}

void		del(t_sh *shell)
{
	del_term(&shell->term);
	del_input(&shell->input);
}
