source_files = files(
  'main.c',
  'gth-metadata-provider-symlink.c'
)

symlink_times_mod = shared_module('symlink_times',
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
  input : 'symlink_times.extension.desktop.in.in',
  output : 'symlink_times.extension.in',
  configuration : extension_data
)

i18n.merge_file(
  input : extension_in_file,
  output : 'symlink_times.extension',
  type : 'desktop',
  po_dir : po_dir,
  install : true,
  install_dir : extensions_install_dir
)
