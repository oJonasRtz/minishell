/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-clean_locals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:11:19 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/13 21:45:07 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_locals(t_localvar	*var)
{
	if (!var)
		return ;
	if (var->next)
		clean_locals(var->next);
	free(var->name);
	free(var->value);
	free(var);
}

t_localvar	*init_local(void)
{
	t_localvar	*new;

	new = ft_calloc(sizeof(t_localvar), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
