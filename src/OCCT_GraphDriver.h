#pragma once

#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <AIS_InteractiveContext.hxx>

class OCCT_GraphDriver
{
private:
	OCCT_GraphDriver(void) {}
	~OCCT_GraphDriver(void) {}
public:
	//������ͼ��
	static Handle(V3d_Viewer) CreateViewer();

	//������������ʽ������
	static Handle(AIS_InteractiveContext) CreateAISContext(const Handle(V3d_Viewer) & hViewer);

	static Handle(AIS_InteractiveContext) CreateViewCubeAISContext(const Handle(V3d_Viewer) & hViewer);

	static Handle(AIS_InteractiveContext) CreateXYZAISContext(const Handle(V3d_Viewer) & hViewer);

	//�õ�ǰ��ͼ����ͼ�������Ӵ�
	static Handle(V3d_View) CreateView(const Handle(V3d_Viewer) & hViewer);
};