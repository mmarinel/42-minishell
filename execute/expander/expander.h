/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:53:32 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/19 18:48:35 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// * user defined types //
# include "expander_types.h"

// * user defined modules //
# include "../../env/env_module.h"
# include "expander_cases/expander_cases.h"
# include "expander_utils/expander_utils.h"
# include "../../utils/ft_utils.h"
# include "../../colors.h"
# include "../../global.h"

char	*expand(char *args);

#endif