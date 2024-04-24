#include "OCCT_ShapeImport.h"
#include "ComplainUtf8.h"
#include <Transfer_TransientProcess.hxx>
#include <XSControl_WorkSession.hxx>
#include <STEPControl_Reader.hxx>
#include <IGESControl_Reader.hxx>
#include <StlAPI_Reader.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <TopExp_Explorer.hxx>

OCCT_ShapeImport::OCCT_ShapeImport(OCCT_ShapeImportUI * pUI)
	:p_UI(pUI)
{
}

OCCT_ShapeImport::~OCCT_ShapeImport()
{
}

OCCT_ShapeList OCCT_ShapeImport::ImportModel()
{
	OCCT_ShapeList Shapes;
	OCCT_Utf8StringList Paths = p_UI->getLoadPathList();
	p_UI->BeginWaitCursor();
    for(OCCT_Utf8String Path : Paths)
	{
		OCCT_ShapeList OneShapeList = ImportModel(Path);
		if (OneShapeList.Size())
		{
			Shapes.Append(OneShapeList);
			p_UI->showPathSuccess(Path);
		}
		else
			p_UI->showPathError(Path);
	}
	p_UI->EndWaitCursor();
	return Shapes;
}

OCCT_ShapeList OCCT_ShapeImport::ImportModel(const OCCT_Utf8String & Path)
{
	OCCT_Utf8String Ext = p_UI->getExtUpper(Path);
	TopoDS_Shape aShape;
	if (Ext == "STEP" || Ext == "STP")
	{
		STEPControl_Reader aReader;
		IFSelect_ReturnStatus status = aReader.ReadFile(Path.ToCString());
		if (status == IFSelect_RetDone)
		{
			aReader.WS()->MapReader()->SetTraceLevel(2);
			Standard_Boolean OK = 1;
			Standard_Integer nbr = aReader.NbRootsForTransfer();
			for (Standard_Integer n = 1; n <= nbr; n++)
			{
				if (!aReader.TransferRoot(n))
				{
					OK = 0;
					break;  //���ټ�����ȡ��
				}
			}
			if (OK)
				aShape = aReader.OneShape();
			else
				p_UI->showError("STEP����ת��ʧ��");
		}
		else
			p_UI->showError("STEP��ȡʧ��");
	}
	else if (Ext == "BREP")
	{
		TopoDS_Shape aTempShape;
		BRep_Builder aBuilder;
		Standard_Boolean Res = BRepTools::Read(aTempShape, Path.ToCString(), aBuilder); //��ȡ
		if (Res)
		{
			BRepTools::Update(aTempShape);
			aShape = aTempShape;
		}
		else
			p_UI->showError("BREP��ȡʧ��");
	}
	else if (Ext == "IGES"|| Ext == "IGS")
	{
		IGESControl_Reader aReader;
		Standard_Integer status = aReader.ReadFile(Path.ToCString());
		if (status == IFSelect_RetDone)
		{
			aReader.TransferRoots();
			aShape = aReader.OneShape();
		}
		else
			p_UI->showError("IGES��ȡʧ��");
	}
	else if (Ext == "STL")
	{
		//STL ��һ��
		StlAPI_Reader aReader;
		TopoDS_Shape aTempShape;
		Standard_Boolean Res = aReader.Read(aShape, Path.ToCString());
		if (Res)
		{
			aShape = aTempShape;
		}
		else
			p_UI->showError("STL��ȡʧ��");
	}
	else
		p_UI->showError("����ʶ��ʧ��");
	if (aShape.IsNull())
		return OCCT_ShapeList();
	OCCT_ShapeList Shapes;
	if (false)//�ֽ�ɵ���
	{
		for (TopExp_Explorer Exp(aShape, TopAbs_SOLID); Exp.More(); Exp.Next())//����
			Shapes.Append(Exp.Current());
	}
	else//������
		Shapes.Append(aShape);
	return Shapes;
}
