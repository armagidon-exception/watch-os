#define __APPLICATIONS__
#include "application.h"
#include "stdlib.h"

Application create_application(const char* title, Bitmap bitmap, ApplicationEntrypoint entrypoint) {
    return {bitmap, entrypoint, create_scene(title), title};
}

void registerApplication(Application* app) {
    //add_element(&applications, app);
    add_element_with_id(&applications, app, app->title);
}