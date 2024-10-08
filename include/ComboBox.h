#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <gtk/gtk.h>

// D�claration de la classe ComboBox
class ComboBox {
public:
    ComboBox();    // Constructeur par d�faut
    ~ComboBox();   // Destructeur

    GtkWidget* getWidget() const;

    static void on_left_combo_button_clicked(GtkWidget* widget, gpointer data);   // M�thode pour obtenir le widget associ� � la combobox (constante pour indiquer que la m�thode ne modifie pas l'objet)
    static gboolean on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);  // Fonction statique appel�e lorsqu'un bouton est enfonc�
    static gboolean on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);    // Fonction statique appel�e lorsqu'un mouvement de souris est d�tect� sur le bouton
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data); // Fonction statique appel�e lorsqu'un bouton de la souris est rel�ch�

private:
    GtkWidget* widget;

    struct ComboSdD {
        GtkWidget* widget;
        gdouble offset_x;
        gdouble offset_y;
    };
};

#endif // COMBOBOX_H
