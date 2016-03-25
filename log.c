#include "VoidTrack.h"

void Log(const char * format, ...){
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
}