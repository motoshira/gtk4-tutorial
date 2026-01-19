#include "gio/gio.h"
#include "glib.h"
#include <gtk/gtk.h>

static void app_open(GApplication *app, GFile ** files, int n_files, char *hint) {
  GtkWidget *win;
  GtkWidget *scrolled_window;
  GtkWidget *text_view;
  GtkTextBuffer *text_buffer;
  char *contents;
  gsize length;
  char *filename;
  GError *err = NULL;

  win = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

  text_view = gtk_text_view_new();

  scrolled_window = gtk_scrolled_window_new();
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);

  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
  gtk_window_set_child(GTK_WINDOW(win), scrolled_window);

  text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

  int success;
  success = g_file_load_contents(files[0], NULL, &contents, &length, NULL, &err);

  if (!success) {
    g_printerr("%s.\n", err->message);
    g_error_free(err);
    gtk_window_destroy(GTK_WINDOW(win));
    return;
  }


  gtk_text_buffer_set_text(text_buffer, contents, -1);
  g_free(contents);
  filename = g_file_get_basename(files[0]);
  if (filename != NULL) {
    gtk_window_set_title(GTK_WINDOW(win), filename);
    g_free(filename);
  }
  gtk_window_present(GTK_WINDOW(win));
}

static void app_activate(GApplication *app) {
  g_printerr("You need a filename argument.\n");
}

int main (int argc, char *argv[]) {
  GtkApplication *app;
  int stat;

  app = gtk_application_new("com.github.motoshira.tfv3", G_APPLICATION_HANDLES_OPEN);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
  g_signal_connect(app, "open", G_CALLBACK (app_open), NULL);
  stat = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return stat;
}
