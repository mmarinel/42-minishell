/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:13:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/15 21:28:40 by earendil         ###   ########.fr       */
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

// * memory utils

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

// * shell utils

/**
 * @brief this function exits the current shell.
 * 
 * @param exit_status exit status chosen
 * @param go_on_new_line iff true, a '\ n ' gets printed before exiting.
 */
void	exit_shell(int exit_status, t_bool go_on_newline);

// * misc utils

/**
 * @brief This function maps points outside range [0, right_edge)
 * to points chosen as arguments.
 * 
 * @param point the point to map
 * @param right_edge the right edge of interval [0, right_edge)
 * @param left_spill_val the point where to map inputs that fall behind 0
 * @param right_spill_val the point where to map inputs that fall "above" (>=) right_edge
 * @return int the mapped point
 */
int	range_spill(int point, int right_edge, int left_spill_val, int right_spill_val);

#endif