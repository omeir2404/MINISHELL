#include "minishell.h"

int	ml_lst_env_setup(void)
{
	extern char **environ;
	int i;

	i = 0;
	if (sh()->env)
	{
		ml_lst_env_clean(&sh()->env);
		sh()->env = NULL;
	}
	while (environ[i])
	{
		ml_env_addl_elem(&sh()->env, ml_lst_nenv_add(environ[i]), 0);
		i++;
	}
	if (!sh()->env)
		return (1);
	return (0);
}