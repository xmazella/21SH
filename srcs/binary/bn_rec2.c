/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_rec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 17:35:34 by mmervoye          #+#    #+#             */
/*   Updated: 2018/09/11 17:01:09 by mmervoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int					free_and_return(char ***ft_tab)
{
	ft_deltab(ft_tab);
	return (-1);
}

char				**ft_sortpath(char **bn_tab, char **cmd_bn_tab)
{
	(void)cmd_bn_tab;
	if (env_get("PATH") == NULL)
		return (NULL);
	if ((bn_tab = ft_strsplit(env_get("PATH"), ':')) == NULL)
		malloc_error();
	return (bn_tab);
}

int					exec_wrapper(t_ps_tree *tree, int p)
{
	if (tree->op_number == '|')
		return (do_pipe(tree));
	else
	{
		if (p && check_redir(tree->content) == 1)
			do_redir(tree->content);
		return (bn_binary(tree));
	}
}

int					bn_rec(t_ps_tree *tree, char prev_op)
{
	int		ret;

	ret = 0;
	if (!tree)
		return (0);
	if (tree->left)
		ret = bn_rec(tree->left, tree->op_number);
	if (tree->op_number && tree->op_number != OP_PIPE)
	{
		if (ret && tree->right && tree->op_number == OP_AND)
			bn_rec(tree->right, tree->op_number);
		else if (!ret && tree->right && tree->op_number == OP_OR)
			bn_rec(tree->right, tree->op_number);
		else if (tree->op_number == OP_DOTCOMA)
			bn_rec(tree->right, tree->op_number);
	}
	else if (prev_op != OP_PIPE)
		return (exec_wrapper(tree, 0));
	return (ret);
}
