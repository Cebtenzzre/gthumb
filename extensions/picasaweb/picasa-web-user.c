/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  GThumb
 *
 *  Copyright (C) 2010 Free Software Foundation, Inc.
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
#include <stdlib.h>
#include <string.h>
#include <gthumb.h>
#include "picasa-web-user.h"


static void picasa_web_user_dom_domizable_interface_init (DomDomizableInterface *iface);


G_DEFINE_TYPE_WITH_CODE (PicasaWebUser,
			 picasa_web_user,
			 G_TYPE_OBJECT,
			 G_IMPLEMENT_INTERFACE (DOM_TYPE_DOMIZABLE,
					        picasa_web_user_dom_domizable_interface_init))


static void
picasa_web_user_finalize (GObject *obj)
{
	PicasaWebUser *self;

	self = PICASA_WEB_USER (obj);

	g_free (self->id);
	g_free (self->nickname);
	g_free (self->icon);

	G_OBJECT_CLASS (picasa_web_user_parent_class)->finalize (obj);
}


static void
picasa_web_user_class_init (PicasaWebUserClass *klass)
{
	G_OBJECT_CLASS (klass)->finalize = picasa_web_user_finalize;
}


static DomElement*
picasa_web_user_create_element (DomDomizable *base,
				DomDocument  *doc)
{
	PicasaWebUser *self;
	DomElement    *element;

	self = PICASA_WEB_USER (base);

	element = dom_document_create_element (doc, "entry",
					       "xmlns", "http://www.w3.org/2005/Atom",
					       "xmlns:media", "http://search.yahoo.com/mrss/",
					       "xmlns:gphoto", "http://schemas.google.com/photos/2007",
					       NULL);
	if (self->id != NULL)
		dom_element_append_child (element, dom_document_create_element_with_text (doc, self->id, "gphoto:user", NULL));
	if (self->nickname != NULL)
		dom_element_append_child (element, dom_document_create_element_with_text (doc, self->nickname, "gphoto:nickname", NULL));
	if (self->icon != NULL)
		dom_element_append_child (element, dom_document_create_element_with_text (doc, self->icon, "icon", NULL));

	dom_element_append_child (element,
				  dom_document_create_element (doc, "category",
							       "scheme", "http://schemas.google.com/g/2005#kind",
							       "term", "http://schemas.google.com/photos/2007#user",
							       NULL));

	return element;
}


static void
picasa_web_user_load_from_element (DomDomizable *base,
				   DomElement   *element)
{
	PicasaWebUser *self;
	DomElement    *node;

	self = PICASA_WEB_USER (base);

	picasa_web_user_set_id (self, NULL);
	picasa_web_user_set_nickname (self, NULL);
	picasa_web_user_set_icon (self, NULL);
	self->quota_limit = 0;
	self->quota_current = 0;
	self->max_photos_per_album = 0;

	for (node = element->first_child; node; node = node->next_sibling) {
		if (g_strcmp0 (node->tag_name, "gphoto:user") == 0) {
			picasa_web_user_set_id (self, dom_element_get_inner_text (node));
		}
		else if (g_strcmp0 (node->tag_name, "gphoto:nickname") == 0) {
			picasa_web_user_set_nickname (self, dom_element_get_inner_text (node));
		}
		else if (g_strcmp0 (node->tag_name, "icon") == 0) {
			picasa_web_user_set_icon (self, dom_element_get_inner_text (node));
		}
		else if (g_strcmp0 (node->tag_name, "gphoto:quotalimit") == 0) {
			picasa_web_user_set_quota_limit (self, dom_element_get_inner_text (node));
		}
		else if (g_strcmp0 (node->tag_name, "gphoto:quotacurrent") == 0) {
			picasa_web_user_set_quota_current (self, dom_element_get_inner_text (node));
		}
		else if (g_strcmp0 (node->tag_name, "gphoto:maxPhotosPerAlbum") == 0) {
			picasa_web_user_set_max_photos (self, dom_element_get_inner_text (node));
		}
	}
}


static void
picasa_web_user_dom_domizable_interface_init (DomDomizableInterface *iface)
{
	iface->create_element = picasa_web_user_create_element;
	iface->load_from_element = picasa_web_user_load_from_element;
}


static void
picasa_web_user_init (PicasaWebUser *self)
{
	/* void */
}


PicasaWebUser *
picasa_web_user_new (void)
{
	return g_object_new (PICASA_WEB_TYPE_USER, NULL);
}


void
picasa_web_user_set_id (PicasaWebUser *self,
			const char    *value)
{
	_g_strset (&self->id, value);
}


void
picasa_web_user_set_nickname (PicasaWebUser *self,
			      const char    *value)
{
	_g_strset (&self->nickname, value);
}


void
picasa_web_user_set_icon (PicasaWebUser *self,
			  const char    *value)
{
	_g_strset (&self->icon, value);
}


void
picasa_web_user_set_quota_limit (PicasaWebUser *self,
				 const char    *value)
{
	self->quota_limit = g_ascii_strtoull (value, NULL, 10);
}


void
picasa_web_user_set_quota_current (PicasaWebUser *self,
				   const char    *value)
{
	self->quota_current = g_ascii_strtoull (value, NULL, 10);
}


void
picasa_web_user_set_max_photos (PicasaWebUser *self,
			        const char     *value)
{
	if (value != NULL)
		self->max_photos_per_album = atoi (value);
	else
		self->max_photos_per_album = 0;
}