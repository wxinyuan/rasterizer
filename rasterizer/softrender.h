#ifndef __SOFTRENDER_H__
#define __SOFTRENDER_H__

class SoftRender
{
public:
	SoftRender(int w, int h);

	~SoftRender();

	void reset(int w, int h);

	void clear(DWORD color);

	//
	void drawLine(int x1, int y1, int x2, int y2, DWORD color);
	
	//
	void drawLine(const Vec3& v0, const Vec3& v1);

	DWORD* getBackBuffer() const { return m_pBackBuffer; }

private:
	inline void setPixel(int x, int y, DWORD color) { m_pBackBuffer[y * m_width + x] = color; }

private:
	DWORD*	m_pBackBuffer;
	int		m_width;
	int		m_hight;
};

#endif