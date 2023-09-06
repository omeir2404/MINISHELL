/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:27:06 by pvital-m          #+#    #+#             */
/*   Updated: 2023/08/14 15:44:07 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	swich_element(char a)
{
	if (a == '\"')
		return ('\2');
	else if (a == '\'')
		return ('\3');
	else if (a == '|')
		return ('\4');
	else if (a == ' ')
		return ('\5');
	else if (a == ';')
		return ('\6');
	return (a);
}


void	ml_ps_quote_trigger_char(char token, t_mode *stat)
{
	if (token == '\'' && *stat == ENV_MODE_TOKEN)
		*stat = ENV_MODE_QUOTE;
	else if (token == '\'' && *stat == ENV_MODE_QUOTE)
		*stat = ENV_MODE_TOKEN;
	else if (token == '\"' && *stat == ENV_MODE_TOKEN)
		*stat = ENV_MODE_DQUOTE;
	else if (token == '\"' && *stat == ENV_MODE_DQUOTE)
		*stat = ENV_MODE_TOKEN;
}

/*
	Replace Tokens for the special Characters
*/
void	ml_input_changer(char *str)
{
	t_mode	*stat;
	t_mode	*old;
	int		index;

	stat = malloc(sizeof(t_mode));
	old = malloc(sizeof(t_mode));
	index = 0;
	*stat = ENV_MODE_TOKEN;
	*old = *stat;
	while (str[index])
	{
		*old = *stat;
		ml_ps_quote_trigger_char(str[index], stat);
		if((*stat == ENV_MODE_DQUOTE && *old == ENV_MODE_TOKEN))
			str[index] = swich_element(str[index]);
		else if((*stat == ENV_MODE_TOKEN && *old == ENV_MODE_DQUOTE))
			str[index] = swich_element(str[index]);
		else if((*stat == ENV_MODE_TOKEN && *old == ENV_MODE_TOKEN))
			str[index] = swich_element(str[index]);
		if((*stat == ENV_MODE_QUOTE && *old == ENV_MODE_TOKEN))
			str[index] = swich_element(str[index]);
		else if((*stat == ENV_MODE_TOKEN && *old == ENV_MODE_QUOTE))
			str[index] = swich_element(str[index]);
		else if((*stat == ENV_MODE_TOKEN && *old == ENV_MODE_TOKEN))
			str[index] = swich_element(str[index]);
		index++;
	}
	free(stat);
	free(old);
}
