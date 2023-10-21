/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:08:45 by oharoon           #+#    #+#             */
/*   Updated: 2023/09/06 18:27:14 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void remove_node(t_env **head, char *content)
{
	t_env *current = *head;
	t_env *previous = NULL;

	// Find the node with the given value
	while (current->next != NULL && ft_strncmp(current->var, content, ft_strlen(current->var)))
	{
		previous = current;
		current = current->next;
	}
	// If the node was found, update pointers to remove it
	if (current != NULL)
	{
		if (current->unset == 0)
		{
			free(current);
			return ;
		}
		if (previous != NULL)
			previous->next = current->next;
		else
			*head = current->next;
		free(current);
	}
}

// char *add_quotes(char *str)
// {
// 	char	*ret;
// 	int	i;

// 	i = 0;
// 	ret = malloc(sizeof(char) * (ft_strlen(str) + 3));
// 	ret[0] = '\"';
// 	while (str[i])
// 	{
// 		ret[i+1] = str[i];
// 		i++;
// 	}
// 	ret[i+1] = '\"';
// 	ret[i+2] = '\0';
// 	return (ret);
// }

// char	*ft_strjoin_equal(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		len1;
// 	int		len2;
// 	char	*str;

// 	if (s1 && s2)
// 	{
// 		len1 = ft_strlen((char *)s1);
// 		len2 = ft_strlen((char *)s2);
// 		str = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
// 		if (str == NULL)
// 			return (NULL);
// 		i = -1;
// 		while (s1[++i])
// 			str[i] = s1[i];
// 		// i++;
// 		str[i] = '=';
// 		i = -1;
// 		len1++;
// 		while (s2[++i])
// 		{
// 			str[len1] = s2[i];
// 			len1++;
// 		}
// 		str[len1] = '\0';
// 		return (str);
// 	}
// 	return (NULL);
// }

// int change_value(t_env *head, int index)
// {
// 	int		current_index;
// 	t_env	*current;
	
// 	if (index < 0)
// 		return (0);
// 	current_index = 0;
// 	current = head;
// 	while (current != NULL) {
// 		if (current_index == index)
// 		{
// 			current->value = 
// 			return (1);
// 		}
// 		current = current->next;
// 		current_index++;
// 	}
// 	return (0); // Index out of bounds
// }

int	check_repetition(t_env *new)
{
	t_env *temp;

	temp = sh()->env;
	if (new->var[0] == '=')
	{
		printf("minishell: %s is not a valid identifier\n", new->var);
		return (1);
	}
	while (temp)
	{
		if (!ft_strncmp(temp->var, new->var, ft_strlen(temp->var)))
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
		printf("declare -x %s", current->var);
		if (ft_isalpha(current->value[0]))
			printf("=\"%s\"\n", current->value);
		else 
			printf("\n");
		current = current->next;
	}

	// printf("\n");
}

int builtin_export(void)
{
	int i = 1;
	char **matrix;
	t_env	*new;
	
	matrix = ft_split(sh()->input, ' ');
	if (ft_strncmp(matrix[0], "export", 7))
		return (0);
	if (!matrix[i])
	{
		// execute_single_comand(shell, "env", shell->en);
		print_export_env(&sh()->env);
		return (1);
	}
	while (matrix[i])
	{
		new = ml_lst_nenv_add(matrix[i]);
		if (check_repetition(new) == 0)
			ml_env_addl_elem(&sh()->env, new, 1);
		i++;
	}
	return (1);
}

int builtin_unset(void)
{
	int i = 0;
	char **matrix;
	matrix = ft_split(sh()->input, ' ');
	if (ft_strncmp(matrix[0], "unset", 6))
		return (0);
	if (!matrix[i])
		return (1);
	while (matrix[++i])
		remove_node(&sh()->env, matrix[i]);
	return (1);
}
