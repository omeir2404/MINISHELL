// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   path.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/27 17:25:46 by oharoon           #+#    #+#             */
// /*   Updated: 2023/08/17 18:36:05 by oharoon          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/minishell.h"


// t_env *lstfinal(t_env *_link_list)
// {
//     if(!_link_list)
//         return NULL;
//     while(_link_list->next)
//         _link_list = _link_list->next;
//     return _link_list;
// }


// t_env *newnode(char *str, int i)
// {
//     t_env *new;
//     new = (t_env *)malloc(sizeof(t_env));
//     if(!new)
//         return NULL;
//     new->value = ft_strdup(str);
//     new->var_len = i;
//     new->next = NULL;
//     return new;
// }

// void addlast(t_env **head, char *str, int index)
// {
//     t_env *new;
//     t_env *last;
//     new = newnode(str, index);
//     if(!new)
//         return;
//     if(!*head)
//     {
//         *head = new;
//         return;
//     }
//     last = lstfinal(*head);
//     last->next = new;
// }


// void	addpath(t_env **head, char **env, int index)
// {
// 	int i = 0;
//     while(env[i])
//     {
//        addlast(head, env[i], index);
//         i++;
//     }
// }

// void	free_matrix(char **matrix)
// {
// 	size_t	i;

// 	i = 0;
// 	while (matrix[i])
// 	{
// 		free(matrix[i]);
// 		i++;
// 	}
// 	free(matrix);
// }


// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dstsize != 0)
// 	{
// 		while (src[i] != '\0' && i < (dstsize - 1))
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	while (src[i])
// 		i++;
// 	return (i);
// }

// int	word_count(char const *s, char c)
// {
// 	int	word;
// 	int	is_c;

// 	word = 0;
// 	is_c = 0;
// 	while (*s)
// 	{
// 		if (*s != c && is_c == 0)
// 		{
// 			is_c = 1;
// 			word++;
// 		}
// 		else if (*s == c)
// 			is_c = 0;
// 		s++;
// 	}
// 	return (word);
// }

// char	*create_str(char *str, int i, char **lst, char c)
// {
// 	int		count;
// 	char	*s;

// 	count = 0;
// 	while (*str == c && *str)
// 		str++;
// 	while (str[count] && str[count] != c)
// 		count++;
// 	s = malloc (sizeof(char ) * (count + 1));
// 	if (!s)
// 		return (NULL);
// 	ft_strlcpy(s, str, count + 1);
// 	lst[i] = s;
// 	return (str + count);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**array;
// 	int		index;
// 	int		size;
// 	char	*temp;

// 	index = -1;
// 	size = word_count(s, c);
// 	array = malloc(sizeof(char *) * (size + 1));
// 	if (!s || !array)
// 		return (0);
// 	temp = (char *)s;
// 	while (++index < size)
// 		temp = create_str(temp, index, array, c);
// 	array[size] = NULL;
// 	return (array);
// }

// char	*my_getenv(const char *name, char **env)
// {
// 	int		i;
// 	size_t	name_len;

// 	i = 0;
// 	name_len = ft_strlen(name);
// 	while (env[i] != NULL)
// 	{
// 		if ((ft_strncmp(env[i], name, name_len) == 0)
// 			&& (env[i][name_len] == '='))
// 			return (env[i] + name_len + 1);
// 		i++;
// 	}
// 	return (NULL);
// }

// // char	*get_path(char *comand, char **env)
// // {
// // 	int		i;
// // 	char	*exec;
// // 	char	**allpath;
// // 	char	*path_part;
// // 	char	**split_comand;

// // 	i = -1;
// // 	allpath = ft_split(my_getenv("PATH", env), ':');
// // 	split_comand = ft_split(comand, ' ');
// // 	while (allpath[++i])
// // 	{
// // 		path_part = ft_strjoin(allpath[i], "/");
// // 		exec = ft_strjoin(path_part, split_comand[0]);
// // 		if (path_part)
// // 			free(path_part);
// // 		if (access(exec, F_OK | X_OK) == 0)
// // 		{
// // 			free_matrix(split_comand);
// // 			return (exec);
// // 		}
// // 		if (exec)
// // 			free(exec);
// // 	}
// // 	if (allpath)
// // 		free_matrix(allpath);
// // 	if (split_comand)
// // 		free_matrix(split_comand);
// // 	return (comand);
// // }

// char	*get_path(char *comand, char **env)
// {
// 	int		i;
// 	char	*exec;
// 	char	**allpath;
// 	char	*path_part;
// 	char	**split_comand;

// 	i = -1;
// 	allpath = ft_split(my_getenv("PATH", env), ':');
// 	split_comand = ft_split(comand, ' ');
// 	while (allpath[++i])
// 	{
// 		path_part = ft_strjoin(allpath[i], "/");
// 		exec = ft_strjoin(path_part, split_comand[0]);
// 		free(path_part);
// 		if (access(exec, F_OK | X_OK) == 0)
// 		{
// 			free_matrix(split_comand);
// 			free_matrix(allpath);
// 			return (exec);
// 		}
// 		free(exec);
// 	}
// 	free_matrix(allpath);
// 	free_matrix(split_comand);
// 	return (comand);
// }