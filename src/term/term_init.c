/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/05 21:47:45 by ferfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	init_caps(struct s_term *term)
{
	term->caps[C_UP] = tgetstr("up", NULL);
	term->caps[C_DOWN] = tgetstr("do", NULL);
	term->caps[C_LEFT] = tgetstr("le", NULL);
	term->caps[C_RIGHT] = tgetstr("nd", NULL);
	term->caps[C_CE] = tgetstr("ce", NULL);
	term->caps[C_CD] = tgetstr("cd", NULL);
	term->caps[C_DC] = tgetstr("dc", NULL);
	term->caps[C_SC] = tgetstr("sc", NULL);
	term->caps[C_RC] = tgetstr("rc", NULL);
	term->caps[C_CR] = tgetstr("cr", NULL);
	term->caps[C_SF] = tgetstr("sf", NULL);
	term->caps[C_SR] = tgetstr("sr", NULL);
	term->caps[C_CM] = tgetstr("cm", NULL);
	term->caps[C_CL] = tgetstr("cl", NULL);
}

int		term_init(struct s_term *term)
{
	struct termios	new_term;

	term->termtype = getenv("TERM");
	if (term->termtype == NULL || tgetent(NULL, term->termtype) <= 0)
		return (-1); //error
	if (!isatty(STDIN_FILENO))
		return (-1); //error
	tcgetattr(STDIN_FILENO, &(term->orig_term));
	new_term = term->orig_term;
	new_term.c_lflag &= ~(ECHO | ICANON /*| ISIG*/);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);
	tputs(tgetstr("ks", NULL), 1, ft_putc);
	term_setsize(term);
	init_caps(term);
	return (0);
}

void	term_reset(struct termios *orig_term)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_term);
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	tputs(tgetstr("te", NULL), 1, ft_putc);
}
