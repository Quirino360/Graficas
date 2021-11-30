#include "EditorManager.h"

#if defined(DX11)
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#elif defined(OGL)
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#endif

#include "GraphicModule.h"

void EditorManager::Init()
{
    //iTextSize = 9999;
    iText = new char[iTextSize];

    //bufferNameSize = 9999;
    bufferName = new char[bufferNameSize];

    //variablesTextSize = 9999;
    variablesText = new char[variablesTextSize];

    // Set All to have nothing, if not they draw '*' chars
    for (int i = 0; i < iTextSize; i++)
    {
        iText[i] = NULL;
    }
    for (int i = 0; i < variablesTextSize; i++)
    {
        variablesText[i] = NULL;
    }
    for (int i = 0; i < bufferNameSize; i++)
    {
        bufferName[i] = NULL;
    }
}

void EditorManager::Update()
{
    auto& testOBj = GraphicsModule::GetTestObj();
}

void EditorManager::RenderBuffers()
{
}

void EditorManager::RenderUI()
{
    auto& testOBj = GraphicsModule::GetTestObj();

#if defined(DX11)
    
    AddVariablesUI();
    RernderShaderEditorUI(); // CreateDefaultShaders, Renders Editor & CompileShader

    /*if (ImGui::Begin("Mesh", nullptr))
    {
        // ---------- Open Object 
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

        // ----- Object Transform 
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
    }/**/


#elif defined(OGL)
    ImGui::Begin("Demo window");
    ImGui::Button("Hello!");
    ImGui::End();

#endif
}

void EditorManager::RernderShaderEditorUI()
{
    auto& testOBj = GraphicsModule::GetTestObj();

    // ---------- Shader Editor
    if (ImGui::Begin("WorkSpace", nullptr))
    {

        CreateDefaultShaders(); // Imgui Button

        if (ImGui::BeginCombo("", "Effect Work Space"))
        {

            ImGui::EndCombo();
        }

        ImGui::Separator();

        // Buffer editor
        ImGui::InputTextMultiline("BufferEditor", iText, iTextSize, ImVec2(250, 500));

        CompileShader(); // Imgui Button

        ImGui::End();
    }
}

void EditorManager::AddVariablesUI()
{
    auto& testOBj = GraphicsModule::GetTestObj();

    // ---------- Add and Print Variables
    if (ImGui::Begin("Variables", nullptr))
    {
        bool changeUI = false;

        ImGui::InputTextMultiline("BufferName", bufferName, bufferNameSize, ImVec2(200, 25));

        if (ImGui::BeginCombo("", "Add Variable"))
        {
            if (ImGui::Button("Add Effect", ImVec2(175, 25)))
            {
                testOBj.m_effects.name = bufferName;
                changeUI = true;
            }
            if (ImGui::Button("Add Pass", ImVec2(175, 25)))
            {
                testOBj.m_effects.CreatePassFromString(bufferName, bufferName); // change thsi to the one im modifying
                changeUI = true;
            }
            if (ImGui::Button("Create Float4", ImVec2(175, 25)))
            {
                testOBj.bufferManager.CreateFloat4(bufferName);
                changeUI = true;
            }
            if (ImGui::Button("Create Float3", ImVec2(175, 25)))
            {
                testOBj.bufferManager.CreateFloat3(bufferName);
                changeUI = true;
            }
            if (ImGui::Button("Create Float2", ImVec2(175, 25)))
            {
                testOBj.bufferManager.CreateFloat2(bufferName);
                changeUI = true;
            }
            if (ImGui::Button("Create Float", ImVec2(175, 25)))
            {
                testOBj.bufferManager.CreateFloat(bufferName);
                changeUI = true;
            }
            if (ImGui::Button("Create Matrix4", ImVec2(175, 25)))
            {
                testOBj.bufferManager.CreateMatrix4x4(bufferName);
                changeUI = true;
            }
            if (ImGui::Button("Create Render Target", ImVec2(175, 25)))
            {
                testOBj.bufferManager.CreateRenderTargetView(bufferName);
                changeUI = true;
            }

            ImGui::EndCombo();
        }

        // ChangeTheUi if they add or remove something
        if (true == changeUI)
        {
            ChangeVariables();
        }

        // Print Variables
        ImGui::InputTextMultiline("Variables", variablesText, variablesTextSize, ImVec2(250, 500));

        ImGui::End();
    }
}

