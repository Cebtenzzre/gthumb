#include <config.h>
#include <gtk/gtk.h>
#include <gthumb.h>

#include "gth-metadata-provider-hash.h"


#define ROR64(x,n) (((x) >> (n)) | ((x) << (64 - (n))))

GthMetadataInfo hasher_metadata_info[] = {
	{ "general::hash", N_("Hash"), "general", 100, NULL, GTH_METADATA_ALLOW_EVERYWHERE },
	{ NULL, NULL, NULL, 0, NULL, 0 }
};

static int
cmp_hash (GthFileData *a,
	  GthFileData *b,
	  guint64 xor,
	  guint64 ror)
{
	guint64 hasha = g_file_info_get_attribute_uint64 (a->info, "general::hash");
	guint64 hashb = g_file_info_get_attribute_uint64 (b->info, "general::hash");

	if (hasha == 0 || hashb == 0 || hasha == hashb) {
		const char *key_a, *key_b;

		if (hasha == 0 || hashb == 0) {
			g_printerr (
				"WARNING: cmp_hash using fallback sort because%s%s\n",
				hasha == 0 ? " hasha=0" : "",
				hashb == 0 ? " hashb=0" : ""
			);
		}

		key_a = g_file_info_get_display_name (a->info);
		key_b = g_file_info_get_display_name (b->info);
		return strcoll (key_a, key_b);
	}

	return ROR64(hasha ^ xor, ror) > ROR64(hashb ^ xor, ror) ? 1 : -1;
}

static int
cmp_hash1 (GthFileData *a,
	   GthFileData *b)
{
	return cmp_hash (a, b, 0x46a4c4ade6595be5, 6);
}

static int
cmp_hash2 (GthFileData *a,
	   GthFileData *b)
{
	return cmp_hash (a, b, 0xed7cd21e31aa5177, 47);
}

static int
cmp_hash3 (GthFileData *a,
	   GthFileData *b)
{
	return cmp_hash (a, b, 0x999768a9a3ec5885, 2);
}

static int
cmp_hash4 (GthFileData *a,
	   GthFileData *b)
{
	return cmp_hash (a, b, 0xb156f901c3360fb8, 18);
}

static int
cmp_hash5 (GthFileData *a,
	   GthFileData *b)
{
	return cmp_hash (a, b, 0xbc4c97663d74af24, 0);
}

GthFileDataSort random_sort_sort_types[] = {
	{ "general::hash1_sort", N_("hash (1)"), "general::hash", cmp_hash1 },
	{ "general::hash2_sort", N_("hash (2)"), "general::hash", cmp_hash2 },
	{ "general::hash3_sort", N_("hash (3)"), "general::hash", cmp_hash3 },
	{ "general::hash4_sort", N_("hash (4)"), "general::hash", cmp_hash4 },
	{ "general::hash5_sort", N_("hash (5)"), "general::hash", cmp_hash5 }
};

G_MODULE_EXPORT void
gthumb_extension_activate (void)
{
	gth_main_register_metadata_info_v (hasher_metadata_info);
	gth_main_register_metadata_provider (GTH_TYPE_METADATA_PROVIDER_HASH);
	int i;
	for (i = 0; i < G_N_ELEMENTS (random_sort_sort_types); i++)
		gth_main_register_sort_type (&random_sort_sort_types[i]);
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
