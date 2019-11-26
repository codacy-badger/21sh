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
# define PS2	">  "
# define PSQ	"quote> "
# define PSDQ	"dquote> "
# define EOL	'\n'

/*
** list of lines
** int shifty = prev line len / ws_col + 1

** display_char(input, char c){
	putc(c)
	if (c == nl)
		input->cursx = 0;
		input->cursy++;
	else
		input->cursx++;
		input->line->len++;
}
** display_str(input, char *){
		diff = ws_col - cursx
		while (*str && diff--)
			display_char(*str)
		if (*str)
			display_char(nl)
		while (*str)
			display_char(*str)
}
** moveleft
*/

typedef struct		s_input
{
	struct s_line	*lines_list;
	struct s_line	*line;
}					t_input;

typedef struct		s_line
{
	struct s_line	*prev;
	struct s_line	*next;
	char			*prompt;
	char			*str;
	size_t			size;
	size_t			len;
	size_t			i;
}					t_line;

void	init_input(t_input *input);
int		read_line(t_term *term, t_input *input);

/*
** t_line
*/
t_line	*line_new(size_t size, char *prompt);
void	line_add(t_line **head, t_line *line); //return ptr to new line
int		line_add_char(t_line *line, int c);
void	line_del_char(t_line *line);
void	line_del(t_line **line);

/*
** Utils
*/
int		move_curs_right(t_term *term, t_input *input);
int		move_curs_left(t_term *term, t_input *input);
int		move_curs_up(t_term *term, t_input *input);
/*
int		move_curs_home(t_input *input, t_term *term);
int		move_curs_nextw(t_input *input, t_term *term);
int		move_curs_prevw(t_input *input, t_term *term);
*/
int		display_char(t_term *term, int c);
int		display_str(t_term *term, char *s);
int		display_line(t_term *term, t_line *line);
int		display_nl(t_term *term);

#endif
