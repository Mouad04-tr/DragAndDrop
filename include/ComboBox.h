#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <gtk/gtk.h>

// Déclaration de la classe ComboBox
class ComboBox {
public:
    ComboBox();    // Constructeur par défaut
    ~ComboBox();   // Destructeur

    GtkWidget* getWidget() const;

    static void on_left_combo_button_clicked(GtkWidget* widget, gpointer data);   // Méthode pour obtenir le widget associé à la combobox (constante pour indiquer que la méthode ne modifie pas l'objet)
    static gboolean on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);  // Fonction statique appelée lorsqu'un bouton est enfoncé
    static gboolean on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);    // Fonction statique appelée lorsqu'un mouvement de souris est détecté sur le bouton
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data); // Fonction statique appelée lorsqu'un bouton de la souris est relâché

private:
    GtkWidget* widget;

    struct ComboSdD {
        GtkWidget* widget;
        gdouble offset_x;
        gdouble offset_y;
    };
};

#endif // COMBOBOX_H
