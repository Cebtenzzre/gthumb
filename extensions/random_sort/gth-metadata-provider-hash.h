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

#ifndef GTH_METADATA_PROVIDER_HASH_H
#define GTH_METADATA_PROVIDER_HASH_H

#include <glib.h>
#include <glib-object.h>
#include <gthumb.h>

#define GTH_TYPE_METADATA_PROVIDER_HASH         (gth_metadata_provider_hash_get_type ())
#define GTH_METADATA_PROVIDER_HASH(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GTH_TYPE_METADATA_PROVIDER_HASH, GthMetadataProviderHash))
#define GTH_METADATA_PROVIDER_HASH_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST ((k), GTH_TYPE_METADATA_PROVIDER_HASH, GthMetadataProviderHashClass))
#define GTH_IS_METADATA_PROVIDER_HASH(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GTH_TYPE_METADATA_PROVIDER_HASH))
#define GTH_IS_METADATA_PROVIDER_HASH_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), GTH_TYPE_METADATA_PROVIDER_HASH))
#define GTH_METADATA_PROVIDER_HASH_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), GTH_TYPE_METADATA_PROVIDER_HASH, GthMetadataProviderHashClass))

typedef struct _GthMetadataProviderHash         GthMetadataProviderHash;
typedef struct _GthMetadataProviderHashClass    GthMetadataProviderHashClass;

struct _GthMetadataProviderHash
{
	GthMetadataProvider __parent;
};

struct _GthMetadataProviderHashClass
{
	GthMetadataProviderClass __parent_class;
};

GType gth_metadata_provider_hash_get_type (void) G_GNUC_CONST;

#endif /* GTH_METADATA_PROVIDER_HASH_H */
