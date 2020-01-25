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
	else if (sig == SIGWINCH)
	{
		signal(sig, SIG_DFL);
		getwinsize(&sh->term);
		redraw(&sh->input);
		signal(sig, sig_handle);
	}
	else if ((1 <= sig && sig <= 15) || sig == 17
			|| (21 <= sig && sig <= 22) || (24 <= sig && sig <= 27))
	{
		del(sh);
		signal(sig, SIG_DFL);
		kill(getpid(), sig);
	}
	return ;
}
