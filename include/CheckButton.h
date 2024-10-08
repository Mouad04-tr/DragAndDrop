#ifndef CHECKBUTTON_H
#define CHECKBUTTON_H

#include <gtk/gtk.h>

// D�claration de la classe CheckButton
class CheckButton {
public:
    CheckButton(const char* label);    // Constructeur avec param�tre
    CheckButton();   // Constructeur par d�faut
    ~CheckButton();     // Destructeur
    GtkWidget* getWidget();      // M�thode pour obtenir le widget associ� au bouton

    static void on_left_check_button_clicked(GtkWidget* widget, gpointer data);    // Fonctions statiques pour les �v�nements de clic et de mouvement de souris
    static void on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data);   // Fonction statique appel�e lorsqu'un bouton est enfonc�
    static gboolean on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);    // Fonction statique appel�e lorsqu'un mouvement de souris est d�tect� sur le bouton
    static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);   // Fonction statique appel�e lorsqu'un mouvement de souris est d�tect� sur le bouton
    static void on_replace_with_check_button(GtkWidget* button, gpointer data) ;  // Fonction statique pour remplacer le bouton par un bouton de coche

private:
    GtkWidget* checkbutton;
    struct CheckButtonMoveData {
        GtkWidget* widget;  // Widget GTK associ� au bouton de coche
        gint offset_x;    // D�calage horizontal lors du d�placement
        gint offset_y;     // D�calage vertical lors du d�placement
    };
};

#endif // CHECKBUTTON_H
