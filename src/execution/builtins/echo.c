/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:51:10 by oharoon           #+#    #+#             */
/*   Updated: 2023/10/21 19:08:35 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// int	env_sizer(int start_index, char *str)
// {
// 	int	i = start_index;
// 	while ((str[i] != ' ' || str[i] != '	') && str[i])
// 		i++;
// 	return (i - start_index);
// }

// char	*ft_str_toupper(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] > 96 && str[i] < 123)
// 			str[i] -= 32;
// 		i++;
// 	}
// 	return (str);
// }

int builtin_echo(char **prompt)
{
    int i;
	int	word;

	word = 1;
    i = 0;
    if (!ft_strncmp(prompt[0], "echo", ft_strlen("echo")))
	{
		int break_line = 0;
		if (!prompt[1])
		{
			printf("\n");
			return (1);
		}
		else 
		{
			if (prompt[word][i] == '-' && prompt[word][i+1] == 'n')
			{
				break_line = 1;
				i = 0;
				word++;
			}
			while(prompt[word])
			{
				while(prompt[word][i])
				{
					if (prompt[word][i] == '$' && prompt[word][i + 1] == '?')
					{
						printf("%d", g_shell.exit);
						i += 2;
					}
					else
					{
						printf("%c",prompt[word][i]);
						i++;
					}
				}
				printf(" ");
				word++;
				i = 0;
			}
			if (break_line == 0)
				printf("\n");
			g_shell.exit = 0;
			return (1);
		}
    }

    return (0);
}