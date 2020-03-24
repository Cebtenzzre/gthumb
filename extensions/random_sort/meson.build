source_files = files(
  'main.c',
  'gth-metadata-provider-hash.c'
)

random_sort_mod = shared_module('random_sort',
  sources : source_files,
  dependencies : [ extension_common_deps ],
  include_directories : [ config_inc, gthumb_inc ],
  c_args : c_args,
  install : true,
  install_dir : extensions_install_dir,
  install_rpath : extensions_install_dir
)

# .extension file

extension_in_file = configure_file(
  input : 'random_sort.extension.desktop.in.in',
  output : 'random_sort.extension.in',
  configuration : extension_data
)

i18n.merge_file(
  input : extension_in_file,
  output : 'random_sort.extension',
  type : 'desktop',
  po_dir : po_dir,
  install : true,
  install_dir : extensions_install_dir
)
