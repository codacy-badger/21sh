/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:10:43 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/14 12:10:49 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_env_var(char *var, char *value, t_env *env)
{
	if (get_env_var(var, env) == NULL)
		add_env_var(var, value, env);
	else
		replace_env_var(var, value, env);
}
