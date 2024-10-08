#ifndef BUTTON_H
#define BUTTON_H

#include <gtk/gtk.h>

///*************************************************Structure WidgetButton***********************************///
typedef struct {
    GtkWidget* widget;   // Pointeur vers le widget GTK associ� au bouton
    gint offset_x;     // D�calage horizontal lors du d�placement
    gint offset_y;    // D�calage vertical lors du d�placement
}SButtonMoveData;


//d�claration de la classe
class Button {
public:
    Button(const char* label);      // Constructeur prenant en param�tre une �tiquette pour le bouton
    GtkWidget* getWidget();
      static void on_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer data); // Fonction statique appel�e lorsqu'un bouton est enfonc�
      static gboolean on_motion_notify_event(GtkWidget* widget, GdkEventMotion* event, gpointer data);    // Fonction statique appel�e lorsqu'un mouvement de souris est d�tect� sur le bouton
      static void on_left_button_clicked(GtkWidget* widget, gpointer data);   // Fonction statique appel�e lorsqu'un clic gauche est d�tect� sur le bouton
      static void on_button_release_event(GtkWidget* widget, GdkEventButton* event, gpointer data);    // Fonction statique appel�e lorsqu'un bouton de la souris est rel�ch�

    GtkWidget* widget;
};


#endif // BUTTON_H
