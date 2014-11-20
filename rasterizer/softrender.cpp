#include "stdafx.h"
#include "softrender.h"

SoftRender::SoftRender(int w, int h)
{
	reset(w, h);
}

SoftRender::~SoftRender()
{
	SAFE_DELETE(m_pBackBuffer);
}

void SoftRender::reset(int w, int h)
{
	SAFE_DELETE(m_pBackBuffer);
	m_pBackBuffer = new DWORD[w * h];
	m_width = w;
	m_hight = h;
}

void SoftRender::clear(DWORD color)
{
	for (int i = 0; i < m_width * m_hight; ++i)
	{
		m_pBackBuffer[i] = color;
	}
}

void SoftRender::drawLine(int x1, int y1, int x2, int y2, DWORD color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int ux = ((dx > 0) << 1) - 1;//x的增量方向，取或-1
	int uy = ((dy > 0) << 1) - 1;//y的增量方向，取或-1
	int x = x1, y = y1, eps;//eps为累加误差

	eps = 0;dx = abs(dx); dy = abs(dy); 
	if (dx > dy) 
	{
		for (x = x1; x != x2; x += ux)
		{
			setPixel(x, y, color);
			eps += dy;
			if ((eps << 1) >= dx)
			{
				y += uy; eps -= dx;
			}
		}
	}
	else
	{
		for (y = y1; y != y2; y += uy)
		{
			setPixel(x, y, color);
			eps += dx;
			if ((eps << 1) >= dy)
			{
				x += ux; eps -= dy;
			}
		}
	}             
}

void SoftRender::drawLine(const Vec3& v0, const Vec3& v1)
{
	
}