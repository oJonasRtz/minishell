/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8-restore_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:31:48 by jonas             #+#    #+#             */
/*   Updated: 2025/03/24 18:41:11 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_redirect(int original[2], t_data *data)
{
	if ((original[0] < 0 || original[1] < 0))
		return ;
	make_redir(original[0], 0);
	make_redir(original[1], 1);
	data->utils.can_read = true;
	data->utils.can_write = true;
	data->flags.shoud_restore = !data->flags.shoud_restore;
}

t_ast	*find_cmd2(t_ast **root)
{
	if (isredir((*root)->id))
		return (*root);
	return (find_cmd(root));
}
