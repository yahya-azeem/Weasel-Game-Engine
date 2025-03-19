#pragma once
#include "Window.h"
#include "WeaselTimer.h"
#include "ImguiManager.h"
#include "Camera.h"

class App
{
public:
	App();
	//master frame / message loop
	int Go();
	~App();
	//window screen ratio 
	int w = 1920;
	int h = 1080;



	// I DONT KNOW
	//bool fullscreen = true;


private:
	void DoFrame();
private:
	ImguiManager imgui;
	Window wnd;
	WeaselTimer timer;
	std::vector<std::unique_ptr<class Box>> boxes;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	float speed_factor = 1.0f;
	Camera cam;
	static constexpr size_t nDrawables = 180;
};

