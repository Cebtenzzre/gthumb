/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  GThumb
 *
 *  Copyright (C) 2011 Free Software Foundation, Inc.
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
#include <gthumb.h>
#include "cairo-io-jpeg.h"
#include "cairo-io-png.h"
#include "cairo-io-svg.h"


G_MODULE_EXPORT void
gthumb_extension_activate (void)
{
#ifdef HAVE_LIBJPEG
	gth_main_register_image_loader_func (_cairo_image_surface_create_from_jpeg,
					     GTH_IMAGE_FORMAT_CAIRO_SURFACE,
					     "image/jpeg",
					     NULL);
#endif
	gth_main_register_image_loader_func (_cairo_image_surface_create_from_png,
					     GTH_IMAGE_FORMAT_CAIRO_SURFACE,
					     "image/png",
					     NULL);
#ifdef HAVE_LIBRSVG
	gth_main_register_image_loader_func (_cairo_image_surface_create_from_svg,
					     GTH_IMAGE_FORMAT_CAIRO_SURFACE,
					     "image/svg+xml",
					     NULL);
#endif
}


G_MODULE_EXPORT void
gthumb_extension_deactivate (void)
{
}


G_MODULE_EXPORT gboolean
gthumb_extension_is_configurable (void)
{
	return FALSE;
}


G_MODULE_EXPORT void
gthumb_extension_configure (GtkWindow *parent)
{
}
