#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
    // Register the window class
    WNDCLASS wc = { 0 };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindow("MyWindowClass", "My Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInst, NULL);

    // Show the window
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
		// Draw a red square in the middle of the client area
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		RECT rect;
		GetClientRect(hwnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		int size = 100;  // Set the size to 100x100 pixels
		int x = (width - size) / 2;
		int y = (height - size) / 2;
		rect.left = x;
		rect.top = y;
		rect.right = x + size;
		rect.bottom = y + size;
		HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(hdc, &rect, hbr);
		DeleteObject(hbr);
		EndPaint(hwnd, &ps);
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
