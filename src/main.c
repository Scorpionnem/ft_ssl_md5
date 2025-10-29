/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:47:30 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/29 14:58:31 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

#define BOOLEAN_FLAGS "pqrs" 
#define ARG_FLAGS "" 

int	main(int ac, char **av)
{
	ac = 42;
	t_opts *opts = ft_getopt(BOOLEAN_FLAGS, ARG_FLAGS, av);
	if (!opts)
		return (1);

	ft_free_opt(opts);
	return (0);
}
