#include <gtk/gtk.h>


// the ui has to be initialized here
// there is text that says "pomodoro" and "short break" and "long break"
// there is a button that says "start"
// there is a button that says "stop"
// there is a button that says "reset"
// there is a context menu that says preferences and about
// there is a timer that counts down from the current state

// static int current_state = 0; // 0 is pomodoro, 1 is short break, 2 is long break


void activate(GtkApplication* app, gpointer user_data) {

}

int init_ui(int pomodoro, int short_break, int long_break) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), 0, NULL);
  g_object_unref (app);

  return status;
}

