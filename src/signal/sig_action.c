/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sig_action(t_sh *shell, int sig)
{
	static t_sh	*sh;

	if (shell)
	{
		sh = shell;
		return ;
	}
	if (sig == SIGINT)
	{
		reset_input(&sh->term, &sh->input);
	}
	else if (sig == SIGWINCH)
	{
		signal(sig, SIG_DFL);
		set_termsize(&sh->term);
		//reprint line;
		signal(sig, sig_handle);
	}
	else if (sig == SIGTSTP)
		;
	else if (sig == SIGCONT)
		;
	//else if (sig == SIGSEGV)
	//	;
	else if ((1 <= sig && sig <= 15) || sig == 17
			|| (21 <= sig && sig <= 22) || (24 <= sig && sig <= 27))
	{
		reset_term(&sh->term.orig_term);
		signal(sig, SIG_DFL);
		kill(getpid(), sig); //ioctl
	}
	return ;
}
