/* This file is part of the KDE project
  Copyright (c) 1999 Matthias Elter (me@kde.org)
  Copyright (c) 2001-2002 Igor Jansen (rm@kde.org)

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/
#ifndef KIS_HSV_WIDGET_H
#define KIS_HSV_WIDGET_H

#include "qwidget.h"
#include <koColor.h>

#include "kis_canvas_subject.h"
#include "kis_canvas_observer.h"

class KoFrameButton;
class QGridLayout;
class KoColor;
class KoColorSlider;
class QLabel;
class QSpinBox;
class KDualColorButton;
class KisColorWheel;
class KValueSelector;

class KisHSVWidget
	 : public QWidget,
	   public KisCanvasObserver
{
	Q_OBJECT
	typedef QWidget super;

public:
	KisHSVWidget(QWidget *parent = 0L, const char *name = 0);
	virtual ~KisHSVWidget() {}

protected slots:
	virtual void slotHChanged(int h);
	virtual void slotSChanged(int s);
	virtual void slotVChanged(int v);
	virtual void slotWheelChanged(const KoColor& c);

	void slotFGColorSelected(const QColor& c);
	void slotBGColorSelected(const QColor& c);

private:
	void update(KisCanvasSubject*);

private:
	KisCanvasSubject *m_subject;
	KisColorWheel *m_colorwheel;
	KValueSelector *m_VSelector;
	QLabel *mHLabel;
	QLabel *mSLabel;
	QLabel *mVLabel;
	QSpinBox *mHIn;
	QSpinBox *mSIn;
	QSpinBox *mVIn;
	KDualColorButton *m_ColorButton;

	KoColor m_fgColor;
	KoColor m_bgColor;
};

#endif
