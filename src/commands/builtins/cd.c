// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cd.c                                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/14 14:45:01 by oharoon           #+#    #+#             */
// /*   Updated: 2023/08/14 15:04:57 by oharoon          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../include/minishell.h"

int builtin_cd(char *prompt)
{
	char **matrix;
	char *path;

	// printf("\n\n\n%s\n\n\n", prompt);
	matrix = ft_split(prompt, ' ');
	if (!ft_strncmp(matrix[0], "cd", 2))
	{
		if (matrix[2])
		{
			printf("cd: too many arguments\n");
			return (1);
		}
		else if (!matrix[1])
			chdir(getenv("HOME"));
		else
		{
			path = matrix[1];
			if (chdir(path))
			{
				printf("error changing directory\n");
				return (1);
			}
		}
		return (1);
	}
	return (0);
}
