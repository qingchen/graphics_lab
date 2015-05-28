#include <windows.h>
  
// ����ע��Ĵ�������
LPCWSTR g_szClassName = L"myWindowClass";
  
/*
 * ���Ĳ�,���ڹ���
 */
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        // ���ڻ�����Ϣ
        case WM_PAINT:
            /*
             * ����ֻ��Ҫ������������ǵ� GDI ���ƺ����Ϳ��ԣ������ط�����������
             */
        break;
        // ���ڹر���Ϣ
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        // ����������Ϣ
        case WM_DESTROY:
            PostQuitMessage(0); // �����뿪��Ϣ��ϵͳ
        break;
        // ������Ϣ
        default:
            // pass ��ϵͳ���۲���
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
  
/*
 * ��һ��,ע�ᴰ����
 */
void RegisterMyWindow(HINSTANCE hInstance)
{
    WNDCLASSEX wc;  
  
    // 1)���ô�������
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = MyWindowProc; // ���õ��Ĳ��Ĵ��ڹ��̻ص�����
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  
    // 2)ע��
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("����ע��ʧ��!"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // �����˳�
    }
}
  
/*
 * �ڶ�������������
 */
HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow)
{
    HWND hwnd;
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        TEXT("�ҵĴ�������"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, // �������� x,y Ĭ�Ϸ��� ���ڿ� 400 �� 300
        NULL, NULL, hInstance, NULL);
  
    if(hwnd == NULL)
    {
        MessageBox(NULL, TEXT("���ڴ���ʧ��!"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // �����˳�
    }
  
    // ��ʾ����
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
  
    return hwnd;
}
  
/*
 * ������
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG Msg;
  
    // ��һ��,ע�ᴰ����
    RegisterMyWindow(hInstance);
    // �ڶ���:��������
    hwnd =  CreateMyWindow(hInstance, nCmdShow);
    // ������:��Ϣѭ��
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}