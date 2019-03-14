/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_print_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmazella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 00:49:38 by xmazella          #+#    #+#             */
/*   Updated: 2018/08/18 00:54:47 by xmazella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			blt_print_env(t_env *env)
{
	while (env)
	{
		if (env->type == ENV)
		{
			ft_putstr(env->name);
			ft_putchar('=');
			ft_putendl(env->value);
		}
		env = env->next;
	}
}
