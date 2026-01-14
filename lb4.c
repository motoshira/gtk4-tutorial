#include <gtk/gtk.h>

static void click_hello_callback(GtkButton *button) {
  const char *s;
  s = gtk_button_get_label(button);
  if (g_strcmp0(s, "Hello.") == 0)
    gtk_button_set_label(button, "Good bye.");
  else
    gtk_button_set_label(button, "Hello.");
}

static void click_close_callback(GtkButton *app, GtkWindow *win) {
  gtk_window_destroy(win);
}

static void app_activate(GApplication *app) {
  GtkWidget *win;
  GtkWidget *box;
  GtkWidget *hello_button;
  GtkWidget *close_button;

  win = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_set_title(GTK_WINDOW(win), "lb4");
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
  gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
  gtk_window_set_child(GTK_WINDOW(win), box);

  hello_button = gtk_button_new_with_label("Hello.");
  g_signal_connect(hello_button, "clicked", G_CALLBACK(click_hello_callback), NULL);

  close_button = gtk_button_new_with_label("Close");
  g_signal_connect(close_button, "clicked", G_CALLBACK(click_close_callback),GTK_WINDOW(win));

  gtk_box_append(GTK_BOX(box), hello_button);
  gtk_box_append(GTK_BOX(box), close_button);


  gtk_window_present(GTK_WINDOW(win));
}

int main (int argc, char *argv[]) {
  GtkApplication *app;
  int stat;

  app = gtk_application_new("com.github.motoshira.lb4", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK (app_activate), NULL);
  stat = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return stat;
}
