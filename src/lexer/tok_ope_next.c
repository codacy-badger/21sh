/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_ope_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     tok_ope_next(t_lexer *lexer, char **str)
{
    if (!lexer->curr_tok->is_delim && is_operator(lexer->prev)
    && is_operator_next(lexer->curr_tok->content->str, **str))
    {
        if (ft_dstr_add(&lexer->curr_tok->content, **str) < 0)
            return (ALLOC_ERROR);
        lexer->prev = **str;
        (*str)++;
        return (1);
    }
    return (0);
}