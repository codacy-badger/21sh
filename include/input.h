/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:14:19 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include "_term.h"

# define PS1	">> "
# define PS2	"> "
# define PSQ	"quote> "
# define PSDQ	"dquote> "
# define EOL	'\n'

typedef struct		s_input
{
	t_dstr			*line;
	int				i;
	int				x;
	int				y;
}					t_input;

void	init_input(t_input *input);
int		read_line(t_term *term, t_input *input);

/*
** Utils
*/
int		move_curs_right(t_input *input, t_term *term);
int		move_curs_left(t_input *input, t_term *term);
int		move_curs_home(t_input *input, t_term *term);
int		move_curs_nextw(t_input *input, t_term *term);
int		move_curs_prevw(t_input *input, t_term *term);
void	str_add_char(t_input *input, int c);
void	str_del_char(t_input *input);
void	display_add_char(t_input *input, t_term *term);
void	display_del_char(t_input *input, t_term *term);

#endif
