// TextView.h

#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <gtk/gtk.h>

// Structure pour stocker les informations de déplacement pour chaque bouton
typedef struct {
    GtkWidget* widget;
    gint offset_x;
    gint offset_y;
    gboolean button_pressed; // Indique si le bouton de la souris est enfoncé
} ButtonMoveData;

class TextView {
public:
       TextView();
    TextView(GtkWidget* parent);
    ~TextView();
 GtkWidget* getWidget() const;
    static gboolean on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);
    static void on_left_text_view_button_clicked(GtkWidget* widget, gpointer data);

    GtkWidget* m_fixed;
};

#endif // TEXTVIEW_H
