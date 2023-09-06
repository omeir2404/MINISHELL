/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:56:11 by pvital-m          #+#    #+#             */
/*   Updated: 2023/09/06 19:00:42 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "classes.h"
#include "libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// syntax error msg;
#define PIPE_SYNTAX_ERROR "Error: syntax error near unexpected token `|'\n"
#define IN_SYNTAX_ERROR "Error: syntax error near unexpected token `<'\n"
#define OUT_SYNTAX_ERROR "Error: syntax error near unexpected token `>'\n"

t_shell *sh(void);
int setup(void);
void leave(t_shell *shell, const char *msg, int fd);
void prepare_singals(t_shell *shell);
void freelist(void);
t_env *ml_lst_nenv_add(char *content);
int ml_lst_env_setup(void);
void ml_env_addl_elem(t_env **lst, t_env *_new, int unset);
void ml_lst_cmd_clean(void);
void clean_dptr(char **_alocated);
void ml_input_changer(char *str);

void ml_input_changer(char *str);

void ml_ps_quote_trigger(char token, t_mode *stat);
void ml_ps_quote_trigger_char(char token, t_mode *stat);

void show_split(char **element);
void print_special(char *s);

void *ml_cmd_add_lst(t_commands **head, t_commands *_node);
t_commands *ml_cmd_lst_last(t_commands **head);
t_commands *ml_cmd_fr_lst(t_commands **head);
t_commands *ml_cmd_add_one(char *cmd);

void ml_ps_var_parser(t_commands *lst, t_env *vars);

void ml_lst_env_clean(t_env **env);

bool ml_register_syntax_report(char *str);

void    redirect_funct(void);
int	execute_single_comand(t_shell *shell, char *path, char  **env);
char	*get_path(char *comand, char **env);
void	addpath(t_env **head, char **env, int index);
int	    setup_omeir(char **env);

int builtins(void);
int builtin_cd(char *prompt);
int builtin_exit(char *prompt);
int builtin_export(void);
int builtin_unset(void);
int builtin_env(void);
int builtin_echo(void);
#endif
