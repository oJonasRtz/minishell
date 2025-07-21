/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1-manage_redir_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:11:48 by jonas             #+#    #+#             */
/*   Updated: 2025/03/24 15:56:48 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	*save_origin(t_data *data)
// {
// 	int	cpy[2];
// 	int	*new;

// 	cpy[0] = dup(0);
// 	cpy[1] = dup(1);
// 	new = (int *)cpy;
// 	data->flags.shoud_restore = !data->flags.shoud_restore;
// 	return (new);
// }

int	*save_origin(int fd[2], t_data *data)
{
	fd[0] = dup(0);
	if (fd[0] < 0)
	{
		fd[0] = -1;
		fd[1] = -1;
		return (NULL);
	}
	fd[1] = dup(1);
	if (fd[1] < 0)
	{
		close (fd[0]);
		fd[0] = -1;
		fd[1] = -1;
		return (NULL);
	}
	data->flags.shoud_restore = !data->flags.shoud_restore;
	return (fd);
}

void	destroy_fd(int fd[2])
{
	if (!fd || !*fd)
		return ;
	close (fd[0]);
	close (fd[1]);
}

void	make_redir(int fd, int fd2)
{
	if (fd < 0 || fd2 < 0)
		return ;
	dup2(fd, fd2);
	close (fd);
}

char	*find_fd(t_token **token)
{
	t_token	*temp;

	if (!*token)
		return (NULL);
	temp = *token;
	while (temp)
	{
		if (temp->id == FD || temp->id == LIMITER)
			return (temp->str);
		temp = temp->next;
	}
	return (NULL);
}

int	switch_redir(t_token **token, t_data *data)
{
	int		fd;
	char	*name;

	if (!*token || !data)
		return (-1);
	name = find_fd(token);
	fd = -1;
	fd = redir_out(name, (*token)->id, data);
	if (fd < 0 && fd != INT_MIN)
		fd = redir_in(name, (*token)->id, token, data);
	return (fd);
}
