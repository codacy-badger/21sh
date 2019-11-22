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

struct				s_keys
{
	unsigned int				del;
	unsigned int				left;
	unsigned int				right;
	unsigned int				up;
	unsigned int				down;
	unsigned int				bsp;
	unsigned int				esc;
	unsigned int				spc;
	unsigned int				enter;
};

struct				s_term
{
	struct termios	orig_termios;
	struct s_keys	keys;
	char			*termtype;
	int				width;
};

void				init_term(struct s_term *term);
int					ft_putc(int c);

#endif 
