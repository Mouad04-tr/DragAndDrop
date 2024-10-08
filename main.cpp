#include <gtk/gtk.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include<Button.h>
#include<Entry.h>
#include<ComboBox.h>
#include<Label.h>
#include<TextView.h>
#include<RadioButton.h>
#include<CheckButton.h>
#include<ListBox.h>
#include<SpinButton.h>
#include<Scale.h>
#include<ProgressBar.h>
#include<utils.h>



// Fonction de rappel pour créer un menu et l'afficher
static void on_create_menu_clicked(GtkWidget *widget, gpointer data) {
    // Création d'un menu
    GtkWidget *menu = gtk_menu_new();

    // Ajout d'éléments de menu au menu
    GtkWidget *item1 = gtk_menu_item_new_with_label("Menu Item 1");
    GtkWidget *item2 = gtk_menu_item_new_with_label("Menu Item 2");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item1);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item2);

    // Création d'un élément de menu pour le bouton "Create menu"
    GtkWidget *menu_button = gtk_menu_item_new_with_label("Menu");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_button), menu);

    // Ajout de l'élément de menu à la left_box
    GtkWidget *left_box = GTK_WIDGET(data);
    gtk_box_pack_start(GTK_BOX(left_box), menu_button, FALSE, FALSE, 0);

    // Affichage de tous les widgets
    gtk_widget_show_all(left_box);
}




// Function to remove all children from a container
void remove_all_children(GtkWidget* container) {
    GList* children = gtk_container_get_children(GTK_CONTAINER(container));
    for (GList* iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}

// Fonction de rappel pour le clic sur le bouton "Destroy Content"
static void on_destroy_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);

    // Créez une boîte de dialogue de confirmation
    GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(fixed)),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_QUESTION,
                                               GTK_BUTTONS_OK_CANCEL,
                                               "Are you sure you want to destroy all content?");

    // Exécutez la boîte de dialogue et attendez la réponse
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    // En fonction de la réponse, effectuez l'action appropriée
    if (result == GTK_RESPONSE_OK) {
        remove_all_children(fixed); // Détruit tous les widgets
    }

    // Détruisez la boîte de dialogue après utilisation
    gtk_widget_destroy(dialog);
}


void save_interface_to_xml(GtkWidget* fixed, const char* filename) {
    // Créer un fichier XML avec une racine différente
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "custom_interface");
    xmlDocSetRootElement(doc, root_node);

    // Parcourir tous les enfants du conteneur fixe
    GList* children = gtk_container_get_children(GTK_CONTAINER(fixed));
    for (GList* iter = children; iter != NULL; iter = g_list_next(iter)) {
        GtkWidget* widget = GTK_WIDGET(iter->data);
        int x, y;
        gtk_widget_translate_coordinates(widget, fixed, 0, 0, &x, &y);

        // Créer un nœud pour chaque widget avec des noms personnalisés
        const gchar* type_name = G_OBJECT_TYPE_NAME(widget);
        xmlNodePtr node = xmlNewChild(root_node, NULL, BAD_CAST "custom_widget", NULL);

        // Ajouter des attributs avec des noms personnalisés
        xmlNewProp(node, BAD_CAST "widget_type", BAD_CAST type_name);
        xmlNewProp(node, BAD_CAST "position_x", BAD_CAST g_strdup_printf("%d", x));
        xmlNewProp(node, BAD_CAST "position_y", BAD_CAST g_strdup_printf("%d", y));

        if (GTK_IS_LABEL(widget)) {
            const gchar* label = gtk_label_get_text(GTK_LABEL(widget));
            xmlNewProp(node, BAD_CAST "custom_label", BAD_CAST label);
        }
        else if (GTK_IS_ENTRY(widget)) {
            const gchar* text = gtk_entry_get_text(GTK_ENTRY(widget));
            xmlNewProp(node, BAD_CAST "custom_text", BAD_CAST text);
        }
        else if (GTK_IS_COMBO_BOX_TEXT(widget)) {
            const gchar* text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));
            xmlNewProp(node, BAD_CAST "custom_combo_text", BAD_CAST text);
        }
        else if (GTK_IS_TEXT_VIEW(widget)) {
            GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
            GtkTextIter start, end;
            gtk_text_buffer_get_start_iter(buffer, &start);
            gtk_text_buffer_get_end_iter(buffer, &end);
            gchar* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
            xmlNewProp(node, BAD_CAST "custom_textview_text", BAD_CAST text);
            g_free(text);
        }
        else if (GTK_IS_SPIN_BUTTON(widget)) {
            gdouble value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
            xmlNewProp(node, BAD_CAST "custom_spin_value", BAD_CAST g_strdup_printf("%f", value));
        }
        else if (GTK_IS_PROGRESS_BAR(widget)) {
            gdouble value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(widget));
            xmlNewProp(node, BAD_CAST "custom_progress_value", BAD_CAST g_strdup_printf("%f", value));
        }
        else if (GTK_IS_SCALE(widget)) {
            gdouble value = gtk_range_get_value(GTK_RANGE(widget));
            xmlNewProp(node, BAD_CAST "custom_scale_value", BAD_CAST g_strdup_printf("%f", value));
        }
    }

    // Enregistrer le document XML dans le fichier
    xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);

    // Libérer la mémoire allouée pour le document XML
    xmlFreeDoc(doc);
}




