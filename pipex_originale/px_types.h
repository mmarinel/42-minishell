/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:16:48 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 15:22:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_TYPES_H
# define PX_TYPES_H

# ifndef T_BOOLEAN
#  define T_BOOLEAN

typedef enum e_boolean
{
	e_false = 0,
	e_true = 1
}	t_boolean;
# endif

# ifndef T_CMD
#  define T_CMD

typedef struct s_cmd
{
	char			*cmd;
	char			*file;
	int				outpipe[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
	t_boolean		is_last;
	t_boolean		is_first;
	t_boolean		append;
}	t_cmd;

# endif

# define PX_FIRST 1
# define PX_MIDDLE 2
# define PX_LAST 3

#endif