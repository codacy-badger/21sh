/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 00:28:15 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "shell.h"

# define PS1		0
# define PS2		1
# define PS3		2
# define PS4		3

/*
** prompt scroll...
*/

struct		s_data;

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
		K_REDRAW,
		K_CUTW,
		K_CUTA,
		K_CUTB,
		K_PAST,
		K_EOL,
		K_EOF,
		KEYS_SIZE
};


typedef struct		s_input
{
	char			*prompts[4];
	char			*prompt;
	struct s_line	*line;
	//struct s_line	*hist;??
	struct s_line	*clipb;
	unsigned int	keys[KEYS_SIZE];
	unsigned int	prev;
}					t_input;

typedef struct		s_line
{
	struct s_line	*prev;
	struct s_line	*next;
	char			*str;
	size_t			size;
	size_t			len;
	size_t			i;
}					t_line;

int					input_init(t_input *input);
void				input_reset(t_term *term, t_input *input);
void				input_clear_line(t_term *term, t_input *input);
int					input_add_char(t_term *term, t_input *input, unsigned int c);
int					input_add_str(t_term *term, t_input *input, char *s);
int					input_del_char(t_term *term, t_input *input, int c);
int					input_del_nchar(t_term *term, t_input *input, int c, int n);
int    				input_add_line(t_input *input);
int					read_line(t_term *term, t_input *input);

/*
** T_line struct
*/
t_line				*line_new(size_t size);
int					line_add_char(t_line *line, unsigned int c);
int					line_add_str(t_line *line, char *s);
int					line_del_char(t_line *line);
int					line_del_nchar(t_line *line, int n);
t_line				*line_add(t_line **head, t_line *line, int stack);
t_line				*line_add_at(t_line **head, t_line *line, int stack);
void				line_delone(t_line **line);
void				line_del(t_line **line);

/*
** Cursor motion
*/
int					move_curs_left(t_term *term, t_input *input);
int					move_curs_right(t_term *term, t_input *input);
int					move_curs_up(t_term *term, t_input *input);
int					move_curs_down(t_term *term, t_input *input);
int					move_curs_home(t_term *term, t_input *input);
int					move_curs_end(t_term *term, t_input *input);
int					move_curs_nextw(t_term *term, t_input *input);
int					move_curs_prevw(t_term *term, t_input *input);

/*
** Copy/Paste
*/
int					cp_cut_before(t_term *term, t_input *input);
int					cp_cut_after(t_term *term, t_input *input);
int					cp_cut_prevw(t_term *term, t_input *input);
int					cp_paste(t_term *term, t_input *input);

int					redraw(t_term *term, t_input *input);
#endif
