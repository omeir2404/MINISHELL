#include "minishell.h"

void ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void up_arrow(int sig)
{
    (void)sig;
    char *prev_command = history_get(history_length - 2)->line;
    if (prev_command != NULL) {
        rl_replace_line(prev_command, 0);
        rl_redisplay();
    }
}

void prepare_singals(t_shell *shell)
{
	shell->control_c.sa_handler = ctrl_c;
	sigaction(SIGINT, &shell->control_c, NULL);
	shell->control_back_slash.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &shell->control_back_slash, NULL);
	shell->up_arrow.sa_handler = up_arrow;
	sigaction(SIGUSR1, &shell->up_arrow, NULL);
}

void clean_dptr(char **_alocated)
{
	int pos;

	pos = 0;
	if(!_alocated)
		return;
	while (_alocated[pos])
	{
		free(_alocated[pos]);
		pos++;
	}
	free(_alocated);
}

void ml_lst_cmd_clean()
{

	t_commands *cur;
	t_commands *next;

	cur = sh()->command;
	while (cur)
	{
		next = cur->next;
		clean_dptr(cur->args);
		cur = next;
	}
}

void ml_env_fr()
{
	t_env *cur;
	t_env *next;

	cur = sh()->env;
	int i = 0;
	while (cur)
	{
		next = cur->next;
		free(cur->value);
		free(cur->var);
		free(cur);
		cur = next;
		i++;
	}
}
void leave(t_shell *shell, const char *msg, int fd)
{
	ml_env_fr();
	if(sh()->paths)
		clean_dptr(sh()->paths);
	if (sh()->input)
		free(sh()->input);
	if (sh()->current_path)
		free(sh()->current_path);
	if(msg)
		write(fd, msg, ft_strlen(msg));
	write(fd, "\n", 1);
	exit(shell->exit);
}
