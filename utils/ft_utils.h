/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:13:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/17 09:56:22 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../includes.h"

// * string utils

size_t	ft_strlcpy(char **dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_strcpy(char *buf, char *src, int src_len);
char	*ft_strjoin(char *pre, char *post, t_bool free_pre, t_bool free_post);
/**
 * @brief this function checks wether the number of occurrences
 * of the quote at the beginning of the input string is balanced
 * 
 * @param str 
 * @return t_bool 
 */
t_bool	ft_quote_occurrence_balanced(char *str);

// * memory utils

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

// * shell utils

t_bool	asked_for_termination(char	*command);

// * misc utils

/**
 * @brief This function maps points outside range [0, right_edge)
 * to points chosen as arguments.
 * 
 * @param point the point to map
 * @param right_edge the right edge of interval [0, right_edge)
 * @param left_spill_val the point where to map inputs that fall behind 0
 * @param right_spill_val the point where to map inputs that
 * fall "above" (>=) right_edge
 * @return int the mapped point
 */
int		range_spill(int point, int right_edge,
			int left_spill_val, int right_spill_val);

#endif