/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_module.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:22:13 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/04 16:36:54 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_MODULE_H
# define PARSER_MODULE_H

# include "parser_types.h"

t_tree_node	*parse(void);
void		free_tree(t_tree_node **root_ref);

#endif
