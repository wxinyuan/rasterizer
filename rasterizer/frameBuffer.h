#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void resize(int w, int h);

public:
	int		m_iWidth;
	int		m_iHight;
	DWORD*	m_dwColorBuffer;	//ARGB
};
#endif