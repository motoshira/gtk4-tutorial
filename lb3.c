#include <gtk/gtk.h>

static void click_callback(GtkButton *app, GtkWindow *win) {
  gtk_window_destroy(win);
}

static void app_activate(GApplication *app) {
  GtkWidget *win;
  GtkWidget *button;

  win = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_set_title(GTK_WINDOW(win), "lb3");
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

  button = gtk_button_new_with_label("Close");
  gtk_window_set_child(GTK_WINDOW(win), button);
  g_signal_connect(button, "clicked", G_CALLBACK(click_callback), GTK_WINDOW(win));

  gtk_window_present(GTK_WINDOW(win));
}

int main (int argc, char *argv[]) {
  GtkApplication *app;
  int stat;

  app = gtk_application_new("com.github.motoshira.lb3", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK (app_activate), NULL);
  stat = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return stat;
}
