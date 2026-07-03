Bouncing Ball Physics (SDL3)

A simple C++ physics simulator built with SDL3: gravity, wall bounces with energy loss, mouse dragging with throw inertia.

Features


Gravity-driven falling and bouncing with damping on collisions
Ground friction so the ball settles instead of sliding forever
Drag-and-throw with mouse, preserving velocity on release
Impact sound on wall collisions, volume scaled by hit strength
FPS counter in the window title


Stack

C++17
SDL3


Project structure

BallSimulation/
├── CMakeLists.txt
├── README.md
└── src/
    ├── scripts/
    │   ├── cpp/        # .cpp sources
    │   └── headers/     # .hpp headers
    └── sound/
        └── Bonk_Sound_Effect.wav

Build

Requires SDL3 (installed system-wide, or CMake will fetch and build it automatically).

bash# Arch Linux (optional, CMake falls back to FetchContent if missing)
sudo pacman -S sdl3

mkdir build && cd build
cmake ..
cmake --build . --config Release

Run

bashcd build
./BouncingBall

Run from inside build/ — the sound path is relative to the executable.

Controls


Click and drag the ball to move it
Throw it (flick the mouse before releasing) to launch it with inertia
Also you can move ball with A and D keys on your keyboard


License

MIT