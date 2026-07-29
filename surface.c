#include "xdg-shell-client-protocol.h"
#include <stdio.h>
#include <string.h>
#include <wayland-client.h>

struct globals {
  struct wl_compositor *compositor;
  struct wl_shm *shm;
};

struct globals {
  struct wl_compositor *compositor;
  struct wl_shm *shm;
  struct xdg_wm_base *wm_base;
};

static void registry_global(void *data, struct wl_registry *registry,
                            uint32_t name, const char *interface,
                            uint32_t version) {
  struct globals *g = data;

  printf("Found: %s (version %u)\n", interface, version);

  if (strcmp(interface, wl_compositor_interface.name) == 0) {
    g->compositor =
        wl_registry_bind(registry, name, &wl_compositor_interface, 4);
  }

  if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
    g->wm_base = wl_registry_bind(registry, name, &xdg_wm_base_interface, 1);
  }

  if (strcmp(interface, wl_shm_interface.name) == 0) {
    g->shm = wl_registry_bind(registry, name, &wl_shm_interface, 1);
  }
}

static void registry_remove(void *data, struct wl_registry *registry,
                            uint32_t name) {
  (void)data;
  (void)registry;
  (void)name;
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = registry_remove,
};

int main(void) {
  struct globals globals = {0};

  struct wl_display *display = wl_display_connect(NULL);

  if (!display) {
    fprintf(stderr, "Unable to connect.\n");
    return 1;
  }

  struct wl_registry *registry = wl_display_get_registry(display);

  wl_registry_add_listener(registry, &registry_listener, &globals);

  wl_display_roundtrip(display);

  struct wl_surface *surface = wl_compositor_create_surface(globals.compositor);

  if (!surface) {
    fprintf(stderr, "Failed to create surface\n");
    return 1;
  }

  printf("Surface created!\n");

  printf("\n");

  if (globals.compositor)
    printf("Got wl_compositor\n");

  if (globals.shm)
    printf("Got wl_shm\n");

  wl_registry_destroy(registry);
  wl_display_disconnect(display);

  return 0;
}