static void on_save_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);
    save_interface_to_xml(fixed, "Saved_interface.xml");
    g_print("Interface saved to 'Saved_interface.xml'\n");
}


void load_interface_from_xml(GtkWidget* fixed, const char* filename) {
    xmlDoc* doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        g_print("Failed to load XML\n");
        return;
    }
    xmlNode* root_element = xmlDocGetRootElement(doc);

    for (xmlNode* a_node = root_element->children; a_node != NULL; a_node = a_node->next) {
        if (a_node->type == XML_ELEMENT_NODE) {
            xmlChar* x = xmlGetProp(a_node, BAD_CAST "position_x");
            xmlChar* y = xmlGetProp(a_node, BAD_CAST "position_y");
            xmlChar* type = xmlGetProp(a_node, BAD_CAST "widget_type");

            GtkWidget* widget = NULL;
            if (xmlStrcmp(type, BAD_CAST "GtkButton") == 0) {
                xmlChar* label = xmlGetProp(a_node, BAD_CAST "custom_label");
                if (label != NULL) {
                    widget = gtk_button_new_with_label((const char*)label);
                    xmlFree(label);
                } else {
                    widget = gtk_button_new();
                }
            }
            else if (xmlStrcmp(type, BAD_CAST "GtkEntry") == 0) {
                xmlChar* text = xmlGetProp(a_node, BAD_CAST "custom_text");
                widget = gtk_entry_new();
                gtk_entry_set_text(GTK_ENTRY(widget), (const char*)text);
                xmlFree(text);
            }
            else if (xmlStrcmp(type, BAD_CAST "GtkComboBoxText") == 0) {
                widget = gtk_combo_box_text_new();
                // Ajouter les options du combobox depuis le XML
                for (xmlNode* option_node = a_node->children; option_node != NULL; option_node = option_node->next) {
                    if (option_node->type == XML_ELEMENT_NODE && xmlStrcmp(option_node->name, BAD_CAST "option") == 0) {
                        xmlChar* option_label = xmlGetProp(option_node, BAD_CAST "label");
                        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widget), (const char*)option_label);
                        xmlFree(option_label);
                    }
                }
            }
            else if (xmlStrcmp(type, BAD_CAST "GtkRadioButton") == 0) {
                xmlChar* label = xmlGetProp(a_node, BAD_CAST "custom_label");
                if (label != NULL) {
                    widget = gtk_radio_button_new_with_label(NULL, (const char*)label);
                    xmlFree(label);
                } else {
                    widget = gtk_radio_button_new(NULL);
                }
            }

            if (widget != NULL) {
                gtk_fixed_put(GTK_FIXED(fixed), widget, atoi((const char*)x), atoi((const char*)y));
                gtk_widget_show(widget);
            }
            xmlFree(x);
            xmlFree(y);
            xmlFree(type);
        }
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
}



