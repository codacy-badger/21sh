/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     tokenize(t_lexer *lexer, t_input *input)
{
    char    *str;
    //int     ret;

    str = input->line->str;
    while (lexer->curr_tok->type != END)
    {
        if (tok_end(lexer, &str))  //check for errors
            continue ;
        if (tok_ope_next(lexer, &str))
            continue ;
        if (tok_ope_end(lexer, &str))
            continue ;
        if (tok_quote(lexer, &str))
          continue ;
        //if (tok_$`)
        //  continue ;
        if (tok_ope_start(lexer, &str))
          continue ;
        if (tok_eol(lexer, &str))
            continue ;
        if (tok_blank(lexer, &str))
            continue ;
        if (tok_word_next(lexer, &str))
          continue ;
        if (tok_hash(lexer, &str))
          continue ;
        if (tok_word_start(lexer, &str))
          continue ;
    }

    /**************debug*************/    
    t_list_head *list;
    t_token     *token;

    list = lexer->tokens->next;
    while (list != lexer->tokens)
    {
        token = (t_token *)list->data;
        if (token->type == START)
            printf("[%s] -> ", "START");
        else if (ft_strequ(token->content->str, "\n"))
            printf("[%s] -> ", "EOL");
        else if (token->type == END)
            printf("[%s] -> ", "END");
        else
            printf("[%d: %s] -> ", token->type, token->content->str);
        list = list->next;
    }
    printf("%s\n", "NULL");
    /**************debug*************/

    input_reset(input);
    return (0);
}
