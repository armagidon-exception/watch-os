#define __APPLICATIONS__
#include "application.h"

Application create_application(const char* title, Bitmap bitmap, ApplicationEntrypoint entrypoint) {
    return {bitmap, entrypoint, create_scene(), title};
}

void registerApplication(Application* app) {
    add_element(&applications, app);
}