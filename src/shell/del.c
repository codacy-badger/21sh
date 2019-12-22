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

/*
static void	lexer_del(t_lexer *lexer)
{
	ft_list_foreach(lexer->tokens, &token_del, NULL);
	while (!ft_list_empty(lexer->tokens))
		ft_list_del(lexer->tokens->next);
	ft_list_del(lexer->tokens);
}
*/

static void	del_input(t_input *input)
{
	while (input->head->next != input->head)
		ft_lstdel(input->head->next, ft_dstr_del, NULL);
	ft_lstdel(input->head, NULL, NULL);
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
