/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_term_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 13:55:41 by mmervoye          #+#    #+#             */
/*   Updated: 2018/09/13 17:45:46 by xmazella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_term.h"

int					term_putchar(int c)
{
	write(1, &c, 1);
	return (c);
}

void				term_exec_tc(char *str)
{
	char		*s;

	s = tgetstr(str, NULL);
	if (s)
		tputs(s, 1, term_putchar);
}

void				term_exec_goto(char *str, int x, int y)
{
	char		*s;

	s = tgoto(tgetstr(str, NULL), x, y);
	write(1, s, ft_strlen(s));
}

void				term_get_row(t_term *term)
{
	struct termios	term_ios;
	char			str[16];
	char			*sep;

	term_ios = term->term_ios;
	term_ios.c_cc[VMIN] = 6;
	term_ios.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term_ios);
	write(1, "\033[6n", 4);
	read(0, str, 16);
	tcsetattr(0, TCSANOW, &(term->term_ios));
	term->row = ft_atoi(str + 2) - 1;
	if ((sep = ft_strchr(str, ';')))
	{
		if (ft_atoi(sep + 1) != 1)
		{
			write(1, "\033[30;47m%\033[0m\n", 14);
			if (term->row < term->wsize.ws_row - 1)
				term->row++;
		}
	}
}
