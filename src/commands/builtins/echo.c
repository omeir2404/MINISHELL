/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:51:10 by oharoon           #+#    #+#             */
/*   Updated: 2023/10/21 14:31:48 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_sizer(int start_index, char *str)
{
	int	i = start_index;
	while ((str[i] != ' ' || str[i] != '	') && str[i])
		i++;
	return (i - start_index);
}

char	*ft_str_toupper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 96 && str[i] < 123)
			str[i] -= 32;
		i++;
	}
	return (str);
}

int builtin_echo(void)
{
    int i;
	int	env_size;
	char	*env_var;
	int	aux;

    i = 0;
	env_var = NULL;
	aux = 0;
	env_size = 0;
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
			if (sh()->input[i] == '$' && sh()->input[i + 1] == '?')
			{
				printf("%d", sh()->exit);
				i += 2;
			}
			else if(sh()->input[i] == '$')
			{
				env_size = env_sizer(i, sh()->input);
				env_var = malloc(sizeof(char) * env_size);
				i++;
				while(aux < env_size)
				{
					env_var[aux] = sh()->input[i + aux];
					aux++;
				}
				printf("%s", getenv(ft_str_toupper(env_var)));
				i +=env_size;
			}
			else
			{
				printf("%c",sh()->input[i]);
				i++;
			}
		}
		if (break_line == 0)
			printf("\n");
		sh()->exit = 0;
        return (1);
    }

    return (0);
}