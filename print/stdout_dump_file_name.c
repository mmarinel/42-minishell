/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:55:24 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/19 17:12:42 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

char	*get_stdout_dump_file_name(void)
{
	static const char	*prefix = ".stdout-dump";

	return (
		ft_strjoin(
			(char *)prefix,
			env_handler(BINDING_GET_VALUE, "SHLVL"),
			e_false, e_true
		)
	);
}
