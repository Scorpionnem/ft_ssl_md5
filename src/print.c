/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:08:06 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/25 12:15:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
static int	ft_putchar_a(char c)
{
	return (write(1, &c, 1));
}

#define LOWER_HEX		"0123456789abcdef"

int	ft_putnbr_hex_u(unsigned long int n, int level)
{
	if (n >= 0 && n <= 15)
	{
		if (level == 0)
			ft_putchar_a('0');
		return (ft_putchar_a("0123456789abcdef"[n % 16]));
	}
	return (ft_putnbr_hex_u(n / 16, level + 1) + ft_putnbr_hex_u(n % 16, level + 1));
}
