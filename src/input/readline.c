/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 03:24:57 by fratajcz         ###   ########.fr       */
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
static int		escape(t_input *input, t_uint8 **bufp)
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

/*
** We increment buf pointer by 1 and call appropriate function.
*/
static int		control(t_input *input, t_uint8 **bufp)
{
	input->key[0] = *(*bufp)++;
	if (*input->key == 27)
		return (escape(input, bufp));
	else if (*input->key == 10)
		return (enter(input));
	else if (*input->key == 127)
		return (backspace(input));
	else if (*input->key == 14)
		return (move_nextword(input));
	else if (*input->key == 24)
		return (move_prevword(input));
	else if (*input->key == 21)
		return (cut_before(input));
	else if (*input->key == 11)
		return (cut_after(input));
	else if (*input->key == 23)
		return (cut_word(input));
	else if (*input->key == 25)
		return (paste(input));
	else if (*input->key == 12)
		return (redraw(input));
	return (0);
}

/*
** Variables are static in case we reach the end of the buffer 
** and the char is not terminated.
*/
static int		addchar(t_input *input, t_uint8 **bufp)
{
	static size_t	i = 0;
	static size_t	charlen = 0;
	size_t 			nprint;

	if (!charlen)
		charlen = ft_charlen(**bufp);
	while (**bufp && i < charlen)
		input->key[i++] = *(*bufp)++;
	if (i == charlen)
	{
		input->key[i] = 0;
		ft_dstr_insert(input->line, input->pos, (char *)input->key, charlen);
		nprint = printstr(input->termp, &input->line->str[input->pos]);
		input->pos += charlen;
		if (input->pos < input->line->len)
			movcto(input->termp, input->termp->cpos - nprint + 1);
		charlen = 0;
		i = 0;
		return (0);
	}
	return (CONTINUE);
}

/*
** We create a new line and add it to the list.
** We read in a buffer of BUFSIZE (2bytes minimum).
** We process each char in the buffer then continue to read.
** It allows better perf on reading from a file,
** but also, in case of a esc sequence, it avoids problems we had
** in prev readline:
**	 if we have "\033[Dabcde", this was stored in an long, the esc sequence
**	 was not recognized by c == key, so it was not handled.
*/
int				readline(t_input *input)
{
	t_uint8		buf[BUFSIZE];
	t_uint8		*bufp;
	int			ret;

	draw_prompt(input);
	if (!input->line_cont)
	{
		input->line = ft_dstr_new("", 0, 32);
		input->pos_min = 0;
		input->pos = 0;
	}
	else
		input->pos_min = input->pos;
	while ((ret = read(STDIN_FILENO, buf, BUFSIZE - 1)) > 0 && (bufp = buf))
	{
		buf[ret] = 0;
		while (*bufp)
		{
			if (ft_isctrl(*bufp))
				ret = control(input, &bufp);
			else if (input->esc)
				ret = escape(input, &bufp);
			else
				ret = addchar(input, &bufp);
			if (ret == CONTINUE)
				continue ; 
			input->oldkey = *(t_uint64 *)input->key;
			*(t_uint64 *)input->key = 0;
			if (ret == EOL)
				return (ret);
		}
	}
	return (ret);
}
