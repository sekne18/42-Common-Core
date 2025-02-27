/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:42:01 by jans              #+#    #+#             */
/*   Updated: 2025/02/12 18:42:02 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	save_material_id(char *line, t_list **mtl_ids)
{
	char	**split;
	t_list	*new_id;
	char	*tmp;

	split = ft_split(line, ' ');
	if (!split)
		return (ERR_MEM);
	tmp = ft_strdup(split[0]);
	if (!tmp)
		return (ft_free_split(split), ERR_MEM);
	new_id = ft_lstnew(tmp);
	if (!new_id)
		return (ft_free_split(split), ERR_MEM);
	ft_lstadd_back(mtl_ids, new_id);
	return (ft_free_split(split), SUCCESS);
}

/*
 * Check if the list of material ids contains duplicate ids
 * RETURN: 1 if the list contains duplicate ids,
	0 if the list does not contain duplicate ids
 * */
int	contains_duplicate_ids(t_list *mtl_ids)
{
	t_list	*head;
	t_list	*tmp;

	head = mtl_ids;
	while (head)
	{
		tmp = head->next;
		while (tmp)
		{
			if (!ft_strcmp(head->content, tmp->content))
				return (1);
			tmp = tmp->next;
		}
		head = head->next;
	}
	return (0);
}

/*
 * Validates the name/id of the material
 * The name/id of the material is valid if it is in the list of material ids
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_material_id(char *value, t_list *mtl_ids)
{
	while (mtl_ids)
	{
		if (ft_strcmp(value, mtl_ids->content) == 0)
			return (1);
		mtl_ids = mtl_ids->next;
	}
	return (0);
}

/*
 * PARAMETHERS: material name, list of materials, list of material ids
 * DESCRIPTION: It gets the index of material from mtl_ids and returns 
 * a material for that index
 * RETURNS: t_material
 * */
t_material	*get_material(char *name, t_material *materials, t_list *mtl_ids)
{
	int	i;

	i = -1;
	while (mtl_ids)
	{
		i++;
		if (ft_strcmp(mtl_ids->content, name) == 0)
			break ;
		mtl_ids = mtl_ids->next;
	}
	return (&materials[i]);
}
