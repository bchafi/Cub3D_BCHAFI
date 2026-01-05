/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:28:25 by bchafi            #+#    #+#             */
/*   Updated: 2025/02/12 23:06:58 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_len(int nbr)
{
	int	len;
    len = 0;
    if (nbr < 0)
    {
        nbr *= -1;
        len += 1;
    }
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		len;
	long	num;

	num = nbr;
	len = get_len(nbr);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_itoa(0));             // "0"
	printf("%s\n", ft_itoa(-10));           // "-10"
	printf("%s\n", ft_itoa(12345));         // "12345"
	printf("%s\n", ft_itoa(-2147483648));   // "-2147483648"
	printf("%s\n", ft_itoa(2147483647));    // "2147483647"
	return (0);
}
