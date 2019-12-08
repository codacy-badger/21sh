/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     tok_end(t_lexer *lexer, char **str)
{
    if (**str == '\0')
    {
        lexer->curr_tok->is_delim = true;
        if (add_token(lexer, END) < 0)
            return (ALLOC_ERROR);
        return (1);
    }
    return (0);
}