#ifndef BUTTON_H
#define BUTTON_H

#include <gtk/gtk.h>

///*************************************************Structure WidgetButton***********************************///
typedef struct {
    GtkWidget* widget;   // Pointeur vers le widget GTK associé au bouton
    gint offset_x;     // Décalage horizontal lors du déplacement
    gint offset_y;    // Décalage vertical lors du déplacement
}SButtonMoveData;


//déclaration de la classe
class Button {
public:
    Button(const char* label);      // Constructeur prenant en paramètre une étiquette pour le bouton
    GtkWidget* getWidget();
      static void on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data); // Fonction statique appelée lorsqu'un bouton est enfoncé
      static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);    // Fonction statique appelée lorsqu'un mouvement de souris est détecté sur le bouton
      static void on_left_button_clicked(GtkWidget* widget, gpointer data);   // Fonction statique appelée lorsqu'un clic gauche est détecté sur le bouton
      static void on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);    // Fonction statique appelée lorsqu'un bouton de la souris est relâché

    GtkWidget* widget;
};


#endif // BUTTON_H
