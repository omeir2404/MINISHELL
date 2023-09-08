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
{//fix for $OLDPWD, cd - should go to the prvious pwd
	char **matrix;
	char *path;
	
	matrix = ft_split(prompt, ' ');
	void remove_part_str(char *str, const char *remove)
	{
		char *pos = strstr(str, remove);
		if (pos != NULL) {
			ft_memmove(pos, pos + strlen(remove), strlen(pos + strlen(remove)) + 1);
		}
	}
	if (!ft_strncmp(matrix[0], "cd", 2))
	{
		if (matrix[2])
		{
			printf("cd: too many arguments\n");
			return (1);
		}
		else if (!matrix[1])
			chdir(getenv("HOME"));
		else if (matrix[1][0] == '~')
		{
			chdir(getenv("HOME"));
			if (matrix[1][1])
			{
				remove_part_str(matrix[1], "~/");
				if (chdir(matrix[1]))
					printf("error changing directory\n");
			}
			return (1);
		}
		else if (matrix[1][0] == '-')
		{
			if (chdir("$OLDPWD"))
				printf("error changing directory\n");
			return (1);
		}
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
