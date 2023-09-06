// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cd.c                                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/14 14:45:01 by oharoon           #+#    #+#             */
// /*   Updated: 2023/08/14 15:04:57 by oharoon          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../include/minishell.h"

int builtins(void)
{
	// redirect doesnt redirect printf() i think, fix!!!!!
	redirect_funct();
	if (builtin_cd(sh()->input) == 1)
		return (1);
	builtin_exit(sh()->input);
	if (builtin_env() == 1)
		return (1);
	if (builtin_export() == 1)
		return (1);
	if (builtin_unset() == 1)
		return (1);
	if (builtin_echo() == 1)
		return (1);
	return (0);
}