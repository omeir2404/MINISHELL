#include "minishell.h"

t_shell	*sh(void)
{
	static t_shell	shell;

	return (&shell);
}

void	prepare_redirect()
{
	
	sh()->redirect.infile = NULL;
	sh()->redirect.outfile = NULL;
	sh()->redirect.input = 0;
	sh()->redirect.output = 0;
}

int	setup_omeir(char **env)
{
	// static int index;

	sh()->env = NULL;
	sh()->en = env;
	sh()->exit = 0;
	sh()->input = NULL;
	sh()->paths = NULL;
	sh()->command = NULL;
	prepare_singals(sh());
	prepare_redirect();
	// addpath(&sh()->env, sh()->en, index + 1);
	return (0);
}

void	ml_ps_quote_trigger(char token, t_mode *stat)
{
	if (token == TOKEN_QUOTE && *stat == ENV_MODE_TOKEN)
		*stat = ENV_MODE_QUOTE;
	else if (token == TOKEN_QUOTE && *stat == ENV_MODE_QUOTE)
		*stat = ENV_MODE_TOKEN;
	else if (token == TOKEN_DQUOTE && *stat == ENV_MODE_TOKEN)
		*stat = ENV_MODE_DQUOTE;
	else if (token == TOKEN_DQUOTE && *stat == ENV_MODE_DQUOTE)
		*stat = ENV_MODE_TOKEN;
}