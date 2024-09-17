#include "../include/Settings.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <memory>


namespace LAB 
{
    //--------------------------

	Settings::Settings() :
        m_hmap {},
        m_shared_data_shptr {},
        //m_hwnd{ nullptr },
        m_is_init { init() }
	{
	}

    //--------------------------

    [[nodiscard]]
    bool
    Settings::isInit() const noexcept
    {
        return m_is_init;
    }

    //--------------------------

    [[nodiscard]]
    bool
	Settings::init()
	{
        wchar_t buf[40]{};
        if (GetEnvironmentVariableW(L"hmap", buf, std::size(buf)) == false) [[unlikely]]
        {
            return false;
        }

        std::wstringstream ss{ buf };

        size_t handle{};

        if (!(ss >> handle))
            return false;

        m_hmap = reinterpret_cast<HANDLE>(handle);

        m_shared_data_shptr = std::shared_ptr<SharedData> {
            static_cast<SharedData*>(MapViewOfFile(m_hmap, FILE_MAP_WRITE, 0, 0, sizeof(SharedData))),
            &UnmapViewOfFile
        };

        return m_shared_data_shptr != nullptr;
	}

    //--------------------------
    
    [[nodiscard]]
    std::shared_ptr<SharedData>
    Settings::getSharedData() const noexcept
    {
        return m_shared_data_shptr;
    }

    //--------------------------
    
    [[nodiscard]]
    std::optional<std::reference_wrapper<WindowInfo>>
    Settings::getWindowInfo() const noexcept
    {
        if (!m_shared_data_shptr) [[unlikely]]
            return std::nullopt;

        return m_shared_data_shptr.get()->win_info;
    }

    //--------------------------
    
    /*void Settings::setHWND(HWND hwnd)
    {
        m_hwnd = hwnd;
    }*/
    
    //--------------------------
}