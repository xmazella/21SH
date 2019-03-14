/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmazella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:58:56 by xmazella          #+#    #+#             */
/*   Updated: 2018/08/28 17:52:39 by xmazella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "parse.h"

void			add_varloc(char *str, t_type type)
{
	char		**split;
	char		*string;
	t_env		*tmp;

	if ((split = (char **)malloc(sizeof(char *) * 2)) == NULL)
		malloc_error();
	split[0] = ft_strdup(str);
	split[1] = 0;
	if ((string = ft_strchr(split[0], '=')) == NULL)
	{
		ft_deltab(&split);
		return ;
	}
	*string = 0;
	tmp = blt_getenv(split[0], g_env);
	*string = '=';
	if (tmp == NULL || tmp->type == type)
		blt_setenv(split, &g_env, type, 0);
	else
		blt_setenv(split, &g_env, ENV, 0);
	ft_deltab(&split);
}

t_list			*set_varloc(t_list *lst)
{
	while (lst)
	{
		if ((lst->content_size != 3) || (!ft_strchr(lst->content, '=')))
			return (lst);
		add_varloc(lst->content, LOCALE);
		lst = lst->next;
	}
	return (lst);
}
