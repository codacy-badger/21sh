/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 02:28:05 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "libft.h"
# include "terminal.h"
# include "input.h"
# include "lexer.h"

/*
** TODO:
** -Improve redraw on resize + deal with
**  line editing of lines with quoted newlines.
** -Find more elegant way to deal with
**  operators in lexer.
*/

typedef struct		s_sh
{
	struct s_term	term;
	struct s_input	input;
	struct s_lexer	lexer;
}					t_sh;

int					init(t_sh *shell);
void				del(t_sh *shell);

void				init_sig(t_sh *shell);
void				sig_handle(int sig);
void				sig_action(t_sh *shell, int sig);

#endif
