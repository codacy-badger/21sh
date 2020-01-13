/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/13 16:46:45 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Variables are static in case we reach the end of the buffer 
** and the char is not terminated.
*/

static int		addchar(t_input *input, t_uint8 **bufp)
{
	static size_t	i = 0;
	static size_t	charlen = 0;
	size_t			offset;

	if (!charlen)
		charlen = ft_charlen(**bufp);
	while (**bufp && i < charlen)
		input->key[i++] = *(*bufp)++;
	if (i == charlen)
	{
		input->key[i] = 0;
		ft_dstr_insert(input->line, input->pos, (char *)input->key, charlen);
		clearfromc(input->termp);
		offset = printstr(input->termp, &input->line->str[input->pos]);
		input->pos += charlen;
		if (input->pos < input->line->len)
			movcto(input->termp, input->termp->cpos - offset + 1);
		charlen = 0;
		i = 0;
		return (0);
	}
	return (CONTINUE);
}

/*
** input->esc means we have started to read an escape sequence,
** but the end of buf was reached before the end of this escape sequence.
*/

static int		process(t_input *input, t_uint8 **bufp)
{
	if (input->esc)
		return (escape(input, bufp));
	else if (ft_isprint(**bufp))
		return (addchar(input, bufp));
	else if ((*input->key = *(*bufp)++) == 27)
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
	else if (*input->key == 3)
		return (ctrl_c(input));
	else if (*input->key == 4)
		return (ctrl_d(input));
	return (0);
}

static void		readline_init(t_input *input, const char *prompt)
{
	draw_prompt(input, prompt);
	input->last_prompt = prompt;
	if (input->line)
		ft_dstr_del((void **)&input->line, NULL);
	input->line = ft_dstr_new("", 0, 32);
	input->pos = 0;
	input->pos_min = 0;
}

/*
** We create a new line
** We read in a buffer of BUFSIZE (2bytes minimum).
** We process each char in the buffer then continue to read.
** It allows better perf on reading from a file,
** but also, in case of a esc sequence, it avoids problems we had
** in prev readline:
**	 if we have "\033[Dabcde", this was stored in an long, the esc sequence
**	 was not recognized by c == key, so it was not handled.
*/

char			*readline(t_input *input, const char *prompt)
{
	t_uint8		buf[BUFSIZE];
	t_uint8		*bufp;
	int			ret;
	char		*nl;

	readline_init(input, prompt);
	while ((ret = read(STDIN_FILENO, buf, BUFSIZE - 1)) > 0)
	{
		bufp = buf;
		buf[ret] = 0;
		while (*bufp)
		{
			if ((ret = process(input, &bufp)) == CONTINUE)
				continue ;
			input->oldkey = *(t_uint64 *)input->key;
			*(t_uint64 *)input->key = 0;
			if (ret == EOL)
				return (input->line->str);
		}
	}
	return (input->line->str);
}
