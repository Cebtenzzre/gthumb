/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  GThumb
 *
 *  Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef GTH_FILE_VIEW_H
#define GTH_FILE_VIEW_H

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GTH_TYPE_FILE_VIEW               (gth_file_view_get_type ())
#define GTH_FILE_VIEW(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTH_TYPE_FILE_VIEW, GthFileView))
#define GTH_IS_FILE_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTH_TYPE_FILE_VIEW))
#define GTH_FILE_VIEW_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTH_TYPE_FILE_VIEW, GthFileViewInterface))

typedef struct _GthFileView GthFileView;
typedef struct _GthFileViewInterface GthFileViewInterface;

#define THUMBNAIL_BORDER (8 * 2)

typedef enum  {
	GTH_VISIBILITY_NONE,
	GTH_VISIBILITY_FULL,
	GTH_VISIBILITY_PARTIAL,
	GTH_VISIBILITY_PARTIAL_TOP,
	GTH_VISIBILITY_PARTIAL_BOTTOM
} GthVisibility;

typedef enum {
	GTH_FILE_VIEW_RENDERER_CHECKBOX,
	GTH_FILE_VIEW_RENDERER_THUMBNAIL,
	GTH_FILE_VIEW_RENDERER_TEXT
} GthFileViewRendererType;

struct _GthFileViewInterface {
	GTypeInterface parent_iface;

	/*< signals >*/

	void            (*file_activated)                (GthFileView              *self,
					     	     	  GtkTreePath              *path);

	/*< virtual functions >*/

	void            (*set_model)                     (GthFileView              *self,
							  GtkTreeModel             *model);
	GtkTreeModel *  (*get_model)                     (GthFileView              *self);
	void            (*scroll_to)                     (GthFileView              *self,
							  int                       pos,
							  double                    yalign);
	GthVisibility   (*get_visibility)                (GthFileView              *self,
							  int                       pos);
	int             (*get_at_position)               (GthFileView              *self,
							  int                       x,
							  int                       y);
	int             (*get_first_visible)             (GthFileView              *self);
	int             (*get_last_visible)              (GthFileView              *self);
	void            (*activated)                     (GthFileView              *self,
							  int                       pos);
	void            (*set_cursor)                    (GthFileView              *self,
							  int                       pos);
	int             (*get_cursor)                    (GthFileView              *self);
	void            (*set_spacing)                   (GthFileView              *self,
							  int                       spacing);
	void            (*enable_drag_source)            (GthFileView              *self,
							  GdkModifierType           start_button_mask,
							  const GtkTargetEntry     *targets,
							  gint                      n_targets,
							  GdkDragAction             actions);
	void            (*unset_drag_source)             (GthFileView              *self);
	void            (*enable_drag_dest)              (GthFileView              *self,
							  const GtkTargetEntry     *targets,
							  gint                      n_targets,
							  GdkDragAction             actions);
	void            (*unset_drag_dest)               (GthFileView              *self);
	void            (*set_drag_dest_pos)             (GthFileView              *self,
							  GdkDragContext           *context,
							  int                       x,
							  int                       y,
							  guint                     time,
			                      	          int                      *pos);
	GtkCellLayout * (*add_renderer)                  (GthFileView              *self,
							  GthFileViewRendererType   renderer_type,
							  GtkCellRenderer          *renderer);
	void            (*update_attributes)             (GthFileView              *self,
							  GtkCellRenderer          *checkbox_renderer,
							  GtkCellRenderer          *thumbnail_renderer,
							  GtkCellRenderer          *text_renderer,
							  int                       thumb_size);
	gboolean        (*truncate_metadata)             (GthFileView              *self);
};

GType           gth_file_view_get_type           (void);
void            gth_file_view_set_model          (GthFileView             *self,
					 	  GtkTreeModel            *model);
GtkTreeModel *  gth_file_view_get_model          (GthFileView             *self);
void            gth_file_view_scroll_to          (GthFileView             *self,
						  int                      pos,
						  double                   yalign);
GthVisibility   gth_file_view_get_visibility     (GthFileView             *self,
						  int                      pos);
int             gth_file_view_get_at_position    (GthFileView             *self,
						  int                      x,
						  int                      y);
int             gth_file_view_get_first_visible  (GthFileView             *self);
int             gth_file_view_get_last_visible   (GthFileView             *self);
void            gth_file_view_activated          (GthFileView             *self,
						  int                      pos);
void            gth_file_view_set_cursor         (GthFileView             *self,
						  int                      pos);
int             gth_file_view_get_cursor         (GthFileView             *self);
void            gth_file_view_set_spacing        (GthFileView             *self,
						  int                      spacing);
void            gth_file_view_enable_drag_source (GthFileView             *self,
				      		  GdkModifierType          start_button_mask,
				      		  const GtkTargetEntry    *targets,
				      		  int                      n_targets,
				      		  GdkDragAction            actions);
void            gth_file_view_unset_drag_source  (GthFileView             *self);
void            gth_file_view_enable_drag_dest   (GthFileView             *self,
				      		  const GtkTargetEntry    *targets,
				      		  int                      n_targets,
				      		  GdkDragAction            actions);
void            gth_file_view_unset_drag_dest    (GthFileView             *self);
void            gth_file_view_set_drag_dest_pos  (GthFileView             *self,
		 			          GdkDragContext          *context,
			                          int                      x,
			                          int                      y,
			                          guint                    time,
				                  int                     *pos);
GtkCellLayout * gth_file_view_add_renderer       (GthFileView             *self,
						  GthFileViewRendererType  renderer_type,
						  GtkCellRenderer         *renderer);
void            gth_file_view_update_attributes  (GthFileView              *self,
						  GtkCellRenderer          *checkbox_renderer,
						  GtkCellRenderer          *thumbnail_renderer,
						  GtkCellRenderer          *text_renderer,
						  int                       thumb_size);
gboolean        gth_file_view_truncate_metadata  (GthFileView              *self);
void            gth_file_view_activate_file      (GthFileView              *self,
						  GtkTreePath              *path);

G_END_DECLS

#endif /* GTH_FILE_VIEW_H */
