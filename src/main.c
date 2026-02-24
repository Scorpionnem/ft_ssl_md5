/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:33 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/24 10:13:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int	main(int UNUSED(ac), char **av)
{
	t_ctx	ctx;

	if (ctx_init(&ctx, &av) == -1)
		return (1);

	char	*inpt = "";
	char	*hash = ctx.fn(inpt, strlen(inpt));

	printf("%s\n", hash);
	free(hash);

	ctx_delete(&ctx);
	return (0);
}
