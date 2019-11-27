/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:53:32 by fratajcz         ###   ########.fr       */
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

/*
** prompt scroll...
** input->prompt...
*/

typedef struct		s_input
{
	char			**pmpt;
	struct s_line	*line;
	//struct s_line	*hist;??
	//struct s_line	*cb;??
	char			*clipboard;
}					t_input;

typedef struct		s_line
{
	struct s_line	*prev; //<= for cutting multiple words in a row
	struct s_line	*next; //	add them like in a stack || for multi line edit
	char			*str;  //   || history...
	size_t			size;
	size_t			len;
	size_t			i;
}					t_line;

void				input_init(t_input *input);
void				input_reset(t_term *term, t_input *input);
int					input_read_line(t_term *term, t_input *input);
void				input_clear_line(t_term *term, t_input *input);
int					input_add_char(t_term *term, t_input *input, char c);
int					input_add_str(t_term *term, t_input *input, char *s);
int					input_del_char(t_term *term, t_input *input, int c);
int					input_del_nchar(t_term *term, t_input *input, int c, int n);

/*
** T_line struct
*/
t_line				*line_new(size_t size);
int					line_add_char(t_line *line, int c);
int					line_add_str(t_line *line, char *s);
int					line_del_char(t_line *line);
int					line_del_nchar(t_line *line, int n);
t_line				*line_add(t_line **head, t_line *line, int stack); // /!\ not tested
t_line				*line_add_at(t_line **head, t_line *line, int stack); // /!\ not tested
void				line_delone(t_line **line);
void				line_del(t_line **line);

/*
** Cursor motion
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
int		cut_previous_word(t_term *term, t_input *input);
int		cut_after(t_input *input);
int		cut_before(t_term *term, t_input *input);
int		paste(t_term *term, t_input *input);

#endif
