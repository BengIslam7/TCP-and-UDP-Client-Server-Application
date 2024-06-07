#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

int client_socket;
struct sockaddr_in server_address;
int choice;
int authenticated = 0;
GtkWidget *window;
GtkWidget *button1;
GtkWidget *button2; 
GtkWidget *button3;
GtkWidget *button4;
GtkWidget *text_view;
GtkWidget *entry;


int authenticate() {
   char username[50];
    char password[50];
    char storedUsername[] = "unix"; 
    char storedPassword[] = "unix"; 

    printf("Enter your username and password to login :\n");
    printf("Username : ");
    scanf("%s", username);
    printf("Password : ");
    scanf("%s", password);

    if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
        printf("Logging.\n");
        return 1; 
    } else {
        printf("Verify your username and password.\n");
}
}

static void
date_time (GtkWidget *widget,
             gpointer   data)
{
  choice=1;	
  write(client_socket, &choice, sizeof(int));
  char dateTime[100];
  read(client_socket, dateTime, sizeof(dateTime));
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  char buffertext[100];
  snprintf(buffertext,sizeof(buffertext),"Date & Time : %s\n",dateTime);
  gtk_text_buffer_set_text(buffer,buffertext,-1);
}

static void
file_list (GtkWidget *widget,
             gpointer   data)
{
  choice=2;	
  write(client_socket, &choice, sizeof(int));
  char fileList[1024];
  read(client_socket, fileList, sizeof(fileList));
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  char buffertext[100];
  snprintf(buffertext,sizeof(buffertext),"File list : \n%s",fileList);
  gtk_text_buffer_set_text(buffer,buffertext,-1);
}

static void
file_content (GtkWidget *widget,
             gpointer   data)
{
  choice=3;	
  write(client_socket, &choice, sizeof(int));
  GtkEntryBuffer *buffer2 = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *text = gtk_entry_buffer_get_text(buffer2);
  write(client_socket, text, sizeof(text));
  char fileContent[2024];
  read(client_socket, fileContent, sizeof(fileContent));
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  char buffertext[100];
  snprintf(buffertext,sizeof(buffertext),"%s File content : \n%s",text,fileContent);
  gtk_text_buffer_set_text(buffer,buffertext,-1);
 }

static void
duration (GtkWidget *widget,
             gpointer   data)
{
  choice=4;	
  write(client_socket, &choice, sizeof(int));
  char duration[50];
  read(client_socket, duration, sizeof(duration));
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  gtk_text_buffer_set_text(buffer,duration,-1);
}


static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Mini Projet");
  gtk_window_set_default_size (GTK_WINDOW (window), 1500, 1500);
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
  gtk_window_set_child(GTK_WINDOW(window),vbox);
  // Ajouter une entrée utilisateur
  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter the file name here");
  gtk_box_append(GTK_BOX(vbox), entry);

  // Ajouter un bouton
    button1 = gtk_button_new_with_label("Date&Time");
    g_signal_connect(button1, "clicked", G_CALLBACK(date_time), NULL);
    gtk_box_append(GTK_BOX(vbox), button1);
    // Ajouter un bouton
    button2 = gtk_button_new_with_label("File List");
    g_signal_connect(button2, "clicked", G_CALLBACK(file_list), NULL);
    gtk_box_append(GTK_BOX(vbox), button2);
    // Ajouter un bouton
    button3 = gtk_button_new_with_label("File Content");
    g_signal_connect(button3, "clicked", G_CALLBACK(file_content), NULL);
    gtk_box_append(GTK_BOX(vbox), button3);
    // Ajouter un bouton
    button4 = gtk_button_new_with_label("Duration");
    g_signal_connect(button4, "clicked", G_CALLBACK(duration), NULL);
    gtk_box_append(GTK_BOX(vbox), button4);
    // Ajouter une zone de texte
    text_view = gtk_text_view_new();
    gtk_box_append(GTK_BOX(vbox), text_view);
    gtk_window_present (GTK_WINDOW (window));
}




int
main (int    argc,
      char **argv)
{

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
GtkApplication *app;
  int status;


     
//DEBUT DE L INTERFACE GRAPHIQUE

  
  while (authenticated==0){
     authenticated = authenticate();
  }

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
	
	

  return status;
}

