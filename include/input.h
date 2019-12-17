/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:06:20 by fratajcz         ###   ########.fr       */
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
		KEYS_SIZE
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
** -esc is a boolean for readline, in case we are reading an
**  escape sequence.
*/
typedef struct		s_input
{
	struct s_term	*termp;
	unsigned long	keys[KEYS_SIZE];
	unsigned char	key[8];
	unsigned long	oldkey;
	t_list			*head;
	t_list			*curr;
	t_dstr			*line;
	t_dstr			*temp;
	t_dstr			*clip;
	size_t			pos;
	bool			esc;
}					t_input;

int					init_input(t_input *input, struct s_term *term);
int					readline(t_input *input);
int					prompt(t_input *input);
int					redraw(t_input *input);

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

#endif
