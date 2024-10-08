#include "Scale.h"

Scale::Scale() {
  scale = gtk_button_new_with_label("Create Scale");
}


Scale::Scale(gdouble min_value, gdouble max_value, gdouble step) {
  scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, min_value, max_value, step);
}
Scale::~Scale() {
}

GtkWidget* Scale::getWidget() const {
  return scale;
}

gboolean Scale::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
  ScaleMoveData* move_data = (ScaleMoveData*)data;
  if (event->button == GDK_BUTTON_PRIMARY) {
    move_data->offset_x = event->x;
    move_data->offset_y = event->y;
    move_data->pressed = TRUE;

    gdk_window_raise(gtk_widget_get_window(widget));
    gtk_grab_add(widget);
  }
  return TRUE;
}

gboolean Scale::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
  ScaleMoveData* move_data = (ScaleMoveData*)data;
  if (event->button == GDK_BUTTON_PRIMARY) {
    move_data->pressed = FALSE;
    gtk_grab_remove(widget);
  }
  return TRUE;
}

gboolean Scale::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    ScaleMoveData* move_data = (ScaleMoveData*)data;
    if (move_data->pressed) {
        GtkAllocation allocation;
        gtk_widget_get_allocation(widget, &allocation);

        gint new_x = (gint)(event->x_root - move_data->offset_x);
        gint new_y = (gint)(event->y_root - move_data->offset_y);

        gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(widget)), widget, new_x, new_y);
    }
    return TRUE;
}

void Scale::on_left_Scale_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Créer une instance de Scale avec des paramètres personnalisés
    Scale* customScale = new Scale(0, 100, 1);
    GtkWidget* scale = customScale->getWidget();
    gtk_container_add(GTK_CONTAINER(fixed), scale);

    ScaleMoveData* move_data = g_new0(ScaleMoveData, 1);
    move_data->widget = scale;

    g_signal_connect(scale, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(scale, "button-release-event", G_CALLBACK(on_button_release_event), move_data);
    g_signal_connect(scale, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);

    gtk_widget_show_all(scale);
}
