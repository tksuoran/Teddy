TeddyPlayer = executable(
    'TeddyPlayer',

    sources : [
        'src/CameraController.cpp',
        'src/EventManager.cpp',
        'src/SimpleText.cpp',
        'src/Root.cpp',
        'src/Display.cpp',
        'src/ObjectManager.cpp',
        'src/Node.cpp',
        'src/UserInterface.cpp'
    ],

    dependencies : [
        teddy_dep,
        opengl_dep,
        sdl2_dep,
        SDL2_mixer_dep,
        SDL2_image_dep,
        libjpeg_dep,
        libpng_dep,
        zlib_dep
    ],

    link_with : [
        teddy,
    ]
)
