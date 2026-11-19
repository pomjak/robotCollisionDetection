# ICP-24: Robot Collision Detection Simulator

ICP-24 is a Qt Widgets desktop application that simulates autonomous robots
moving around rectangular obstacles. Each robot has a configurable speed,
orientation, detection distance, turn angle, and turn direction. During the
simulation, a robot moves forward when its detection area is clear and turns
when it detects an obstacle, another robot, or the edge of the scene.

The scene can also be edited interactively: objects can be spawned, selected,
moved, resized or reconfigured, and saved as JSON for later use.

## Authors

- Pomsar Jakub (`xpomsa00`)
- Simon Cagala (`xcagal00`)

## Features

- Autonomous robot movement with collision detection and avoidance.
- Manual control of a selected robot.
- Rectangular obstacles with editable width and height.
- Random, non-overlapping robot and obstacle spawning.
- Drag-and-drop scene editing.
- Robot and obstacle property dialogs.
- JSON save/load support.
- Zooming and a 1920 × 1080 simulation scene.
- Doxygen documentation generation.

## Requirements

- Qt 5 or Qt 6 with Widgets support.
- A C++17 compiler.
- `qmake`.
- GNU Make.

## Build and run

Build the application from the repository root:

```sh
make
```

The executable is created as `./icp24`. Build and launch it in one step with:

```sh
make run
```

Remove generated build files and the executable with:

```sh
make clean
```

The Makefile creates a temporary `build/` directory, runs `qmake`, compiles
the project, and copies the resulting executable back to the repository root.
The project can also be opened directly in Qt Creator using `icp24.pro`.

## Using the simulator

The application starts with an empty scene. Use the **Simulation** menu or the
shortcuts below to create a layout:

| Action | Shortcut |
| --- | --- |
| Play / pause simulation | `Space` |
| Add a robot | `Ctrl+N` |
| Add an obstacle | `Ctrl+M` |
| Load a JSON layout | `Ctrl+O` |
| Save the current layout | `Ctrl+S` |
| Clear the scene | `Ctrl+L` |
| Exit | `Ctrl+Q` |
| Zoom in / out | `+` / `-` |
| Delete selected items | `Delete` |

Object interaction:

- **Click and drag** an object to move it.
- **Ctrl+click** an object to select or deselect it.
- **Double-click** a robot or obstacle to open its properties dialog.
- **Right-click** a robot to enable manual control.
- With a manually controlled robot, use `Up` or `W` to move forward and
  `Left`/`A` or `Right`/`D` to rotate.
- The robot's detection area is shown in front of it. Manual and autonomous
  movement are blocked when that area would leave the scene or overlap another
  object.

## JSON layout files

Layouts are JSON objects containing `robots` and `obstacles` arrays. A robot
entry contains its position and movement parameters:

```json
{
  "robots": [
    {
      "x": 49,
      "y": 44,
      "orientation": 0,
      "speed": 0.5,
      "rotation": 12,
      "detection_dist": 25,
      "clockwise": true
    }
  ],
  "obstacles": [
    {
      "x": 75,
      "y": 27,
      "width": 80,
      "height": 20
    }
  ]
}
```

Ready-made layouts are available in [`examples/`](examples/), including
[`examples/intro.json`](examples/intro.json). The application writes the same
format when a layout is saved.

## Documentation

Generate HTML and LaTeX API documentation with:

```sh
make doxygen
```

Generated documentation is placed under `doc/html` and `doc/latex`.

## Known limitations

- Obstacles cannot be rotated.
- New objects are placed by repeatedly choosing random positions. If the
  scene has no remaining free space, spawning can take indefinitely.
- There is no automated test suite in the repository; validation is currently
  performed through the Qt application and the provided example layouts.
