#ifndef __SOFTRENDER_H__
#define __SOFTRENDER_H__

#include "frameBuffer.h"

class SoftRender
{
public:
	SoftRender();

	~SoftRender();

	void resize(int w, int h);

	//void reset(int w, int h);

	void clear(DWORD color);

	//
	void drawLine(int x1, int y1, int x2, int y2, DWORD color);
	
	//
	void drawLine(const Vec3& v0, const Vec3& v1);

	//DWORD* getBackBuffer() const { return m_pBackBuffer; }

	const FrameBuffer& getBackBuffer() { return m_backBuffer; }

private:
	inline void setPixel(int x, int y, DWORD color) { m_backBuffer.m_dwColorBuffer[y * m_backBuffer.m_iWidth + x] = color; }

private:
	FrameBuffer		m_backBuffer;

	//DWORD*			m_pBackBuffer;
	//int				m_width;
	//int				m_hight;
};

#endif