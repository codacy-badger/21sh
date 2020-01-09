/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:17:30 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/09 13:23:57 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	is_quote_stop(char *str, int i, char quote_status)
{
	if (str[i] != quote_status)
		return (false);
	if (quote_status == DQUOTE && i != 0 && str[i - 1] == BSLASH)
		return (false);
	return (true);
}

bool	is_quote_start(char *str, int i, char quote_status)
{
	if (i != 0 && str[i - 1] == BSLASH)
		return (false);
	return ((str[i] == SQUOTE || str[i] == DQUOTE) && quote_status == NONE);
}

/*
** We never want to remove a character after a backslash so it's ok to increment
** i directly after we delete a backslash. However, we must be careful not to
** increment i after deleting a backslash at the end of a word.
*/

void	remove_quotes(t_dstr *str)
{
	char	quote_status;
	int		i;

	quote_status = NONE;
	i = 0;
	while (str->str[i])
	{
		if (is_quote_start(str->str, i, quote_status))
		{
			quote_status = str->str[i];
			ft_dstr_remove(str, i, 1);
			continue;
		}
		if (is_quote_stop(str->str, i, quote_status))
		{
			quote_status = NONE;
			ft_dstr_remove(str, i, 1);
			continue;
		}
		if ((quote_status == NONE || quote_status == DQUOTE)
				&& str->str[i] == BSLASH)
			ft_dstr_remove(str, i, 1);
		if (str->str[i])
			i++;
	}
}
