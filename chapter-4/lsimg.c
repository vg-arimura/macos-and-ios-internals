#include "stdio.h"
#include <dlfcn.h>
#include <mach-o/dyld.h>

void listImages(void){
  uint32_t i;
  uint32_t ic = _dyld_image_count();

  printf("Got %d images\n", ic);
  for(i = 0;i<ic;i++){
    printf("%d: %p\t%s\t\n"
      ,i
      ,_dyld_get_image_header(i)
      ,_dyld_get_image_name(i));
  }
}

void add_callback(const struct mach_header* mh, intptr_t vmaddr_slide) {
  Dl_info info;
  dladdr(mh, &info);
  printf("Callback invoked for image: %p %s (slide: %ld)\n"
    ,mh
    ,info.dli_fname
    ,vmaddr_slide);
}

void main(int argc, char **argv) {
  listImages();
  _dyld_register_func_for_add_image(add_callback);
}

