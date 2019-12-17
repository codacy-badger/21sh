/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:32:58 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** qstatus described in header.
**
** Before tokenization we remove eventual \\n at the end of the line.
** (added in input/read_line:handle_eol())
**
** In case there is no final newline, but there was a space before \\n,
** the last token is delimited properly because of the space but no EOL 
** nor END tokens are appended to the list.
**
** In case the input is not correctly quoted, the last token is not 
** delimited, qstatus is not reset to 0, and no EOL nor END tokens are appended
** to the list.
** Also the final newline, which is escaped by the unclosed quote, is stored
** in the token. (we could decide to remove all newlines from a token in token_delim)
**
** After parsing, in lexer_reset, we ll be able to check if the last token is delimited.
** If it is not the case, we ll just update the list head to point on the last elem,
** so that when parser will be called again, it will not reparse what was already done.
** Of course parser must ignore non delimited tokens.
**
** If last token is delimited but there is no END token, then the newline must have been
** escaped but a space were juste before the \, so the token has been delimited.
** In this case we reset the lexer normally, creating new list.
**
** In both cases the parser should not return EXECUTE, but LINE_CONTINUE.
**
** Normally as qstatus and curr_tok remain unmodified, lexer will have no pbm to continue
** where it stopped. There is a test just below the main loop, you can uncomment it, put
** a string with closing quote in strdup, run the shell and send a string with 
** corresponding opening quote in input and see the result.
*/

int			tokenize(t_lexer *lexer, t_input *input)
{
	char	*str;
	int		ret;
	int		i;

	str = input->line->str;
	while (*str)
	{
		i = 0;
		while (i < FUNC_NB)
		{
			if ((ret = lexer->ftable[i](lexer, &str)) != 0)
			{
				if (ret < 0)
					return (ret);
				break ;
			}
			i++;
		}
	}
	//to test no eol or uncorrect quotes
	if (lexer->curr_tok->type != END)
	{
		input->line->str = ft_strdup("blabla'def ghi\n");
		return (tokenize(lexer, input));
	}
	
	t_list_head *list;
	t_token     *token;

	list = lexer->tokens->next;
	while (list != lexer->tokens)
	{
		token = (t_token *)list->data;
		if (token->type == START)
			printf("[START] -> ");
		else if (token->type == NEWLINE)
			printf("[EOL] -> ");
		else if (token->type == END)
			printf("[END]\n");
		else
			printf("[%d: %s] -> ", token->type, token->content->str);
		list = list->next;
	}
	printf("qstatus: %d, last_tok->delimited: %d\n", lexer->qstatus, lexer->curr_tok->delimited);
	return (0);
}
