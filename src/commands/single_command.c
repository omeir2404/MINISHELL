/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:34:25 by oharoon           #+#    #+#             */
/*   Updated: 2023/08/22 17:10:32 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_redirects_to_zero(void)
{
	sh()->redirect.infile = NULL;
	sh()->redirect.outfile = NULL;
	sh()->redirect.output = 0;
	sh()->redirect.input = 0;
}

int	execute_single_comand(t_shell *shell, char *path, char  **env)
{
	char	**split_comand;
	(void) shell;
	pid_t   pid;
	// int stat;

	// if (ft_strncmp(path, "history", 7) == 0)
	// {
	// 	print_list(shell->comands);
	// 	return (0);
	// }

	printf("here is the comand: %s\n", path);
	pid = fork();
	if (pid == 0)
	{
		// path = get_path(split_comand[0], env);
		split_comand = ft_split(path, ' ');
		if (!split_comand)
		{
			printf("error\n");
			return (1);
		}
		if (sh()->redirect.outfile && sh()->redirect.output)
		{
			dup2(sh()->redirect.output, STDOUT_FILENO);
			close(sh()->redirect.output);
		}
		if (sh()->redirect.infile && sh()->redirect.input)
		{
			dup2(sh()->redirect.input, STDIN_FILENO);
			close(sh()->redirect.input);
		}
		// redirect_funct();// seperate comand from file!
		if (execve(path, split_comand, env) == -1)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(split_comand[0], 2);
			// free_matrix(split_comand);
			exit(127);
		}
	}
	else if (pid > 0)
	{
		int child_status;
		waitpid(pid, &child_status, 0); // Wait for the specific child process to exit
		if (WIFEXITED(child_status))
		{
		   shell->exit = WEXITSTATUS(child_status);
			// printf("Child process exited with status: %d\n", exit_status);
		}
	} 
	// printf("\n");
	// shell->status = wait(0);
	// printf("loool: %d\n", shell->status);
	// dup2(STDOUT_FILENO, sh()->redirect.output);
	// dup2(STDIN_FILENO, sh()->redirect.input);
	set_redirects_to_zero();
	return (0);
}