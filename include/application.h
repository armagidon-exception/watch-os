#pragma once
#include "scene.h"
#include "utils.h"

typedef struct Application {
    //Icon
    Bitmap icon;
    //Entry point
    void (*invoke)(Application* context);
    //Scene to render on
    Scene scene;
    //Title
    const char* title;
} Application;

typedef void (*ApplicationEntrypoint)(Application* context);

#ifndef __APPLICATIONS__
    extern List applications;
#else
    List applications = create_arraylist(1, sizeof(Application));
#endif

Application create_application(const char*, Bitmap, ApplicationEntrypoint);
void registerApplication(Application*);