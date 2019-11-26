/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	init_caps(struct s_caps *caps)
{
	/*
	** handle error : if essential caps are missing, quit
	**					or just disable line editing
	*/
	caps->cm = tgetstr("cm", NULL);
	caps->up = tgetstr("up", NULL);
	caps->dn = tgetstr("do", NULL);
	caps->le = tgetstr("le", NULL);
	caps->nd = tgetstr("nd", NULL);
	caps->ce = tgetstr("ce", NULL);
	caps->sc = tgetstr("sc", NULL);
	caps->rc = tgetstr("rc", NULL);
}

static void	init_keys(struct s_keys *keys)
{
	char	*s;

	keys->del = (s = tgetstr("kD", NULL)) ? *(int *)s : 0;
	keys->left = (s = tgetstr("kl", NULL)) ? *(int *)s : 0;
	keys->right = (s = tgetstr("kr", NULL)) ? *(int *)s : 0;
	keys->up = (s = tgetstr("ku", NULL)) ? *(int *)s : 0;
	keys->down = (s = tgetstr("kd", NULL)) ? *(int *)s : 0;
	keys->home = (s = tgetstr("kh", NULL)) ? *(int *)s : 0;
	//keys->end = ??
	keys->nextw = 26139; //Alt(option) + right arrow
	keys->prevw = 25115; //Alt(option) + left arrow
	keys->bsp = 127;
	keys->esc = 27;
	keys->spc = 32;
	keys->enter = 10;
}

void		init_term(struct s_term *term)
{
	struct termios	new_term;

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
	tcgetattr(STDIN_FILENO, &(term->orig_term));
	new_term = term->orig_term;
	new_term.c_lflag &= ~(ECHO | ICANON);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &term->win);
	tputs(tgetstr("ks", NULL), 1, ft_putc);
	init_keys(&(term->keys));
	init_caps(&(term->caps));
	term->cx = 0;
	term->cy = 0;
}
