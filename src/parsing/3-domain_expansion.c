/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-domain_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:24:54 by jonas             #+#    #+#             */
/*   Updated: 2025/03/26 16:53:17 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_after(char *str, int i)
{
	if (!ft_strncmp(str, "$?", 2))
		return (ft_strdup(&str[2]));
	i++;
	while (str[i] && str[i] != '$' && str[i] != '\"' && str[i] != ' ')
		i++;
	return (ft_strdup(&str[i]));
}

static char	*put_together(char *prev, char *expand, char *after)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(prev, expand);
	if (!temp)
		return (NULL);
	ft_double_free(prev, expand);
	temp2 = ft_strjoin(temp, after);
	ft_double_free(temp, after);
	return (temp2);
}

static char	*make_replacement(char *str, char *expand, int *i)
{
	char	*exp;
	char	*prev;
	char	*after;

	prev = ft_strndup(str, *i);
	after = get_after(str, *i);
	if (expand)
		exp = put_together(prev, expand, after);
	else
	{
		exp = ft_strjoin(prev, after);
		ft_double_free(prev, after);
	}
	if (!exp)
		return (str);
	*i = -1;
	free(str);
	return (exp);
}

char	*domain_expansion(char *str, t_id id, t_data *data)
{
	char	*expand;
	int		i;

	if ((!str || !data) || str[0] == '\'')
		return (str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			expand = make_expansion(str, data, i, id);
			str = make_replacement(str, expand, &i);
		}
	}
	return (str);
}
