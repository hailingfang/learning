#define _GNU_SOURCE
#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static struct wl_compositor *compositor;
static struct wl_shm *shm;
static struct wl_surface *surface;

static void registry_handler(void *data, struct wl_registry *registry,
                             uint32_t id, const char *interface, uint32_t version) {
    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 4);
    } else if (strcmp(interface, "wl_shm") == 0) {
        shm = wl_registry_bind(registry, id, &wl_shm_interface, 1);
    }
}

static void registry_remover(void *data, struct wl_registry *registry, uint32_t id) {}

static const struct wl_registry_listener registry_listener = {
    registry_handler,
    registry_remover
};

int create_shm_file(size_t size) {
    char filename[] = "/tmp/wayland-shm-XXXXXX";
    int fd = mkstemp(filename);
    if (fd >= 0) {
        unlink(filename);
        ftruncate(fd, size);
    }
    return fd;
}

int main() {
    struct wl_display *display = wl_display_connect(NULL);
    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(display);

    // Create a surface
    surface = wl_compositor_create_surface(compositor);

    // Create shared memory buffer for 1 pixel
    int width = 1, height = 1;
    int stride = width * 4;
    int size = stride * height;
    int fd = create_shm_file(size);
    void *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    memset(data, 0xFF, size); // White pixel (ARGB: 0xFFFFFFFF)

    struct wl_shm_pool *pool = wl_shm_create_pool(shm, fd, size);
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0, width, height,
                                                          stride, WL_SHM_FORMAT_ARGB8888);

    wl_surface_attach(surface, buffer, 0, 0);
    wl_surface_commit(surface);
    wl_display_roundtrip(display);

    sleep(3); // Keep the window for 3 seconds

    wl_display_disconnect(display);
    return 0;
}

