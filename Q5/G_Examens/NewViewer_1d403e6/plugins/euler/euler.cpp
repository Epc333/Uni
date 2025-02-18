#include "euler.h"
#include "glwidget.h"
#include <set>

void Euler::onPluginLoad()
{
	calculateEuler();
}

void Euler::preFrame()
{
	
}

void Euler::postFrame()
{
	
}

void Euler::onObjectAdd()
{
	
}


void Euler::calculateEuler()
{
	F = V = E = X = 0;
	int nObjs = scene()->objects().size(); 
	for (int i = 0; i < nObjs; ++i){
		const Object& obj = scene()->objects()[i];
		F += obj.faces().size();
		V += obj.vertices().size();
		std::set<std::pair<int, int>> Arestes;
		for (const auto& face : obj.faces()){
			for (int k = 0; k < face.numVertices(); ++k){
				int v1 = face.vertexIndex(k);
				int v2 = face.vertexIndex((k + 1) % face.numVertices());
				if (v1 > v2) std::swap(v1, v2);
				Arestes.insert({v1, v2});
			}
		}
		E += Arestes.size();
	}
	cout << "F: " << F << endl;
	cout << "V: " << V << endl;
	cout << "E: " << E << endl;
	cout << "X: " << V - E + F << endl;
}