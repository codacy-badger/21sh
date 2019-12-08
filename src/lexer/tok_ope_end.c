/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_ope_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void set_operator_type(t_lexer *lexer, char **str)
{
    char    *ope;
    char    *prev_tok;

    ope = lexer->curr_tok->content->str;
    lexer->curr_tok->type = get_operator_type(ope);
    if (is_operator_redir(lexer->curr_tok) && lexer->prev_tok)
    {
        prev_tok = lexer->prev_tok->content->str;
        if (!ft_isblank(*(*str - (ft_strlen(ope) + 1))) && ft_strisnbr(prev_tok))
            lexer->prev_tok->type = IO_NUMBER;
    }
}

int         tok_ope_end(t_lexer *lexer, char **str)
{
    if (!lexer->curr_tok->is_delim && is_operator(lexer->prev)
    && !is_operator_next(lexer->curr_tok->content->str, **str))
    {
        set_operator_type(lexer, str);
        lexer->curr_tok->is_delim = true;
        return (1);
    }
    return (0);
}