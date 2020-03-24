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
#include "gth-metadata-provider-hash.h"


#define BUFFER_SIZE 4096


G_DEFINE_TYPE (GthMetadataProviderHash, gth_metadata_provider_hash, GTH_TYPE_METADATA_PROVIDER)


static gboolean
gth_metadata_provider_hash_can_read (GthMetadataProvider  *self,
				      GthFileData          *file_data,
				      const char           *mime_type,
				      char                **attribute_v)
{
	return _g_file_attributes_matches_any_v ("general::hash",
					         attribute_v);
}


static void
gth_metadata_provider_hash_read (GthMetadataProvider *self,
				  GthFileData         *file_data,
				  const char          *attributes,
				  GCancellable        *cancellable)
{
	GFileInputStream *stream;
	guchar           *buffer;
	gsize             buffer_len;

	stream = g_file_read (file_data->file, cancellable, NULL);
	if (stream == NULL)
		return;

	/* Roughly center the read */
	g_seekable_seek (
		G_SEEKABLE (stream),
		(g_file_info_get_size (file_data->info) / BUFFER_SIZE - 1) / 2 * BUFFER_SIZE,
		G_SEEK_SET,
		cancellable,
		NULL
	);

	buffer = g_new (guchar, BUFFER_SIZE);
	if (! g_input_stream_read_all (G_INPUT_STREAM (stream),
				       buffer,
				       BUFFER_SIZE,
				       &buffer_len,
				       cancellable,
				       NULL))
	{
		buffer_len = 0;
	}

	if (buffer_len > 0) {
		GChecksum *checksum;
		guint8     digest[20];
		gsize      digest_len = sizeof (digest);
		guint64    hash;

		checksum = g_checksum_new (G_CHECKSUM_SHA1);
		g_checksum_update (checksum, buffer, buffer_len);
		g_checksum_get_digest (checksum, digest, &digest_len);
		g_checksum_free (checksum);

		memcpy (&hash, digest, MIN(sizeof (hash), digest_len));
		g_file_info_set_attribute_uint64 (file_data->info, "general::hash", hash);
	}

	g_free (buffer);
	g_object_unref (stream);
}


static void
gth_metadata_provider_hash_class_init (GthMetadataProviderHashClass *klass)
{
	GthMetadataProviderClass *metadata_provider_class;

	metadata_provider_class = GTH_METADATA_PROVIDER_CLASS (klass);
	metadata_provider_class->can_read = gth_metadata_provider_hash_can_read;
	metadata_provider_class->read = gth_metadata_provider_hash_read;
}


static void
gth_metadata_provider_hash_init (GthMetadataProviderHash *self)
{
	/* void */
}
