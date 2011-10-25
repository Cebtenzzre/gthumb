/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  GThumb
 *
 *  Copyright (C) 2009 Free Software Foundation, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <gtk/gtk.h>
#include "gth-dumb-notebook.h"


struct _GthDumbNotebookPrivate {
	GList     *children;
	int        n_children;
	GtkWidget *current;
	int        current_pos;
};


static gpointer parent_class = NULL;


static void
gth_dumb_notebook_finalize (GObject *object)
{
	GthDumbNotebook *dumb_notebook = GTH_DUMB_NOTEBOOK (object);
	
	if (dumb_notebook->priv != NULL) {
		g_free (dumb_notebook->priv);
		dumb_notebook->priv = NULL;
	}
	
	G_OBJECT_CLASS (parent_class)->finalize (object);
}


static GtkSizeRequestMode
gth_dumb_notebook_get_request_mode (GtkWidget *widget)
{
	return GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH;
}


static void
gth_dumb_notebook_get_preferred_height (GtkWidget *widget,
                			int       *minimum_height,
                			int       *natural_height)
{
	GthDumbNotebook *dumb_notebook = GTH_DUMB_NOTEBOOK (widget);
	GList           *scan;
	int              border_width;

	*minimum_height = 0;
	*natural_height = 0;

	for (scan = dumb_notebook->priv->children; scan; scan = scan->next) {
		GtkWidget *child = scan->data;
		int        child_minimum_height;
		int        child_natural_height;
		
		if (! gtk_widget_get_visible (child))
                        continue;

		gtk_widget_get_preferred_height (child, &child_minimum_height, &child_natural_height);
		*minimum_height = MAX (*minimum_height, child_minimum_height);
		*natural_height = MAX (*natural_height, child_natural_height);
	}
	
	border_width = gtk_container_get_border_width (GTK_CONTAINER (widget));
	*minimum_height += border_width * 2;
	*natural_height += border_width * 2;
}


static void
gth_dumb_notebook_get_preferred_width_for_height (GtkWidget *widget,
                				  int        height,
                				  int       *minimum_width,
                				  int       *natural_width)
{
	GthDumbNotebook *dumb_notebook = GTH_DUMB_NOTEBOOK (widget);
	GList           *scan;
	int              border_width;

	*minimum_width = 0;
	*natural_width = 0;

	for (scan = dumb_notebook->priv->children; scan; scan = scan->next) {
		GtkWidget *child = scan->data;
		int        child_minimum_width;
		int        child_natural_width;

		if (! gtk_widget_get_visible (child))
                        continue;

		gtk_widget_get_preferred_width_for_height (child, height, &child_minimum_width, &child_natural_width);
		*minimum_width = MAX (*minimum_width, child_minimum_width);
		*natural_width = MAX (*natural_width, child_natural_width);
	}

	border_width = gtk_container_get_border_width (GTK_CONTAINER (widget));
	*minimum_width += border_width * 2;
	*natural_width += border_width * 2;
}


static void
gth_dumb_notebook_get_preferred_width (GtkWidget *widget,
                		       int       *minimum_width,
                		       int       *natural_width)
{
	GthDumbNotebook *dumb_notebook = GTH_DUMB_NOTEBOOK (widget);
	GList           *scan;
	int              border_width;

	*minimum_width = 0;
	*natural_width = 0;

	for (scan = dumb_notebook->priv->children; scan; scan = scan->next) {
		GtkWidget *child = scan->data;
		int        child_minimum_width;
		int        child_natural_width;

		if (! gtk_widget_get_visible (child))
                        continue;

		gtk_widget_get_preferred_width (child, &child_minimum_width, &child_natural_width);
		*minimum_width = MAX (*minimum_width, child_minimum_width);
		*natural_width = MAX (*natural_width, child_natural_width);
	}

	border_width = gtk_container_get_border_width (GTK_CONTAINER (widget));
	*minimum_width += border_width * 2;
	*natural_width += border_width * 2;
}


static void
gth_dumb_notebook_get_preferred_height_for_width (GtkWidget *widget,
                				  int        width,
                				  int       *minimum_height,
                				  int       *natural_height)
{
	GthDumbNotebook *dumb_notebook = GTH_DUMB_NOTEBOOK (widget);
	GList           *scan;
	int              border_width;

	*minimum_height = 0;
	*natural_height = 0;

	for (scan = dumb_notebook->priv->children; scan; scan = scan->next) {
		GtkWidget *child = scan->data;
		int        child_minimum_height;
		int        child_natural_height;

		if (! gtk_widget_get_visible (child))
                        continue;

		gtk_widget_get_preferred_height_for_width (child, width, &child_minimum_height, &child_natural_height);
		*minimum_height = MAX (*minimum_height, child_minimum_height);
		*natural_height = MAX (*natural_height, child_natural_height);
	}

	border_width = gtk_container_get_border_width (GTK_CONTAINER (widget));
	*minimum_height += border_width * 2;
	*natural_height += border_width * 2;
}


static void
gth_dumb_notebook_size_allocate (GtkWidget     *widget,
				 GtkAllocation *allocation)
{
	GthDumbNotebook *dumb_notebook = GTH_DUMB_NOTEBOOK (widget);
	int              border_width;
	GtkAllocation    child_allocation;
	GList           *scan;
	
	border_width = gtk_container_get_border_width (GTK_CONTAINER (widget));
	child_allocation.x = allocation->x + border_width;
	child_allocation.y = allocation->y + border_width;
	child_allocation.width = MAX (1, allocation->width - border_width * 2);
	child_allocation.height = MAX (1, allocation->height - border_width * 2);

	for (scan = dumb_notebook->priv->children; scan; scan = scan->next) {
		GtkWidget *child = scan->data;
		
		if (gtk_widget_get_visible (child))
			gtk_widget_size_allocate (child, &child_allocation);
	}

	gtk_widget_set_allocation (widget, allocation);
}


