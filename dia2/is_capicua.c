/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_capicua.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 23:35:13 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/02 23:39:52 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

static int is_capicua(const char *num_str)
{
	int		len = ft_strlen(num_str);
	int		jumps = 1;
	char	*cmp;
	int		i;
	int		is_capicua;

	while (jumps <= len / 2)
	{
		if (len % jumps == 0)
		{
			i = 1;
			is_capicua = 1;
			while (i * jumps < len)
			{
				cmp = (char *)&num_str[i * jumps];
				if (ft_strncmp_p(&num_str[0], cmp, jumps) != 0)
				{
					is_capicua = 0;
					break ;
				}
				i++;
			}
			if (is_capicua)
				return (1);
		}
		jumps++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_dprintf(2, "Usage: %s <number>\n", argv[0]);
		return (1);
	}
	long num = ft_atol(argv[1]);
	printf("The number %ld is %s\n", num, is_capicua(argv[1]) ? "Capicua" : "Not Capicua");
	return (0);
}