#include "window.h"

std::vector<HWND> buttonList;
HWND output;

std::string one = "";
std::string two = "";
int operation = -1;

HWND createButton(const char * text, int x, int y, int w, int h, HWND hWnd, HMENU hMenu) {
    HWND button = CreateWindow("BUTTON", text, WS_VISIBLE | WS_CHILD, x, y, w, h, hWnd, hMenu, NULL, NULL);
    return button;
}

HWND createTextField(const char * text, int x, int y, int w, int h, HWND hWnd, HMENU hMenu) {
    HWND field = CreateWindow("STATIC", text, WS_VISIBLE | WS_CHILD, x, y, w, h, hWnd, hMenu, NULL, NULL);
    return field;
}

static void removeTrailingCharacters(std::string &str, const char charToRemove) {
    str.erase (str.find_last_not_of(charToRemove) + 1, std::string::npos );
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            // Row 1 (Text)
            output =             createTextField("",  5,   5, 375, 35, hWnd, (HMENU)16);
            SendMessage(output, WM_SETFONT, WPARAM(CreateFont(35, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial")), TRUE);

            // Row 2 (1 - 3 +)
            buttonList.push_back(createButton("1",   5,  45,  90, 90, hWnd, (HMENU)1));
            buttonList.push_back(createButton("2", 100,  45,  90, 90, hWnd, (HMENU)2));
            buttonList.push_back(createButton("3", 195,  45,  90, 90, hWnd, (HMENU)3));
            buttonList.push_back(createButton("+", 290,  45,  90, 90, hWnd, (HMENU)10));
 
            // Row 3 (4 - 6 -) 
            buttonList.push_back(createButton("4",   5, 140,  90, 90, hWnd, (HMENU)4));
            buttonList.push_back(createButton("5", 100, 140,  90, 90, hWnd, (HMENU)5));
            buttonList.push_back(createButton("6", 195, 140,  90, 90, hWnd, (HMENU)6));
            buttonList.push_back(createButton("-", 290, 140,  90, 90, hWnd, (HMENU)11));
 
            // Row 4 (7 - 9 *) 
            buttonList.push_back(createButton("7",   5, 235,  90, 90, hWnd, (HMENU)7));
            buttonList.push_back(createButton("8", 100, 235,  90, 90, hWnd, (HMENU)8));
            buttonList.push_back(createButton("9", 195, 235,  90, 90, hWnd, (HMENU)9));
            buttonList.push_back(createButton("*", 290, 235,  90, 90, hWnd, (HMENU)12));
 
            // Row 5 (C 0 = /) 
            buttonList.push_back(createButton("C",   5, 330,  90, 90, hWnd, (HMENU)15));
            buttonList.push_back(createButton("0", 100, 330,  90, 90, hWnd, (HMENU)0));
            buttonList.push_back(createButton("=", 195, 330,  90, 90, hWnd, (HMENU)14));
            buttonList.push_back(createButton("/", 290, 330,  90, 90, hWnd, (HMENU)13));

            break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_COMMAND:
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);

            /* std::string button = std::to_string(wmId);
            std::cout << "Button " + button + " pressed." << std::endl;

            SetWindowText(output, const_cast<char *>(button.c_str())); */

            if (wmId < 10) {
                // Number
                if (operation == -1) {
                    one += std::to_string(wmId);
                    SetWindowText(output, const_cast<char *>(one.c_str()));
                } else {
                    two += std::to_string(wmId);
                    SetWindowText(output, const_cast<char *>(two.c_str()));
                }
            } else {
                switch (wmId) {
                    case 10:
                        // +
                        if (one == "")
                            one = "0";
                        operation = 0;
                        SetWindowText(output, "");
                        break;
                    case 11:
                        // -
                        if (one == "")
                            one = "0";
                        operation = 1;
                        SetWindowText(output, "");
                        break;
                    case 12:
                        // *
                        if (one == "")
                            one = "0";
                        operation = 2;
                        SetWindowText(output, "");
                        break;
                    case 13:
                        // /
                        if (one == "")
                            one = "0";
                        operation = 3;
                        SetWindowText(output, "");
                        break;
                    case 14: {
                        // =
                        if (one == "")
                            one = "0";
                        if (two == "")
                            two = "0";

                        int x = std::stoi(one);
                        int y = std::stoi(two);

                        if (operation == 0) {
                            float Plus = (float)x + (float)y;
                            std::string plus = std::to_string(Plus);
                            removeTrailingCharacters(plus, '0');
                            removeTrailingCharacters(plus, '.');
                            SetWindowText(output, const_cast<char *>(plus.c_str()));
                        } else if (operation == 1) {
                            float Minus = (float)x - (float)y;
                            std::string minus = std::to_string(Minus);
                            removeTrailingCharacters(minus, '0');
                            removeTrailingCharacters(minus, '.');
                            SetWindowText(output, const_cast<char *>(minus.c_str()));
                        } else if (operation == 2) {
                            float Mult = (float)x * (float)y;
                            std::string mult = std::to_string(Mult);
                            removeTrailingCharacters(mult, '0');
                            removeTrailingCharacters(mult, '.');
                            SetWindowText(output, const_cast<char *>(mult.c_str()));
                        } else if (operation == 3) {
                            float Div = (float)x / (float)y;
                            std::string div = std::to_string(Div);
                            removeTrailingCharacters(div, '0');
                            removeTrailingCharacters(div, '.');
                            SetWindowText(output, const_cast<char *>(div.c_str()));
                        }

                        one = "";
                        two = "";
                        operation = -1;
                        break;
                    }
                    case 15:
                        // Clear
                        SetWindowText(output, "");
                        one = "";
                        two = "";
                        operation = -1;
                        break;
                }
            }

            break;
    } 

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Window(LPCSTR name, int width, int height): m_hInstance(GetModuleHandle(nullptr)) {
    WNDCLASS wndClass = {};
    wndClass.lpszClassName = "WindowClass";
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    RegisterClass(&wndClass);

    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, style, false);

    m_hWnd = CreateWindowEx(
        0,
        "WindowClass",
        name,
        style,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        m_hInstance,
        NULL
    );

    ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window() {
    UnregisterClass("WindowClass", m_hInstance);
}

bool Window::proccessMessages() {
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
        if (msg.message == WM_QUIT)
            return false;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}
