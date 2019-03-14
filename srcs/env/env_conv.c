/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:49:59 by mmervoye          #+#    #+#             */
/*   Updated: 2018/08/28 17:17:23 by xmazella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int			count_env(t_env *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		if (tmp->type == ENV)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char				**env_conv_tab(void)
{
	char		**env_tab;
	char		*tmp_n;
	t_env		*tmp;
	int			i;

	tmp = g_env;
	i = count_env(tmp);
	if (i == 0 || !(env_tab = (char **)malloc(sizeof(char *) * i + 1)))
		return (i == 0 ? NULL : (char **)malloc_error());
	tmp = g_env;
	i = -1;
	while (tmp->next)
	{
		if (tmp->type == ENV)
		{
			tmp_n = ft_strdup(tmp->name);
			tmp_n = ft_strjoinf(tmp_n, "=");
			env_tab[++i] = ft_strjoinf(tmp_n, tmp->value);
		}
		tmp = tmp->next;
	}
	env_tab[i] = 0;
	return (env_tab);
}
