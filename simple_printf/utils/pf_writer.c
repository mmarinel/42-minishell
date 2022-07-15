/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_writer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:20:52 by earendil          #+#    #+#             */
/*   Updated: 2022/07/15 13:46:39 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	pf_write(const char *c, int *count)
{
	write(STDOUT_FILENO, c, sizeof(char));
	*count = *count + 1;
}
