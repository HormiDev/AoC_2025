/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:42:53 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/06 17:14:42 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

long	process_column(long **matrix, int column, int size)
{
	long	result;
	int		i;
	long	operation;

	result = matrix[0][column];
	printf("%ld ", matrix[0][column]);
	operation = matrix[size - 1][column];
	i = 1;
	while (i < size - 1)
	{
		if (operation == 1) // suma
		{
			result += matrix[i][column];
			printf("+ ");
		}
		else if (operation == 2) // multiplicacion
		{
			result *= matrix[i][column];
			printf("* ");
		}
		printf("%ld ", matrix[i][column]);
		i++;
	}
	printf("= %ld\n", result);
	return (result);
}

int	main(int argc, char **argv)
{
	t_file		*file;
	t_strlist	*current_line;
	long		**matrix;
	char		**split_line;
	int			i;
	int			len;
	int			j;
	long		result;

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
	current_line = file->list_content;
	matrix = calloc(sizeof(long *), file->lines + 1);
	i = 0;
	result = 0;
	while (current_line)
	{
		split_line = ft_split(current_line->str, ' ');
		len = ft_splitlen(split_line);
		matrix[i] = calloc(sizeof(long), len);
		j = 0;
		if (current_line->next)
		{
			while (j < len)
			{
				matrix[i][j] = ft_atol(split_line[j]);
				//printf("%ld ", matrix[i][j]);
				j++;
			}
		}
		else
		{
			while (j < len)
			{
				if (split_line[j][0] == '+')
				{
					matrix[i][j] = 1;
					//printf("+ ");
				}
				else if (split_line[j][0] == '*')
				{
					matrix[i][j] = 2;
					//printf("* ");
				}
				else
				{
					matrix[i][j] = 0;
					//printf("? ");
				}
				result += process_column(matrix, j, i + 1);
				j++;
			}
		}
		ft_free_split(split_line);
		//printf("\n");
		current_line = current_line->next;
		i++;
	}
	printf("Final Result: %ld\n", result);
	i = 0;
	while (i < file->lines)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	ft_file_clear(&file);
	return (0);
}