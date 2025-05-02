#include "Common.hpp"

WNDCLASSEX InitWNDCLASS(HINSTANCE hInstance, const char CLASS_NAME[], WNDPROC WindowProc) {
    WNDCLASSEX wc = { 0 };

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
    wc.hbrBackground = CreateSolidBrush(RGB(100, 100, 100));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassEx(&wc);
    return wc;
}

void CreateWidget(HWND hwnd) {
    RECT rect;
    GetClientRect(hwnd, &rect);

    int Width = rect.right - rect.left;
    int Height = rect.bottom - rect.top;

    int buttonWidth = 100;
    int Margin = 10;
    int EditWidth = (Width - buttonWidth) - (Margin * 3);
    int ControlHeight = 20;

    HWND staticText = CreateWindow("STATIC", "Поздравляю! Твои файлы были зашифрованны :D", WS_VISIBLE | WS_CHILD | SS_CENTER,
        0, 0,
        Width, ControlHeight,
        hwnd, NULL, NULL, NULL);

    HWND TextEdit = CreateWindow("EDIT", "Нo ты мoжешь нe вoлнoвaтcя! Для pacшифрoфки тебе нужно написать правельный ключ! Но есть нюанс... я его тебе не скажу. Удачи!",
        WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
        Margin, 25 + Margin,
        Width - Margin * 2,
        Height - (ControlHeight + Margin * 2) * 2,
        hwnd, NULL, NULL, NULL);

    HWND editControl = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | ES_NUMBER,
        Margin,
        Height - ControlHeight - Margin,
        EditWidth,
        ControlHeight,
        hwnd, (HMENU)EditBoxID, NULL, NULL);

    HWND buttonControl = CreateWindow("BUTTON", "Click me", WS_VISIBLE | WS_CHILD,
        Margin + EditWidth + Margin,
        Height - ControlHeight - Margin,
        buttonWidth, ControlHeight,
        hwnd, (HMENU)ButtonID, NULL, NULL);
}