/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 13:14:43 by mmervoye          #+#    #+#             */
/*   Updated: 2018/09/10 21:01:09 by mmervoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				lx_is_word(char buf)
{
	if (buf == ' ' || buf == '\t' || buf == 0)
		return (0);
	if (buf == '&' || buf == '|' || buf == ';' || buf == '>' || buf == '<')
		return (0);
	return (1);
}

int				lx_is_op(char buf)
{
	if (buf == '&' || buf == '|' || buf == ';')
		return (1);
	return (0);
}

int				lx_wlen(char *buf)
{
	int			i;
	char		c;

	i = 0;
	while (*buf)
	{
		if (!lx_is_word(*buf))
			return (i);
		if (*buf != '"' && *buf != '\'')
			i++;
		else
		{
			c = *buf;
			buf++;
			while (*buf != c)
			{
				buf++;
				i++;
			}
		}
		buf++;
	}
	return (i);
}

char			*lx_strdup(char *buf)
{
	char		*str;
	int			i;
	char		c;

	str = ft_strnew(lx_wlen(buf));
	i = 0;
	while (*buf)
	{
		if (!lx_is_word(*buf))
			break ;
		if (*buf != '"' && *buf != '\'')
			str[i++] = *buf;
		else
		{
			c = *buf;
			buf++;
			while (*buf != c)
			{
				str[i++] = *buf;
				buf++;
			}
		}
		buf++;
	}
	return (str);
}
