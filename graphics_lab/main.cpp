#include <windows.h>
#include "perspectivecamera.h"
#include "sphere.h"
#include "checkermaterial.h"
#include "color.h"
#include "phongmaterial.h"
#include "plane.h"
#include "union.h"
#include "directionallight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <iostream>

using namespace std;
// 用于注册的窗口类名
LPCWSTR g_szClassName = L"myWindowClass";

Color RaytraceRecursive(Geometry *geo, const Ray &ray, double max_reflect)
{
	IntersectResult result = geo->intersect(ray);
	if (result.geometry)
	{
		double reflectiveness = result.geometry->material->reflectiveness;
		Color color = result.geometry->material->sample(ray, result.position, result.normal);
		color = color.multiply(1 - reflectiveness);
		if (reflectiveness > 0 && max_reflect > 0)
		{
			Vector3 r = result.normal.multiply(-2 * result.normal.dot(ray.direction)).add(ray.direction);
			Ray ray_tmp(result.position, r);
			Color reflected_color = RaytraceRecursive(geo, ray_tmp, max_reflect - 1);
			color = color.add(reflected_color.multiply(reflectiveness));
		}
		return color;
	}
	else
		return black;
}
void Paint(HWND hwnd) 
{
    // paint struct 绘图结构体，存储目标窗口可以绘图的客户端区域(client area)
    PAINTSTRUCT ps;
    HDC hdc;   // DC(可画图的内存对象) 的句柄
	RECT rc;
	GetClientRect(hwnd, &rc);
    // 通过窗口句柄获取该窗口的 DC
    hdc = BeginPaint(hwnd, &ps);
#if 0
	Plane *plane = new Plane(Vector3(0, 1, 0), 0);
	Sphere *sphere1 = new Sphere(Vector3(-10, 10, -10), 10);
	Sphere *sphere2 = new Sphere(Vector3(10, 10, -10), 10);
	plane->material = new CheckerMaterial(0.1, 0.5);
	sphere1->material = new PhongMaterial(red, white, 16, 0.25);
	sphere2->material = new PhongMaterial(blue, white, 16, 0.25);
	PerspectiveCamera camera(Vector3(0, 5, 15), Vector3(0, 0, -1), Vector3(0, 1, 0), 90);
	Union uni;
	uni.geometrys.push_back(plane);
	uni.geometrys.push_back(sphere1);
	uni.geometrys.push_back(sphere2);
	camera.Initialize();
#endif
#if 1
	Union uni;
	uni.geometrys.push_back(new Sphere(Vector3(0, 10, -10), 10));
	uni.geometrys.push_back(new Plane(Vector3(0, 1, 0), 0));
	uni.geometrys.push_back(new Plane(Vector3(0, 0, 1), -50));
	uni.geometrys.push_back(new Plane(Vector3(1, 0, 0), -20));
	vector<Light*> lights;
	//lights.push_back(new DirectionalLight(white, Vector3(-1.75, -2, -1.5)));
	lights.push_back(new PointLight(white.multiply(2000), Vector3(30, 40, 20)));
	PerspectiveCamera camera(Vector3(0, 10, 10), Vector3(0, 0, -1), Vector3(0, 1, 0), 90);
	camera.Initialize();
#endif
	//IntersectResult result;
	//int depth;
	double sx, sy;
	Ray ray;
	int r, g, b;
	for (int y = 0; y <= 256; y++)
	{
		sy = 1 - y / 256.0;
		for (int x = 0; x <= 256; x++)
		{
			sx = x / 256.0;
			ray = camera.generateRay(sx, sy);
			IntersectResult result = uni.intersect(ray);
			if (result.geometry)
			{
				Color color = black;
				for (int i = 0; i < lights.size(); i++)
				{
					LightSample lightsample = lights[i]->sample(&uni, result.position);
					if (lightsample != zero)
					{
						double NdotL = result.normal.dot(lightsample.L);
						if (NdotL >= 0)
							color = color.add(lightsample.EL.multiply(NdotL));
					}
				}
				//depth = 255 - min((result.distance/10)*255, 255);
				//Color color = result.geometry->material->sample(ray, result.position, result.normal);
				//Color color = RaytraceRecursive(&uni, ray, 3);
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
 * 第四步,窗口过程
 */
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        // 窗口绘制消息
        case WM_PAINT:
			Paint(hwnd); 
            /*
             * 我们只需要在这里调用我们的 GDI 绘制函数就可以，其他地方可以先无视
             */
        break;
        // 窗口关闭消息
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        // 窗口销毁消息
        case WM_DESTROY:
            PostQuitMessage(0); // 发送离开消息给系统
        break;
        // 其他消息
        default:
            // pass 给系统，咱不管
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
  
/*
 * 第一步,注册窗口类
 */
void RegisterMyWindow(HINSTANCE hInstance)
{
    WNDCLASSEX wc;  
  
    // 1)配置窗口属性
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = MyWindowProc; // 设置第四步的窗口过程回调函数
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  
    // 2)注册
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("窗口注册失败!"), TEXT("错误"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // 进程退出
    }
}
  
/*
 * 第二步，创建窗口
 */
HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow)
{
    HWND hwnd;
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        TEXT("我的窗口名称"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, // 出现坐标 x,y 默认分配 窗口宽 400 高 300
        NULL, NULL, hInstance, NULL);
  
    if(hwnd == NULL)
    {
        MessageBox(NULL, TEXT("窗口创建失败!"), TEXT("错误"), MB_ICONEXCLAMATION | MB_OK);
        exit(0); // 进程退出
    }
  
    // 显示窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
  
    return hwnd;
}
  
/*
 * 主函数
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG Msg;
  
    // 第一步,注册窗口类
    RegisterMyWindow(hInstance);
    // 第二步:创建窗口
    hwnd =  CreateMyWindow(hInstance, nCmdShow);
    // 第三步:消息循环
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}