#ifndef UI_H
#define UI_H

typedef struct _uivars {
	GtkWidget *mainWindow;
	GtkWidget *drawingArea;
	GdkPixmap *pixMap;
} uivars;

uivars this;

void initUI();

#endif