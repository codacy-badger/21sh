/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     add_token(t_lexer *lexer, int type)
{
    lexer->prev_tok = lexer->curr_tok;
    if (!(lexer->curr_tok = token_new(type)))
        return (ALLOC_ERROR);
    ft_list_add_tail(lexer->curr_tok, lexer->tokens);
    return (0);
}