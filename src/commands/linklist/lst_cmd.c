/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:26:13 by pvital-m          #+#    #+#             */
/*   Updated: 2023/08/14 17:29:04 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*ml_cmd_fr_lst(t_commands **head)
{
	t_commands	*next;
	t_commands	*cur;

	next = NULL;
	cur = *head;
	if (!*head)
		return (NULL);
	while (cur)
	{
		next = cur->next;
		clean_dptr(cur->args);
		free(cur);
		cur = next;
	}
	*head = NULL;
	return (NULL);
}

t_commands	*ml_cmd_add_one(char *cmd)
{
	t_commands	*new;

	if(!cmd)
		return NULL;
	new = malloc(sizeof(t_commands));
	if (!new)
		return (NULL);
	new->args = ft_split(cmd, TOKEN_SPACE);
	new->redirect = NULL;
	new->next = NULL;
	return (new);
}

/*
	Add a Command for the list
*/

t_commands	*ml_cmd_last_pos(t_commands *head)
{
	t_commands	*local;

	if (!head)
		return (NULL);
	local = head;
	while (local->next)
		local = local->next;
	return (local);
}
/*
	Create a link list with the command separacted with the pipe
*/
void	*ml_cmd_add_lst(t_commands **head, t_commands *_node)
{
	t_commands *backup_head = *head;
	if (!*head)
	{
		*head = _node;
		return (backup_head);
	}
	t_commands *lst = ml_cmd_last_pos(*head);
	if (!lst)
	{
		free(_node);
		return (backup_head);
	}
	lst->next = _node;
	return (backup_head);
}