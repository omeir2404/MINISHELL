// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exit.c                                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/14 14:45:01 by oharoon           #+#    #+#             */
// /*   Updated: 2023/08/14 15:04:57 by oharoon          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../include/minishell.h"

int builtin_exit(char *prompt)
{
	char **matrix;

	matrix = ft_split(prompt, ' ');
	if (!ft_strncmp(matrix[0], "exit", 5))
	{
        if (matrix[1])
            printf("minishell: exit: %s: numeric argument required", matrix[1]);
        leave(sh(), "exit", 1);
	}
	return (0);
}