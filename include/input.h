/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/13 18:21:09 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "shell.h"

# define BUFSIZE	256
# define CONTINUE	1
# define EOL		10

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
		K_CUP,
		K_CDOWN,
		KEYS_NB
};

/*
** -termp is a pointer to term struct to avoid extra parameters.
** -key is a buffer for the current key being processed.
** -oldkey is the previous key received.
** -head is a list of dstr, its data is NULL.
**  A line is added to the list when eol is received.
** -curr is a pointer for history, it points to head 
**  when the line being edited is the current line.
** -line is the current line being edited.
** -temp is the current line backup for history.
** -clip is the clipboard.
** -pos is the index in the current line being edited.
** -pos_min is the minimum index we can reach, in case of line continuation
**  for example it is the beginning of the line.
** -esc is a boolean for readline, in case we are reading an
**  escape sequence.
*/
typedef struct		s_input
{
	struct s_term	*termp;
	unsigned long	keys[KEYS_NB];
	unsigned char	key[8];
	unsigned long	oldkey;
	t_list			*head;
	t_list			*curr;
	t_dstr			*line;
	t_dstr			*temp;
	t_dstr			*clip;
	const char		*last_prompt;
	size_t			pos;
	size_t			pos_min;
	bool			esc;
	bool			first_line;
	bool			multiline;
	char			char_after_nl;
	bool			interactive;
}					t_input;

int					init_input(t_input *input, struct s_term *term);
char				*readline(t_input *input, const char *prompt);

int					backspace(t_input *input);
int					delete(t_input *input);
int					enter(t_input *input);

int					move_left(t_input *input);
int					move_right(t_input *input);
int					move_up(t_input *input);
int					move_down(t_input *input);
int					move_home(t_input *input);
int					move_end(t_input *input);
int					move_nextword(t_input *input);
int					move_prevword(t_input *input);

int					history_up(t_input *input);
int					history_down(t_input *input);

int					cut_before(t_input *input);
int					cut_after(t_input *input);
int					cut_word(t_input *input);
int					paste(t_input *input);

int					draw_prompt(t_input *input, const char *prompt);
int					redraw(t_input *input);

int					cpos_to_prevline(t_input *input);
int					cpos_to_nextline(t_input *input);

int					ctrl_c(t_input *input);
int					ctrl_d(t_input *input);

int					escape(t_input *input, t_uint8 **bufp);

#endif
