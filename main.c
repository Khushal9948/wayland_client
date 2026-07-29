#include <stdio.h>
#include <wayland-client.h>

int main(void) {
  struct wl_display *display;

  display = wl_display_connect(NULL);

  if (display == NULL) {
    fprintf(stderr, "Failed to connect to Wayland compositor.\n");
    return 1;
  }

  printf("Connected successfully!\n");

  wl_display_disconnect(display);

  return 0;
}
