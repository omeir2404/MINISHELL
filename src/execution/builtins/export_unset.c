/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:08:45 by oharoon           #+#    #+#             */
/*   Updated: 2023/10/21 18:25:15 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void remove_node(t_env **head, char *content)
{
	t_env *current = *head;
	t_env *previous = NULL;

	// Find the node with the given value
	while (current->next != NULL && ft_strncmp(current->vars[0], content, ft_strlen(current->vars[0])))
	{
		previous = current;
		current = current->next;
	}
	// If the node was found, update pointers to remove it
	if (current != NULL)
	{
		if (previous != NULL)
			previous->next = current->next;
		else
			*head = current->next;
		free(current);
	}
}

int	check_repetition(t_env *new)
{
	t_env *temp;

	temp = g_shell.env;
	if (new->vars[0][0] == '=')
	{
		printf("minishell: %s is not a valid identifier\n", new->vars[0]);
		return (1);
	}
	while (temp)
	{
		if (!ft_strncmp(temp->vars[0], new->vars[0], ft_strlen(temp->vars[0])))
		{
			if (ft_isprint(new->value[0]))
			{
				printf("\n\n\n%s\n\n\n",new->value);
				temp->value = new->value;
			}
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void print_export_env(t_env **list)
{
	t_env *current = *list;

	while (current != NULL) {
		printf("declare -x %s", current->vars[0]);
		if (ft_isalpha(current->value[0]))
			printf("=\"%s\"\n", current->value);
		else 
			printf("\n");
		current = current->next;
	}

	// printf("\n");
}

int builtin_export(char **prompt)
{
	int i = 1;
	t_env	*new;
	
	if (ft_strncmp(prompt[0], "export", 7))
		return (0);
	if (!prompt[i])
	{
		print_export_env(&g_shell.env);
		return (1);
	}
	while (prompt[i])
	{
		new = ft_env_add(prompt[i]);
		if (check_repetition(new) == 0)
			ft_ml_envadd_back(&g_shell.env, new);
		i++;
	}
	return (1);
}

int builtin_unset(char **prompt)
{
	int i = 0;

	if (ft_strncmp(prompt[0], "unset", 6))
		return (0);
	if (!prompt[i])
		return (1);
	while (prompt[++i])
		remove_node(&g_shell.env, prompt[i]);
	return (1);
}
