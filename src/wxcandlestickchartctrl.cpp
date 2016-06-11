/*
	Copyright (c) 2016 Xavier Leclercq

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.
*/

/// @file

#include "wxcandlestickchartctrl.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

wxCandlestickChartData::wxCandlestickChartData(const wxVector<wxString> &labels)
    : m_labels(labels)
{
}

const wxVector<wxString>& wxCandlestickChartData::GetLabels() const
{
    return m_labels;
}

wxCandlestickChartCtrl::wxCandlestickChartCtrl(wxWindow *parent,
                                               wxWindowID id,
                                               const wxCandlestickChartData &data,
                                               const wxPoint &pos,
                                               const wxSize &size,
                                               long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_grid(
        wxPoint2DDouble(m_options.GetPadding().GetLeft(), m_options.GetPadding().GetTop()),
        size, data.GetLabels(), 12, 100, m_options.GetGridOptions()
        )
{
}

const wxCandlestickChartOptions& wxCandlestickChartCtrl::GetOptions() const
{
    return m_options;
}

void wxCandlestickChartCtrl::Resize(const wxSize &size)
{
    wxSize newSize(
        size.GetWidth() - m_options.GetPadding().GetTotalHorizontalPadding(),
        size.GetHeight() - m_options.GetPadding().GetTotalVerticalPadding()
        );
    m_grid.Resize(newSize);
}

wxSharedPtr<wxVector<const wxChartElement*> > wxCandlestickChartCtrl::GetActiveElements(const wxPoint &point)
{
    wxSharedPtr<wxVector<const wxChartElement*> > activeElements(new wxVector<const wxChartElement*>());
    return activeElements;
}

void wxCandlestickChartCtrl::OnPaint(wxPaintEvent &evt)
{
    wxAutoBufferedPaintDC dc(this);

    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        m_grid.Draw(*gc);

        DrawTooltips(*gc);

        delete gc;
    }
}

BEGIN_EVENT_TABLE(wxCandlestickChartCtrl, wxChartCtrl)
	EVT_PAINT(wxCandlestickChartCtrl::OnPaint)
END_EVENT_TABLE()