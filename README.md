<img src="fffWayPreview.gif" alt="wayPreview running on fff in floating mode"
height="260" align="right" style="margin-left: 1px; margin-bottom: 1px;"/>

# wayPreview

A client server, wayland native, terminal emulator independent image previewer.

## Introduction

Terminal file managers are great, but they all have a major drawback when it
comes to image previews: lots of terminal emulators don't support them, moreover
it seems like there's no way to make this feature work natively on wayland.

In fact, this project's main goal is to bring the functionalities of ranger with
w3m or ueberzug on all file managers and terminal emulators in a completely
different way, while also adding more features and customisability.

For this reason, wayPreview is a GUI application, written in Qt. It can work
both as a floating and as tiling/fullscreen window. When used as a floating
window, it behaves similarly to w3m (like in the gif above): the image preview
occurs on top of the actual terminal window where the file manager is running.

The server is the actual window that displays the image, the client is used to
send to the server the path of the image to be previewed and other options (like
the zoom) through a local (UNIX) socket.

Works out of the box with [my fork](https://github.com/Stivvo/fff) of the FFF
file manager and the [sway](https://github.com/swaywm/sway) window manager.

## Installation

To run only ``qt5-base`` (Archlinux) or ``qt5-default`` (Debian) is required.

### Compile

To compile, Qt version must be at least 5.14.

```bash
mkdir wayPreview1
cd wayPreview1
git clone https://github.com/Stivvo/wayPreview
cd scripts
./compile.sh
```

### Install

Manually add ``../../clientBuild/wayPreviewClient``,
``../../serverBuild/wayPreviewServer`` and all the scripts in the
[wrappers](wrappers) directory to your path.

However, in case of multiple users on the system or for a simpler install
process just run:

```bash
sudo ./install.sh install program
./install.sh install config
```

Run the second commands for each user and add ``~/.local/bin`` to their path to
use the wrappers. Backup wrappers are stored in ``/etc/wayPreview``

### Uninstall

```bash
sudo ./uninstall.sh
```

Run the last command for each user. I encourage to look at
[install.sh](scripts/install.sh) and [uninstall.sh](scripts/uninstall.sh) before
running them.

### Development

To install symbolic links for development:

```bash
sudo ./install.sh link program
./install.sh link config
```

### Universal package

Go to [releases](https://github.com/Stivvo/wayPreview/releases), download the
universal package (or create your own with ``./createPackage.sh``), then:

```bash
unzip wayPreview_universal_v1.1.zip
cd wayPreview_universal_v1.1
sudo ./install.sh
./installConfig.sh
```

## Configuration

The installation process will create 4 executables:

* ``wayPreviewClient`` command line tool to open files and set options (runs
    instantly)
* ``wayPreviewServer`` the window (always running)
* ``wrappers/wrapWayP*.sh`` run append the client or to the server with
    default options and open a file passed as argument. Keep in mind that the
    server wrapper will run just for the first time.
* ``wrappers/wrapSetPos.sh`` contains window manager specific commands (some
    window managers ignore the position set from the application itself) to set
    the position of the server window, if ``--wx`` and ``--wy`` options are
    provided to wayPreviewServer, and focus tiling windows. It is meant to be
    used only in floating mode.

My fork of fff works out of the box with wayPreview. However, most terminal file
managers have a configuration file that allows to bind keys to shell commands.
It's better to configure your file manager to run the shell wrappers to isolate
the configuration of wayPreview.

The use of wayPreview isn't necessarily limited to previews for terminal file
managers though.

If for whatever reason something brakes, just delete the socket files (each
wayPreview session has a different one, see ``--socket`` option):

```bash
sudo rm /tmp/wayPreview*
```

You may want to make the window always floating: this is how you do that on the
sway window manager:

```
for_window [app_id="wayPreviewServer"] floating enable
```

You may also want to disable borders:

```
for_window [app_id="wayPreviewServer"] border none
```

To set a default position without using ``--wx`` and ``--wy`` options:

```
for_window [app_id="wayPreviewServer"] move position 500 50
```

## Options

All the options can be found with ``wayPreviewClient --help`` or
``wayPreviewServer --help``. They allow to open a file, set any number of
options, or both. Options are normally set from the client, but it may be useful
to set them directly on the server when it is started for the first time.

```
Usage: wayPreviewServer [options] [file]

Options:
  -h, --help        Displays help on commandline options.
  --help-all        Displays help including Qt specific options.
  --quit            close and disconnect the server
  --socket <name>   name for the wayPreview instance (string to append to the
                    socket <name>), allows to run more than one instance of
                    wayPreview at the same time, optional
  --wsize <ratio>   set the <ratio>, between window height and screen height
                    (0.5 uses half of the screen height), 0.3 is default if not
                    set
  --wzoom <factor>  resize window by a <factor> (< 1 smaller, > 1 bigger)
  --infinite        assing the window the max possible size ("tiling" or
                    "fullscreen" mode). If is already set, it will return to
                    "floating" mode, with previous window size
  --normal          image real size, 1:1 pixel
  --fit             fit image to window
  --zoom <factor>   zoom the image by a <factor> (< 1 zoomin, > 1 zoomout)
  --wx <position>   set window horizontal position in floating mode, wy must
                    also be set for this option to take effect. If it isn't set,
                    the window manager will decide the position
  --wy <position>   set window vertical position in floating mode, wx must also
                    be set for this option to take effect. If it isn't set, the
                    window manager will decide the position

Arguments:
  [file]            Image file to open
```

The ``--infinite`` option is useful when running wayPreviewServer in full screen
or tiling mode, because it sets the the height of. It should be used together
with something like ``--fit``. Don't follow the sway commands of the previous
section if you want to make wayPreviewServer tiling.

The factor is a decimal number that will multiply the related value by itself

The order in which the options appear on the menu is the same order in which
they are applied by the server. The exception is the file opening, which is
always done as first.

(Lag in the gif is due to the recording)

## Keyboard shortcuts

Even though the focus of this project is its client-server architecture, some
keyboard shortcuts on the server window may be useful too:

+ ``q`` close the window and the socket communication (same as ``--quit``)
+ ``s`` image real size (same as ``--normal``)
+ ``a`` fit the image to window (same as ``--fit``)
+ ``i`` zoom in the image (same as ``--zoom 1.1``)
+ ``o`` zoom out the image (same as ``--zoom 0.9``)
