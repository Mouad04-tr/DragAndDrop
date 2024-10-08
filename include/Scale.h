#ifndef SCALE_H
#define SCALE_H

#include <gtk/gtk.h>

class Scale {
public:
      Scale(gdouble min_value, gdouble max_value, gdouble step);
  Scale();
  ~Scale();
  GtkWidget* getWidget() const;

  static gboolean on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
  static gboolean on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);
  static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);
  static void on_left_Scale_clicked(GtkWidget* widget, gpointer data);

private:
  GtkWidget* scale;

  // Structure de donn�es pour stocker les informations de d�placement de la widget Scale
  struct ScaleMoveData {
    GtkWidget* widget;
    gint offset_x;
    gint offset_y;
    gboolean pressed; // Ajouter un bool�en pour suivre l'�tat press�
  };
};

#endif // SCALE_H
