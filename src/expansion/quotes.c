/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:17:30 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/08 18:19:32 by fratajcz         ###   ########.fr       */
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
	return ((str[i] == SQUOTE || str[i] == DQUOTE) && quote_status == NONE);
}

void	remove_quotes(t_dstr *str)
{
}
