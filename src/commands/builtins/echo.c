/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:51:10 by oharoon           #+#    #+#             */
/*   Updated: 2023/09/06 18:59:10 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int builtin_echo(void)
{
    int i;

    i = 0;
    if (!ft_strncmp(sh()->input, "echo", ft_strlen("echo")))
	{
		i += 4;
		int break_line = 0;
		while(sh()->input[i] == 32)
			i++;
		if (sh()->input[i] == '-' && sh()->input[i+1] == 'n')
		{
			break_line = 1;
			i += 2;
		}
		while(sh()->input[i] == 32)
			i++;
		while(sh()->input[i])
		{
			if (sh()->input[i] == '$' && sh()->input[i+1] == '?')
			{
				printf("%d", sh()->exit);
				i += 2;
			}
			printf("%c",sh()->input[i]);
			i++;
		}
		if (break_line == 0)
			printf("\n");
		sh()->exit = 0;
        return (1);
    }
    return (0);
}