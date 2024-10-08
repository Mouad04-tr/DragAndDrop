#ifndef SPINBUTTON_H
#define SPINBUTTON_H

#include <gtk/gtk.h>

class SpinButton {
public:
    SpinButton();
    ~SpinButton();
    GtkWidget* getWidget() const;
    static void on_left_spin_button_clicked(GtkWidget* widget, gpointer data);
    static void on_spin_button_clicked(GtkWidget* widget, gpointer data);

private:
    GtkWidget* widget;

    typedef struct {
        GtkWidget* widget;
        gint offset_x, offset_y;
    } SpinSdD;

    static gboolean on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);
    static void on_change_value(GtkAdjustment* adjustment, gpointer data);
};

#endif // SPINBUTTON_H
