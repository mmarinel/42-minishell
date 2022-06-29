/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:19:19 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/29 18:06:52 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#ifndef T_BOOL_H
# define T_BOOL_H
typedef enum e_bool
{
	e_true = 1,
	e_false = 0
}	t_bool;
#endif

typedef enum e_status
{
	ERROR,
	OK
}	t_status;


typedef struct s_bindings
{
	t_bool				concat_mode;
	char				*var_name;
	char				*var_val;
	struct s_bindings	*next;
}	t_bindings;

#endif
