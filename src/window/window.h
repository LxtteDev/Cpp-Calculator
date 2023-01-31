#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Window {
    public:
        Window(LPCSTR name, int width, int height);
        Window(const Window&) = delete;
        Window& operator =(const Window&) = delete;
        ~Window();

        bool proccessMessages();

    private:
        HINSTANCE m_hInstance;
        HWND m_hWnd;
};