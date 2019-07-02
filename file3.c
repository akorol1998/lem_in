/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 11:10:11 by akorol            #+#    #+#             */
/*   Updated: 2019/06/06 11:10:23 by akorol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_link(t_table *tbl)
{
	t_pipe	*pip;
	int		flag;

	pip = tbl->start->branch;
	flag = 0;
	while (pip)
	{
		if (!pip->node->visited)
			flag = 1;
		pip = pip->next;
	}
	if (!flag)
		return (0);
	return (1);
}

int			launch_algorithm(t_table *tbl)
{
	t_node	*curr;
	int		idx;
	int		f;
	int		i;

	curr = tbl->nodes;
	f = 1;
	if (!check_link(tbl))
	{
		ft_printf("Path is not valid!\n");
		return (0);
	}
	while ((idx = set_levels(tbl)) && f)
	{
		if (idx == -1)
			return (0);
		f = extract_path(tbl, idx);
		i = -1;
		while (tbl->q[++i])
			tbl->q[i] = NULL;
	}
	return (1);
}

void		making_path(t_table *tbl, int idx, int j, int size)
{
	t_node	*node;

	node = tbl->q[idx];
	tbl->path[j][size] = node;
	node = node->prev;
	while (ft_strcmp(node->name, tbl->start->name))
	{
		node->visited = 1;
		size--;
		tbl->path[j][size] = node;
		node = node->prev;
	}
	tbl->start->visited = 0;
}

int			extract_path(t_table *tbl, int idx)
{
	int		i;
	int		j;
	int		size;

	i = -1;
	while (tbl->q[++i])
		;
	j = -1;
	while (tbl->path[++j])
		;
	if (!tbl->q[idx])
		return (-1);
	size = count_nodes(tbl, idx);
	tbl->path[j] = (t_node**)malloc(sizeof(t_node*) * size + 1);
	tbl->path[j][size] = NULL;
	making_path(tbl, idx, j, size - 1);
	if (j + 1 == tbl->ants)
		return (0);
	return (1);
}

void		add_to_queue(t_table *tbl, t_node *cur)
{
	t_pipe	*pip;
	int		idx;

	idx = -1;
	pip = cur->branch;
	while (tbl->q[++idx])
		;
	pip = cur->branch;
	while (pip)
	{
		really_add(cur, pip, tbl, &idx);
		pip = pip->next;
	}
}
