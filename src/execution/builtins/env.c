/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:20:50 by oharoon           #+#    #+#             */
/*   Updated: 2023/09/04 16:56:25 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_env(t_env **list)
{
	t_env *current = *list;

	while (current != NULL)
	{
		printf("%s", current->var);
		if (ft_isprint(current->value[0]))
			printf("=%s\n", current->value);
		else 
			printf("\n");
		current = current->next;
	}
}

int builtin_env(void)
{
	char **matrix;
	matrix = ft_split(sh()->input, ' ');
    if (ft_strncmp(matrix[0], "env", ft_strlen("env")))
	    return (0);
    if (matrix[1])
    {
        printf("minishell: error: too many arguments");
        return (1);
    }
	print_env(&sh()->env);
	return (1);
}