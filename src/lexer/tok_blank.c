/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_blank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     tok_blank(t_lexer *lexer, char **str)
{
    if (ft_isblank(**str))
    {
        lexer->curr_tok->is_delim = true;
        while (ft_isblank(**str))
        {
            lexer->prev = **str;
            (*str)++;
        }
        return (1);
    }
    return (0);
}