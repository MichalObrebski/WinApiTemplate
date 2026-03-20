#include <windows.h>
#include "app.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE

#include <windows.h>
int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR, int show_command){
    app thisApp{ instance };
    return thisApp.run(show_command);
}