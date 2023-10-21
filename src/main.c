#include "minishell.h"

struct s_shell g_shell;

void execution(char *input)
{
	t_cmds *cmds;

	switch_caracters(input);
	cmds = ft_buildlst(input);
	software(cmds);
	CommandDisplay(cmds);
	
	clean_commands(&cmds);
	free(input);
}
	// if (sh()->current_path)
		// free(sh()->current_path);
//	sh()->current_path = get_path(sh()->input, sh()->en);

//	execute_single_comand(sh(), sh()->current_path, sh()->en);

void prompt(void)
{
	char *input;
	input = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			if (input)
				free(input);
			ft_env_delete(&g_shell.env);
			write(1, "Exit\n", 6);
			exit(0);
		}
		add_history(input);
		ft_syntax_checker(input);
		execution(input);
	}
}

int main(int c, char **v, char **envp)
{
	(void)c;
	(void)v;
	g_shell.env = set_env(envp);
	g_shell.exit = 0;
	rl_catch_signals = 0;
	ft_ml_sigdefault();
	prompt();
	printf("%sDIOS%s", GRN, RESET);
	return (0);
}