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

#include "../../../include/minishell.h"

void remove_part_str(char *str, const char *remove)
{
	char *pos = strstr(str, remove);
	if (pos != NULL) {
		ft_memmove(pos, pos + strlen(remove), strlen(pos + strlen(remove)) + 1);
	}
}

int builtin_cd(char **prompt)
{//OLDPWD working, but need to change oldpwd, it doesnt change for some reason

	if (!prompt || !prompt[0])
	{
		printf("\n");
		return (1);
	}
	if (!ft_strncmp(prompt[0], "cd", 2))
	{
		if (prompt[2])
		{
			printf("cd: too many arguments\n");
			return (1);
		}
		else if (!prompt[1])
			chdir(getenv("HOME"));
		else if (prompt[1][0] == '~')
		{
			chdir(getenv("HOME"));
			if (prompt[1][1])
			{
				remove_part_str(prompt[1], "~/");
				if (chdir(prompt[1]))
					printf("error changing directory\n");
			}
			return (1);
		}
		else if (prompt[1][0] == '-')
		{
			if (chdir(getenv("OLDPWD")))
				printf("error changing directory\n");
			return (1);
		}
		else
		{
			if (chdir(prompt[1]))
			{
				printf("error changing directory\n");
				g_shell.exit = 127;
				return (1);
			}
		}
		return (1);
	}
	return (0);
}
