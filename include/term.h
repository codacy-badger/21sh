/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/21 20:39:09 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include <term.h>
# include <termios.h>
# include <curses.h>

struct				s_keys
{
	int				del;
	int				left;
	int				right;
	int				up;
	int				down;
	int				bsp;
	int				esc;
	int				spc;
	int				enter;
};

struct				s_term
{
	struct termios	orig_termios;
	struct s_keys	keys;
	char			*termtype;
	int				width;
};

void				init_term(struct s_term *term);

#endif 
