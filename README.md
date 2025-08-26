# Audio Switcher

Audio Switcher is a simple GTK application for Linux that lets you toggle between two audio outputs (speakers and headphones) with a single click.

## Features

- Detects current default audio output (sink) using PulseAudio.
- Switches between speakers and headphones.
- Provides a minimal graphical interface with a button and status label.

## Installation

Run the install script to build and install the application:

```sh
./install.sh
```

This will compile `switcher.c` and copy the resulting binary to `/usr/local/bin/Switcher`.

## Usage

Launch the application from your desktop environment or run:

```sh
Switcher
```

You can also use the provided [switcher.desktop](switcher.desktop) file to add it to your application menu.

## Requirements

- GTK+ 3
- PulseAudio (`pactl` command)

## Files

- [`switcher.c`](switcher.c): Main source code for the application.
- [`install.sh`](install.sh): Build and install script.
- [`switcher.desktop`](switcher.desktop): Desktop entry for launching the app.
- [`.gitignore`](.gitignore): Ignores the built binary.
- [`.vscode/c_cpp_properties.json`](.vscode/c_cpp_properties.json): VSCode configuration for C/C++.

## License

MIT License (add your license text here)
