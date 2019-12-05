/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:57 by fratajcz         ###   ########.fr       */
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

# define ALLOC_ERROR	3

typedef struct		s_data
{
	char			**prompts;
}					t_data;

typedef struct		s_sh
{
	struct s_term	term;
	struct s_data	data;
	struct s_input	input;
	struct s_lexer	lexer;
}					t_sh;

int		shell_init(t_sh *shell);
void	shell_del(t_sh *shell);

void	sig_init(t_sh *shell);
void	sig_handle(int sig);
void	sig_action(t_sh *shell, int sig);

/*
** Utils
*/
int		ft_putc(int c);
ssize_t	ft_putwc(char *c);
ssize_t	getcsize(int c);
ssize_t	getcsize_rev(char *s, int i);
int		isctrl(t_term *term, unsigned int c);

#endif
