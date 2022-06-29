#include "y11.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
struct y11_region*
y11_region_create(struct wl_client* client, uint32_t id)
{
  struct y11_region* region;
  region = zalloc(sizeof *region);
  if (region == NULL) goto no_mem_region;
  return region;
no_mem_region:
  wl_client_post_no_memory(client);
  return NULL;
}
