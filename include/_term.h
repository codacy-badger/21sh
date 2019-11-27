/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TERM_H
# define _TERM_H

# include <curses.h>
# include <termios.h>
# include <term.h>

enum	e_keys
{
		K_UP,
		K_DOWN,
		K_LEFT,
		K_RIGHT,
		K_HOME,
		K_END,
		K_BSP,
		K_SPC,
		K_DEL,
		K_ENTER,
		K_ESC,
		K_NXTW,
		K_PRVW,
		K_CUTWORD,
		K_CUTAFTER,
		K_CUTBEFORE,
		K_PASTE,
		KEYS_SIZE
};

enum	e_caps
{
		C_UP,
		C_DOWN,
		C_LEFT,
		C_RIGHT,
		C_CL,
		C_CD,
		C_SC,
		C_RC,
		C_CR,
		C_SF,
		C_SR,
		C_CM,
		CAPS_SIZE
};

typedef struct		s_term
{
	struct termios	orig_term;
	struct winsize	win;
	unsigned int	keys[KEYS_SIZE];
	char			*caps[CAPS_SIZE];
	char			*termtype;
	size_t			sizex;
	size_t			sizey;
	size_t			cx;
	size_t			cy;
}					t_term;

void				init_term(struct s_term *term);
void				reset_term(struct termios *orig_termios);
int					set_termsize(t_term *term);

size_t				display_char(t_term *term, int c);
size_t				display_str(t_term *term, char *s);
size_t				display_nl(t_term *term);


int					movcdown(t_term *term);
int					movcup(t_term *term);
int					movcleft(t_term *term);
int					movcright(t_term *term);
void				movchx(t_term *term);
void				movchy(t_term *term);
void				movch(t_term *term);


#endif 
