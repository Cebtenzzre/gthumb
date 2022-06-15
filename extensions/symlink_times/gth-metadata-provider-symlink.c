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
#include <glib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gthumb.h>
#include "gth-metadata-provider-symlink.h"


G_DEFINE_TYPE (GthMetadataProviderSymlink, gth_metadata_provider_symlink, GTH_TYPE_METADATA_PROVIDER)


static gboolean
gth_metadata_provider_symlink_can_read (GthMetadataProvider  *self,
					GthFileData          *file_data,
					const char           *mime_type,
					char                **attribute_v)
{
	return _g_file_attributes_matches_any_v ("gth::file::symlink-created,"
					         "gth::file::symlink-created-usec,"
					         "gth::file::symlink-modified,"
					         "gth::file::symlink-modified-usec,"
						 "gth::file::symlink-display-btime,"
						 "gth::file::symlink-display-mtime",
					         attribute_v);
}


static void
gth_metadata_provider_symlink_read (GthMetadataProvider *self,
				    GthFileData         *file_data,
				    const char          *attributes,
				    GCancellable        *cancellable)
{
	GFileInfo *info;
	GTimeVal   time;
	char      *value;

	info = g_file_query_info (file_data->file,
				  "time::*",
				  G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
				  cancellable,
				  NULL);
	if (info == NULL)
		return;

	time.tv_sec = g_file_info_get_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_CREATED);
	time.tv_usec = g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_TIME_CREATED_USEC);
	g_file_info_set_attribute_uint64 (file_data->info, "gth::file::symlink-created", time.tv_sec);
	g_file_info_set_attribute_uint32 (file_data->info, "gth::file::symlink-created-usec", time.tv_usec);

	value = _g_time_val_strftime (&time, "%x %X");
	g_file_info_set_attribute_string (file_data->info, "gth::file::symlink-display-btime", value);
	g_free (value);

	g_file_info_get_modification_time (info, &time);
	g_file_info_set_attribute_uint64 (file_data->info, "gth::file::symlink-modified", time.tv_sec);
	g_file_info_set_attribute_uint32 (file_data->info, "gth::file::symlink-modified-usec", time.tv_usec);

	value = _g_time_val_strftime (&time, "%x %X");
	g_file_info_set_attribute_string (file_data->info, "gth::file::symlink-display-mtime", value);
	g_free (value);

	g_object_unref (info);
}


static void
gth_metadata_provider_symlink_class_init (GthMetadataProviderSymlinkClass *klass)
{
	GthMetadataProviderClass *metadata_provider_class;

	metadata_provider_class = GTH_METADATA_PROVIDER_CLASS (klass);
	metadata_provider_class->can_read = gth_metadata_provider_symlink_can_read;
	metadata_provider_class->read = gth_metadata_provider_symlink_read;
}


static void
gth_metadata_provider_symlink_init (GthMetadataProviderSymlink *self)
{
	/* void */
}
