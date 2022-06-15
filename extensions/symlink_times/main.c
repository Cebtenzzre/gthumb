#include <config.h>
#include <gtk/gtk.h>
#include <gthumb.h>

#include "gth-metadata-provider-symlink.h"


GthMetadataInfo symlink_metadata_info[] = {
	{ "gth::file::symlink-display-btime", N_("Symlink Created Date & Time"), "file", 20, NULL, GTH_METADATA_ALLOW_EVERYWHERE },
	{ "gth::file::symlink-display-mtime", N_("Symlink Modified Date & Time"), "file", 21, NULL, GTH_METADATA_ALLOW_EVERYWHERE },
	{ "gth::file::symlink-created", "", "", 0, NULL, GTH_METADATA_ALLOW_NOWHERE },
	{ "gth::file::symlink-created-usec", "", "", 0, NULL, GTH_METADATA_ALLOW_NOWHERE },
	{ "gth::file::symlink-modified", "", "", 0, NULL, GTH_METADATA_ALLOW_NOWHERE },
	{ "gth::file::symlink-modified-usec", "", "", 0, NULL, GTH_METADATA_ALLOW_NOWHERE },
	{ NULL, NULL, NULL, 0, NULL, 0 }
};

static int
cmp_filename (GthFileData *a,
			    GthFileData *b)
{
	const char *key_a, *key_b;

	key_a = gth_file_data_get_filename_sort_key (a);
	key_b = gth_file_data_get_filename_sort_key (b);

	return strcmp (key_a, key_b);
}

static int
cmp_modified_time (GthFileData *a,
		   GthFileData *b)
{
	GTimeVal ta, tb;
	int      result;

	ta.tv_sec = g_file_info_get_attribute_uint64 (a->info, "gth::file::symlink-modified");
	ta.tv_usec = g_file_info_get_attribute_uint32 (a->info, "gth::file::symlink-modified-usec");
	tb.tv_sec = g_file_info_get_attribute_uint64 (b->info, "gth::file::symlink-modified");
	tb.tv_usec = g_file_info_get_attribute_uint32 (b->info, "gth::file::symlink-modified-usec");

	result = _g_time_val_cmp (&ta, &tb);
	if (result == 0)
		result = cmp_filename (a, b);

	return result;
}


static int
cmp_created_time (GthFileData *a,
		  GthFileData *b)
{
	GTimeVal ta, tb;
	int      result;

	ta.tv_sec = g_file_info_get_attribute_uint64 (a->info, "gth::file::symlink-created");
	ta.tv_usec = g_file_info_get_attribute_uint32 (a->info, "gth::file::symlink-created-usec");
	tb.tv_sec = g_file_info_get_attribute_uint64 (b->info, "gth::file::symlink-created");
	tb.tv_usec = g_file_info_get_attribute_uint32 (b->info, "gth::file::symlink-created-usec");

	result = _g_time_val_cmp (&ta, &tb);
	if (result == 0)
		result = cmp_filename (a, b);

	return result;
}

static GthFileDataSort symlink_times_sort_types[] = {
	{ "file::mtime-nofollow", N_("symlink modified date"), "gth::file::symlink-modified,gth::file::symlink-modified-usec", cmp_modified_time },
	{ "file::btime-nofollow", N_("symlink created date"), "gth::file::symlink-created,gth::file::symlink-created-usec", cmp_created_time }
};

G_MODULE_EXPORT void
gthumb_extension_activate (void)
{
	int i;
	gth_main_register_metadata_info_v (symlink_metadata_info);
	gth_main_register_metadata_provider (GTH_TYPE_METADATA_PROVIDER_SYMLINK);
	for (i = 0; i < G_N_ELEMENTS (symlink_times_sort_types); i++)
		gth_main_register_sort_type (&symlink_times_sort_types[i]);
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
