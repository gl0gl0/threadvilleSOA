#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

typedef struct _uivars {
	GtkWidget *mainWindow;
	GtkWidget *vbox;
	GtkWidget *drawingArea;
	GdkPixmap *pixMap;
} uivars;

uivars this;


#endif