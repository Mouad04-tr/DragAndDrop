#include "ProgressBar.h"

ProgressBar::ProgressBar() {
  progressbar =gtk_button_new_with_label("Create ProgressBar");
}


ProgressBar::ProgressBar(double initial_value) {
  progressbar = gtk_progress_bar_new();
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar), initial_value);
}
ProgressBar::~ProgressBar() {
}

GtkWidget* ProgressBar::getWidget() const {
  return progressbar;
}

gboolean ProgressBar::on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
  ProgressBarMoveData* move_data = (ProgressBarMoveData*)data;
  if (event->button == GDK_BUTTON_PRIMARY) {
    move_data->offset_x = event->x;
    move_data->offset_y = event->y;

    move_data->pressed = TRUE; // Mettre à jour pressed lorsque le bouton de la souris est enfoncé

    gdk_window_raise(gtk_widget_get_window(widget));
    gtk_grab_add(widget);
  }
  return TRUE;
}

gboolean ProgressBar::on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data) {
  ProgressBarMoveData* move_data = (ProgressBarMoveData*)data;
  if (event->button == GDK_BUTTON_PRIMARY) {
    move_data->pressed = FALSE; // Mettre à jour pressed lorsque le bouton de la souris est relâché
    gtk_grab_remove(widget);
  }
  return TRUE;
}

gboolean ProgressBar::on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data) {
    ProgressBarMoveData* move_data = (ProgressBarMoveData*)data;
    if (move_data->pressed) {
        // Obtenir la position actuelle de la barre de progression dans son parent
        GtkAllocation allocation;
        gtk_widget_get_allocation(widget, &allocation);

        // Calculer les nouvelles coordonnées en fonction du mouvement de la souris
        gint new_x = (gint)(event->x_root - move_data->offset_x);
        gint new_y = (gint)(event->y_root - move_data->offset_y);

        // Déplacer la barre de progression à la nouvelle position
        gtk_fixed_move(GTK_FIXED(gtk_widget_get_parent(widget)), widget, new_x, new_y);
    }
    return TRUE;
}

void ProgressBar::on_left_ProgBar_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Créer une instance de la barre de progression avec une valeur initiale de 0.5 (par exemple)
    ProgressBar* customProgressBar = new ProgressBar(0.5);
    GtkWidget* progbarr = customProgressBar->getWidget();

    // Positionner la barre de progression à la position (100, 300)
    gtk_fixed_put(GTK_FIXED(fixed), progbarr, 100, 300);

    // Allouer de la mémoire pour move_data (une fois pour l'ensemble du programme)
    ProgressBarMoveData* move_data = g_new0(ProgressBarMoveData, 1);
    move_data->widget = progbarr;

    // Connecter les signaux pour la fonctionnalité de glisser-déposer
    g_signal_connect(progbarr, "button-press-event", G_CALLBACK(on_button_press_event), move_data);
    g_signal_connect(progbarr, "button-release-event", G_CALLBACK(on_button_release_event), move_data);
    g_signal_connect(progbarr, "motion-notify-event", G_CALLBACK(on_motion_notify_event), move_data);

    // Afficher la barre de progression
    gtk_widget_show_all(progbarr);
}


