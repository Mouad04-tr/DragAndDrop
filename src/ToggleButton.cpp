#include "ToggleButton.h"

ToggleButton::ToggleButton(const char* label) {
    togglebutton = gtk_toggle_button_new_with_label(label);
}

GtkWidget* ToggleButton::getWidget() {
    return togglebutton;
}
