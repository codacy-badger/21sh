/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 20:35:05 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include "_term.h"
# include "shell.h"

# define PS1		0
# define PS2		1
# define PS3		2
# define PS4		3
# define EOL		'\n'

typedef struct		s_input
{
	char			*clipboard;
	char			**pmpt;
	struct s_line	*line;
}					t_input;

typedef struct		s_line
{
	char			*str;
	size_t			size;
	size_t			len;
	size_t			i;
}					t_line;

void				init_input(t_input *input);
void				reset_input(t_term *term, t_input *input);
int					read_line(t_term *term, t_input *input);
void				clear_line(t_term *term, t_input *input);

/*
** t_line
*/
t_line				*line_new(size_t size);
int					line_add_char(t_line *line, int c);
int					line_del_char(t_line *line);
void				line_del(t_line **line);

/*
** cursor
*/
int					move_curs_left(t_term *term, t_input *input);
int					move_curs_right(t_term *term, t_input *input);
int					move_curs_home(t_term *term, t_input *input);
int					move_curs_end(t_term *term, t_input *input);
int					move_curs_nextw(t_term *term, t_input *input);
int					move_curs_prevw(t_term *term, t_input *input);

/*
** Copy/Paste
*/

int					cut_previous_word(t_term *term, t_input *input);
int					cut_after(t_input *input);
int					cut_before(t_term *term, t_input *input);
int					paste(t_term *term, t_input *input);

void				redraw(t_term *term, t_input *input);

#endif
