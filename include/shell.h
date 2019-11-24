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
# include "_term.h"
# include "input.h"
# include "libft.h"

typedef struct		s_sh
{
	struct s_term	term;
	struct s_input	input;
}					t_sh;

void	init_shell(t_sh *shell);
void	init_sig(t_sh *shell);
void	del_shell(t_sh *shell);

void	sig_handle(int sig);
void	sig_action(t_sh *shell, int sig);

/*
** Utils
*/
int		ft_putc(int c);

#endif
