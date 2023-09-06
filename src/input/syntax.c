#include "minishell.h"

bool report_error(int mode, int c)
{
	if (c == '|' && mode != 0)
		ERR(2, PIPE_SYNTAX_ERROR);
	if (c == '<' && mode != 0)
		ERR(2, IN_SYNTAX_ERROR);
	if (c == '>' && mode != 0)
		ERR(2, OUT_SYNTAX_ERROR);
	return true;
}

static bool skip(char *str, char c, int mode)
{
	while (!ft_isalnum(*str) && *str)
		str++;
	if (!*str)
	{
		report_error(mode, c);
		return (true);
	}
	return (false);
}

bool report_syntax(int mode, char c, char *str)
{
	if (!mode)
		return (false);
	else if (mode)
	{
		if (!*str)
			return report_error(mode, c);
		while (*str)
		{
			if (mode == 1)
			{
				if (!(*(str + 1)))
					return report_error(mode, c);
				else
					return (skip(str, c, mode));
			}
			str++;
		}
	}
	return (false);
}

/*
	mode
	1 = token
	2 = double quote
	3 = single quote
*/
static bool report(char c, char *str, t_mode *stat)
{
	int mode;

	if (c == '\"')
		mode = 2;
	else if (c == '\'')
		mode = 3;
	else if (*stat == ENV_MODE_TOKEN && (c == '|' || c == '<' || c == '>'))
		mode = 1;
	else
		mode = 0;
	return (report_syntax(mode, c, str));
}

bool ml_register_syntax_report(char *str)
{
	t_mode stat;
	char target;

	stat = ENV_MODE_TOKEN;
	while (*str)
	{
		ml_ps_quote_trigger_char(*str, &stat);
		if (stat == ENV_MODE_TOKEN && (*str == '|' || *str == '<' || *str == '>'))
		{
			target = *str;
			++str;
			if (report(target, str, &stat))
				return true;
		}
		str++;
	}
	return (false);
}