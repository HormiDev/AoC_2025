/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:11:07 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/02 23:45:29 by ide-dieg         ###   ########.fr       */
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

static long	capicuas_in_range(char *start, char *end)
{
	long	inum;
	long	lastnum;
	long	result;
	char	cnum[30];

	inum = ft_atol(start);
	lastnum = ft_atol(end);
	result = 0;
	while (inum <= lastnum)
	{
		ft_sprintf(cnum, "%ld", inum);
		if (is_capicua(cnum))
		{
			result += inum;
			printf(" [%s]", cnum);
		}
		inum++;
	}
	return (result);
}

int	main(int argc, char **argv)
{
	char	**ranges;
	int 	i;
	char	**range;
	long	result;

	if (argc != 2)
	{
		ft_dprintf(2, "Usage: %s <input>\n", argv[0]);
		return (1);
	}
	ranges = ft_split(argv[1], ',');
	i = 0;
	result = 0;
	while (ranges[i])
	{
		printf(YELLOW"Range %d: %s\n"RESET, i, ranges[i]);
		range = ft_split(ranges[i], '-');
		result += capicuas_in_range(range[0], range[1]);
		printf(GREEN"\nResult: %ld \n\n"RESET, result);
		i++;
		ft_free_split(range);
	}
	ft_free_split(ranges);
	return (0);
}
