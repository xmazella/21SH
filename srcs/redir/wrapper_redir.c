/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmervoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 10:46:58 by mmervoye          #+#    #+#             */
/*   Updated: 2018/09/13 18:06:19 by mmervoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int			exec_output(int out, char *name, int n)
{
	int			fd;

	if (n == 1)
		fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, FLAG_OPEN);
	else
		fd = open(name, O_WRONLY | O_APPEND | O_CREAT, FLAG_OPEN);
	if (fd < 0)
		return (-1);
	dup2(fd, out);
	close(fd);
	return (0);
}

static int			exec_input(int out, char *name)
{
	int			fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (-1);
	dup2(fd, out);
	close(fd);
	return (0);
}

static char			*heredoc_read_line(void)
{
	char		buf[2];
	char		*line;

	line = ft_strnew(1);
	buf[1] = 0;
	while (read(0, &buf, 1) != -1)
	{
		if (buf[0] == 0)
		{
			free(line);
			return (NULL);
		}
		if (buf[0] == '\n')
			return (line);
		line = ft_strjoinf(line, buf);
	}
	return (line);
}

static int			exec_heredoc(int out, char *name)
{
	int		fd;
	char	*line;
	char	*tmp;

	(void)out;
	tmp = ft_strnew(1);
	fd = open(".heredoc_tmp", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU | S_IRWXG);
	while (1)
	{
		if ((line = heredoc_read_line()) == NULL)
			break ;
		if (!ft_strcmp(line, name))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	return (exec_input(0, ".heredoc_tmp"));
}

int					wrapper_redir(t_list *lst, int out, char *name)
{
	int			op;

	op = lst->content_size;
	if (lst->next->content_size == 9)
	{
		exec_agreg(lst, out, op);
		return (0);
	}
	else if (lst->next->content_size != 9)
	{
		if (op == 5)
			return (exec_input(out, name));
		if (op == 6)
			return (exec_output(out, name, 1));
		if (op == 7)
			return (exec_heredoc(out, name));
		if (op == 8)
			return (exec_output(out, name, 2));
	}
	return (0);
}
