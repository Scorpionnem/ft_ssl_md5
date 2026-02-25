/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:01:23 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/25 12:30:29 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ctx.h"
#include "libft.h"

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

static uint32_t rotl(uint32_t value, uint32_t shift)
{
	if ((shift &= 31) == 0)
		return (value);
	return (value << shift) | (value >> (32 - shift));
}

const uint32_t	K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

const uint32_t	S[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
};

char	*md5(char *msg, uint32_t len)
{
	(void)msg;(void)len;

	uint32_t	number_blocks = ((len + 8) >> 6) + 1;
	uint32_t	total_length = number_blocks << 6;

	uint8_t	*padding_bytes = ft_calloc((total_length - len), sizeof(uint8_t));
	uint64_t	padding_bytes_size = (total_length - len) * sizeof(uint8_t); 
	padding_bytes[0] = (uint8_t)0x80;

	uint64_t message_length_bits = len << 3;
	for (uint32_t i = 0; i < 8; ++i )
	{
		padding_bytes[padding_bytes_size - 8 + i] = (uint8_t)message_length_bits;
		message_length_bits >>= 8;
	}

	uint32_t	a0 = 0x67452301;
	uint32_t	b0 = 0xefcdab89;
	uint32_t	c0 = 0x98badcfe;
	uint32_t	d0 = 0x10325476;

	for (uint32_t c = 0; c < number_blocks; c++)
	{
		uint32_t	buffer[16] = {0};
		uint32_t	index = c << 6;

		for (uint32_t j = 0; j < 64; index++, ++j)
			buffer[j >> 2] = ((uint32_t)( (index < len) ? msg[index] : padding_bytes[index - len]) << 24) | (buffer[j >> 2] >> 8);

		uint32_t	A = a0;
		uint32_t	B = b0;
		uint32_t	C = c0;
		uint32_t	D = d0;

		for (uint32_t i = 0; i < 64; i++)
		{
			uint32_t	F = 0;
			uint32_t	G = 0;

			if (i <= 15)
			{
				F = (B & C) | ((~B) & D);
				G = i;
			}
			else if (i <= 31)
			{
				F = (D & B) | ((~D) & C);
				G = (5 * i + 1) % 16;
			}
			else if (i <= 47)
			{
				F = B ^ C ^ D;
				G = (3 * i + 5) % 16;
			}
			else if (i <= 63)
			{
				F = C ^ (B | (~D));
				G = (7 * i) % 16;
			}

			F = F + A + K[i] + buffer[G];
			A = D;
			D = C;
			C = B;
			B = B + rotl(F, S[i]);
		}
		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
	}

	uint8_t	hash[16] = {0};
	uint32_t count = 0;
	for (uint32_t i = 0; i < 4; ++i)
	{
		uint32_t n = (i == 0) ? a0 : ((i == 1) ? b0 : ((i == 2) ? c0 : d0));
		for (uint32_t j = 0; j < 4; ++j)
		{
			hash[count++] = (uint8_t)(n);
			n >>= 8;
		}
	}
	
	for (uint32_t i = 0; i < 16; i++)
		ft_putnbr_hex_u(hash[i], 0);

	free(padding_bytes);
	return (NULL);
}
