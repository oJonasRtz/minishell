/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_signal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:49:44 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/30 14:51:25 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_command(int signal)
{
	t_data	*minishell;

	minishell = get_minishell();
	call_clean(minishell, minishell->flags.shoud_restore);
	clean_program(&minishell->utils);
	if (signal == SIGINT)
		exit(130);
	else if (signal == SIGQUIT)
		exit(131);
}

void	handle_command_signal(void)
{
	signal(SIGINT, handle_command);
	signal(SIGQUIT, handle_command);
}
