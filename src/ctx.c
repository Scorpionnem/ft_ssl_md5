/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:05:50 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/25 12:30:24 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int		ctx_init_opts(t_ctx *ctx, char ***av);
void	print_help();

static t_hash_func	get_hash_func(char *id)
{
	#define COMMANDS_COUNT 2
	const struct {char *id; t_hash_func fn;} commands_to_funcs[COMMANDS_COUNT] =
	{
		{.id = "md5", .fn = md5},
		{.id = "sha256", .fn = sha256},
	};

	for (int i = 0; i < COMMANDS_COUNT; i++)
		if (!ft_strcmp(commands_to_funcs[i].id, id))
			return (commands_to_funcs[i].fn);
	return (NULL);
}

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

	if (*av[0] == NULL)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		ft_dprintf(2, "ft_ssl: command required (see -h)\n");
		return (-1);
	}
	ctx->fn = get_hash_func(*av[0]);
	if (ctx->fn == NULL)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		ft_dprintf(2, "ft_ssl: Unknown command (%s)\n", *av[0]);
		return (-1);
	}
	ctx->fn_str = ft_strdup(*av[0]);

	(*av)++;

	return (0);
}

void	ctx_delete(t_ctx *ctx)
{
	free(ctx->fn_str);
	opt_ctx_delete(&ctx->opt_ctx);
}

void	print_help()
{
	ft_printf("\nUsage:\n  ./ft_ssl <command> [options]\n\n");
	ft_printf("Standard commands:\n");
	ft_printf("\n");
	ft_printf("Message Digest commands:\n");
	ft_printf("  md5\n");
	ft_printf("  sha256\n");
	ft_printf("\n");
	ft_printf("Cipher commands:\n");
	ft_printf("\n");
	ft_printf("Options:\n");
	ft_printf("  -h\t\tshow help message and exit\n");
	ft_printf("  -p\t\techo STDIN to STDOUT and append the checksum to STDOUT\n");
	ft_printf("  -q\t\tquiet mode\n");
	ft_printf("  -r\t\treverse the format of the output\n");
	ft_printf("  -s <string>\tprint the sum of <string>\n");
	ft_printf("\n");
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
