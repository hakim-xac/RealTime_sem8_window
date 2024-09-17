#include "include/framework.h"
#include "include/window.h"
#include "include/window_handler.h"
#include "include/Structs.h"
#include "include/Settings.h"
#include "include/common.h"
#include "include/HdcScoped.h"

//--------------------------

LAB::Settings g_settings {};

//--------------------------

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    try
    {
        if (g_settings.isInit() == false) [[unlikely]]
        {
            std::wcerr << L"Can not init App!\n";
            return 1;
        }

        auto winfo_opt { g_settings.getWindowInfo() };

        if (winfo_opt.has_value() == false) [[unlikely]]
        {
            std::wcerr << L"winfo_opt.has_value() == false\n";
            return 2;
        }

        LAB::Window window { 
            hInstance,
            hPrevInstance,
            lpCmdLine,
            nCmdShow,
            LAB::WindowHandler::WndProc, // callback wnd_proc
            winfo_opt.value().get().pos_x, // start_pos_x
            winfo_opt.value().get().pos_y, // start_pos_y
            winfo_opt.value().get().width, // width
            winfo_opt.value().get().height, // height
        };

        window.loop();
    }
    catch (const std::exception& ex)
    {
        std::wcerr << L"Exception: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}