/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:05:50 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/23 18:45:31 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include <stdlib.h>
#include <stdio.h>

int		ctx_init_opts(t_ctx *ctx, char ***av);
void	print_help();

int	ctx_init(t_ctx *ctx, char ***av)
{
	if (ctx_init_opts(ctx, av) == -1)
		return (-1);
	if (ctx->help._bool)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		print_help();
		return (-1);
	}

	if (!*av[0])
	{
		opt_ctx_delete(&ctx->opt_ctx);
		dprintf(2, "ft_ssl: command required (see help)\n");
		return (-1);
	}

	return (0);
}

void	ctx_delete(t_ctx *ctx)
{
	opt_ctx_delete(&ctx->opt_ctx);
}

void	print_help()
{
	printf("\nUsage:\n  ./ft_ssl <command> [options]\n\n");
	printf("Commands:\n");
	printf("  md5\n");
	printf("  sha256\n");
	printf("\n");
	printf("Options:\n");
	printf("  -h\t\tshow help message and exit\n");
	printf("  -p\t\techo STDIN to STDOUT and append the checksum to STDOUT\n");
	printf("  -q\t\tquiet mode\n");
	printf("  -r\t\treverse the format of the output\n");
	printf("  -s <string>\tprint the sum of <string>\n");
	printf("\n");
}

int	ctx_init_opts(t_ctx *ctx, char ***av)
{
	opt_ctx_init(&ctx->opt_ctx);

	opt_ctx_add_opt(&ctx->opt_ctx, "-h", &ctx->help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--help", &ctx->help, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-p", &ctx->echo, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "-q", &ctx->quiet, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "-r", &ctx->reverse, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-s", &ctx->string, OPT_STR);

	if (opt_ctx_parse(&ctx->opt_ctx, av) == -1)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		return (-1);
	}
	return (0);
}
