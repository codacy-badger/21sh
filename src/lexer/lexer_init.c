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

int     lexer_init(t_lexer *lexer)
{
    int     ret;

    lexer->prev_tok = NULL;
    lexer->curr_tok = NULL;
    if (!(lexer->tokens = ft_list_first_head(NULL)))
        return (-1);
    if (!(ret = add_token(lexer, START)))
        return (ret);
    return (0);
}