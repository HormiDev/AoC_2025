/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:51:56 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/02 18:31:05 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	**ranges;
	int 	i;
	char	**range;
	char	cnum[30];
	long	inum;
	long	result;
	int 	len;
	long	lastnum;

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
		ft_sprintf(cnum, "%s", range[0]);
		inum = ft_atol(cnum);
		lastnum = ft_atol(range[1]);
		while (inum <= lastnum)
		{
			len = ft_strlen(cnum);
			if (len % 2 == 0)
			{
				if (ft_strncmp_p(&cnum[0], &cnum[len / 2], len / 2) == 0)
				{
					result += inum;
					printf(" [%s]", cnum);
				}
				inum++;
			}
			else
			{
				inum = 1;
				while (len--)
					inum *= 10;
			}
			ft_sprintf(cnum, "%ld", inum);
		}
		printf(GREEN"\nResult: %ld \n\n"RESET, result);
		i++;
		ft_free_split(range);
	}
	ft_free_split(ranges);
	return (0);
}
