#include "game.h"

LRESULT CALLBACK windowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
			break;
		}

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);

			renderer.width = rect.right - rect.left;
			renderer.height = rect.bottom - rect.top;

			int renderer_size = renderer.width * renderer.height * sizeof(uint32);

			if (renderer.memory) {
				VirtualFree(renderer.memory, 0, MEM_RELEASE);
			}
			renderer.memory = VirtualAlloc(0, renderer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			renderer.bitmap_info.bmiHeader.biSize = sizeof(renderer.bitmap_info.bmiHeader);
			renderer.bitmap_info.bmiHeader.biWidth = renderer.width;
			renderer.bitmap_info.bmiHeader.biHeight = renderer.height;
			renderer.bitmap_info.bmiHeader.biPlanes = 1;
			renderer.bitmap_info.bmiHeader.biBitCount = 32;
			renderer.bitmap_info.bmiHeader.biCompression = BI_RGB;
			/* reference
			typedef struct tagBITMAPINFOHEADER {
				DWORD biSize;
				LONG  biWidth;
				LONG  biHeight;
				WORD  biPlanes;
				WORD  biBitCount;
				DWORD biCompression;
				DWORD biSizeImage;
				LONG  biXPelsPerMeter;
				LONG  biYPelsPerMeter;
				DWORD biClrUsed;
				DWORD biClrImportant;
			} BITMAPINFOHEADER, * LPBITMAPINFOHEADER, * PBITMAPINFOHEADER;
			*/
		}

		default: {
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	//**************************Window Management**************************
	// Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = windowCallback;
	const char* title = "Simple C++ Snake";

	// Register Class
	RegisterClass(&window_class);

	// Create window
	// lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent,hMenu, hInstance, lpParam
	HWND window = CreateWindow(window_class.lpszClassName, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 1080, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);
	//**************************Window Management**************************


	//***************DATA COLLECTION***************
	std::ofstream writeFile;
	// Clear all data inside file, keep outside menu screen loop
	writeFile.open("food_positions.txt", std::ofstream::out | std::ofstream::trunc);
	writeFile.close();
	//***************DATA COLLECTION***************

	// Game loop
	int choiceMade;

	// populate tilemap
	for (int i = 0; i < tilemapSizeX; i++) {
		for (int j = 0; j < tilemapSizeY; j++) {
			tilemap[i][j] = calculateTileColor(i, j);
		}
	}

	do {
		updateVars(); // Renderering vars
		// render background to screen once
		clearScreen(0x000000);
		renderBackground();
		renderTilemap(tilemap);
		StretchDIBits(hdc, 0, 0, renderer.width, renderer.height, 0, 0, renderer.width, renderer.height,
					  renderer.memory, &renderer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		choiceMade = -1;

		uint32 vk_code;

		MSG message;
		if (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			switch (message.message) {
				case WM_KEYDOWN: {
					vk_code = static_cast<uint32>(message.wParam);
					switch (vk_code) {
						case VK_ESCAPE:
							choiceMade = 0;
							break;
						case VK_SPACE:
							choiceMade = 1;
							break;
					}
				} break;
			}

			TranslateMessage(&message);
			DispatchMessageA(&message);
		}

		// Create Game
		if (choiceMade == 1) {
			//***************DATA COLLECTION***************
			std::ofstream writeFile;
			writeFile.open("food_positions.txt", std::ofstream::app);
			writeFile << "\n";
			writeFile.close();
			//***************DATA COLLECTION***************

			ObjectManager objectManager;
			auto& food = (objectManager.addObject<FoodObject>(APPLERED, 1));
			auto& player = (objectManager.addObject<PlayerObject>(BEAUTIFULBLUE));
			auto& score = (objectManager.addObject<ScoreObject>());

			Game* game = new Game(&window, &hdc, &objectManager, &food, &player, &score);

			// Framerate lock
			int frames = getFPS();

			const int FPS = frames;
			const int FRAME_DELAY = 1000000 / FPS;


			game->init();
			while (running) {
				auto frameBegin = std::chrono::high_resolution_clock::now();

				game->draw();
				game->input();
				game->update();

				auto frameEnd = std::chrono::high_resolution_clock::now();
				const auto FRAME_TIME = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd - frameBegin);

				if (FRAME_DELAY > FRAME_TIME.count()) {
					std::this_thread::sleep_for(std::chrono::microseconds(FRAME_DELAY - FRAME_TIME.count()));
				}
				runNumber++;
			}
		}
	} while (choiceMade != 0);
}