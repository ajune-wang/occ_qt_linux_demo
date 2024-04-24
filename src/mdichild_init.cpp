#include "mdichild.h"
#include "ComplainUtf8.h"
#include "OcctView.h"
#include <QtWidgets>

void MdiChild::Init()
{

	//OCCVIEW
	{
		QWidget * p3DWidget = new QWidget(this);
		QHBoxLayout * pLayout = new QHBoxLayout();
		pLayout->setMargin(0);
		p3DWidget->setLayout(pLayout);
		q3dView = new OcctView(h_MyViewer->getAisContext(), this);
		connect(q3dView, &OcctView::selectionChanged, this, &MdiChild::selectionChanged);
		pLayout->addWidget(q3dView);

		QToolBar * pToolbar = new QToolBar(p3DWidget);
		pToolbar->setOrientation(Qt::Vertical);
		pToolbar->setIconSize(QSize(20, 20));
		pToolbar->addActions(*q3dView->getViewActions());
		pToolbar->addActions(*q3dView->getRaytraceActions());
		pLayout->addWidget(pToolbar);
		this->setCentralWidget(p3DWidget);
	}
}
