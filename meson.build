project(
    'Teddy', 'c', 'cpp',

    default_options : [
        'c_std=c11',
        'cpp_std=c++2a'
    ],

    license: [
        'MIT',
    ],

    version: '1.0'
)

cpp = meson.get_compiler('cpp')
dl = cpp.find_library('dl', required: false)

threads_dep    = dependency('threads')
freetype_dep   = dependency('freetype2')
libpng_dep     = dependency('libpng')
opengl_dep     = dependency('opengl')
sdl2_dep       = dependency('sdl2')
SDL2_mixer_dep = dependency('SDL2_mixer')
SDL2_image_dep = dependency('SDL2_image')
libjpeg_dep    = dependency('libjpeg')
libpng_dep     = dependency('libpng')
zlib_dep       = dependency('zlib')

subdir('Teddy')
subdir('Programs')
