/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:25:43 by pvital-m          #+#    #+#             */
/*   Updated: 2023/08/12 18:25:44 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ml_lst_nenv_add(char *content)
{
	int		i;
	t_env	*new;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	while (content[i] != '=' && content[i])
		i++;
	new->var = ft_substr(content, 0, (i));
	new->value = ft_substr(content, i + 1, ft_strlen(&content[i]));
	new->var_len = ft_strlen(new->var);
	new->next = NULL;
	return (new);
}

t_env	*last_ptr(t_env *head)
{
	if (!head)
		return (NULL);
	while (head)
	{
		if (!head->next)
			return (head);
		head = head->next;
	}
	return (head);
}
void	ml_env_addl_elem(t_env **lst, t_env *_new, int unset)
{
	t_env *last;

	if (lst == NULL || _new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = _new;
		return ;
	}
	last = last_ptr(*lst);
	last->next = _new;
	_new->unset = unset;
}