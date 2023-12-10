/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quote_Parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:52:20 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/06 00:52:21 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse(t_cmds *node, t_shell *sh)
{
	t_cmds	*command;

	command = node;
	while (command)
	{
		redirection(command, sh);
		command = command->next;
	}
}

void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\1' || str[i] == '\2')
			i++;
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}
