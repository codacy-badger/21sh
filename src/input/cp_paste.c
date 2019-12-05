/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:30:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:38:29 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** TODO++: find a key for enter in select mode, set int start & int end,
			highlight the current char (no need to reprint all line),
			increase int end or decrease int start when moving right or left,
			when cut is press, clipboard = strsub(start end)...
*/

int		cp_paste(t_term *term, t_input *input)
{
	t_line	*cb;

	cb = input->clipb;
	if (input->clipb == NULL)
		return (0);
	while (cb)
	{
		input_add_str(term, input, cb->str);
		cb = cb->next;
	}
	return (0);
}

