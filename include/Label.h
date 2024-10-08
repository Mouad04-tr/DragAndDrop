#ifndef LABEL_H
#define LABEL_H

#include <gtk/gtk.h>

#include <gtk/gtk.h>

class Label {
public:
    Label();
    Label(const char* text);
    ~Label();

    GtkWidget* getWidget();

    static gboolean on_label_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_label_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static gboolean on_label_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);
    static void on_left_label_clicked(GtkWidget* widget, gpointer data);

private:
    GtkWidget* label;

    struct LabelMoveData {
        GtkWidget* widget;
        gdouble offset_x;
        gdouble offset_y;
    };
};

#endif // LABEL_H