// Fonction de gestion du clic sur le bouton de chargement de l'interface
static void on_load_interface_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* fixed = GTK_WIDGET(data);
    load_interface_from_xml(fixed, "Saved_interface.xml");
    g_print("Interface loaded from 'Saved_interface.xml'\n");
    gtk_widget_show_all(fixed);  // Redessine le conteneur fixe
}



int main(int argc, char* argv[])
 {
  gtk_init(&argc, &argv);



  ///****************************************Appel aux macros***************************************///


     GtkWidget* window = Creer_fenetre("Drag and Drop App", 900, 600);   //Appel de la fonction Creer_fenetre pour la création de la fenetre principale

    load_css("C:\\Users\\asus\\OneDrive\\Desktop\\Style_DragDropGTK\\style.css");  //Apporter un Style CSS à notre window

    GtkWidget *scrolled_window, *main_box, *right_fixed, *left_box;

    Ajuster_fenetre(window, &scrolled_window, &main_box, &right_fixed, &left_box);   //pour l'ajustement des composants de la fenetre


///****************************************************ButtonWidget**********************************************************************///

        Button button1("Create a simple button");
        GtkWidget* button1Widget = button1.getWidget(); // Obtenir le widget associé
        g_signal_connect(button1Widget, "clicked", G_CALLBACK(Button::on_left_button_clicked), right_fixed);
        gtk_box_pack_start(GTK_BOX(left_box), button1Widget, FALSE, FALSE, 0);


   ///****************************************************EntryWidget***********************************************************************///

        Entry entrywidget;
        GtkWidget* entry1 = entrywidget.getWidget(); // Obtenir le widget associé
        g_signal_connect(entry1, "clicked", G_CALLBACK(Entry::on_left_entry_button_clicked), right_fixed);
        gtk_box_pack_start(GTK_BOX(left_box), entry1, FALSE, FALSE, 0);

///*****************************************************ComboBoxWidget*******************************************************************///

    // Create and add a button to create the combo box
    ComboBox comboBoxButton;
     GtkWidget* comb1 = comboBoxButton.getWidget(); // Obtenir le widget associé
    g_signal_connect(comb1, "clicked", G_CALLBACK(ComboBox::on_left_combo_button_clicked), right_fixed);
    gtk_box_pack_start(GTK_BOX(left_box), comb1, FALSE, FALSE, 0);


///*********************************************************Label ********************************************************************///

    // Create and add a button to create the label
    Label labelButton;
    GtkWidget* label1=labelButton.getWidget();
    g_signal_connect(label1, "clicked", G_CALLBACK(Label::on_left_label_clicked), right_fixed);
    gtk_box_pack_start(GTK_BOX(left_box), label1, FALSE, FALSE, 0);


  ///********************************************************TextView******************************************************************///
    // Créer et ajouter un bouton pour créer le textview
    TextView textViewButton;
    GtkWidget* textview1 = textViewButton.getWidget();
    g_signal_connect(textview1, "clicked", G_CALLBACK(TextView::on_left_text_view_button_clicked), right_fixed);
   gtk_box_pack_start(GTK_BOX(left_box), textview1, FALSE, FALSE, 0);


    ///***************************************************** RadioButton**********************************************************///

    // Créer une instance de RadioButton
     RadioButton radio;
    // Créer un bouton pour ajouter un bouton radio
    GtkWidget* radio_button = radio.getWidget();
    // Connecter le signal "clicked" à la méthode non statique de l'instance de RadioButton
    g_signal_connect(radio_button, "clicked", G_CALLBACK(RadioButton::on_left_radio_button_clicked), right_fixed);
    gtk_box_pack_start(GTK_BOX(left_box), radio_button, FALSE, FALSE, 0);


///*********************************************************CheckButton**********************************************************///
    // Créer une instance de RadioButton
     CheckButton cb1;
    // Créer un bouton pour ajouter un bouton radio
    GtkWidget* check_button = cb1.getWidget();
    // Connecter le signal "clicked" à la méthode non statique de l'instance de RadioButton
    g_signal_connect(check_button, "clicked", G_CALLBACK(CheckButton::on_left_check_button_clicked), right_fixed);
    gtk_box_pack_start(GTK_BOX(left_box), check_button, FALSE, FALSE, 0);


    ///*****************************************************ListBox*****************************************************************///
    GtkWidget* create_listbox_button = gtk_button_new_with_label("Create a ListBox");
    gtk_box_pack_start(GTK_BOX(left_box), create_listbox_button, FALSE, FALSE, 0);
    // Connexion du signal "clicked" du bouton "Create a ListBox" à la méthode on_left_listbox_clicked
    g_signal_connect(create_listbox_button, "clicked", G_CALLBACK(ListBox::on_left_listbox_clicked), right_fixed);


    ///****************************************************SpinButton*********************************************************************///
         SpinButton sb1;
    // Créer un bouton pour ajouter un bouton radio
    GtkWidget* spn_button = sb1.getWidget();
    // Connecter le signal "clicked" à la méthode non statique de l'instance de RadioButton
    g_signal_connect(spn_button, "clicked", G_CALLBACK(SpinButton::on_left_spin_button_clicked), right_fixed);
    gtk_box_pack_start(GTK_BOX(left_box), spn_button, FALSE, FALSE, 0);


///*****************************************************Scale**************************************************************///
     Scale sc1;
    GtkWidget *addScaleButton = sc1.getWidget();
    g_signal_connect(addScaleButton, "clicked", G_CALLBACK(Scale::on_left_Scale_clicked), right_fixed);
     gtk_box_pack_start(GTK_BOX(left_box), addScaleButton, FALSE, FALSE, 0);


///******************************************************ProgressBar********************************************************///
         ProgressBar pr1;
    GtkWidget *progbr = pr1.getWidget();
    g_signal_connect(progbr, "clicked", G_CALLBACK(ProgressBar::on_left_ProgBar_clicked), right_fixed);
     gtk_box_pack_start(GTK_BOX(left_box), progbr, FALSE, FALSE, 0);



///**********************************************************Sauvegarder XML********************************************************///
    // Add Save and Load buttons
    GtkWidget* saveButton = gtk_button_new_with_label("Save ALL");
    g_signal_connect(saveButton, "clicked", G_CALLBACK(on_save_button_clicked), right_fixed);
    gtk_box_pack_start(GTK_BOX(left_box), saveButton, FALSE, FALSE, 0);




    // Création du bouton "Create menu"
    GtkWidget *create_menu_button = gtk_button_new_with_label("Create Menu");
    g_signal_connect(create_menu_button, "clicked", G_CALLBACK(on_create_menu_clicked), left_box);
    gtk_box_pack_start(GTK_BOX(left_box), create_menu_button, FALSE, FALSE, 0);



 ///**********************************************************Load XML ***************************************************************///
    GtkWidget* loadButton = gtk_button_new_with_label("Charger l'interface");
    g_signal_connect(loadButton, "clicked", G_CALLBACK(on_load_interface_clicked), right_fixed);
    gtk_box_pack_start(GTK_BOX(left_box), loadButton, FALSE, FALSE, 0);



///***********************************************************Suppression de tous les widgets******************************************///
 GtkWidget* destroy_button = gtk_button_new_with_label("Destroy Content");
    g_signal_connect(destroy_button, "clicked", G_CALLBACK(on_destroy_button_clicked), right_fixed);
    gtk_box_pack_start(GTK_BOX(left_box), destroy_button, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
