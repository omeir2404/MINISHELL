/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:27:04 by oharoon           #+#    #+#             */
/*   Updated: 2023/08/15 14:43:25 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ml_ps_str_var_index(const char *str)
{
	t_mode	stat;
	int		i;

	stat = ENV_MODE_TOKEN;
	if (!str)
		return (-1);
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		ml_ps_quote_trigger(str[i], &stat);
		if (str[i] == '$' && (stat == ENV_MODE_TOKEN
				|| stat == ENV_MODE_DQUOTE))
			return (i);
		i--;
	}
	return (-1);
}

int	ml_ps_var_counter(const char *str)
{
	int		i;
	int		num_of_var;
	t_mode	stat;

	i = 0;
	num_of_var = 0;
	stat = ENV_MODE_TOKEN;
	if (!str)
		return (0);
	while (str[i])
	{
		ml_ps_quote_trigger(str[i], &stat);
		if (str[i] == '$' && (stat == ENV_MODE_TOKEN
				|| stat == ENV_MODE_DQUOTE))
			num_of_var++;
		// printf("%c | %d | %d\n", str[i], num_of_var, stat);
		i++;
	}
	return (num_of_var);
}

void	*ml_ps_var_replacer(char **target, t_env *var, int pos, int len)
{
	char	*new;
	int		i;
	int		k;
	int		j;

	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	k = 0;
	while (i < pos)
	{
		new[i] = (*target)[i];
		i++;
	}
	k = i + var->var_len + 1;
	j = 0;
	while (var->value[j])
		new[i++] = var->value[j++];
	while ((*target)[k])
	{
		new[i] = (*target)[k];
		i++;
		k++;
	}
	new[i] = '\0';
	(*target) = new;
	return (NULL);
}

char	*ml_rep_var_parser(char *str, t_env *vars)
{
	int		len;
	char	*varname;
	t_env	*tmp;

	int i, j = i = j = 0;
	if (!str)
		return (NULL);
	len = 0;
	varname = NULL;
	i = ml_ps_str_var_index(str);
	if (i == -1)
		return (str);
	tmp = vars;
	while (tmp)
	{
		varname = ft_substr(str, i + 1, tmp->var_len);
		if (ft_strcmp(varname, tmp->var) == 0)
		{
			len = (int)ft_strlen(str) - tmp->var_len + ft_strlen(tmp->value);
			ml_ps_var_replacer(&str, tmp, i, len);
			return (str);
		}
		free(varname);
		tmp = tmp->next;
	}
	return (str);
}

void	ml_ps_var_parser(t_commands *lst, t_env *vars)
{
	int counter;
	int i = 0;
	;

	if (!lst)
	{
		printf("There is no command to register\n");
		return ;
	}
	t_commands *local = lst;
	int index = 0;
	if (!vars || !lst)
		return ;
	while (local)
	{
		index = 0;
		while (local->args[index])
		{
			counter = ml_ps_var_counter(local->args[index]);
			i = 0;
			while (i < counter)
				i++;
			index++;
		}
		local = local->next;
	}
	(void)(vars);
}