void EditorManager::ChangeVariables()
{
    auto& testOBj = GraphicsModule::GetTestObj();

    unsigned int textAux = 0;
    // ----- Print all float 4
    for (unsigned int i = 0; i < testOBj.bufferManager.m_floats4.size(); i++)
    {
        variablesText[textAux + 0] = 'f'; variablesText[textAux + 1] = 'l'; variablesText[textAux + 2] = 'o'; variablesText[textAux + 3] = 'a';
        variablesText[textAux + 4] = 't'; variablesText[textAux + 5] = '4'; variablesText[textAux + 6] = ' ';
        textAux += 7;
        for (unsigned int j = 0; j < testOBj.bufferManager.m_floats4[i].name.size(); j++)
        {
            variablesText[textAux] = testOBj.bufferManager.m_floats4[i].name[j];
            textAux++;
        }
        variablesText[textAux] = '\n';
        textAux++;
    }

    // ----- Print all float 3
    for (unsigned int i = 0; i < testOBj.bufferManager.m_floats3.size(); i++)
    {
        variablesText[textAux + 0] = 'f'; variablesText[textAux + 1] = 'l'; variablesText[textAux + 2] = 'o'; variablesText[textAux + 3] = 'a';
        variablesText[textAux + 4] = 't'; variablesText[textAux + 5] = '3'; variablesText[textAux + 6] = ' ';
        textAux += 7;
        for (unsigned int j = 0; j < testOBj.bufferManager.m_floats3[i].name.size(); j++)
        {
            variablesText[textAux] = testOBj.bufferManager.m_floats3[i].name[j];
            textAux++;
        }
        variablesText[textAux] = '\n';
        textAux++;
    }

    // ----- Print all float 2
    for (unsigned int i = 0; i < testOBj.bufferManager.m_floats2.size(); i++)
    {
        variablesText[textAux + 0] = 'f'; variablesText[textAux + 1] = 'l'; variablesText[textAux + 2] = 'o'; variablesText[textAux + 3] = 'a';
        variablesText[textAux + 4] = 't'; variablesText[textAux + 5] = '2'; variablesText[textAux + 6] = ' ';
        textAux += 7;
        for (unsigned int j = 0; j < testOBj.bufferManager.m_floats2[i].name.size(); j++)
        {
            variablesText[textAux] = testOBj.bufferManager.m_floats2[i].name[j];
            textAux++;
        }
        variablesText[textAux] = '\n';
        textAux++;
    }

    // ----- Print all float 
    for (unsigned int i = 0; i < testOBj.bufferManager.m_floats.size(); i++)
    {
        variablesText[textAux + 0] = 'f'; variablesText[textAux + 1] = 'l'; variablesText[textAux + 2] = 'o'; variablesText[textAux + 3] = 'a';
        variablesText[textAux + 4] = 't'; variablesText[textAux + 5] = ' '; variablesText[textAux + 6] = ' ';
        textAux += 7;
        for (unsigned int j = 0; j < testOBj.bufferManager.m_floats[i].name.size(); j++)
        {
            variablesText[textAux] = testOBj.bufferManager.m_floats[i].name[j];
            textAux++;
        }
        variablesText[textAux] = '\n';
        textAux++;
    }

    // ----- Print all Matrix4
    for (unsigned int i = 0; i < testOBj.bufferManager.m_matrix.size(); i++)
    {
        variablesText[textAux + 0] = 'm'; variablesText[textAux + 1] = 'a'; variablesText[textAux + 2] = 't'; variablesText[textAux + 3] = 'i';
        variablesText[textAux + 4] = 'x'; variablesText[textAux + 5] = '4'; variablesText[textAux + 6] = ' ';
        textAux += 7;
        for (unsigned int j = 0; j < testOBj.bufferManager.m_matrix[i].name.size(); j++)
        {
            variablesText[textAux] = testOBj.bufferManager.m_matrix[i].name[j];
            textAux++;
        }
        variablesText[textAux] = '\n';
        textAux++;
    }

    // ----- Print all Render Target View
    for (unsigned int i = 0; i < testOBj.bufferManager.m_renderTargetsView.size(); i++)
    {
        variablesText[textAux + 0] = 'r'; variablesText[textAux + 1] = 'e'; variablesText[textAux + 2] = 'n'; variablesText[textAux + 3] = 'd';
        variablesText[textAux + 4] = 'e'; variablesText[textAux + 5] = 'r'; variablesText[textAux + 6] = ' ';
        textAux += 7;
        for (unsigned int j = 0; j < testOBj.bufferManager.m_renderTargetsView[i].name.size(); j++)
        {
            variablesText[textAux] = testOBj.bufferManager.m_renderTargetsView[i].name[j];
            textAux++;
        }
        variablesText[textAux] = '\n';
        textAux++;
    }
}

void EditorManager::CreateDefaultShaders()
{
    auto& testOBj = GraphicsModule::GetTestObj();

    // ----- Create default Shaders
    if (ImGui::Button("Create Default Effect", ImVec2(175, 25)))
    {
        HRESULT hr = S_OK;
        BUFFER_DESC_DX11 bd;
        testOBj.aLoadModel.loadModel("ZResorces/meshes/Sphere/sphere.obj");

        testOBj.mesh.setVetices(testOBj.aLoadModel.getVertexData(), testOBj.aLoadModel.numVertex);

        // Vertex Buffer
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

        // Index Buffer
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

        //testOBj.m_effects.CreateTechine("Default");
        testOBj.m_effects.CreatePassFromString("DefaultVertexShader.fx", "DefaultPixelShader.fx");
    }
}

void EditorManager::CompileShader()
{
    // Compile Buttom
    if (ImGui::Button("Complie shader", ImVec2(175, 25)))
    {

    }
}

void EditorManager::AddEffect()
{

}

void EditorManager::AddPass()
{
}

void EditorManager::CreateFloat4Buffer()
{
}

void EditorManager::CreateFloat3Buffer()
{
}

void EditorManager::CreateFloat2Buffer()
{
}

void EditorManager::CreateFloatBuffer()
{
}

void EditorManager::CreateMatrix4Buffer()
{
}

void EditorManager::CreateRenderTargetBuffer()
{
}

std::string EditorManager::OpenFileGetName(HWND owner)
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
