#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <gtk/gtk.h>

// Structure pour stocker les informations de déplacement pour chaque bouton
typedef struct {
    GtkWidget* widget;
    gint offset_x;
    gint offset_y;
}RadioMoveData;

class RadioButton {
public:
    RadioButton();
    RadioButton(const char* label);
    GtkWidget* getWidget();
    static void on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);
      static void on_left_radio_button_clicked(GtkWidget* widget, gpointer data);
      static void on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);

    GtkWidget* radiobutton;
};

#endif // RADIOBUTTON_H
