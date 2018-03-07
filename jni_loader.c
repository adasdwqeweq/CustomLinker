#include "gbdlfcn.h"
#include "linker_debug.h"
#include "linker_format.h"
// #include "linker.h"
#include "linker4_4.h"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
    // soinfo *si;
    DL_ERR("load start\n");
 
    //4.1.2  start
    // si = (soinfo *)gbdlopen("/data/local/tmp/libfoo.so",RTLD_NOW);
    // if(si!=NULL){
    //     DL_ERR("success");
    // }
    // xor_code(si->base);
    DL_ERR("-------%08x",sizeof(unsigned char));
    // jint (*real_JNI_OnLoad)(JavaVM*, void*);
    // real_JNI_OnLoad = (jint (*)(JavaVM*, void*))(gbdlsym(si,"JNI_OnLoad"));
    // if(real_JNI_OnLoad == NULL){
    //  DL_ERR("cannot find sym %s\n", "JNI_OnLoad");
    // }
    // return real_JNI_OnLoad(vm, reserved);
    //4.1.2 end
    //4.4 start
    soinfo4_4* soinfo4_4=find_library_internal4_4("/data/local/tmp/libfoo.so");
    if(soinfo4_4==NULL){
        DL_ERR("find soinfo fail");
    } 
    DL_ERR("find soinfo success");
    jint (*real_JNI_OnLoad)(JavaVM*, void*);
    real_JNI_OnLoad = (jint (*)(JavaVM*, void*))(lookup_in_library4_4(soinfo4_4,"JNI_OnLoad"));
  if(real_JNI_OnLoad == NULL){
     DL_ERR("cannot find sym %s\n", "JNI_OnLoad");
    }
    return real_JNI_OnLoad(vm, reserved);

     //4.4 end
    // return JNI_VERSION_1_4;
}
