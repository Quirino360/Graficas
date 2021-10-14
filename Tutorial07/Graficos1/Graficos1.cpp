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


#include <iostream>
#include <string>

#include "imgui.h"



// -----------------Global var-----------------------------------------------------------------
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
//
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
//
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
//
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


void UIRender()
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


    if (ImGui::Begin("WorkSpace", nullptr))
    {
		if (ImGui::Button("Create Default Effect", ImVec2(175, 25)))
		{
			HRESULT hr = S_OK;
			BUFFER_DESC_DX11 bd;
			testOBj.aLoadModel.loadModel("ZResorces/meshes/Sphere/sphere.obj");

			testOBj.mesh.setVetices(testOBj.aLoadModel.getVertexData(), testOBj.aLoadModel.numVertex);

			//D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT_DX11;
			bd.ByteWidth = sizeof(Vertex) * testOBj.aLoadModel.numVertex;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA InitData;
			ZeroMemory(&InitData, sizeof(InitData));
			InitData.pSysMem = testOBj.mesh.getVertices();
			hr = testOBj.renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), &InitData, &testOBj.g_pVertexBuffer->getyBufferDX11());
			if (FAILED(hr))
			{
				std::cout << "Error at CreateBufferDX11 &g_pVertexBuffer->getyBufferDX11(), in Graficos cpp" << std::endl;
				return;
			}

			testOBj.mesh.setIndexBuffer(testOBj.aLoadModel.getIndexData()->data(), testOBj.aLoadModel.numIndices);
			bd.Usage = D3D11_USAGE_DEFAULT_DX11;
			bd.ByteWidth = sizeof(unsigned short) * testOBj.aLoadModel.numIndices;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			InitData.pSysMem = testOBj.mesh.getIndexBuffer();
			hr = testOBj.renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), &InitData, &testOBj.g_pIndexBuffer->getyBufferDX11());
			if (FAILED(hr))
			{
				std::cout << "Error at CreateBufferDX11 &g_pIndexBuffer->getyBufferDX11(), in Graficos cpp" << std::endl;
				return;
			}


		}

		if (ImGui::BeginCombo("","Effect Work Space"))
		{

            ImGui::EndCombo();
		}

		if (ImGui::BeginTabBar("0")) {
			ImGui::EndTabBar();
		}        
        ImGui::End();
    }




    if (ImGui::Begin("Mesh", nullptr))
    {
        // ------------------------------ Open Object ------------------------------ //
        if (ImGui::Button("Open file", ImVec2(75, 25)))
        {
            HRESULT hr = S_OK;
            BUFFER_DESC_DX11 bd;
            std::string fName = OpenFileGetName(g_hwnd);
            testOBj.aLoadModel.loadModel(fName);

            testOBj.mesh.setVetices(testOBj.aLoadModel.getVertexData(), testOBj.aLoadModel.numVertex);

            //D3D11_BUFFER_DESC bd;
            ZeroMemory(&bd, sizeof(bd));
            bd.Usage = D3D11_USAGE_DEFAULT_DX11;
            bd.ByteWidth = sizeof(Vertex) * testOBj.aLoadModel.numVertex;
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            bd.CPUAccessFlags = 0;
            D3D11_SUBRESOURCE_DATA InitData;
            ZeroMemory(&InitData, sizeof(InitData));
            InitData.pSysMem = testOBj.mesh.getVertices();
            hr = testOBj.renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), &InitData, &testOBj.g_pVertexBuffer->getyBufferDX11());
            if (FAILED(hr))
            {
                std::cout << "Error at CreateBufferDX11 &g_pVertexBuffer->getyBufferDX11(), in Graficos cpp" << std::endl;
                return;
            }

            testOBj.mesh.setIndexBuffer(testOBj.aLoadModel.getIndexData()->data(), testOBj.aLoadModel.numIndices);
            bd.Usage = D3D11_USAGE_DEFAULT_DX11;
            bd.ByteWidth = sizeof(unsigned short) * testOBj.aLoadModel.numIndices;
            bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
            bd.CPUAccessFlags = 0;
            InitData.pSysMem = testOBj.mesh.getIndexBuffer();
            hr = testOBj.renderManager.CreateBufferDX11(reinterpret_cast<D3D11_BUFFER_DESC*>(&bd), &InitData, &testOBj.g_pIndexBuffer->getyBufferDX11());
            if (FAILED(hr))
            {
                std::cout << "Error at CreateBufferDX11 &g_pIndexBuffer->getyBufferDX11(), in Graficos cpp" << std::endl;
                return;
            }
        }

        // ------------------------------ Object Transform ------------------------------/
        static float position[3]{ 0.0, 0.0, 0.0f };
        static float rotation[3]{ 0.0f, 0, 0.0f };
        static float scale[3]{ 1.0f, 1.0f, 1.0f };

        testOBj.mesh.position = Vector3(position[0], position[1], position[2]);
        testOBj.mesh.rotation = Vector3(rotation[0], rotation[1], rotation[2]);
        testOBj.mesh.scale = Vector3(scale[0], scale[1], scale[2]);

        if (ImGui::DragFloat3("Position", position, 0.1f))
        {
            testOBj.mesh.position = Vector3(position[0], position[1], position[2]);
        }
        if (ImGui::DragFloat3("Rotation", rotation, 0.1f))
        {
            testOBj.mesh.rotation = Vector3(rotation[0], rotation[1], rotation[2]);
        }
        if (ImGui::DragFloat3("Scale", scale, 0.1f))
        {
            testOBj.mesh.scale = Vector3(scale[0], scale[1], scale[2]);
        }
        ImGui::End();
    }


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



void Render()
{
    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);
    testOBj.Render();

#if defined(DX11) || defined(OGL)
    UIRender();
#endif

#if defined(DX11)
    testOBj.renderManager.PresentDX11(0, 0);
#elif defined(OGL)
    
#endif
}


//
int main()
{
#if defined(DX11)
    // create the window and console
    if (FAILED(InitWindow(1080, 720)))
    {
        DestroyWindow(g_hwnd);
        return 0;
    }

    auto& testOBj = GraphicsModule::GetTestObj(g_hwnd);
    // create Graphic API interface
    if (FAILED(testOBj.InitDevice(g_hwnd)))
    {
        testOBj.CleanupDevice();
        return 0;
    }

    // create UI
    if (FAILED(InitImgUI()))
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
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
            testOBj.Update();
            Render();
        }
    }


    // clean resources
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    testOBj.CleanupDevice();
    DestroyWindow(g_hwnd);
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
