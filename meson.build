# SPDX-License-Identifier: CC0-1.0
project('ipa_ipu3', 'c', 'cpp',
        meson_version : '>= 0.54',
        default_options : [
            'werror=true',
            'warning_level=2',
            'cpp_std=c++17',
        ],
        license : 'LGPL 2.1+')

subdir('data')

ipa_name = 'ipa_ipu3'

ipa_install_dir = get_option('libdir') / 'libcamera'

cc = meson.get_compiler('c')
libcamera_dep = dependency('camera')
libcamera_helper_dep = dependency('camera_helper')
libatomic = cc.find_library('atomic', required : false)

config_h = configuration_data()
config_h.set('MACRO_KBL_AIC', 1)
configure_file(output : 'config.h', configuration : config_h)
common_arguments = [
    '-Wshadow',
    '-include', 'config.h',
]

c_arguments = []
cpp_arguments = []

if cc.get_id() == 'clang'
    if cc.version().version_compare('<5')
        error('clang version is too old, libcamera requires 5.0 or newer')
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
    'ipu3.cpp',
])

ipa_includes = include_directories('include')

ipu3_ipa_deps = [
    libatomic,
    libcamera_dep,
    libcamera_helper_dep,
]

mod = shared_module(ipa_name,
                    [ipu3_ipa_files],
                    name_prefix : '',
                    include_directories : ipa_includes,
                    dependencies : ipu3_ipa_deps,
                    install : true,
                    install_dir : ipa_install_dir)

#if ipa_sign_module
#    custom_target(ipa_name + '.so.sign',
#                  input : mod,
#                  output : ipa_name + '.so.sign',
#                  command : [ipa_sign, ipa_priv_key, '@INPUT@', '@OUTPUT@'],
#                  install : false,
#                  build_by_default : true)
#endif



