
#include "modelInfo.h"
#include "glwidget.h"

void ModelInfo::sceneInfo() 
{
    nPolig = nVerts = percTri = nTriangles = 0;
    for (unsigned int i = 0; i < nObjs; ++i) { 
        const Object& obj = scene()->objects()[i];
        nPolig += obj.faces().size();
		for (unsigned int j = 0; j < obj.faces().size(); ++j){
			if (obj.faces()[j].numVertices() == 3) ++nTriangles;
		}
		nVerts += obj.vertices().size(); 
    }
    percTri = nTriangles/nPolig * 100;
}

void ModelInfo::onPluginLoad()
{
    nObjs = scene() -> objects().size();
    sceneInfo();
}

void ModelInfo::postFrame()
{
	cout << "Number of objects: " << nObjs << endl;
	cout << "Number of polygons: " << nPolig << endl;
	cout << "Number of vertexs: " << nVerts << endl;
	cout << "Number of trinagles: " << nTriangles<< endl;
	cout << "Percentage of triangles: " << percTri << "%" << endl;
}

void ModelInfo::onObjectAdd()
{
	nObjs += 1;
	sceneInfo();
}

void ModelInfo::onSceneClear()
{
    nObjs = 0;
    nPolig = 0;
    nVerts = 0;
    percTri = 0; 
}