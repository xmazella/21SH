/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 21:15:06 by matteo            #+#    #+#             */
/*   Updated: 2018/09/11 16:46:05 by mmervoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				do_pipe(t_ps_tree *tree)
{
	int		fd[2];
	pid_t	c_pid[2];

	pipe(fd);
	if ((c_pid[0] = fork()) == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		exec_wrapper(tree->left, 1);
		exit(0);
	}
	else if ((c_pid[1] = fork()) == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		exec_wrapper(tree->right, 1);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(c_pid[0], 0, 0);
	waitpid(c_pid[1], 0, 0);
	return (0);
}
