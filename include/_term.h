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

struct				s_keys
{
	unsigned int	del;
	unsigned int	left;
	unsigned int	right;
	unsigned int	up;
	unsigned int	down;
	unsigned int	bsp;
	unsigned int	esc;
	unsigned int	spc;
	unsigned int	enter;
	unsigned int	home;
	unsigned int	end;
	unsigned int	nextw;
	unsigned int	prevw;

};

struct				s_caps
{
	char			*cm;
	char			*up;
	char			*dn;
	char			*le;
	char			*nd;
	char			*ce;
	char			*sc;
	char			*rc;
};

typedef struct		s_term
{
	struct termios	orig_term;
	struct winsize	win;
	struct s_keys	keys;
	struct s_caps	caps;
	char			*termtype;
	size_t			cx;
	size_t			cy;
}					t_term;

void				init_term(struct s_term *term);
void				reset_term(struct termios *orig_termios);

#endif 
