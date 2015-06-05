#include <windows.h>
#include "perspectivecamera.h"
#include "sphere.h"
#include "checkermaterial.h"
#include "color.h"
#include "phongmaterial.h"
#include <iostream>

using namespace std;
// ����ע��Ĵ�������
LPCWSTR g_szClassName = L"myWindowClass";

void Paint(HWND hwnd) 
{
    // paint struct ��ͼ�ṹ�壬�洢Ŀ�괰�ڿ��Ի�ͼ�Ŀͻ�������(client area)
    PAINTSTRUCT ps;
    HDC hdc;   // DC(�ɻ�ͼ���ڴ����) �ľ��
	RECT rc;
	GetClientRect(hwnd, &rc);
    // ͨ�����ھ����ȡ�ô��ڵ� DC
    hdc = BeginPaint(hwnd, &ps);
	PerspectiveCamera camera(Vector3(0, 10, 5), Vector3(0, 0, -1), Vector3(0, 1, 0), 90);
	Sphere *sphere = new Sphere(Vector3(0, 10, -10), 10);
	sphere->material = new PhongMaterial(red, white, 16);
	camera.Initialize();
	double sx, sy;
	Ray ray;
	//IntersectResult result;
	int depth;
	int r, g, b;
	for (int y = 0; y < 256; y++)
	{
		sy = 1 - y / 256.0;
		for (int x = 0; x < 256; x++)
		{
			sx = x / 256.0;
			ray = camera.generateRay(sx, sy);
			IntersectResult result = sphere->intersect(ray);
			if (result.geometry)
			{
				//depth = 255 - min((result.distance/10)*255, 255);
				Color color = result.geometry->material->sample(ray, result.position, result.normal);
				r = min(color.r * 255, 255);
				g = min(color.g * 255, 255);
				b = min(color.b * 255, 255);
				SetPixel(hdc, x, y, RGB((BYTE)(r), (BYTE)(g), (BYTE)(b)));
			}
			
		}
	}
 
    EndPaint(hwnd, &ps);
}

/*
 * ���Ĳ�,���ڹ���
 */
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        // ���ڻ�����Ϣ
        case WM_PAINT:
			Paint(hwnd); 
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
        CW_USEDEFAULT, CW_USEDEFAULT, 256, 256, // �������� x,y Ĭ�Ϸ��� ���ڿ� 400 �� 300
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