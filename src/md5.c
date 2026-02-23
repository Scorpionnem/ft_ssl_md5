/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:01:23 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/24 00:41:49 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>

uint32_t rotl(uint32_t value, uint32_t shift)
{
	if ((shift &= 31) == 0)
		return (value);
	return (value << shift) | (value >> (32 - shift));
}

uint32_t rotr(uint32_t value, uint32_t shift)
{
	if ((shift &= 31) == 0)
		return (value);
	return (value >> shift) | (value << (32 - shift));
}

typedef struct s_md5_output
{
	uint32_t	A;
	uint32_t	B;
	uint32_t	C;
	uint32_t	D;
}	t_md5_output;

uint32_t	f(uint32_t B, uint32_t C, uint32_t D, uint32_t i)
{
	if (i <= 15)
		return ((B & C) | ((~B) & D));
	if (i <= 31)
		return ((D & B) | ((~D) & C));
	if (i <= 47)
		return (B ^ C ^ D);
	if (i <= 63)
		return (C ^ (B | (~D)));
	return (0);
}

uint32_t	combine(uint32_t A, uint32_t B, uint32_t C, uint32_t D, uint32_t word, uint32_t i)
{
	uint32_t	res = f(B, C, D, i);

	res += A;
	res += word;

	int	r[64] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
		5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
		4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
		6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};

	int	k[64] = {0};
	for (int x = 0; x < 64; x++)
		k[x] = floor(fabs(sin(x + 1)) * pow(2, 32));

	res += k[i];
	res = rotl(res, r[i]);
	res += B;
	return (res);
}


char	*md5(char *inputs)
{
	(void)inputs;
	t_md5_output	output;
	t_md5_output	output_prime;

	uint32_t	input[16] = {0};

	output.A = 0x67452301;
	output.B = 0xEFCDAB89;
	output.C = 0x98BADCFE;
	output.D = 0x10325476;

	int	i = 0;

	uint32_t AA = output.A;
	uint32_t BB = output.B;
	uint32_t CC = output.C;
	uint32_t DD = output.D;

	while (i < 16)
	{
		output_prime.A = output.D;
		output_prime.C = output.B;
		output_prime.D = output.C;
		output_prime.B = combine(output.A, output.B, output.C, output.D, input[i], i);

		output = output_prime;

		i++;
	}

	while (i < 32)
	{
		output_prime.A = output.D;
		output_prime.C = output.B;
		output_prime.D = output.C;

		int	index = (5 * i + 1) % 16;
		(void)index;

		output_prime.B = combine(output.A, output.B, output.C, output.D, input[index], i);

		output = output_prime;

		i++;
	}

	while (i < 48)
	{
		output_prime.A = output.D;
		output_prime.C = output.B;
		output_prime.D = output.C;

		int	index = (3 * i + 5) % 16;
		(void)index;

		output_prime.B = combine(output.A, output.B, output.C, output.D, input[index], i);

		output = output_prime;

		i++;
	}

	while (i < 64)
	{
		output_prime.A = output.D;
		output_prime.C = output.B;
		output_prime.D = output.C;

		int	index = 7 * i % 16;
		(void)index;

		output_prime.B = combine(output.A, output.B, output.C, output.D, input[index], i);

		output = output_prime;

		i++;
	}

	output.A += AA;
	output.B += BB;
	output.C += CC;
	output.D += DD;

	typedef struct	s_md5_output
	{
		uint32_t	words[4];
	}	t_md5_output;
	t_md5_output	out;

	out.words[0] = output.A;
	out.words[1] = output.B;
	out.words[2] = output.C;
	out.words[3] = output.D;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			printf("%02x", ((uint8_t*)&(out.words[i]))[j]);

	printf("\n");

	(void)input;
	return (NULL);
}
