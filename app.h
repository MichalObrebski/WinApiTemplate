#pragma once
#include "board.h"
#include <windows.h>
#include <string>
#include "resource.h"

class app{
private:
    static std::wstring const s_class_name;
    HINSTANCE m_instance;
    HWND m_main;
    board m_board;
    HBRUSH m_field_brush;
    POINT m_screen_size;

    bool register_class();
    static LRESULT CALLBACK window_proc_static(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
    LRESULT window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
    HWND create_window(DWORD style, HWND parent = nullptr, DWORD ex_style = 0);
    void on_window_move(HWND window, LPWINDOWPOS params);
    void on_command(WORD cmdID);
    void on_resize(int width, int height);
public:
    app(HINSTANCE instance);
    int run(int show_command);
};
