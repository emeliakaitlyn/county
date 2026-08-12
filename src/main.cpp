#include <windows.h>

#include <string>

namespace {
constexpr int kWindowWidth = 360;
constexpr int kWindowHeight = 220;
constexpr int kLabelId = 1001;
constexpr int kIncrementId = 1002;
constexpr int kDecrementId = 1003;
constexpr int kResetId = 1004;

int g_count = 0;
HWND g_countLabel = nullptr;

std::wstring FormatCountText() {
    return L"Count: " + std::to_wstring(g_count);
}

void UpdateCountLabel() {
    if (g_countLabel != nullptr) {
        SetWindowTextW(g_countLabel, FormatCountText().c_str());
    }
}

void LayoutControls(HWND hwnd) {
    RECT clientRect{};
    GetClientRect(hwnd, &clientRect);

    const int width = clientRect.right - clientRect.left;
    const int labelWidth = width - 40;

    MoveWindow(g_countLabel, 20, 25, labelWidth, 40, TRUE);
    MoveWindow(GetDlgItem(hwnd, kIncrementId), 20, 90, 90, 32, TRUE);
    MoveWindow(GetDlgItem(hwnd, kDecrementId), 135, 90, 90, 32, TRUE);
    MoveWindow(GetDlgItem(hwnd, kResetId), 250, 90, 90, 32, TRUE);
}

void HandleCommand(WPARAM wParam) {
    switch (LOWORD(wParam)) {
    case kIncrementId:
        ++g_count;
        UpdateCountLabel();
        break;
    case kDecrementId:
        --g_count;
        UpdateCountLabel();
        break;
    case kResetId:
        g_count = 0;
        UpdateCountLabel();
        break;
    default:
        break;
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        g_countLabel = CreateWindowExW(
            0,
            L"STATIC",
            FormatCountText().c_str(),
            WS_CHILD | WS_VISIBLE,
            0,
            0,
            0,
            0,
            hwnd,
            reinterpret_cast<HMENU>(kLabelId),
            reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hwnd, GWLP_HINSTANCE)),
            nullptr);

        CreateWindowExW(
            0,
            L"BUTTON",
            L"+1",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0,
            0,
            0,
            0,
            hwnd,
            reinterpret_cast<HMENU>(kIncrementId),
            reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hwnd, GWLP_HINSTANCE)),
            nullptr);

        CreateWindowExW(
            0,
            L"BUTTON",
            L"-1",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0,
            0,
            0,
            0,
            hwnd,
            reinterpret_cast<HMENU>(kDecrementId),
            reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hwnd, GWLP_HINSTANCE)),
            nullptr);

        CreateWindowExW(
            0,
            L"BUTTON",
            L"Reset",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0,
            0,
            0,
            0,
            hwnd,
            reinterpret_cast<HMENU>(kResetId),
            reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hwnd, GWLP_HINSTANCE)),
            nullptr);

        LayoutControls(hwnd);
        return 0;
    }
    case WM_SIZE:
        LayoutControls(hwnd);
        return 0;
    case WM_COMMAND:
        HandleCommand(wParam);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcW(hwnd, message, wParam, lParam);
    }
}
}  // namespace

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int showCommand) {
    const wchar_t kClassName[] = L"CounterAppWindowClass";

    WNDCLASSW windowClass{};
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = instance;
    windowClass.lpszClassName = kClassName;
    windowClass.hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(32512));
    windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

    if (!RegisterClassW(&windowClass)) {
        MessageBoxW(nullptr, L"Failed to register window class.", L"Counter App", MB_ICONERROR | MB_OK);
        return 1;
    }

    HWND hwnd = CreateWindowExW(
        0,
        kClassName,
        L"Counter App",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        kWindowWidth,
        kWindowHeight,
        nullptr,
        nullptr,
        instance,
        nullptr);

    if (hwnd == nullptr) {
        MessageBoxW(nullptr, L"Failed to create the main window.", L"Counter App", MB_ICONERROR | MB_OK);
        return 1;
    }

    ShowWindow(hwnd, showCommand);
    UpdateWindow(hwnd);

    MSG message{};
    while (GetMessageW(&message, nullptr, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    return static_cast<int>(message.wParam);
}
