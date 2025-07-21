/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:51:02 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/27 17:45:42 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	permission_case(int *pipefd, t_ast **root, t_data *data, int flag)
{
	if (check_is_directory_fd((*root)->cmd[0], &data->utils))
	{
		if (flag == 1)
			close_descriptors(pipefd, 1, data);
		else if (flag == 0)
			close_descriptors(pipefd, 0, data);
		exit(126);
	}
	if (ft_strcmp((*root)->cmd[0], "sudo") == 0)
	{
		if (flag == 1)
			close_descriptors(pipefd, 1, data);
		else if (flag == 0)
			close_descriptors(pipefd, 0, data);
		exit(126);
	}
}
