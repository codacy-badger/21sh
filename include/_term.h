/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:20:09 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TERM_H
# define _TERM_H

# include <curses.h>
# include <termios.h>
# include <term.h>

# define K_UP		0
# define K_DOWN		1
# define K_LEFT		2
# define K_RIGHT	3
# define K_HOME		4
# define K_END		5
# define K_BSP		6
# define K_SPC		7
# define K_DEL		8
# define K_ENTER	9
# define K_ESC		10
# define K_NXTW		11
# define K_PRVW		12

# define C_UP		0
# define C_DOWN		1
# define C_LEFT		2
# define C_RIGHT	3
# define C_CL		4
# define C_CD		5
# define C_SC		6
# define C_RC		7
# define C_CR		8
# define C_SF		9
# define C_SR		10

typedef struct		s_term
{
	struct termios	orig_term;
	struct winsize	win;
	unsigned int	keys[13];
	char			*caps[11];
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
