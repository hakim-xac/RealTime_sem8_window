#pragma once

#include "common.h"
#include "Settings.h"

//--------------------------
extern LAB::Settings g_settings;
//--------------------------
namespace LAB
{

	class WindowHandler final
	{
	public:


		//--------------------------
		
		explicit WindowHandler(HWND hwnd);
		
		//--------------------------
		
		~WindowHandler();

		//--------------------------
		
		void moveCircle1() const;

		//--------------------------
		
		void moveCircle2() const;

		//--------------------------
		
		void moveSquare1() const;

		//--------------------------
		
		void moveSquare2() const;

		//--------------------------
		
		static void drawCircle(const Circle& circle, HDC hdc);

		//--------------------------

		static void drawSquare(const Square& square, HDC hdc);

		//--------------------------
		
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		//--------------------------

	private:

		HWND m_hwnd;
		HDC m_hdc;
		mutable std::mutex m_draw_mx;
		std::vector<std::jthread> m_threads;

		static std::atomic_bool m_is_running;
	};
}
