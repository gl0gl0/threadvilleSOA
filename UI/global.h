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

enum CarType {
	RED,
	BLUE,
	GREEN,
	BLACK,
	WHITE,
	YELLOW
};

GtkWidget *carPathInput;
GtkWidget *carTypeCombo;
GtkWidget *carModeCheck;

GtkWidget *ambulancePathInput;
GtkWidget *ambulanceModeCheck;

GtkWidget *redBusModeCheck;
GtkWidget *greenBusModeCheck;
GtkWidget *blueBusModeCheck;
GtkWidget *whiteBusModeCheck;
GtkWidget *grayBusModeCheck;
GtkWidget *blackBusModeCheck;
GtkWidget *lightBlueBusModeCheck;
GtkWidget *pinkBusModeCheck;
GtkWidget *orangeBusModeCheck;
GtkWidget *allBusesModeCheck;
GtkWidget *obstaclesModeCheck;


#endif