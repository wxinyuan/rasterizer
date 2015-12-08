#include "stdafx.h"
#include "frameBuffer.h"

FrameBuffer::FrameBuffer()
: m_iWidth(0)
, m_iHight(0)
, m_dwColorBuffer(NULL)
{

}

FrameBuffer::~FrameBuffer()
{
	SAFE_DELETE_ARRAY(m_dwColorBuffer);
}

void FrameBuffer::resize(int w, int h)
{
	if (w == 0 || h == 0)
	{
		return;
	}

	SAFE_DELETE_ARRAY(m_dwColorBuffer);

	m_iWidth = w;
	m_iHight = h;
	m_dwColorBuffer = new DWORD[w * h];
}