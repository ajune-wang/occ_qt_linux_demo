#include "OCCT_ShapeExport.h"
#include "ComplainUtf8.h"
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <TopExp_Explorer.hxx>

#include <Interface_Static.hxx>
#include <XSControl_WorkSession.hxx>
#include <Transfer_TransientProcess.hxx>
#include <Transfer_ProcessForTransient.hxx>

#include <STEPControl_Writer.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <StlAPI_Writer.hxx>


OCCT_ShapeExport::OCCT_ShapeExport(OCCT_ShapeExportUI * pUI)
	:p_UI(pUI)
{
}


OCCT_ShapeExport::~OCCT_ShapeExport()
{
}

void OCCT_ShapeExport::ExportModel(OCCT_ShapeList theExportList)
{
	if (theExportList.IsEmpty())
		return;
	ModelFileType Type;
    const OCCT_Utf8String & FolderPath = p_UI->getSavePath(Type);
	p_UI->BeginWaitCursor();
	if (FolderPath.Size())
	{
		OCCT_Utf8String aFileName = FolderPath;
		switch (Type)
		{
		case MFT_STEP:
		{
			STEPControl_StepModelType StepControlType = STEPControl_AsIs;
			//aFileName += ".step";
			STEPControl_Writer aWriter;
            for(TopoDS_Shape shape:theExportList)
			{
				IFSelect_ReturnStatus status = aWriter.Transfer(shape, STEPControl_AsIs);
				if (status != IFSelect_RetDone)
				{
					p_UI->showError("STEPת��ʧ��");
					return;
				}
			}
			aWriter.Write(aFileName.ToCString());
		}
		break;
		case MFT_IGES:
		{
			//aFileName += ".iges";
			IGESControl_Controller::Init();
			IGESControl_Writer aWriter(Interface_Static::CVal("XSTEP.iges.unit"),
				Interface_Static::IVal("XSTEP.iges.writebrep.mode"));
            for(TopoDS_Shape shape : theExportList)
			{
				aWriter.AddShape(shape);
				aWriter.ComputeModel();
			}
			//���ָ���ģʽ��ת�� ���õ���ʵ����һ������ �����Ǹ���ʵ���һ�������
			Standard_Integer result = aWriter.Write(aFileName.ToCString());
			if (!result)
				p_UI->showError("IGESת��ʧ��");
		}
		break;
		case MFT_STL:
		case MFT_BREP:
		{
			TopoDS_Compound ResultShape;
			BRep_Builder MKCP;
			MKCP.MakeCompound(ResultShape);
            for(TopoDS_Shape shape : theExportList)
				MKCP.Add(ResultShape, shape);
			if (ResultShape.IsNull()) {
				p_UI->showError("ת��ʧ��,����ͼ��Ϊ��");
				return;
			}
			else
			{
				if (Type == MFT_BREP)//".BREP"
				{
					//aFileName += ".brep";
					Standard_Boolean status = BRepTools::Write(ResultShape, aFileName.ToCString());
					if (!status) {
						p_UI->showError("BREPת��ʧ��");
						return;
					}
				}
				else if (Type == MFT_STL)//".STL"
				{
					//STLͬbrep ������״��Ӷ��
					//aFileName += ".stl";
					if (ResultShape.IsNull()) {
						p_UI->showError("STLת��ʧ��");
					}
					else
					{
						StlAPI_Writer myStlWriter;
						myStlWriter.Write(ResultShape, aFileName.ToCString());
					}
				}
			}

		}
		break;
		default:
			break;
		}
		p_UI->showSuccess("ת���ɹ�");
	}
	p_UI->EndWaitCursor();
}

void OCCT_ShapeExport::ExportMutiModel(OCCT_ShapeList theExportList)
{
	if (theExportList.IsEmpty())
		return;
	ModelFileType Type;
    const OCCT_Utf8String & FolderPath = p_UI->getSavePathFolder(Type);
	if (FolderPath.Size())
	{
		OCCT_Utf8String aFileName;
		STEPControl_StepModelType StepControlType = STEPControl_AsIs;
		bool Index = true;
        for(TopoDS_Shape shape : theExportList)
		{
			Standard_Character Buffer[30] = { 0 };
			if (!Index++)
			{
				Sprintf(Buffer, "[%d]", Index - 1);
			}
			aFileName += Buffer;
			if (Type == MFT_STEP)
			{
				aFileName += ".step";
				STEPControl_Writer aWriter;
				//Transfer ����ת�����ģ�� �൱�����
				IFSelect_ReturnStatus status = aWriter.Transfer(shape, StepControlType);//STEPControl_ManifoldSolidBrep
				if (status != IFSelect_RetDone)
					p_UI->showError("STEPת��ʧ��");
				aWriter.Write(aFileName.ToCString());
			}
			else if (Type == MFT_BREP)
			{
				aFileName += ".brep";
				//Brep ������ TopoDS_Compound RES;	BRep_Builder MKCP;MKCP.MakeCompound(RES);MKCP.Add(RES, aShape); ���д��RES
				Standard_Boolean status = BRepTools::Write(shape, aFileName.ToCString());
				if (!status)
					p_UI->showError("BREPת��ʧ��");
			}
			else if (Type == MFT_IGES)
			{
				aFileName += ".iges";
				IGESControl_Controller::Init();
				IGESControl_Writer aWriter(Interface_Static::CVal("XSTEP.iges.unit"),
					Interface_Static::IVal("XSTEP.iges.writebrep.mode"));
				//iges AddShape ������Ӷ��ģ��
				aWriter.AddShape(shape);
				aWriter.ComputeModel();
				Standard_Integer result = aWriter.Write(aFileName.ToCString());
				if (!result)
					p_UI->showError("IGESת��ʧ��");
			}
			else if (Type == MFT_STL)//".STL"
			{
				//STLͬbrep ������״��Ӷ��
				aFileName += ".stl";
				if (shape.IsNull())
					p_UI->showError("STLת��ʧ��");
				else
				{
					StlAPI_Writer myStlWriter;
					myStlWriter.Write(shape, aFileName.ToCString());
				}
			}
		}
		p_UI->showSuccess("ת���ɹ�");
	}
}
