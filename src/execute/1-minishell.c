/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/26 12:25:07 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	case_builtins_op(char *cmd)
// {
// 	if (ft_strcmp(cmd, "cd") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "export") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "unset") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "pwd") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "env") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "echo") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "exit") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "clear") == 0)
// 		return (1);
// 	return (0);
// }

static int	exec_multi_cmd(t_ast **root, t_data *data)
{
	t_ast	*ast;
	int		fd[2];

	if (!*root || !data)
		return (1);
	fd[0] = -1;
	fd[1] = -1;
	ast = *root;
	if (isredir(ast->id) && find_cmd(&ast))
	{
		save_origin(fd, data);
		if (manage_redir(&ast, &data->token, data))
		{
			if (data->flags.shoud_restore)
				restore_redirect(fd, data);
			return (1);
		}
	}
	if (ast->id != CMD)
	{
		exec_multi_cmd(&ast->left, data);
		exec_multi_cmd(&ast->right, data);
	}
	exec_pipe(&ast, data, fd);
	return (0);
}

int	minishell(t_ast **root, t_data *data)
{
	t_ast	*ast;

	if (!data)
		return (1);
	ast = *root;
	if (ast->id == PIPE)
		exec_multi_cmd(&ast, data);
	exec_single_cmd(&ast, data);
	start_echo();
	close_all_fds();
	return (0);
}
