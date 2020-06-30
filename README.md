# wayPreview
A client server, wayland native, terminal emulator independent image previewer

## Introduction

Terminal file managers are great, but they all have a major drawback when it
comes to image previews:
lots of terminal emulators don't support image previews, moreover it seems like
there's no way to make this feature work natively on wayland.

For this reason, wayPreview is a GUI application, written in Qt. It can work
both as a floating and tiling and fullscreen window (if you have more than one
monitor). When used as a floating window, it looks the same as w3m for example,
the image preview occurs on top of the actual terminal
window where the file manager is running.

The server is the actual window that displays the image, the client is used to
send to the server the path of the image to be previewed and other options (like
the zoom) through a local (UNIX) socket.

My fork of [fff](https://github.com/Stivvo/fff) works out of the box with
wayPreview and the [sway window manager](https://github.com/swaywm/sway).
However, a one line editing of ``wrapWayPserver.sh`` could make it work with
every window manager.

However, most terminal file managers have a configuration file that can bind
keys to the execution of shell commands, therefore also wayPreviewClient.
The use of wayPreview isn't necessarely limited to previews in terminal file
managers through.

The server doesn't support any option, all must be done through the client. To
set default options, is possible to append them to ``wrapWayPclient.sh`` (my
fork of fff already uses it) or make your own wrapper script and use it instead
of wayPreviewClient.

## Compile, install, configure

Requires qt base, widgets and network

```bash
mkdir wayPreview
cd wayPreview
git clone https://github.com/Stivvo/wayPreview
chmod +x compile.sh
./compile.sh
chmod +x install.sh
sudo ./install.sh
```

To unistall:

```bash
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

## Options

All the options can be found with ``wayPreviewClient --help``. Those options can
only be set from the client and have effect on the server (open a file, set any
number of options, or both).

```
Usage: wayPreviewClient [options] [file]

Options:
  -h, --help        Displays help on commandline options.
  --help-all        Displays help including Qt specific options.
  --quit            close and disconnect the server
  --normal          image real size, 1:1 pixel
  --fit             fit image to window
  --zoom <factor>   zoom the image by a <factor> (< 1 zoomin, > 1 zoomout)
  --wsize <ratio>   set the <ratio>, between window height and screen height
                    (0.5 uses half of the screen height), 0.3 is default if not
                    set
  --wzoom <factor>  resize window by a <factor> (< 1 smaller, > 1 bigger)
  --infinite        assing the window the max possible size ("tiling" or
                    "fullscreen" mode). If is already set, it will return to
                    "floating" mode, with previous window size

Arguments:
  [file]            Image file to open
```

The ``--infinite`` option is useful when running wayPreviewServer in fullscreen
mode, because it sets the window height

The factor is a decimal number that will multiply the related value by itself

The order in which the options appear on the menu is the same order in which
they are applied by the server. The exception is the file opening, which is
always done as first.
