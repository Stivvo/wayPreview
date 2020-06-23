QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

HEADERS       = wayPreviewServer.h
SOURCES       = wayPreviewServer.cpp \
                main.cpp
