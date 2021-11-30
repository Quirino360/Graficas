#pragma once 
#pragma comment(lib, "ComDlg32.lib")

#include <windows.h>

#if defined(DX11)
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#elif defined(OGL)
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#endif

#include "GraphicModule.h"
#include "EditorManager.h"

#include <iostream>
#include <string>

#include "imgui.h"

// ----- Global var
HWND g_hwnd;
GraphicsModule::test MiObj;

#if defined (OGL)
GLFWwindow* OGLwindow;
#endif 

#if defined(OGL)
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

#endif

#if defined(DX11)
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
#endif


std::string OpenFileGetName(HWND owner = NULL)
{
    // common dialog box structure, setting all fields to 0 is important
    OPENFILENAME ofn = { 0 };
    TCHAR szFile[260] = { 0 };

    // Initialize remaining fields of OPENFILENAME structure
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = owner;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = ("All\0*.*\0Text\0*.TXT\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        return szFile;
    }
    return "";
}
/**/

#if defined(DX11)
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{

    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);
    // Handle UI inputs
    if (ImGui_ImplWin32_WndProcHandler(_hwnd, _msg, _wParam, _lParam))
        return 1;

    // Handle Window inputs
    switch (_msg)
    {
    case WM_SIZE:
        //if (g_pd3dDevice != NULL && _wParam != SIZE_MINIMIZED)
    {
    }
    return 0;
    break;

    case WM_SYSCOMMAND:
        if ((_wParam & 0xfff0) == SC_KEYMENU)
        {
            return 0;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

#if defined(DX11)
    case WM_KEYDOWN: {
        UINT key = LOWORD(_wParam);
        switch (key)
        {
        case 'O':
        {
            break;
        }
        case'M':
        {
            testOBj.mouseMove = !testOBj.mouseMove;
            break;
        }

        case 37:    //Left key 
            testOBj.camera.move(-1, 0, 0);
            break;
        case 38:    //Up key
            testOBj.camera.move(0, 1, 0);
            break;
        case 39:    //Right key
            testOBj.camera.move(1, 0, 0);
            break;
        case 40:    //Down key 
            testOBj.camera.move(0, -1, 0);
            break;
        case 'A':    //Key A
            testOBj.camera.move(0, 0, 1);
            break;
        case 'D':
            testOBj.camera.move(0, 0, -1);
            break;

        case 9:     //Tab 
        {
            testOBj.cameraChange = !testOBj.cameraChange;
            if (testOBj.cameraChange)
            {
                testOBj.g_Projection = XMMATRIX(testOBj.camera.getMatrixPerspective().matrix4);
            }
            else
            {
                testOBj.g_Projection = XMMATRIX(testOBj.camera.getMatrixOrthographic().matrix4);
            }
            GraphicsModule::cbChangeOnResize cbChangesOnResize;
            cbChangesOnResize.mProjection = XMMatrixTranspose(testOBj.g_Projection);
            testOBj.renderManager.getDeviceContextDX11()->UpdateSubresource(testOBj.g_pCBChangeOnResize->getyBufferDX11(), 0, NULL, &cbChangesOnResize, 0, 0);
            break;
        }

        default:
            break;
        }
    }
#endif
    }
    return ::DefWindowProc(_hwnd, _msg, _wParam, _lParam);
}

#elif defined(OGL)
//manage inputs
void processInput(GLFWwindow* window)
{
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        std::string fName = OpenFileGetName(g_hwnd);
        testOBj.aLoadModel.loadModel(fName);
    }
}

//manage window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
#endif


#if defined(DX11)   
HRESULT InitWindow(LONG _width, LONG _height)
{

    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = nullptr;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "TutorialWindowClass";
    wcex.hIconSm = nullptr;
    if (!RegisterClassEx(&wcex))
    {
        return E_FAIL;
    }

    // Create window
    RECT rc = { 0, 0, _width, _height };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    g_hwnd = CreateWindow("TutorialWindowClass", "Graficos 1", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, _width, _height, NULL, NULL, NULL, NULL);
    if (!g_hwnd)
    {
        return E_FAIL;
    }
    ShowWindow(g_hwnd, SW_SHOWNORMAL);

    return S_OK;
}
#endif


//
HRESULT InitImgUI()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer back ends
#if defined(DX11)
    ImGui_ImplWin32_Init(g_hwnd);
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);
    ImGui_ImplDX11_Init(testOBj.renderManager.getDeviceDX11(), testOBj.renderManager.getDeviceContextDX11());
#elif defined(OGL)
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);
    ImGui_ImplGlfw_InitForOpenGL(OGLwindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");
#endif
    return S_OK;
}

EditorManager editManager;


void RenderUI()
{
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);
    // Start the Dear ImGui frame

#if defined(DX11)
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();



#elif defined(OGL)
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
#endif
    ImGui::NewFrame();

#if defined(DX11)

    editManager.RenderUI();

#elif defined(OGL)
ImGui::Begin("Demo window");
ImGui::Button("Hello!");
ImGui::End();

#endif

    // render UI
    ImGui::Render();
#if defined(DX11)
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#elif defined(OGL)
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}


bool Init()
{
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);

    // create the window and console
    if (FAILED(InitWindow(1080, 720)))
    {
        DestroyWindow(g_hwnd);
        return false;
    }

    // create Graphic API interface
    if (FAILED(testOBj.InitDevice(g_hwnd)))
    {
        testOBj.CleanupDevice();
        return false;
    }

    // create UI
    if (FAILED(InitImgUI()))
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        return false;
    }

    editManager.Init();
}

void Render()
{
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);
    testOBj.Render();
    editManager.RenderBuffers();

#if defined(DX11) || defined(OGL)
    RenderUI();
#endif

#if defined(DX11)
    testOBj.renderManager.PresentDX11(0, 0);
#elif defined(OGL)
    
#endif
}

void Update()
{
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);

    testOBj.Update();
    editManager.Update();
}


void CleanResources()
{
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);

    // clean resources
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    testOBj.CleanupDevice();
    DestroyWindow(g_hwnd);
}

//
int main()
{
#if defined(DX11)
    
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);

    if (Init() == false)
    {
        return 0;
    }

    // main loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Update();
            Render();
        }
    }

    CleanResources();
    return (int)msg.wParam;

#elif defined(OGL)

    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    // glfw window creation
    OGLwindow = glfwCreateWindow(1080, 720, "LearnOpenGL", NULL, NULL);
    if (OGLwindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(OGLwindow);
    glfwSetFramebufferSizeCallback(OGLwindow, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    if (FAILED(InitImgUI()))
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        
        ImGui::DestroyContext();
        return 0;
    }

    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(OGLwindow))
    {
        // input
        processInput(OGLwindow);

        testOBj.Update();

        // render
        Render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(OGLwindow);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
#endif

}

// Vertex Array Objects = VAO
// Vertex Buffer Objects = VAO
//Element Buffer Object = EBO
