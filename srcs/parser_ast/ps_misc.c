/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:10:24 by mmervoye          #+#    #+#             */
/*   Updated: 2018/09/05 17:30:54 by mmervoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int					ps_check_word_redir(int n)
{
	if (n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || \
n == 9 || n == 10)
		return (1);
	return (0);
}

t_ps_tree			*ps_init_tree(void)
{
	t_ps_tree	*new;

	if (!(new = (t_ps_tree *)malloc(sizeof(t_ps_tree))))
		return ((t_ps_tree *)malloc_error());
	new->left = NULL;
	new->right = NULL;
	new->op_number = 0;
	return (new);
}

int					ps_error(char c)
{
	ft_putstr("minishell: syntax error near unexcepted token: `");
	if (c == 125)
		ft_putstr("||");
	else if (c == 39)
		ft_putstr("&&");
	else if (c == 5)
		ft_putchar('<');
	else if (c == 6)
		ft_putchar('>');
	else if (c == 7)
		ft_putstr("<<");
	else if (c == 8)
		ft_putstr(">>");
	else
		ft_putchar(c);
	ft_putchar('\'');
	ft_putchar('\n');
	return (-1);
}

void				ps_free_ast(t_ps_tree **ast)
{
	if (!(*ast))
		return ;
	ps_free_ast(&((*ast)->right));
	if (((*ast)->op_number) == 0 && (*ast)->content)
		ft_lstdel(&(*ast)->content, &ft_delfunction);
	ps_free_ast(&((*ast)->left));
	free(*ast);
}

t_list				*ps_check_content(t_list *tokens)
{
	t_list		*tmp;

	tmp = NULL;
	tmp = ft_lstreverse(tokens);
	if (!(tmp->content) || ((char *)tmp->content)[0] == '\0')
		return (tmp->next);
	else
		return (tmp);
}
