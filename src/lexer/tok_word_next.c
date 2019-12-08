/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_word_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     tok_word_next(t_lexer *lexer, char **str)
{
    if (**str && !lexer->curr_tok->is_delim)
    {
        if (ft_dstr_add(&lexer->curr_tok->content, **str) < 0)
            return (ALLOC_ERROR);
        lexer->prev = **str;
        (*str)++;
        return (1);
    }
    return (0);
}