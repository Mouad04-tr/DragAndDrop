#include "LinkButton.h"

LinkButton::LinkButton(const char* uri, const char* label) {
    link_button = gtk_link_button_new(uri);
}

GtkWidget* LinkButton::getWidget() {
    return link_button;
}
