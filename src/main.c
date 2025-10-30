/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:47:30 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/30 08:32:47 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

/*
	-p	echo STDIN to STDOUT and append the checksum to STDOUT
	-q	quiet mode
	-r	reverse the format of the output
	-s	print the sum of the given string
*/

#define BOOLEAN_FLAGS "pqrs" 
#define ARG_FLAGS ""

#include <stdio.h>

typedef struct s_ctx
{
	char	*command;
	char	*file;
	t_opts	*opts;
}	t_ctx;

void	print_usage()
{
	ft_putendl_fd("usage: ft_ssl command [flags] [file/string]", 2);
	ft_putendl_fd("\nCommands:\nmd5\nsha256", 2);
	ft_putendl_fd("\nOptions:\n-p -q -r -s", 2);
}

int	ctx_set_command(t_ctx *ctx, char *cmd)
{
	int	res;
	
	res = 0;
	ctx->command = cmd;
	if (!ft_strcmp("md5", cmd))
		res = 1;
	if (!ft_strcmp("sha256", cmd))
		res = 1;
	if (!res)
		printf("ft_ssl: invalid command: '%s'\n", cmd);
	return (res);
}

int	ctx_treat_args(t_ctx *ctx)
{
	t_arg	*args = ctx->opts->args;

	if (!args)
	{
		print_usage();
		ft_free_opt(ctx->opts);
		return (0);
	}
	
	if (!ctx_set_command(ctx, args->arg))
	{
		ft_free_opt(ctx->opts);
		return (0);
	}
	args = args->next;
	if (args)
		ctx->file = args->arg;
	return (1);
}

int	ctx_init_options(t_ctx *ctx, char **av)
{
	ctx->opts = ft_getopt(BOOLEAN_FLAGS, ARG_FLAGS, av);
	if (!ctx->opts)
		return (0);
	if (!ctx_treat_args(ctx))
		return (0);
	return (1);
}

int	ctx_init(t_ctx *ctx, char **av)
{
	ft_bzero(ctx, sizeof(t_ctx));

	if (!ctx_init_options(ctx, av))
		return (0);

	printf("%s %s\n", ctx->command, ctx->file);
	return (1);
}

int	ctx_delete(t_ctx *ctx)
{
	ft_free_opt(ctx->opts);
	return (0);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	ac = 42;
	if (!ctx_init(&ctx, av))
		return (1);
	return (ctx_delete(&ctx));
}
