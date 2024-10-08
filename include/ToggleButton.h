#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <gtk/gtk.h>

class ToggleButton {
public:
    ToggleButton(const char* label);
    GtkWidget* getWidget();

private:
    GtkWidget* togglebutton;
};

#endif // TOGGLEBUTTON_H
