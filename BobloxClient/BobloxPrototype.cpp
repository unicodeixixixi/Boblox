#include <windows.h>

// Declare a global variable for the window class name
const char g_szClassName[] = "myWindowClass";

// Declare global variables for the buttons
HWND g_hButtonRect;
HWND g_hButtonAnchor;

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            // Create the "Place Rectangles" button
            g_hButtonRect = CreateWindow(
                "BUTTON",               // Predefined class; Unicode assumed 
                "Place Rectangles",     // Button text 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                10,                     // x position 
                10,                     // y position 
                150,                    // Button width
                30,                     // Button height
                hwnd,                   // Parent window
                (HMENU) 1,              // Button ID
                (HINSTANCE) GetWindowLong(hwnd, GWLP_HINSTANCE),
                NULL);                  // No additional data  

            // Create the "Anchor" button
            g_hButtonAnchor = CreateWindow(
                "BUTTON",               // Predefined class; Unicode assumed 
                "Anchor",               // Button text 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                10,                     // x position 
                50,                     // y position 
                150,                    // Button width
                30,                     // Button height
                hwnd,                   // Parent window
                (HMENU) 2,              // Button ID
                (HINSTANCE) GetWindowLong(hwnd, GWLP_HINSTANCE),
                NULL);                  // No additional data  
            break;
        case WM_COMMAND:
            // Handle button clicks
            switch(LOWORD(wParam))
            {
                case 1:
                    // Handle "Place Rectangles" button click
                    MessageBox(hwnd, "Place Rectangles button clicked!", "Button Click", MB_OK);
                    break;
                case 2:
                    // Handle "Anchor" button click
                    MessageBox(hwnd, "Anchor button clicked!", "Button Click", MB_OK);
                    break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Step 1: Registering the Window Class
int RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassEx(&wc);
}

// Step 2: Creating the Window
HWND CreateMainWindow(HINSTANCE hInstance)
{
    HWND hwnd = CreateWindowEx(
        0,                          // Optional
        g_szClassName,              // Window class name
        "My Title",                 // Window title
        WS_OVERLAPPEDWINDOW,        // Window style
        CW_USEDEFAULT,              // Window x position
        CW_USEDEFAULT,              // Window y position
        500,                        // Window width
        400,                        // Window height
        NULL,                       // Parent window    
        NULL,                       // Menu
        hInstance,                  // Instance handle
        NULL                        // Additional application data
    );

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return NULL;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    return hwnd;
}

// Step 3: The Message Loop
int MessageLoop()
{
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}

// The main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Step 1: Registering the Window Class
    if(RegisterWindowClass(hInstance) == 0)
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // Step 2: Creating the Window
    HWND hwnd = CreateMainWindow(hInstance);
    if(hwnd == NULL)
    {
        return 1;
    }

    // Step 3: The Message Loop
    int exitCode = MessageLoop();

    return exitCode;
}
