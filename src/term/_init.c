/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/05 18:47:52 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	init_caps(struct s_term *term)
{
	tputs(tgetstr("ks", NULL), 1, ft_putc);
	term->caps[C_UP] = tgetstr("up", NULL);
	term->caps[C_DO] = tgetstr("do", NULL);
	term->caps[C_LE] = tgetstr("le", NULL);
	term->caps[C_ND] = tgetstr("nd", NULL);
	term->caps[C_HO] = tgetstr("ho", NULL);
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
	term->caps[C_BL] = tgetstr("bl", NULL);
}

void		reset_term(struct termios *old_termios)
{
	static struct termios	*old_termios_ptr;

	if (old_termios_ptr == NULL && old_termios == NULL)
		return ;
	if (old_termios_ptr == NULL)
	{
		old_termios_ptr = old_termios;
		return ;
	}
	if (old_termios == NULL)
		old_termios = old_termios_ptr;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, old_termios);
}

int			init_term(struct s_term *term)
{
	if (tgetent(NULL, getenv("TERM")) <= 0)
		exit(1);
	if (!isatty(STDIN_FILENO))
		exit(1);
	tcgetattr(STDIN_FILENO, &(term->oldterm));
	reset_term(&(term->oldterm));
	term->newterm = term->oldterm;
	term->newterm.c_lflag &= ~(ECHO | ICANON | ISIG);
	term->newterm.c_cc[VMIN] = 1;
	term->newterm.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->newterm);
	init_caps(term);
	getwinsize(term);
	getcpos(term);
	return (0);
}