static gboolean
gth_dumb_notebook_draw (GtkWidget *widget,
			cairo_t   *cr)
{
	GthDumbNotebook *dumb_notebook = GTH_DUMB_NOTEBOOK (widget);
	
	if (dumb_notebook->priv->current == NULL)
		return FALSE;

	gtk_widget_draw (dumb_notebook->priv->current, cr);

	return TRUE;
}


static void
gth_dumb_notebook_add (GtkContainer *container,
		       GtkWidget    *child)
{
	GthDumbNotebook *notebook;
	
	notebook = GTH_DUMB_NOTEBOOK (container);
	
	gtk_widget_freeze_child_notify (child);
	
	notebook->priv->children = g_list_append (notebook->priv->children, child);
	gtk_widget_set_parent (child, GTK_WIDGET (notebook));
	
	notebook->priv->n_children++;
	if (notebook->priv->current_pos == notebook->priv->n_children - 1)
		gtk_widget_set_child_visible (child, TRUE);
	else
		gtk_widget_set_child_visible (child, FALSE);
		
	gtk_widget_thaw_child_notify (child);
}


static void
gth_dumb_notebook_remove (GtkContainer *container,
			  GtkWidget    *widget)
{
	/* FIXME */
}


static void
gth_dumb_notebook_forall (GtkContainer *container,
			  gboolean      include_internals,
			  GtkCallback   callback,
			  gpointer      callback_data)
{
	GthDumbNotebook *notebook;
	GList           *scan;
	
	notebook = GTH_DUMB_NOTEBOOK (container);
	
	for (scan = notebook->priv->children; scan; scan = scan->next) 
		(* callback) (scan->data, callback_data);
}


static GType
gth_dumb_notebook_child_type (GtkContainer *container)
{
	return GTK_TYPE_WIDGET;
}


static void 
gth_dumb_notebook_class_init (GthDumbNotebookClass *klass) 
{
	GObjectClass      *gobject_class;
	GtkWidgetClass    *widget_class;
	GtkContainerClass *container_class;
	
	parent_class = g_type_class_peek_parent (klass);

	gobject_class = G_OBJECT_CLASS (klass);
	gobject_class->finalize = gth_dumb_notebook_finalize;
	
	widget_class = GTK_WIDGET_CLASS (klass);
	widget_class->get_request_mode = gth_dumb_notebook_get_request_mode;
	widget_class->get_preferred_height = gth_dumb_notebook_get_preferred_height;
	widget_class->get_preferred_width_for_height = gth_dumb_notebook_get_preferred_width_for_height;
	widget_class->get_preferred_width = gth_dumb_notebook_get_preferred_width;
	widget_class->get_preferred_height_for_width = gth_dumb_notebook_get_preferred_height_for_width;
	widget_class->size_allocate = gth_dumb_notebook_size_allocate;
	widget_class->draw = gth_dumb_notebook_draw;

	container_class = GTK_CONTAINER_CLASS (klass);
	container_class->add = gth_dumb_notebook_add;
	container_class->remove = gth_dumb_notebook_remove;
	container_class->forall = gth_dumb_notebook_forall;
	container_class->child_type = gth_dumb_notebook_child_type;
}


static void
gth_dumb_notebook_init (GthDumbNotebook *notebook) 
{
	gtk_widget_set_has_window (GTK_WIDGET (notebook), FALSE);
	
	notebook->priv = g_new0 (GthDumbNotebookPrivate, 1);
	notebook->priv->n_children = 0;	
}


GType 
gth_dumb_notebook_get_type (void) 
{
	static GType type = 0;
	
	if (type == 0) {
		static const GTypeInfo g_define_type_info = { 
			sizeof (GthDumbNotebookClass), 
			(GBaseInitFunc) NULL, 
			(GBaseFinalizeFunc) NULL, 
			(GClassInitFunc) gth_dumb_notebook_class_init, 
			(GClassFinalizeFunc) NULL, 
			NULL, 
			sizeof (GthDumbNotebook), 
			0, 
			(GInstanceInitFunc) gth_dumb_notebook_init, 
			NULL 
		};
		type = g_type_register_static (GTK_TYPE_CONTAINER, 
					       "GthDumbNotebook", 
					       &g_define_type_info, 
					       0);
	}
	
	return type;
}


GtkWidget *
gth_dumb_notebook_new (void) 
{
	return g_object_new (GTH_TYPE_DUMB_NOTEBOOK, NULL);
}


void
gth_dumb_notebook_show_child (GthDumbNotebook *notebook,
			      int              pos)
{
	GList *link;
	
	if (notebook->priv->current_pos == pos)
		return;
		
	if (notebook->priv->current)
		gtk_widget_set_child_visible (notebook->priv->current, FALSE);
	
	notebook->priv->current = NULL;
	notebook->priv->current_pos = pos;
	
	link = g_list_nth (notebook->priv->children, pos);
	if (link == NULL)
		return;
	
	notebook->priv->current = link->data;
	gtk_widget_set_child_visible (notebook->priv->current, TRUE);
	
	gtk_widget_queue_resize (GTK_WIDGET (notebook));
}
