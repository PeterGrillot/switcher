#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

const char *sink_speakers = "alsa_output.usb-DisplayLink_Plugable_UD-3900PDZ_4201A01438-02.iec958-stereo";
const char *sink_headphones = "alsa_output.pci-0000_00_1f.3-platform-skl_hda_dsp_generic.HiFi__hw_sofhdadsp__sink";

GtkWidget *button;
GtkWidget *label;

gboolean is_headphone_active()
{
  FILE *fp = popen("pactl get-default-sink", "r");
  if (!fp)
    return FALSE;

  char buf[256];
  if (fgets(buf, sizeof(buf), fp) != NULL)
  {
    buf[strcspn(buf, "\n")] = 0;
    pclose(fp);
    return strcmp(buf, sink_headphones) == 0;
  }
  pclose(fp);
  return FALSE;
}

void update_labels()
{
  if (is_headphone_active())
  {
    gtk_label_set_text(GTK_LABEL(label), "Playing audio through Headphones");
    gtk_button_set_label(GTK_BUTTON(button), "🔉 Switch to Speakers");
  }
  else
  {
    gtk_label_set_text(GTK_LABEL(label), "Playing audio through Speakers");
    gtk_button_set_label(GTK_BUTTON(button), "🎧 Switch to Headphones");
  }
}

void toggle_sink(GtkWidget *widget, gpointer data)
{
  const char *new_sink = is_headphone_active() ? sink_speakers : sink_headphones;
  char cmd[512];
  snprintf(cmd, sizeof(cmd), "pactl set-default-sink %s\n", new_sink);
  system(cmd);
  update_labels();
}

int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  // Window settings
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Audio Switcher");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Box layout
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_set_border_width(GTK_CONTAINER(box), 20);

  // Text label
  gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
  gtk_widget_show(label);

  // Button setup
  button = gtk_button_new();
  label = gtk_label_new("Initializing...");
  update_labels();

  g_signal_connect(button, "clicked", G_CALLBACK(toggle_sink), NULL);
  // Build the UI

  gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);
  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
