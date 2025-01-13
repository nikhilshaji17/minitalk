/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:34:46 by nkunnath          #+#    #+#             */
/*   Updated: 2024/07/24 11:34:48 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_number(unsigned int x, int *num_printed)
{
	char	digit;
	int		y;

	if (x > 0)
	{
		digit = (x % 10) + '0';
		print_number(x / 10, num_printed);
		if (*num_printed == -1)
			return ;
		y = write(1, &digit, 1);
		if (y == -1)
		{
			*num_printed = -1;
			return ;
		}
		*num_printed += 1;
	}
}

void	ft_putnbr(int n, int *num_printed)
{
	unsigned int	x;
	int				y;

	x = n;
	if (n == 0)
	{
		y = write(1, "0", 1);
		if (y == -1)
			*num_printed = -1;
		else
			*num_printed += 1;
		return ;
	}
	else if (n < 0)
	{
		y = write(1, "-", 1);
		if (y == -1)
		{
			*num_printed = -1;
			return ;
		}
		*num_printed += 1;
		x = n * -1;
	}
	print_number(x, num_printed);
}
