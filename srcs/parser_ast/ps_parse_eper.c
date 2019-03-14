/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parse_eper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 00:57:00 by mmervoye          #+#    #+#             */
/*   Updated: 2018/08/21 01:03:50 by mmervoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int				ps_parse_eper(t_list *tokens)
{
	t_list		*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->content_size == '&')
			tmp->content_size = 3;
		tmp = tmp->next;
	}
	return (0);
}
