/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:42:27 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/13 16:44:10 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** We cant unsigned long cast because of:
** 	-Invalid read if buff pointer is more than end_of_buf - 8.
**	-Possible chars after a code of less than 8 bytes.
**	-The rest of the sequence may not have been read yet.
** We only handle CSI codes ('\033[' but it seems here is '\0330') less than 8 bytes,
** so we assume the last byte is between '@' and '~'.
** If the sequence is more than 8 bytes, we cant handle it but we continue to read it 
** until end to discard the sequence and avoid printing trash.
** If end of buf is reached and the sequence is not terminated, i is not reset, 
** and the input->esc bool is not reset so readline will automatically
** send escape() after reading the next chars (except if next char is a ctrl char),
** and we can get the rest of the code. 
*/

static t_uint64	get_csi_code(t_input *input, t_uint8 **bufp)
{
	static int	i = 1;
	t_uint64	code;

	while (**bufp)
	{
		input->key[i] = *(*bufp)++;
		if (i != 1 && '@' <= input->key[i])
		{
			code = *(t_uint64 *)input->key;
			input->esc = false;
			i = 1;
			return (code);
		}
		i += i < 7 ? 1 : 0;
	}
	return (0);
}

/*
** We want to get the exact CSI code and call the appropriate function.
*/
int		escape(t_input *input, t_uint8 **bufp)
{
	t_uint64	code;

	input->esc = true;
	if (!(code = get_csi_code(input, bufp)))
		return (CONTINUE);
	else if (code == input->keys[K_UP])
		return (history_up(input));
	else if (code == input->keys[K_DOWN])
		return (history_down(input));
	else if (code == input->keys[K_LEFT])
		return (move_left(input));
	else if (code == input->keys[K_RIGHT])
		return (move_right(input));
	else if (code == input->keys[K_HOME])
		return (move_home(input));
	else if (code == input->keys[K_END])
		return (move_end(input));
	else if (code == input->keys[K_DEL])
		return (delete(input));
	else if (code == input->keys[K_CUP])
		return (move_up(input));
	else if (code == input->keys[K_CDOWN])
		return (move_down(input));
	return (0);
}

