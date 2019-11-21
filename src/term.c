/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <curses.h>
#include <term.h>

int			ft_putc(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void			init_keys(struct s_keys *keys)
{
	keys->del = (tgetstr("kD", NULL)) ? *((int *)(tgetstr("kD", NULL))) : 0;
	keys->left = (tgetstr("kl", NULL)) ? *((int *)(tgetstr("kl", NULL))) : 0;
	keys->right = (tgetstr("kr", NULL)) ? *((int *)(tgetstr("kr", NULL))) : 0;
	keys->up = (tgetstr("ku", NULL)) ? *((int *)(tgetstr("ku", NULL))) : 0;
	keys->down = (tgetstr("kd", NULL)) ? *((int *)(tgetstr("kd", NULL))) : 0;
	keys->bsp = 127;
	keys->esc = 27;
	keys->spc = 32;
	keys->enter = 10;
}

void	init_term(struct s_term *term)
{
	struct termios	new_termios;

	term->termtype = getenv("TERM");
	if (term->termtype == NULL || tgetent(NULL, term->termtype) <= 0)
	{
		//ft_putendl_fd("Error: unknown terminal. Try setting $TERM", 2);
		exit(1);
	}
	if (!isatty(STDIN_FILENO))
	{
		//ft_putendl_fd("Error: STDIN is not a tty", 2);
		exit(1);
	}
	tcgetattr(STDIN_FILENO, &(term->orig_termios));
	new_termios = term->orig_termios;
	new_termios.c_lflag &= ~(ECHO | ICANON);
	new_termios.c_cc[VMIN] = 1;
	new_termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);
	tputs(tgetstr("ks", NULL), 1, ft_putc);
	init_keys(&(term->keys));
}

void		reset_term(struct termios *orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	tputs(tgetstr("te", NULL), 1, ft_putc);
}
