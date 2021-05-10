# SPDX-License-Identifier: CC0-1.0
project('ipa_ipu3', 'c', 'cpp',
        meson_version : '>= 0.54',
        version : '0.0.0',
        default_options : [
            'werror=true',
            'warning_level=2',
            'cpp_std=c++17',
        ],
        license : 'LGPL 2.1+')

ipa_name = 'ipa_ipu3'

ipa_install_dir = get_option('libdir') / 'libcamera'

cc = meson.get_compiler('c')
libcamera_dep = dependency('camera')
libatomic = cc.find_library('atomic', required : false)

ia_deps = [
  cc.find_library('libia_aiq'),
  cc.find_library('libia_exc'),
  cc.find_library('libia_coordinate'),
  cc.find_library('libia_nvm'),
  cc.find_library('libia_cmc_parser'),
  cc.find_library('libia_mkn'),
  cc.find_library('libia_log'),
  cc.find_library('libSkyCamAICKBL'),
]

ia_imaging_dep = declare_dependency(
    dependencies : ia_deps,
    include_directories : include_directories('include/ia_imaging'),
)

config_h = configuration_data()

if cc.has_header_symbol('stdlib.h', 'secure_getenv', prefix : '#define _GNU_SOURCE')
    config_h.set('HAVE_SECURE_GETENV', 1)
endif

config_h.set('MACRO_KBL_AIC', 1)

configure_file(output : 'config.h', configuration : config_h)
common_arguments = [
    '-Wshadow',
    '-include', 'config.h',
]

ipa_includes = [
    include_directories('include'),
    include_directories('include/ia_imaging'),
    include_directories('.'),
]

c_arguments = []
cpp_arguments = []

if cc.get_id() == 'clang'
    if cc.version().version_compare('<5')
        error('clang version is too old, ipa-ipu3 requires 5.0 or newer')
    endif

    # Use libc++ by default if available instead of libstdc++ when compiling
    # with clang.
    if cc.find_library('libc++', required: false).found()
        cpp_arguments += [
            '-stdlib=libc++',
        ]
    endif

    cpp_arguments += [
        '-Wextra-semi',
    ]
endif

c_arguments += common_arguments
cpp_arguments += common_arguments

add_project_arguments(c_arguments, language : 'c')
add_project_arguments(cpp_arguments, language : 'cpp')

ipu3_ipa_files = files([
    'binary_data.cpp',
    'ipu3.cpp',
])

ipu3_ipa_deps = [
    libatomic,
    libcamera_dep,
    ia_imaging_dep,
]

subdir('aic')
subdir('aiq')
subdir('data')
subdir('src')
subdir('stats')

mod = shared_module(ipa_name,
                    [ipu3_ipa_files, libcamera_internal_sources],
                    name_prefix : '',
                    include_directories : ipa_includes,
                    dependencies : ipu3_ipa_deps,
                    install : true,
                    install_dir : ipa_install_dir)
