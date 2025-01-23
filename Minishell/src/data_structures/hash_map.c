/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:37:49 by fmol              #+#    #+#             */
/*   Updated: 2024/12/17 15:40:52 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	hash(const char *key)
{
	unsigned int	sum;

	sum = 0;
	while (*key)
	{
		sum += (unsigned int)*key;
		key++;
	}
	return (sum % HASH_TABLE_SIZE);
}

void	free_keyword_table(t_hash_table *table)
{
	size_t	i;

	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		ft_lstclear((*table + i), free);
		i++;
	}
	free(table);
}

int	table_insert(t_hash_table *table, const char *key, int value)
{
	t_list			*new;
	t_table_pair	*pair;

	pair = malloc(sizeof(t_table_pair));
	if (!pair)
		return (0);
	pair->key = key;
	pair->value = value;
	new = ft_lstnew(pair);
	if (!new)
		return (0);
	ft_lstadd_back(*table + hash(key), new);
	return (1);
}

t_hash_table	*new_keyword_table(void)
{
	t_hash_table	*table;

	table = malloc(sizeof(t_hash_table));
	if (!table)
		return (NULL);
	ft_memset(table, 0, sizeof(t_hash_table));
	if (!table_insert(table, "export", EXPORT) || !table_insert(table, "exit",
			EXIT) || !table_insert(table, "env", ENV) || !table_insert(table,
			"echo", ECHO) || !table_insert(table, "pwd", PWD)
		|| !table_insert(table, "cd", CD) || !table_insert(table, "unset",
			UNSET))
	{
		free_keyword_table(table);
		return (NULL);
	}
	return (table);
}

int	search_table(t_hash_table *table, const char *key)
{
	t_list			*list;
	t_table_pair	*data;

	list = (*table)[hash(key)];
	while (list)
	{
		data = (t_table_pair *)list->content;
		if (!ft_strcmp(data->key, key))
			return (data->value);
		list = list->next;
	}
	return (UNKNOWN);
}
