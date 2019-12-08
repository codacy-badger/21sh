/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_eol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     tok_eol(t_lexer *lexer, char **str)
{
    if (**str == '\n')
    {
        lexer->curr_tok->is_delim = true;
        if (add_token(lexer, NEWLINE) < 0)
            return (ALLOC_ERROR);
        if (ft_dstr_add(&lexer->curr_tok->content, **str) < 0) //not neccessary ?
            return (ALLOC_ERROR);
        lexer->curr_tok->is_delim = true;
        lexer->prev = **str;
        (*str)++;
        return (1);
    }
    return (0);
}