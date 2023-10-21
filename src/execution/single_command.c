/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:34:25 by oharoon           #+#    #+#             */
/*   Updated: 2023/10/21 16:32:02 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	set_redirects_to_zero(void)
// {
// 	sh()->redirect.infile = NULL;
// 	sh()->redirect.outfile = NULL;
// 	sh()->redirect.output = 0;
// 	sh()->redirect.input = 0;
// }

int	execute_single_comand(struct s_cmd *command)
{
	// char	**split_comand;
	pid_t   pid;

	printf("here is the comand: %s\n", command->args[0]);
	pid = fork();
	if (pid == 0)
	{
		// split_comand = ft_split(path, ' ');
		// if (!split_comand)
		// {
		// 	printf("error\n");
		// 	return (1);
		// }
		// if (sh()->redirect.outfile && sh()->redirect.output)
		// {
		// 	dup2(sh()->redirect.output, STDOUT_FILENO);
		// 	close(sh()->redirect.output);
		// }
		// if (sh()->redirect.infile && sh()->redirect.input)
		// {
		// 	dup2(sh()->redirect.input, STDIN_FILENO);
		// 	close(sh()->redirect.input);
		// }

		if (execve(command->args[0], command->args, NULL) == -1)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(command->args[0], 2);
			exit(127);
		}
	}
	else if (pid > 0)
	{
		int child_status;
		waitpid(pid, &child_status, 0); // Wait for the specific child process to exit
		if (WIFEXITED(child_status))
		   g_shell.exit = WEXITSTATUS(child_status);
	}

	// set_redirects_to_zero();
	return (0);
}