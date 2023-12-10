/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redirection.functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:59:38 by pedro             #+#    #+#             */
/*   Updated: 2023/12/07 20:59:50 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	t_redirection_has_hd(t_redirections *lst)
{
	while (lst)
	{
		if (lst->mode == FILE_IN_HEREDOC)
			return (true);
		lst = lst->next;
	}
	return (false);
}
