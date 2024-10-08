#ifndef LISTBOX_H
#define LISTBOX_H

#include <gtk/gtk.h>

class ListBox {
public:
    ListBox();
     ListBox(const char* label);
    ~ListBox();
    GtkWidget* getWidget() const;

    static gboolean on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);
    static void on_left_listbox_clicked(GtkWidget* widget, gpointer data);

private:
    GtkWidget* list_box;
    struct ListBoxMoveData {
        GtkWidget* widget;
        gint offset_x;
        gint offset_y;
        gboolean pressed; // Indique si le bouton est enfoncé ou non
    };
};

#endif // LISTBOX_H
