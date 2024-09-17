#pragma once
#include "Structs.h"

namespace LAB
{
	class Settings
	{
	public:

		//--------------------------

		Settings();

		//--------------------------

		[[nodiscard]] bool isInit() const noexcept;

		//--------------------------

		[[nodiscard]] std::shared_ptr<SharedData> getSharedData() const noexcept;

		//--------------------------
		
		[[nodiscard]] std::optional<std::reference_wrapper<WindowInfo>> getWindowInfo() const noexcept;

		//--------------------------
		
		//void setHWND(HWND hwnd);

		//--------------------------

	private:

		//--------------------------

		[[nodiscard]] bool init();

		//--------------------------

	private:
		HANDLE m_hmap;
		std::shared_ptr<SharedData> m_shared_data_shptr;
		//HWND m_hwnd;
		//HDC m_hdc;
		//std::mutex m_draw_mx;
		bool m_is_init;
	};
}
