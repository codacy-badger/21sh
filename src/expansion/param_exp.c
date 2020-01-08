/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:36:33 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/08 17:21:24 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_var_name(char *str)
{
	int	i;

	if (ft_isdigit(str[0]))
		return (NULL);
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == 0)
		return (NULL);
	return (ft_strsub(str, 0, i));
}

int		param_expand(t_dstr *str, int start, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		i;

	i = start;
	while (str->str[i])
	{
		if (str->str[i] == '$' && (var_name = get_var_name(str->str + i + 1)))
		{
				var_value = get_env_var(var_name, env);
				ft_dstr_remove(str, i, ft_strlen(var_name) + 1);
				ft_dstr_insert(str, i, var_value, ft_strlen(var_value));
				i += ft_strlen(var_value) - 1;
		}
		i++;
	}
	return (0);
}
