/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parte2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:32:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/06 03:49:07 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../42_Libft/libft.h"
#include <stdio.h>

// me ralle mucho la cabeza con este problema, interprete que solo contaban los 
// rangos activados por algun numero de la segunta lista y resulta que contaban
// todos todor los rangos, 

typedef struct s_range
{
	long	range[2];
	int		active;
}	t_range;

int is_in_the_range(long value, long *range)
{
	return (value >= range[0] && value <= range[1]);
}

void ordered_t_range_array(t_range **array)
{
	size_t i, j;
	t_range *temp;
	size_t size;

	size = 0;
	while (array[size])
		size++;
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (array[i]->range[0] > array[j]->range[0])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void **ft_lst_to_array(t_list *lst)
{
	size_t	size;
	void	**array;
	size_t	i;
	t_list	*current;

	size = ft_lstsize(lst);
	array = malloc(sizeof(void *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = lst;
	while (current)
	{
		array[i] = current->content;
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	main(int argc, char **argv)
{
	t_file		*file;
	t_list		*ranges;
	t_strlist	*current_line;
	char		**range_parts;
	long		result;
	t_range		*range_values;
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
		range_values = calloc(sizeof(t_range), 1);
		range_values->range[0] = ft_atol(range_parts[0]);
		range_values->range[1] = ft_atol(range_parts[1]);
		range_values->active = 1;
		if (range_values->range[0] > range_values->range[1])
		{
			long temp = range_values->range[0];
			range_values->range[0] = range_values->range[1];
			range_values->range[1] = temp;
		}
		ft_lstadd_back(&ranges, ft_lstnew(range_values));
		ft_free_split(range_parts);
		printf("Range: %ld - %ld\n", range_values->range[0], range_values->range[1]);
		current_line = current_line->next;
	}
	t_range	**ranges_array;
	ranges_array = (t_range **)ft_lst_to_array(ranges);
	ordered_t_range_array(ranges_array);
	size_t	i;
	t_list	*new_merged_ranges;
	new_merged_ranges = NULL;
	long current_start, current_end;
	current_start = ranges_array[0]->range[0];
	current_end = ranges_array[0]->range[1];
	i = 1;
	while (ranges_array[i])
	{
		if (ranges_array[i]->range[0] <= current_end)
		{
			if (ranges_array[i]->range[1] > current_end)
			{
				current_end = ranges_array[i]->range[1];
			}
		}
		else
		{
			t_range	*new_range;
			new_range = malloc(sizeof(t_range));
			new_range->range[0] = current_start;
			new_range->range[1] = current_end;
			new_range->active = 1;
			ft_lstadd_back(&new_merged_ranges, ft_lstnew(new_range));
			current_start = ranges_array[i]->range[0];
			current_end = ranges_array[i]->range[1];
		}
		i++;
	}
	t_range	*new_range;
	new_range = malloc(sizeof(t_range));
	new_range->range[0] = current_start;
	new_range->range[1] = current_end;
	new_range->active = 1;
	ft_lstadd_back(&new_merged_ranges, ft_lstnew(new_range));
	free(ranges_array);
	ft_lstclear(&ranges, free);

	result = 0;
	ranges_tmp = new_merged_ranges;
	while (ranges_tmp)
	{
		result += ((t_range *)(ranges_tmp->content))->range[1] - ((t_range *)(ranges_tmp->content))->range[0] + 1;
		printf("Merged Range: %ld - %ld  result: %ld\n", ((t_range *)(ranges_tmp->content))->range[0], ((t_range *)(ranges_tmp->content))->range[1], result);
		ranges_tmp = ranges_tmp->next;
	}
	

	printf("Result: %ld\n", result);
	free(ranges_array);
	ft_lstclear(&new_merged_ranges, free);
	ft_lstclear(&ranges, free);
	ft_file_clear(&file);
	return (0);
}

/*int	main(int argc, char **argv)
{
	t_file		*file;
	t_list		*ranges;
	t_strlist	*current_line;
	char		**range_parts;
	long		result;
	t_range		*range_values;
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
		range_values = calloc(sizeof(t_range), 1);
		range_values->range[0] = ft_atol(range_parts[0]);
		range_values->range[1] = ft_atol(range_parts[1]);
		if (range_values->range[0] > range_values->range[1])
		{
			long temp = range_values->range[0];
			range_values->range[0] = range_values->range[1];
			range_values->range[1] = temp;
		}
		ft_lstadd_back(&ranges, ft_lstnew(range_values));
		ft_free_split(range_parts);
		printf("Range: %ld - %ld\n", range_values->range[0], range_values->range[1]);
		current_line = current_line->next;
	}
	current_line = current_line->next;
	while (current_line)
	{
		ranges_tmp = ranges;
		while (ranges_tmp)
		{
			if (is_in_the_range(ft_atol(current_line->str), ((t_range *)(ranges_tmp->content))->range))
			{
				((t_range *)(ranges_tmp->content))->active = 1;
			}
			ranges_tmp = ranges_tmp->next;
		}
		current_line = current_line->next;
	}
	
	t_list	*active_ranges_list;
	active_ranges_list = NULL;
	ranges_tmp = ranges;
	while (ranges_tmp)
	{
		if (((t_range *)(ranges_tmp->content))->active)
		{
			t_range	*active_range;
			active_range = malloc(sizeof(t_range));
			ft_memcpy(active_range, ranges_tmp->content, sizeof(t_range));
			ft_lstadd_back(&active_ranges_list, ft_lstnew(active_range));
			printf("Active Range: %ld - %ld\n", active_range->range[0], active_range->range[1]);
		}
		ranges_tmp = ranges_tmp->next;
	}
	
	t_range	**active_ranges_array;
	active_ranges_array = (t_range **)ft_lst_to_array(active_ranges_list);
	ordered_t_range_array(active_ranges_array);
	size_t	i;
	i = 0;
	printf("Ordered Active Ranges:\n");
	while (active_ranges_array[i])
	{
		printf("  %ld - %ld\n", active_ranges_array[i]->range[0], active_ranges_array[i]->range[1]);
		i++;
	}

	t_list	*merged_ranges;
	merged_ranges = NULL;
	long current_start, current_end;
	current_start = active_ranges_array[0]->range[0];
	current_end = active_ranges_array[0]->range[1];
	i = 1;
	while (active_ranges_array[i])
	{
		if (active_ranges_array[i]->range[0] <= current_end)
		{
			if (active_ranges_array[i]->range[1] > current_end)
			{
				current_end = active_ranges_array[i]->range[1];
			}
		}
		else
		{
			t_range	*new_range;
			new_range = malloc(sizeof(t_range));
			new_range->range[0] = current_start;
			new_range->range[1] = current_end;
			ft_lstadd_back(&merged_ranges, ft_lstnew(new_range));
			current_start = active_ranges_array[i]->range[0];
			current_end = active_ranges_array[i]->range[1];
		}
		i++;
	}
	t_range	*new_range;
	new_range = malloc(sizeof(t_range));
	new_range->range[0] = current_start;
	new_range->range[1] = current_end;
	ft_lstadd_back(&merged_ranges, ft_lstnew(new_range));

	result = 0;
	ranges_tmp = merged_ranges;
	while (ranges_tmp)
	{
		result += ((t_range *)(ranges_tmp->content))->range[1] - ((t_range *)(ranges_tmp->content))->range[0] + 1;
		printf("Merged Range: %ld - %ld  result: %ld\n", ((t_range *)(ranges_tmp->content))->range[0], ((t_range *)(ranges_tmp->content))->range[1], result);
		ranges_tmp = ranges_tmp->next;
	}
	

	printf("Result: %ld\n", result);
	ft_lstclear(&active_ranges_list, free);
	ft_lstclear(&merged_ranges, free);
	free(active_ranges_array);
	
	ft_lstclear(&ranges, free);
	ft_file_clear(&file);
	return (0);
}*/
