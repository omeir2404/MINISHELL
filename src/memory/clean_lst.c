#include "minishell.h"

t_commands	*ml_cmd_lst_last(t_commands **head)
{
	t_commands *local;

	local = *head;
	if (!*head)
		return (NULL);
	while (local->next)
		local = local->next;
	return (local);
}
void	ml_lst_env_clean(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		*env = tmp->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
		tmp = *env;
	}
}