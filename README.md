<img src="fffWayPreview.gif" alt="wayPreview running on fff in floating mode"
height="260" align="right" style="margin-left: 1px; margin-bottom: 1px;"/>

# wayPreview

A client server, wayland native, terminal emulator independent image previewer

## Introduction

Terminal file managers are great, but they all have a major drawback when it
comes to image previews: lots of terminal emulators don't support them, moreover
it seems like there's no way to make this feature work natively on wayland.

In fact, this project's main goal is to bring the functionalities of ranger with
w3m or ueberzug on all file managers and terminal emulators in a completely
different way, while also adding more features and customisability.

For this reason, wayPreview is a GUI application, written in Qt. It can work
both as a floating and as tiling or full screen window. When used as a floating
window, it behaves similarly to w3m and (like the gif above): the image preview
occurs on top of the actual terminal window where the file manager is prunning.

The server is the actual window that displays the image, the client is used to
send to the server the path of the image to be previewed and other options (like
the zoom) through a local (UNIX) socket.

Works out of the box with [my fork](https://github.com/Stivvo/fff) of the FFF
file manager and the [sway](https://github.com/swaywm/sway) window manager.

## Compile, install

For compiling, qt base, widgets and network are required.

```bash
mkdir wayPreview1
cd wayPreview1
git clone https://github.com/Stivvo/wayPreview
cd scripts
chmod +x compile.sh
./compile.sh
```

To install you can manually add ``../../clientBuild/wayPreviewClient``,
``../../serverBuild/wayPreviewServer`` and all the scripts in the
[config](config) directory to your path.

However, in case of multiple users on the system or for a simpler install
process just run:

```bash
chmod +x install.sh
sudo ./install.sh
chmod +x installConfig.sh
./installConfig.sh
```

The last command will show you where the configuration scripts are located,
that's where you can set default options and configure wayPreview for your
window manager. Run ``installConfig.sh`` for each user.

Alternatively it's possible to copy the default configurations created in
``/etc/wayPreview`` by ``install.sh`` to ``$XDG_CONFIG_HOME/wayPreview`` for each
user.

To uninstall:

```bash
cd wayPreview1/wayPreview/scripts/
chmod +x uninstall.sh.sh
sudo ./uninstall.sh.sh
```

And delete the config files for each user.

I encourage to look at [install.sh](scripts/install.sh) and
[uninstall.sh.sh](scripts/uninstall.sh.sh) before running them.

## Configuration

The installation process will create 4 executables:

* ``wayPreviewClient`` command line tool to open files and set options (runs
    instantly)
* ``wayPreviewServer`` the window (always running)
* ``config/wrapWayPclient.sh`` and ``config/wrapWayPserver.sh`` append to the
    client and to the server respectively default options and open a file passed
    as argument. Keep in mind that the server wrapper will run just for the
    first time, then only use the client wrapper until you close the server.
* ``wrappers/*.sh`` just run the ``config/*.sh`` wrappers for the current user.
* ``wrapSetPos.sh`` contains window manager specific commands (sway in my case,
    but you can easily customize it) to set the position of the server window
    (when using --wx and --wy options, see below) and then focus tiling windows,
    since some window managers ignore the position set from the program itself.
    It is meant to be used only in floating mode. If --wx and --wy aren't set to
    wayPreviewServer, it is implicitly run with -1 -1 as parameters, so it just
    focuses tiling without setting the position

My fork of fff works out of the box with wayPreview. However, most terminal file
managers have a configuration file that allows to bind keys to shell commands.
It's better to configure your file manager to use the shell wrappers to separe
your file manager's config from wayPreview's config.

The use of wayPreview isn't necessarily limited to previews for terminal file
managers though.

If for whatever reason something brakes, just delete the socket file:

```bash
sudo rm /tmp/wayPreview
```

``install.sh`` will install the wrapper scripts in ``/usr/bin`` but in case of
multimple users it may be better to move them to something like ``~/.local`` and
add that directory to the user ``$PATH``.

You may want to make the window always floating: this is how you do that on the
sway window manager:

```
for_window [app_id="wayPreviewServer"] floating enable
```

You may also want to disable borders:

```
for_window [app_id="wayPreviewServer"] border none
```

To set a default position without using --wx and --wy options:

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
  --wx <position>   set window horizontal position, wy must also be set for
                    this option to take effect
  --wy <position>   set window vertical position, wx must also be set for this
                    option to take effect

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
