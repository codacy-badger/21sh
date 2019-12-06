/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/05 21:51:40 by ferfi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <curses.h>
# include <termios.h>
# include <term.h>

enum	e_caps
{
		C_UP,
		C_DOWN,
		C_LEFT,
		C_RIGHT,
		C_CE,
		C_CD,
		C_DC,
		C_SC,
		C_RC,
		C_CR,
		C_SF,
		C_SR,
		C_CM,
		C_CL,
		CAPS_SIZE
};

typedef struct		s_term
{
	struct s_sh		*shell;
	struct termios	orig_term;
	struct winsize	win;
	char			*caps[CAPS_SIZE];
	char			*termtype;
	size_t			sizex;
	size_t			sizey;
	size_t			cx;
	size_t			cy;
}					t_term;

int					term_init(struct s_term *term);
void				term_reset(struct termios *orig_termios);
int					term_setsize(t_term *term);

size_t				display_char(t_term *term, char *c);
size_t				display_str(t_term *term, char *s);
size_t				display_nl(t_term *term);
void				clear_fromc(t_term *term);
int					movcdown(t_term *term);
int					movcup(t_term *term);
int					movcleft(t_term *term);
int					movcright(t_term *term);
void				movchx(t_term *term);
void				movchy(t_term *term);
void				movch(t_term *term);
void				movcex(t_term *term);
void				movcey(t_term *term);
void				movce(t_term *term);

#endif 
