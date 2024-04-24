#设置

OCCPath=            /home/ajune/OCC/occ_src/OCCT-7_8_0/install
OCCIncludePath =    $$OCCPath/include/opencascade
OCCLibPath =        $$OCCPath/lib

message($$OCCIncludePath)

INCLUDEPATH += $$OCCIncludePath

LIBS += -L$$OCCLibPath -lTKBO
LIBS += -L$$OCCLibPath -lTKBRep
LIBS += -L$$OCCLibPath -lTKBin
LIBS += -L$$OCCLibPath -lTKBinL
LIBS += -L$$OCCLibPath -lTKBinTObj
LIBS += -L$$OCCLibPath -lTKBinXCAF
LIBS += -L$$OCCLibPath -lTKBool
LIBS += -L$$OCCLibPath -lTKCAF
LIBS += -L$$OCCLibPath -lTKCDF
LIBS += -L$$OCCLibPath -lTKDE
LIBS += -L$$OCCLibPath -lTKDECascade
LIBS += -L$$OCCLibPath -lTKDEGLTF
LIBS += -L$$OCCLibPath -lTKDEIGES
LIBS += -L$$OCCLibPath -lTKDEOBJ
LIBS += -L$$OCCLibPath -lTKDEPLY
LIBS += -L$$OCCLibPath -lTKDESTEP
LIBS += -L$$OCCLibPath -lTKDESTL
LIBS += -L$$OCCLibPath -lTKDEVRML
LIBS += -L$$OCCLibPath -lTKExpress
LIBS += -L$$OCCLibPath -lTKFeat
LIBS += -L$$OCCLibPath -lTKFillet
LIBS += -L$$OCCLibPath -lTKG2d
LIBS += -L$$OCCLibPath -lTKG3d
LIBS += -L$$OCCLibPath -lTKGeomAlgo
LIBS += -L$$OCCLibPath -lTKGeomBase
LIBS += -L$$OCCLibPath -lTKHLR
LIBS += -L$$OCCLibPath -lTKLCAF
LIBS += -L$$OCCLibPath -lTKMath
LIBS += -L$$OCCLibPath -lTKMesh
LIBS += -L$$OCCLibPath -lTKMeshVS
LIBS += -L$$OCCLibPath -lTKOffset
LIBS += -L$$OCCLibPath -lTKOpenGl
LIBS += -L$$OCCLibPath -lTKPrim
LIBS += -L$$OCCLibPath -lTKRWMesh
LIBS += -L$$OCCLibPath -lTKService
LIBS += -L$$OCCLibPath -lTKShHealing
LIBS += -L$$OCCLibPath -lTKStd
LIBS += -L$$OCCLibPath -lTKStdL
LIBS += -L$$OCCLibPath -lTKTObj
LIBS += -L$$OCCLibPath -lTKTopAlgo
LIBS += -L$$OCCLibPath -lTKV3d
LIBS += -L$$OCCLibPath -lTKVCAF
LIBS += -L$$OCCLibPath -lTKXCAF
LIBS += -L$$OCCLibPath -lTKXMesh
LIBS += -L$$OCCLibPath -lTKXSBase
LIBS += -L$$OCCLibPath -lTKXml
LIBS += -L$$OCCLibPath -lTKXmlL
LIBS += -L$$OCCLibPath -lTKXmlTObj
LIBS += -L$$OCCLibPath -lTKXmlXCAF
LIBS += -L$$OCCLibPath -lTKernel


INCLUDEPATH += $$OCCLibPath
DEPENDPATH += $$OCCLibPath
