#include "game.h"

Game* game = nullptr;

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
	const char* title = "First Game";

	// Register Class
	RegisterClass(&window_class);

	// Create window
	// lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent,hMenu, hInstance, lpParam
	HWND window = CreateWindow(window_class.lpszClassName, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 720, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);
	//**************************Window Management**************************


	// Game loop

	Game* game = new Game(&window, &hdc);

	std::ifstream readFile;
	std::string settings = "settings.txt";

	// Framerate lock
	short frames;

	readFile.open(settings);
	if (!readFile.is_open()) {
		frames = 60;
	}
	else {
		readFile >> frames;
	}

	readFile.close();

	const int fps = frames;
	const int frameDelay = 1000000 / fps;

	game->init();
	while (running) {
		auto frameBegin = std::chrono::high_resolution_clock::now();

		game->input();
		game->update();
		game->draw();

		auto frameEnd = std::chrono::high_resolution_clock::now(); 
		auto frameTime = std::chrono::duration_cast<std::chrono::microseconds>(frameBegin - frameEnd);

		if (frameDelay > frameTime.count()) {
			std::this_thread::sleep_for(std::chrono::microseconds(frameDelay - frameTime.count()));
		}
	}
}