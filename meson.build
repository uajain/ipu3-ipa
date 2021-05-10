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

ipa_includes = [
    include_directories('include'),
]

subdir('src')
