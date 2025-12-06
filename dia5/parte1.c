/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:57:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/05 14:13:55 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

int is_in_the_range(long value, long *range)
{
	return (value >= range[0] && value <= range[1]);
}

int	main(int argc, char **argv)
{
	t_file		*file;
	t_list		*ranges;
	t_strlist	*current_line;
	char		**range_parts;
	long		*range_values;
	int			result;
	t_list		*ranges_tmp;

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
	ranges = NULL;
	current_line = file->list_content;
	while (current_line->str[0] != '\n')
	{
		range_parts = ft_split(current_line->str, '-');
		range_values = malloc(sizeof(long) * 2);
		range_values[0] = ft_atol(range_parts[0]);
		range_values[1] = ft_atol(range_parts[1]);
		ft_lstadd_back(&ranges, ft_lstnew(range_values));
		ft_free_split(range_parts);
		printf("Range: %ld - %ld\n", range_values[0], range_values[1]);
		current_line = current_line->next;
	}
	result = 0;
	current_line = current_line->next;
	while (current_line)
	{
		ranges_tmp = ranges;
		while (ranges_tmp)
		{
			if (is_in_the_range(ft_atol(current_line->str), (long *)ranges_tmp->content))
			{
				result++;
				break ;
			}
			ranges_tmp = ranges_tmp->next;
		}
		current_line = current_line->next;
	}
	printf("Result: %d\n", result);
	ft_lstclear(&ranges, free);
	ft_file_clear(&file);
	return (0);
}