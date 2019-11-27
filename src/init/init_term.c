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


static void	init_caps(struct s_term *term)
{
	term->caps[C_UP] = tgetstr("up", NULL);
	term->caps[C_DOWN] = tgetstr("do", NULL);
	term->caps[C_LEFT] = tgetstr("le", NULL);
	term->caps[C_RIGHT] = tgetstr("nd", NULL);
	term->caps[C_CL] = tgetstr("ce", NULL);
	term->caps[C_CD] = tgetstr("cd", NULL);
	term->caps[C_SC] = tgetstr("sc", NULL);
	term->caps[C_RC] = tgetstr("rc", NULL);
	term->caps[C_CR] = tgetstr("cr", NULL);
	term->caps[C_SF] = tgetstr("sf", NULL);
	term->caps[C_SR] = tgetstr("sr", NULL);
}

static void	init_keys(struct s_term *term)
{
	char	*s;

	term->keys[K_DEL] = (s = tgetstr("kD", NULL)) ? *(int *)s : 0;
	term->keys[K_LEFT] = (s = tgetstr("kl", NULL)) ? *(int *)s : 0;
	term->keys[K_RIGHT] = (s = tgetstr("kr", NULL)) ? *(int *)s : 0;
	term->keys[K_UP] = (s = tgetstr("ku", NULL)) ? *(int *)s : 0;
	term->keys[K_DOWN] = (s = tgetstr("kd", NULL)) ? *(int *)s : 0;
	term->keys[K_HOME] = (s = tgetstr("kh", NULL)) ? *(int *)s : 0;
	term->keys[K_END] = 4607771;
	term->keys[K_NXTW] = 26139; //Alt(option) + right arrow
	term->keys[K_PRVW] = 25115; //Alt(option) + left arrow
	term->keys[K_BSP] = 127;
	term->keys[K_ESC] = 27;
	term->keys[K_SPC] = 32;
	term->keys[K_ENTER] = 10;
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
	new_term.c_cc[VMIN] = 0;
	new_term.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);
	tputs(tgetstr("ks", NULL), 1, ft_putc);
	set_termsize(term);
	init_keys(term);
	init_caps(term);
}
