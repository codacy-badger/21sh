/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** should use the list functions of new/lexer branch, added to the libft
** to replace current list functions.
*/

void    init_ftable(t_lexer *lexer)
{
    lexer->ftable[0] = &tok_ope_next;
    lexer->ftable[1] = &tok_ope_end;
    lexer->ftable[2] = &tok_quote;
    lexer->ftable[3] = &tok_ope_start;
    lexer->ftable[4] = &tok_eol;
    lexer->ftable[5] = &tok_blank;
    lexer->ftable[6] = &tok_word_next;
    lexer->ftable[7] = &tok_hash;
    lexer->ftable[8] = &tok_word_start;
}

int     lexer_init(t_lexer *lexer)
{
    int     ret;

    lexer->prev_tok = NULL;
    lexer->curr_tok = NULL;
    init_ftable(lexer);
    if ((ret = token_add(lexer, START)) < 0)
        return (ret);
    lexer->prev = 0;
    return (0);
}