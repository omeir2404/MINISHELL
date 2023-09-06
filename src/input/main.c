#include "minishell.h"

bool ml_syntax_check(char *cmd)
{
	t_mode stat;
	int index;

	stat = ENV_MODE_TOKEN;
	index = -1;
	while (cmd[++index])
		ml_ps_quote_trigger_char(cmd[index], &stat);
	if (stat != ENV_MODE_TOKEN)
		return (true);
	return (false);
}

void ml_build_cmd(t_shell *shell, char **ptr)
{
	int selector;
	char *trimmed;

	selector = 0;
	while (ptr[selector])
	{
		trimmed = ft_strtrim(ptr[selector], "\2");
		ml_cmd_add_lst(&shell->command, ml_cmd_add_one(trimmed));
		free(trimmed);
		selector++;
	}
}

// static void ml_cache_cleaner(char *input, char **individual_cmd,
// 							 t_shell *center)
// {
// 	if (input)
// 		free(input);
// 	if (center->command)
// 		ml_cmd_fr_lst(&center->command);
// 	if (individual_cmd)
// 		clean_dptr(individual_cmd);
// 	input = NULL;
// 	individual_cmd = NULL;
// }

void execution(t_shell *shell, char *user_in)
{
	// char **commands;

	// commands = NULL;
	(void)shell;
	(void)user_in;
	// if (ml_register_syntax_report(user_in))
	// 	return;
	// ml_input_changer(user_in);
	// commands = ft_split(user_in, TOKEN_PIPE);
	// if (!commands)
	// 	return;
	if (sh()->current_path)
		free(sh()->current_path);
	// redirect_funct();// seperate comand from file!
	sh()->current_path = get_path(sh()->input, sh()->en);
	// ml_build_cmd(shell, commands);
	execute_single_comand(sh(), sh()->current_path, sh()->en);
	// ml_cache_cleaner(user_in, commands, shell);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	system("clear");
	printf("Welcome to MiniShell! %s\n", VERSION);
	setup_omeir(env);
	if (ml_lst_env_setup())
		leave(sh(), "Error, Setting the env list", 2);
	while (1)
	{
		sh()->input = readline("Minishell >");
		if (sh()->input == NULL)
			leave(sh(), "exit", 1);
		if (builtins() == 0)
			execution(sh(), sh()->input);
	}
	return (0);
}