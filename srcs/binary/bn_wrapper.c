/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_wrapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 09:42:37 by mmervoye          #+#    #+#             */
/*   Updated: 2018/09/11 17:02:06 by mmervoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int					check_redir(t_list *lst)
{
	t_list		*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->content_size != 3 && tmp->content_size != 7)
			return (1);
		else if (tmp->content_size == 7)
			return (2);
		tmp = tmp->next;
	}
	return (0);
}

int					bn_wrap_exec(char **bn_tab, char **cpath,\
char **cmd_bn_tab, t_ps_tree *tree)
{
	int		ret;

	if (check_redir(tree->content))
		ret = redir_exec(bn_tab, cpath, cmd_bn_tab, tree);
	else
		ret = bn_func_exec(bn_tab, cpath, cmd_bn_tab);
	return (ret);
}

int					bn_wrap_blt(char **cmd, t_ps_tree *tree)
{
	int		ret;

	ret = blt_check_ret(cmd);
	if (ret && check_redir(tree->content))
		redir_blt_exec(cmd, tree);
	else
		ret = blt_check(cmd);
	return (ret);
}
