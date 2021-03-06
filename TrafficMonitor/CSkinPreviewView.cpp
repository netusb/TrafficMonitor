// CSkinPreviewView.cpp: 实现文件
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "CSkinPreviewView.h"


// CSkinPreviewView

IMPLEMENT_DYNCREATE(CSkinPreviewView, CScrollView)

CSkinPreviewView::CSkinPreviewView()
{

}

CSkinPreviewView::~CSkinPreviewView()
{
}


BEGIN_MESSAGE_MAP(CSkinPreviewView, CScrollView)
END_MESSAGE_MAP()


// CSkinPreviewView 绘图

void CSkinPreviewView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO:  计算此视图的合计大小
	m_size.cx = 0;
	m_size.cy = 0;
	SetScrollSizes(MM_TEXT, m_size);


}

void CSkinPreviewView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
	CDrawCommon draw;
	draw.Create(pDC, nullptr);
	if (!m_skin_data->font.name.IsEmpty() && m_skin_data->font.size > 0)
		draw.SetFont(&m_skin_font);
	else
		draw.SetFont(m_font);
	CRect draw_rect(CPoint(0, 0), m_size);
	draw.SetDrawRect(draw_rect);
	draw.FillRect(draw_rect, RGB(255, 255, 255));
	//绘制背景
	CRect rect_s(CPoint(m_skin_data->layout.preview_x_s, m_skin_data->layout.preview_y_s),
		CSize(m_skin_data->layout.width_s, m_skin_data->layout.height_s));
	CRect rect_l(CPoint(m_skin_data->layout.preview_x_l, m_skin_data->layout.preview_y_l),
		CSize(m_skin_data->layout.width_l, m_skin_data->layout.height_l));
	if (m_background_s->IsNull())
		draw.FillRect(rect_s, RGB(230, 230, 230));
	else
		draw.DrawBitmap(*m_background_s, rect_s.TopLeft(), rect_s.Size());
	if (m_background_l->IsNull())
		draw.FillRect(rect_l, RGB(230, 230, 230));
	draw.DrawBitmap(*m_background_l, rect_l.TopLeft(), rect_l.Size());

	//绘制文本
	CString up_str;
	CString down_str;
	CString cpu_str;
	CString memory_str;
	DispStrings disp_str;
	if (m_skin_data->disp_str.Get(TDI_UP) == NONE_STR)
		m_skin_data->disp_str.Get(TDI_UP) = theApp.m_main_wnd_data.disp_str.Get(TDI_UP);
	if (m_skin_data->disp_str.Get(TDI_DOWN) == NONE_STR)
		m_skin_data->disp_str.Get(TDI_DOWN) = theApp.m_main_wnd_data.disp_str.Get(TDI_DOWN);
	if (m_skin_data->disp_str.Get(TDI_CPU) == NONE_STR)
		m_skin_data->disp_str.Get(TDI_CPU) = theApp.m_main_wnd_data.disp_str.Get(TDI_CPU);
	if (m_skin_data->disp_str.Get(TDI_MEMORY) == NONE_STR)
		m_skin_data->disp_str.Get(TDI_MEMORY) = theApp.m_main_wnd_data.disp_str.Get(TDI_MEMORY);
	up_str.Format(_T("%s88.8 KB/s"), (m_skin_data->layout.no_text ? _T("") : m_skin_data->disp_str.Get(TDI_UP).c_str()));
	down_str.Format(_T("%s88.9 KB/s"), (m_skin_data->layout.no_text ? _T("") : m_skin_data->disp_str.Get(TDI_DOWN).c_str()));
	cpu_str.Format(_T("%s50%%"), (m_skin_data->layout.no_text ? _T("") : m_skin_data->disp_str.Get(TDI_CPU).c_str()));
	memory_str.Format(_T("%s51%%"), (m_skin_data->layout.no_text ? _T("") : m_skin_data->disp_str.Get(TDI_MEMORY).c_str()));

	int text_colors[MAIN_WND_COLOR_NUM];
	if (m_skin_data->specify_each_item_color)
	{
		for (int i{}; i < MAIN_WND_COLOR_NUM; i++)
			text_colors[i] = m_skin_data->text_colors[i];
	}
	else
	{
		for (int i{}; i < MAIN_WND_COLOR_NUM; i++)
			text_colors[i] = m_skin_data->text_colors[0];
	}
	CPoint point;
	//绘制小预览图文本
	//绘制“上传”文本
	if (m_skin_data->layout.show_up_s)
	{
		point.SetPoint(m_skin_data->layout.up_x_s, m_skin_data->layout.up_y_s);
		point.Offset(m_skin_data->layout.preview_x_s, m_skin_data->layout.preview_y_s);
		CRect rect(point, CSize(m_skin_data->layout.up_width_s, m_skin_data->layout.text_height));
		draw.DrawWindowText(rect, up_str, text_colors[0], m_skin_data->layout.up_align_s);
	}
	//绘制“下载”文本
	if (m_skin_data->layout.show_down_s)
	{
		point.SetPoint(m_skin_data->layout.down_x_s, m_skin_data->layout.down_y_s);
		point.Offset(m_skin_data->layout.preview_x_s, m_skin_data->layout.preview_y_s);
		CRect rect(point, CSize(m_skin_data->layout.down_width_s, m_skin_data->layout.text_height));
		draw.DrawWindowText(rect, down_str, text_colors[1], m_skin_data->layout.down_align_s);
	}
	//绘制“CPU”文本
	if (m_skin_data->layout.show_cpu_s)
	{
		point.SetPoint(m_skin_data->layout.cpu_x_s, m_skin_data->layout.cpu_y_s);
		point.Offset(m_skin_data->layout.preview_x_s, m_skin_data->layout.preview_y_s);
		CRect rect(point, CSize(m_skin_data->layout.cpu_width_s, m_skin_data->layout.text_height));
		draw.DrawWindowText(rect, cpu_str, text_colors[2], m_skin_data->layout.cpu_align_s);
	}
	//绘制“内存”文本
	if (m_skin_data->layout.show_memory_s)
	{
		point.SetPoint(m_skin_data->layout.memory_x_s, m_skin_data->layout.memory_y_s);
		point.Offset(m_skin_data->layout.preview_x_s, m_skin_data->layout.preview_y_s);
		CRect rect(point, CSize(m_skin_data->layout.memory_width_s, m_skin_data->layout.text_height));
		draw.DrawWindowText(rect, memory_str, text_colors[3], m_skin_data->layout.memory_align_s);
	}

	//绘制大预览图文本
	//绘制“上传”文本
	if (m_skin_data->layout.show_up_l)
	{
		point.SetPoint(m_skin_data->layout.up_x_l, m_skin_data->layout.up_y_l);
		point.Offset(m_skin_data->layout.preview_x_l, m_skin_data->layout.preview_y_l);
		CRect rect(point, CSize(m_skin_data->layout.up_width_l, m_skin_data->layout.text_height));
		draw.DrawWindowText(rect, up_str, text_colors[0], m_skin_data->layout.up_align_l);
	}
	//绘制“下载”文本
	if (m_skin_data->layout.show_down_l)
	{
		point.SetPoint(m_skin_data->layout.down_x_l, m_skin_data->layout.down_y_l);
		point.Offset(m_skin_data->layout.preview_x_l, m_skin_data->layout.preview_y_l);
		CRect rect(point, CSize(m_skin_data->layout.down_width_l, m_skin_data->layout.text_height));
		draw.DrawWindowText(rect, down_str, text_colors[1], m_skin_data->layout.down_align_l);
	}
	//绘制“CPU”文本
	if (m_skin_data->layout.show_cpu_l)
	{
		point.SetPoint(m_skin_data->layout.cpu_x_l, m_skin_data->layout.cpu_y_l);
		point.Offset(m_skin_data->layout.preview_x_l, m_skin_data->layout.preview_y_l);
		CRect rect(point, CSize(m_skin_data->layout.cpu_width_l, m_skin_data->layout.text_height));
		draw.DrawWindowText(rect, cpu_str, text_colors[2], m_skin_data->layout.cpu_align_l);
	}
	//绘制“上传”文本
	if (m_skin_data->layout.show_memory_l)
	{
		point.SetPoint(m_skin_data->layout.memory_x_l, m_skin_data->layout.memory_y_l);
		point.Offset(m_skin_data->layout.preview_x_l, m_skin_data->layout.preview_y_l);
		CRect rect(point, CSize(m_skin_data->layout.memory_width_l, m_skin_data->layout.text_height));
		draw.DrawWindowText(rect, memory_str, text_colors[3], m_skin_data->layout.memory_align_l);
	}
}


