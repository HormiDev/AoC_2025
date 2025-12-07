/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 02:12:47 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/07 02:50:22 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

void rotate_str(char *str)
{
	size_t	len;
	size_t	i;
	char	temp;

	len = ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_file		*file;
	char		**rotate_file;
	int			i, j;
	int			x, y;
	long		result;
	long		final_result;

	if (argc != 2)
	{
		ft_dprintf(2, "Usage: %s <input_file>\n", argv[0]);
		return (1);
	}
	file = ft_create_file_from_filename(argv[1]);
	if (!file)
	{
		ft_dprintf(2, "Error: Could not create file from %s\n", argv[1]);
		return (1);
	}
	x = file->lines;
	y = file->list_content->len - 1;
	rotate_file = calloc(sizeof(char *), file->list_content->len + 1);
	i = 0;
	while (i < y)
	{
		rotate_file[i] = calloc(sizeof(char), file->lines + 1);
		j = 0;
		while (j < x)
		{
			rotate_file[i][j] = file->array_content[x - j - 1][i];
			j++;
		}
		rotate_str(&rotate_file[i][1]);
		printf("%s\n", rotate_file[i]);
		rotate_file[i][j] = '\0';
		i++;
	}
	printf("\nResult of each operation:\n");
	final_result = 0;
	i = 0;
	char **tmp;
	while (i < y)
	{
		result = 0;
		if (rotate_file[i][0] == '+')
		{
			tmp = ft_split(rotate_file[i], ' ');
			while (ft_splitlen(tmp) > 0 && i < y)
			{
				result += ft_atol(&rotate_file[i][1]);
				ft_free_split(tmp);
				i++;
				if (i < y)
					tmp = ft_split(rotate_file[i], ' ');
			}
			if (i < y)
				ft_free_split(tmp);
			printf("%ld\n", result);
			final_result += result;
		}
		else if (rotate_file[i][0] == '*')
		{
			result = 1;
			tmp = ft_split(rotate_file[i], ' ');
			while (ft_splitlen(tmp) > 0 && i < y)
			{
				result *= ft_atol(&rotate_file[i][1]);
				ft_free_split(tmp);
				i++;
				if (i < y)
					tmp = ft_split(rotate_file[i], ' ');
			}
			printf("%ld\n", result);
			final_result += result;
			if (i < y)
				ft_free_split(tmp);
		}
		i++;
	}
	printf("Final Result: %ld\n", final_result);
	i = 0;
	while (i < y)
	{
		free(rotate_file[i]);
		i++;
	}
	free(rotate_file);
	ft_file_clear(&file);
	return (0);
}