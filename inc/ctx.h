/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:07 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/24 10:37:26 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define UNUSED(x)	_unused_##x __attribute__((unused))

#include "opt.h"
#include "md5.h"
#include "sha256.h"

typedef char *(*t_hash_func)(char*, uint32_t);

typedef struct	s_ctx
{
	t_hash_func	fn;
	char		*fn_str;

	t_opt_ctx			opt_ctx;

	t_opt				help;

	t_opt				echo;
	t_opt				quiet;
	t_opt				reverse;
	t_opt				string;
}	t_ctx;

int		ctx_init(t_ctx *ctx, char ***av);
void	ctx_delete(t_ctx *ctx);
