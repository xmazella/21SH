/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 13:55:41 by mmervoye          #+#    #+#             */
/*   Updated: 2018/09/13 16:34:33 by xmazella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_term.h"

char			*term_main_loop(t_term *term)
{
	term_get_row(term);
	if (tcsetattr(0, TCSANOW, &(term->term_ios)) == -1)
		return (NULL);
	if (!(term->history) || term->history->text != term->buffer)
		term_hst_add_entry(&(term->history), term->buffer);
	term_le_clear(&(term->line_edit));
	term->ctn = 1;
	term_exec_tc("vi");
	while (term->ctn > 0)
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &(term->wsize));
		term_write_prompt(term, 1);
		term_read_input(term);
		term_refresh(term);
	}
	term_write_prompt(term, 0);
	term_exec_tc("ve");
	tcsetattr(0, TCSANOW, &(term->old_ios));
	term_hst_goto_head(&(term->history));
	if (term->ctn == -1)
		return (NULL);
	if (term->line_edit.len != 0)
		term->history->text = ft_strdup(term->line_edit.text);
	return (term->line_edit.text);
}

void			term_write_prompt(t_term *term, int cursor)
{
	char		*ptr;
	char		*ptr1;
	char		*ptr2;
	int			offset;

	offset = ft_strlen(term->line_edit.prompt) - 2;
	ptr = le_cursortext(&term->line_edit, cursor);
	ptr2 = ptr;
	term_exec_goto("cm", 0, term->row);
	ft_putstr(term->line_edit.prompt);
	term_exec_tc("cd");
	while ((ptr1 = ft_strchr(ptr2, '\n')))
	{
		term_exec_goto("ch", 0, offset);
		term_exec_tc("ce");
		write(1, "> ", 2);
		write(1, ptr2, ptr1 - ptr2);
		term_exec_tc("do");
		ptr2 = ptr1 + 1;
	}
	term_exec_goto("ch", 0, offset);
	write(1, "> ", 2);
	ft_putstr(ptr2);
	free(ptr);
}

void			term_refresh(t_term *term)
{
	char		*ptr;
	char		*ptr1;
	char		*ptr2;
	int			offset;
	int			y;

	offset = ft_strlen(term->line_edit.prompt);
	ptr = term->line_edit.text;
	ptr2 = ptr;
	y = 0;
	while ((ptr1 = ft_strchr(ptr2, '\n')))
	{
		y += 1 + ((offset + (ptr1 - ptr2)) / term->wsize.ws_col);
		ptr2 = ptr1 + 1;
	}
	y += 1 + ((ft_strlen(ptr2) + offset) / term->wsize.ws_col);
	while (term->row + y > term->wsize.ws_row)
	{
		term_exec_tc("sf");
		term->row--;
	}
}

int				term_read_input(t_term *term)
{
	char		kc;
	int			rd;

	kc = 0;
	rd = read(0, &kc, 1);
	if (rd > 0)
	{
		if (!ft_isprint(kc))
		{
			if (term_evt_dispatch(term, kc) == -1)
				term_exec_tc("bl");
			return (0);
		}
		term_hst_goto_head(&(term->history));
		term_le_insert(&(term->line_edit), kc);
	}
	return (0);
}

int				term_init(t_term *term)
{
	char		*term_name;

	term_name = getenv("TERM");
	if (tgetent(NULL, term_name) <= 0)
		term_name = "xterm-256color";
	if (tgetent(NULL, term_name) <= 0)
		return (-1);
	if (tcgetattr(0, &(term->term_ios)))
		return (-1);
	term->line_edit.prompt = "21sh $> ";
	term->history = NULL;
	term->old_ios = term->term_ios;
	term->term_ios.c_iflag &= ~(ICRNL | IXON);
	term->term_ios.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	term->term_ios.c_cc[VMIN] = 1;
	term->term_ios.c_cc[VTIME] = 0;
	return (0);
}
