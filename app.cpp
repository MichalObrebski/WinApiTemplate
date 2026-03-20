#include "app.h"
#include <stdexcept>
#include <dwmapi.h>

std::wstring const app::s_class_name{ L"Template Window" };
bool app::register_class() {
    WNDCLASSEXW desc{};
    if (GetClassInfoExW(m_instance, s_class_name.c_str(), &desc) != 0)
        return true;
    desc = {
        .cbSize = sizeof(WNDCLASSEXW),
        .lpfnWndProc = window_proc_static,
        .hInstance = m_instance,
        // .hIcon = static_cast<HICON>(LoadImageW(
        //     m_instance,
        //     MAKEINTRESOURCEW(ID_APPICON),
        //     IMAGE_ICON,
        //     0, 0,
        //     LR_SHARED | LR_DEFAULTSIZE
        // )),
        .hCursor = LoadCursorW(nullptr, (LPCWSTR)IDC_ARROW),
        .hbrBackground = CreateSolidBrush(RGB(250, 247, 238)),
        // .lpszMenuName = MAKEINTRESOURCEW(ID_MAINMENU),
        .lpszClassName = s_class_name.c_str()
    };
    return RegisterClassExW(&desc) != 0;
}
HWND app::create_window(DWORD style, HWND parent, DWORD ex_style){
    RECT size {0, 0, board::width, board::height};
    AdjustWindowRectEx(&size, style, true, 0);
    HWND window = CreateWindowExW(
        ex_style,
        s_class_name.c_str(),
        L"Template",
        style,
        CW_USEDEFAULT, 0, /*default position*/
        CW_USEDEFAULT, 0, /*default size*/
        parent,
        nullptr,
        m_instance,
        this
    );
    // for (auto &f : m_board.fields())
    //     f.window = CreateWindowExW(
    //         0,
    //         f.class_name,
    //         f.window_name,
    //         f.style,
    //         f.position.left, f.position.top,
    //         f.position.right - f.position.left,
    //         f.position.bottom - f.position.top,
    //         window,
    //         f.menu,
    //         m_instance,
    //         nullptr
    //     );
    return window;
}
LRESULT app::window_proc_static(HWND window, UINT message, WPARAM wparam, LPARAM lparam){
    app *thisApp = nullptr;
    if (message == WM_NCCREATE){
        auto p = reinterpret_cast<LPCREATESTRUCTW>(lparam);
        thisApp = static_cast<app *>(p->lpCreateParams);
        SetWindowLongPtrW(window, GWLP_USERDATA,
        reinterpret_cast<LONG_PTR>(thisApp));
    }
    else{
        thisApp = reinterpret_cast<app *>(
        GetWindowLongPtrW(window, GWLP_USERDATA));
    }
    if (thisApp != nullptr){
        return thisApp->window_proc(window, message,wparam, lparam);
    }
    return DefWindowProcW(window, message, wparam, lparam);
}
LRESULT app::window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam){
    switch (message) {
        case WM_CLOSE:
            DestroyWindow(window);
            return 0;
        case WM_DESTROY:
            if (window == m_main)
            PostQuitMessage(EXIT_SUCCESS);
            return 0;
        case WM_CTLCOLORSTATIC:
            return reinterpret_cast<INT_PTR>(m_field_brush);
        case WM_MOVE:
            on_window_move(window, reinterpret_cast<LPWINDOWPOS>(lparam));
            return 0;
        case WM_SIZE:
            on_resize(LOWORD(lparam), HIWORD(lparam));
            return 0;
        case WM_COMMAND:
            on_command(LOWORD(wparam));
            return 0;
    }
    return DefWindowProcW(window, message, wparam, lparam);
}
app::app(HINSTANCE instance)
    : m_instance{ instance }, m_main{},
        m_field_brush{ CreateSolidBrush(RGB(204, 192, 174)) },
        m_screen_size { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)}{
    register_class();
    DWORD main_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX;
    m_main = create_window(main_style);
}
int app::run(int show_command){
    ShowWindow(m_main, show_command);
    MSG msg{};
    BOOL result = TRUE;
    HACCEL shortcuts = LoadAcceleratorsW(m_instance, MAKEINTRESOURCEW(ID_SHORTCUTS));
    while ((result = GetMessageW(&msg, nullptr, 0, 0)) != 0){
        if (result == -1)
            return EXIT_FAILURE;
        if(!TranslateAcceleratorW(msg.hwnd, shortcuts, &msg)){
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    return EXIT_SUCCESS;
}
void app::on_window_move(HWND window, LPWINDOWPOS params){

}
void app::on_command(WORD cmdID){

}
void app::on_resize(int width, int height){
    m_board.recalculate_fields(width, height);
    for(auto &f : m_board.const_fields())
        MoveWindow(
            f.window,
            f.position.left,
            f.position.top,
            f.position.right - f.position.left,
            f.position.bottom - f.position.top,
            true
        );
}