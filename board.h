#pragma once
#include <array>
#include <windows.h>

struct field{
    RECT position;
    DWORD style = WS_CHILD | WS_VISIBLE;
    HWND window = nullptr;
    LPCWSTR class_name = L"BUTTON";
    LPCWSTR window_name = nullptr;
    HMENU menu = nullptr;
};

class board{
public:
    static constexpr LONG field_count = 9;
    static constexpr LONG field_size = 60;
    static constexpr LONG rows = 3;
    static constexpr LONG cols = 3;
    static constexpr LONG width = 3*65;
    static constexpr LONG height = 3*65;
    using field_array = std::array<field, field_count>;
    board();
    field_array & fields() {return m_fields;}
    field_array const & const_fields() const {return m_fields;}
    void recalculate_fields(int new_width, int new_height);
private:
    field_array m_fields;
};