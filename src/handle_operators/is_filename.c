/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_filename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:07:45 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/27 10:08:42 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_filename(char *f, t_utils *data)
{
	if (!f)
	{
		ft_printf("No such file or directory\n");
		data->exec_status = 1;
		return (0);
	}
	return (1);
}
