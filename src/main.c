/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:33 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/24 11:02:02 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int	process(t_ctx *ctx, char *input, uint32_t len)
{
	char	*hash = ctx->fn(input, len);
	if (!hash)
		return (-1);
	printf("%s", hash);
	free(hash);
	return (0);
}

int	process_av(t_ctx *ctx, char **av)
{
	while (*av)
	{
		int	fd = open(*av, O_RDONLY);
		if (fd == -1)
		{
			dprintf(2, "ft_ssl: %s: %s\n", *av, strerror(errno));
			av++;
			continue ;
		}

		struct stat	stats;
		fstat(fd, &stats);

		char	*input = mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, fd, 0);
		if (input == (void*)-1)
			return (dprintf(2, "ft_ssl: mmap: %s\n", strerror(errno)), -1);

		if (!ctx->reverse._bool && !ctx->quiet._bool)
			printf("%s (%s) = ", ctx->fn_str, *av);

		process(ctx, input, stats.st_size);

		if (ctx->reverse._bool && !ctx->quiet._bool)
			printf(" %s", *av);
		printf("\n");

		munmap(input, stats.st_size);
		close(fd);
		av++;
	}
	return (0);
}

int	process_string(t_ctx *ctx, char *str)
{
	if (!ctx->reverse._bool && !ctx->quiet._bool)
		printf("%s (\"%s\") = ", ctx->fn_str, str);

	process(ctx, str, strlen(str));

	if (ctx->reverse._bool && !ctx->quiet._bool)
		printf(" \"%s\"", str);
	printf("\n");

	return (0);
}

int	process_stdin(t_ctx *ctx)
{
	char	*buf = calloc(1, 1);
	int		total_read = 0;

	while (1)
	{
		int bytes = read(0, buf + total_read, 1);
		if (bytes <= 0)
			break ;
		total_read += bytes;
		buf = realloc(buf, total_read + 1);
		buf[total_read] = 0;
	}
	if (!ctx->reverse._bool && !ctx->quiet._bool)
		printf("%s (stdin) = ", ctx->fn_str);

	process(ctx, buf, total_read);

	if (ctx->reverse._bool && !ctx->quiet._bool)
		printf(" stdin");
	printf("\n");

	free(buf);
	return (0);
}

int	main(int UNUSED(ac), char **av)
{
	t_ctx	ctx;

	if (ctx_init(&ctx, &av) == -1)
		return (1);

	if (ctx.string._str)
		process_string(&ctx, ctx.string._str);
	if (*av)
		process_av(&ctx, av);
	else if (!ctx.string._str)
		process_stdin(&ctx);

	ctx_delete(&ctx);
	return (0);
}
