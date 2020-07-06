<img src="fffWayPreview.gif" alt="wayPreview running on fff in floating mode"
height="260" align="right" style="margin-left: 1px; margin-bottom: 1px;"/>

# wayPreview

A client server, wayland native, terminal emulator independent image previewer

## Introduction

Terminal file managers are great, but they all have a major drawback when it
comes to image previews: lots of terminal emulators don't support them, moreover
it seems like there's no way to make this feature work natively on wayland.

In fact, this project's main goal is to bring the ranger with w3m or ueberzug
functionalities on all file managers and terminal emulators, in a completely
different way, while also adding more features and customisability.

For this reason, wayPreview is a GUI application, written in Qt. It can work
both as a floating and tiling and full screen window (if you have more than one
monitor). When used as a floating window, it looks the same as w3m for example,
the image preview occurs on top of the actual terminal window where the file
manager is running.

The server is the actual window that displays the image, the client is used to
send to the server the path of the image to be previewed and other options (like
the zoom) through a local (UNIX) socket.

Works out of the box with [my fork](https://github.com/Stivvo/fff) of the FFF
file manager and the [sway](https://github.com/swaywm/sway) window manager.

## Compile, install

Requires qt base, widgets and network. I encourage to look at
[install.sh](scripts/install.sh) and [unistall.sh](scripts/unistall.sh) before
running them.

```bash
mkdir wayPreview1
cd wayPreview1
git clone https://github.com/Stivvo/wayPreview
cd scripts
chmod +x compile.sh
./compile.sh
chmod +x install.sh
sudo ./install.sh
```

To unistall:

```bash
cd wayPreview1/wayPreview/scripts/
chmod +x unistall.sh
./unistall.sh
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

## Configuration

The installation process will create 4 executables:

* ``wayPreviewClient`` command line tool to open files and set options
* ``wayPreviewServer`` the window (always running)
* ``wrapWayPclient.sh`` appends to wayPreviewClient default options and opens a
    file passed as argument
* ``wrapWayPserver.sh`` executes the server, focuses tiling windows and
    runs wrapWayPclient.sh to view the first image passed as parameter

The command used by ``wrapWayPserver.sh`` to focus tiling windows is sway wm
specific, but is possible to adapt it to different window managers editing or
deliting its second last line.

My fork of fff works out of the box with wayPreview and only uses the shell
wrappers, which can easily be customized by the user. However, most terminal
file managers have a configuration file that can bind keys to shell commands.

The use of wayPreview isn't necessarily limited to previews for terminal file
managers though.

If for whatever reason something brakes, just delete the socket file:

```bash
sudo rm /tmp/wayPreview
```

## Options

All the options can be found with ``wayPreviewClient --help``. Those options can
only be set from the client and have effect on the server. They allow to open a
file, set any number of options, or both.

```
Usage: wayPreviewClient [options] [file]

Options:
  -h, --help        Displays help on commandline options.
  --help-all        Displays help including Qt specific options.
  --quit            close and disconnect the server
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

Arguments:
  [file]            Image file to open
```

The ``--infinite`` option is useful when running wayPreviewServer in full screen
mode, because it sets the window height

The factor is a decimal number that will multiply the related value by itself

The order in which the options appear on the menu is the same order in which
they are applied by the server. The exception is the file opening, which is
always done as first.

(The gif is lagging just because of the recording)

## Keyboard shortcuts

Even though the focus of this project is its client-server architecture, some
keyboard shortcuts on the server window may be useful too:

+ ``q`` close the window and the socket communication (same as ``--quit``)
+ ``s`` image real size (same as ``--normal``)
+ ``a`` fit the image to window (same as ``--fit``)
+ ``i`` zoom in the image (same as ``--zoom 1.1``)
+ ``o`` zoom out the image (same as ``--zoom 0.9``)
