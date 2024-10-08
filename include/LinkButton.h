#ifndef LINKBUTTON_H
#define LINKBUTTON_H

#include <gtk/gtk.h>

class LinkButton {
public:
    LinkButton(const char* uri, const char* label);
    GtkWidget* getWidget();

private:
    GtkWidget* link_button;
};

#endif // LINKBUTTON_H
