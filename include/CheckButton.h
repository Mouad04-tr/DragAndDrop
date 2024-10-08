#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include <gtk/gtk.h>

// Déclaration de la classe CheckButton
class CheckButton {
public:
    CheckButton(const char* label);    // Constructeur avec paramètre
    CheckButton();   // Constructeur par défaut
    ~CheckButton();     // Destructeur
    GtkWidget* getWidget();      // Méthode pour obtenir le widget associé au bouton

    static void on_left_check_button_clicked(GtkWidget* widget, gpointer data);    // Fonctions statiques pour les événements de clic et de mouvement de souris
    static void on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);   // Fonction statique appelée lorsqu'un bouton est enfoncé
    static gboolean on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);    // Fonction statique appelée lorsqu'un mouvement de souris est détecté sur le bouton
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);   // Fonction statique appelée lorsqu'un mouvement de souris est détecté sur le bouton
    static void on_replace_with_check_button(GtkWidget* button, gpointer data) ;  // Fonction statique pour remplacer le bouton par un bouton de coche

private:
    GtkWidget* checkbutton;
    struct CheckButtonMoveData {
        GtkWidget* widget;  // Widget GTK associé au bouton de coche
        gint offset_x;    // Décalage horizontal lors du déplacement
        gint offset_y;     // Décalage vertical lors du déplacement
    };
};

#endif // CHECKBUTTON_H