// CSkinPreviewView 诊断

//#ifdef _DEBUG
//void CSkinPreviewView::AssertValid() const
//{
//	CScrollView::AssertValid();
//}

//#ifndef _WIN32_WCE
//void CSkinPreviewView::Dump(CDumpContext& dc) const
//{
//	CScrollView::Dump(dc);
//}
//#endif
//#endif //_DEBUG

void CSkinPreviewView::InitialUpdate()
{
	OnInitialUpdate();
}
void CSkinPreviewView::SetSize(int width, int hight)
{
	m_size = CSize(width, hight);
	SetScrollSizes(MM_TEXT, m_size);
}
void CSkinPreviewView::SetBackImage(CImage * background_s, CImage * background_l)
{
	m_background_s = background_s;
	m_background_l = background_l;
}

void CSkinPreviewView::IniFont()
{
	if (!m_skin_data->font.name.IsEmpty() && m_skin_data->font.size > 0)
	{
		if (m_skin_font.m_hObject)
			m_skin_font.DeleteObject();
		//m_skin_font.CreatePointFont(m_skin_data->font_size * 10, m_skin_data->font_name.c_str());
		m_skin_font.CreateFont(
			FONTSIZE_TO_LFHEIGHT(m_skin_data->font.size), // nHeight
			0, // nWidth
			0, // nEscapement
			0, // nOrientation
			(m_skin_data->font.bold ? FW_BOLD : FW_NORMAL), // nWeight
			m_skin_data->font.italic, // bItalic
			m_skin_data->font.underline, // bUnderline
			m_skin_data->font.strike_out, // cStrikeOut
			DEFAULT_CHARSET, // nCharSet
			OUT_DEFAULT_PRECIS, // nOutPrecision
			CLIP_DEFAULT_PRECIS, // nClipPrecision
			DEFAULT_QUALITY, // nQuality
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
			m_skin_data->font.name);
	}
}

// CSkinPreviewView 消息处理程序
