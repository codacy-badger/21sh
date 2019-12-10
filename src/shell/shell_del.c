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

static void	lexer_del(t_lexer *lexer)
{
	while (!ft_list_empty(lexer->tokens))
		ft_list_del(lexer->tokens->next);
	ft_list_del(lexer->tokens);
}

//file
static void	input_del(t_input *input)
{
	int		i;

	i = 0;
	line_del(&input->line);
	line_del(&input->clipb);
	while (i < 4)
		ft_memdel((void *)&input->prompts[i++]);
	input->prompt = NULL;
}

//file
static void	term_del(t_term *term)
{
	term->termtype = NULL;
	term_reset(&term->orig_term);
	return ;
}

void		shell_del(t_sh *shell)
{
	lexer_del(&shell->lexer);
	input_del(&shell->input);
	term_del(&shell->term);
}
