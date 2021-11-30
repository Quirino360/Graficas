#pragma once
#include <windows.h>
#include <string>

class EditorManager
{
public:
	EditorManager() = default;
	~EditorManager() = default;



private:
	const unsigned int iTextSize = 9999;
	char* iText = new char[iTextSize];

	const unsigned int bufferNameSize = 9999;
	char* bufferName = new char[bufferNameSize];

	const unsigned int variablesTextSize = 9999;
	char* variablesText = new char[variablesTextSize];

	HWND g_hwnd;
public:
	// ---------- Game Loop
	void Init(); 
	void Update(); // Updates buffers
	void RenderBuffers();  // Render buffers 
	void RenderUI(); // Render UI

private:
	// ---------- Game Loop
	// ----- 
	void RernderShaderEditorUI();
	void CreateDefaultShaders(); 
	void CompileShader();
	// -----
	void AddVariablesUI();
	void ChangeVariables();

	// ----- Render Editor UI

	// ----- Add and Remove
	void AddEffect();
	void AddPass();

	void CreateFloat4Buffer();
	void CreateFloat3Buffer();
	void CreateFloat2Buffer();
	void CreateFloatBuffer();

	void CreateMatrix4Buffer();

	void CreateRenderTargetBuffer();

	// Utilities
	std::string OpenFileGetName(HWND owner = NULL);
};

