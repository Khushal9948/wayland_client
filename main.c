#include <stdio.h>
#include <wayland-client.h>

int main(int argc, char *argv[]) {
  struct wl_display *display =
      wl_display_connect("wayland-1"); // NULL or wayland-0
  if (!display) {
    fprintf(stderr, "Failed to connect to Wayland display.\n");
    return 1;
  }
  fprintf(stderr, "Connection established!\n");
  // to get the file descriptor
  int something = wl_display_get_fd(display);
  printf("the fd is %d", display);
  wl_display_disconnect(display);
  return 0;
}
