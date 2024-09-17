#include "../include/window_handler.h"
#include "../include/resource.h"
#include "../include/HdcScoped.h"
#include "../include/Structs.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <memory>

namespace LAB
{
	//--------------------------
	
    std::atomic_bool WindowHandler::m_is_running = true;

    //--------------------------
	
    WindowHandler::WindowHandler(HWND hwnd) :
        m_hwnd{ hwnd },
        m_hdc { GetDC(m_hwnd) }
    {

        m_threads.emplace_back([this]() 
        {
             moveCircle1();
        });

        m_threads.emplace_back([this]() 
        {
             moveCircle2();
        });

        m_threads.emplace_back([this]() 
        {
             moveSquare1();
        });

        m_threads.emplace_back([this]() 
        {
             moveSquare2();
        });
    }

	//--------------------------
	
    WindowHandler::~WindowHandler()
    {
        ReleaseDC(m_hwnd, m_hdc);
    }
    
    //--------------------------
	
    LRESULT CALLBACK
        WindowHandler::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CREATE:
            SetTimer(hWnd, 1, 20, nullptr);
            break;
        case WM_TIMER:
            InvalidateRect(hWnd, nullptr, true);
            break;
        case WM_COMMAND:
        {
            int wmId{ LOWORD(wParam) };
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_PAINT:
        {
            if (g_settings.isInit() == false) [[unlikely]]
                break;

            LAB::HdcScoped hdc_scoped{ hWnd };
            HDC hdc{ hdc_scoped.getHDC() };

            std::shared_ptr<SharedData> shared_data_shptr{ g_settings.getSharedData() };

            drawCircle(shared_data_shptr.get()->circle1, hdc);
            drawCircle(shared_data_shptr.get()->circle2, hdc);

            drawSquare(shared_data_shptr.get()->square1, hdc);
            drawSquare(shared_data_shptr.get()->square2, hdc);

        }
        break;
        case WM_DESTROY:
            m_is_running = false;
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }

	//--------------------------
     
    void WindowHandler::moveCircle1() const
    {
        if (g_settings.isInit() == false) [[unlikely]]
            return;

        std::shared_ptr<SharedData> shared_data_shptr{ g_settings.getSharedData() };
        Circle& circle_data{ shared_data_shptr.get()->circle1 };

        while (m_is_running)
        {
            circle_data.pos_x++;

            if (circle_data.pos_x + circle_data.radius >= 320)
            {
                shared_data_shptr.get()->square1.color = Color { .r = 0, .g = 0, .b = 150 };
                shared_data_shptr.get()->square2.color = Color { .r = 0, .g = 0, .b = 150 };
            }
            std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        }
    }

	//--------------------------
     
    void WindowHandler::moveCircle2() const
    {
        if(g_settings.isInit() == false) [[unlikely]]
            return;

        std::shared_ptr<SharedData> shared_data_shptr{ g_settings.getSharedData() };
        Circle& circle_data{ shared_data_shptr.get()->circle2 };

        while (m_is_running)
        {
            circle_data.pos_x--;
            std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        }

    }

	//--------------------------
     
    void WindowHandler::moveSquare1() const
    {
        if (g_settings.isInit() == false) [[unlikely]]
            return;

        std::shared_ptr<SharedData> shared_data_shptr{ g_settings.getSharedData() };
        Square& squarte_data{ shared_data_shptr.get()->square1 };

        while (m_is_running)
        {
            squarte_data.pos_x += 2;
            std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        }
    }

	//--------------------------
     
    void WindowHandler::moveSquare2() const
    {
        if (g_settings.isInit() == false) [[unlikely]]
            return;

        std::shared_ptr<SharedData> shared_data_shptr{ g_settings.getSharedData() };
        Square& squarte_data{ shared_data_shptr.get()->square2 };

        while (m_is_running)
        {
            squarte_data.pos_x -= 4;
            std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        }
    }

	//--------------------------
     
    void WindowHandler::drawCircle(const Circle& circle, HDC hdc)
    {
        HBRUSH hBrush{ CreateSolidBrush(RGB(circle.color.r, circle.color.g, circle.color.b)) };
        SelectObject(hdc, hBrush);

        Ellipse(
            hdc,
            circle.pos_x - circle.radius,
            circle.pos_y - circle.radius,
            circle.pos_x + circle.radius,
            circle.pos_y + circle.radius
        );
    }

	//--------------------------
     
    void WindowHandler::drawSquare(const Square& square, HDC hdc)
    {
        if (g_settings.isInit() == false) [[unlikely]]
            return;

        RECT r{
            .left = square.pos_x,
            .top = square.pos_y,
            .right = square.pos_x + square.length,
            .bottom = square.pos_y + square.length
        };

        HBRUSH hBrush{ CreateSolidBrush(RGB(square.color.r, square.color.g, square.color.b)) };

        FillRect(hdc, &r, hBrush);
    }

	//--------------------------
}