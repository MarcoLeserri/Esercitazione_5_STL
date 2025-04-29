#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>                 
#include <vector>               
#include <string>               
#include <map>                  
#include <iostream>             
#include <Eigen/Dense>  

using namespace Eigen;
using namespace std;
using namespace PolygonalLibrary;
namespace PolygonalLibrary
{
bool ImportMesh(PolygonalMesh& mesh)
{
	if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;
	
    return true;

}
// ***************************************************************************
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if(file.fail())
        return false;
	
	list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);
	file.close();
    
	listLines.pop_front();
	
	mesh.NumCell0Ds = listLines.size();
    mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = MatrixXd::Zero(3, mesh.NumCell0Ds);
	
	if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    for (const string& line : listLines)
    {
        istringstream ss(line);
		string val;

        unsigned int id;
        unsigned int marker;
        double x, y;
		
		getline(ss, val, ';'); id = stoi(val);
		getline(ss, val, ';'); marker = stoi(val);
		getline(ss, val,';'); x = stod(val);
		getline(ss, val, ';'); y = stod(val);

        mesh.Cell0DsId.push_back(id);
        mesh.Cell0DsCoordinates(0, id) = x;
        mesh.Cell0DsCoordinates(1, id) = y;
		mesh.Cell0DsCoordinates(2, id) = 0.0;
		
        if(marker != 0)
        {
            auto it = mesh.MarkerCell0Ds.find(marker);
            if(it == mesh.MarkerCell0Ds.end())
            {
                mesh.MarkerCell0Ds.insert({marker, {id}});
            }
            else
            {
                it->second.push_back(id);
            }
        }

    }


	
	// funzione per area funzione per lunghezza, ultima richiesta devi sfuttare le utilities di Vicini

	return true;
}

// ***************************************************************************

bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;
	
	list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);
	file.close();
    
	listLines.pop_front();
	mesh.NumCell1Ds = listLines.size();
	mesh.Cell0DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = MatrixXi::Zero(2, mesh.NumCell1Ds);
	
	if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }
	
	for(const string& line : listLines)
	{
		istringstream ss(line);
		string val;
		
		unsigned int id, marker, origin, end;
		
		getline(ss, val, ';'); id = stoi(val);
		getline(ss, val, ';'); marker = stoi(val);
		getline(ss, val, ';'); origin = stoi(val);
		getline(ss, val, ';'); end = stoi(val);
		
		mesh.Cell1DsId.push_back(id);
		mesh.Cell1DsExtrema(0, id) = origin;
		mesh.Cell1DsExtrema(1, id) = end;
		
		if (marker!= 0){
			auto it = mesh.MarkerCell1Ds.find(marker);
			if (it == mesh.MarkerCell1Ds.end())
				mesh.MarkerCell1Ds.insert({marker,{id}});
			else
				it-> second.push_back(id);
		}	
	}
	
	
	return true;
}

//***************************************************************************
bool ImportCell2Ds(PolygonalMesh& mesh)
{	
    ifstream file("./Cell2Ds.csv");

    if(file.fail())
        return false;
	
	list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);
	file.close();
    
	listLines.pop_front();
	
	mesh.NumCell2Ds = listLines.size();
	if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
	}
    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
	mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
	
	for(const string& line : listLines)
	{
		istringstream ss(line);
		string val;
		
		unsigned int id, marker, numVertices, numEdges;
		
		getline(ss, val, ';'); id = stoi(val);
		getline(ss, val, ';'); marker = stoi(val);
		getline(ss, val, ';'); numVertices = stoi(val);
		vector<unsigned int> vertices(numVertices);
		
		for(unsigned int i = 0; i< numVertices; ++i){
			getline(ss, val, ';');
			vertices[i]= stoi(val);
		}
		
		getline(ss, val, ';'); numEdges = stoi(val);
		
		vector<unsigned int> edges(numEdges);
		for(unsigned int i = 0; i< numEdges; ++i){
			getline(ss, val, ';');
			edges[i]= stoi(val);
		}
		
		mesh.Cell2DsId.push_back(id);
		mesh.Cell2DsVertices.push_back(vertices);
		mesh.Cell2DsEdges.push_back(edges);
		
		if (marker!= 0){
			auto it = mesh.MarkerCell2Ds.find(marker);
			if (it == mesh.MarkerCell2Ds.end())
				mesh.MarkerCell2Ds.insert({marker,{id}});
			else
				it-> second.push_back(id);
		}	
	}
	
	 return true;
}
}
