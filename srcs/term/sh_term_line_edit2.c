/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_term_line_edit2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 13:55:41 by mmervoye          #+#    #+#             */
/*   Updated: 2018/09/13 17:45:46 by xmazella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_term.h"

int					term_le_move_fwd(t_line_edit *le)
{
	if (le->cur == le->len)
		return (-1);
	le->cur++;
	return (0);
}

int					term_le_move_bwd(t_line_edit *le)
{
	if (le->cur == 0)
		return (-1);
	le->cur--;
	return (0);
}

int					term_le_move_next_word(t_line_edit *le)
{
	char			*text;

	text = le->text;
	if (le->cur == le->len)
		return (-1);
	while (text[le->cur] != ' ' && text[le->cur] != '\n' &&\
			le->cur < le->len)
		le->cur++;
	while ((text[le->cur] == ' ' || text[le->cur] == '\n') &&\
			le->cur < le->len)
		le->cur++;
	return (0);
}

int					term_le_move_prev_word(t_line_edit *le)
{
	char			*text;

	text = le->text;
	if (le->cur == 0)
		return (-1);
	le->cur--;
	while ((text[le->cur] == ' ' || text[le->cur] == '\n') && le->cur > 0)
		le->cur--;
	while (le->cur > 0 && text[le->cur - 1] != ' ' &&\
			text[le->cur - 1] != '\n')
		le->cur--;
	return (0);
}
