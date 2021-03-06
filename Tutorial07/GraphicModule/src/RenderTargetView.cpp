#include "RenderTargetView.h"

RenderTargetView::RenderTargetView()
{
}

RenderTargetView::~RenderTargetView()
{
}

#if defined(DX11)
void RenderTargetView::ReleaseDX11()
{
}
#endif