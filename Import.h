#ifndef IMPORT
#define IMPORT

#include "Engine.h"
#include <fstream>

string cut(string base, int ofset) {
	if (ofset > 0) {
		string res = "";
		for (int i = 0; i < ofset; i++)
		{
			res += base[i];
		}
		return res;
	}
	else
	{
		if (ofset < 0) {
			string res;
			for (int i = base.length() + ofset; i < base.length(); i++)
			{
				res += base[i];
			}
			return res;
		}
		else
		{
			return(base);
		}
	}
}

struct Face {
	List<int> verticesNumbers;
	int normalNumber;

	Face() {
		verticesNumbers = List<int>();
		normalNumber = 0;
	}
};

Mesh importAssetMesh(string path) {
	ifstream file;
	file.open(path, ios_base::in);
	if (!file.is_open()) {
		//cout << "not opened" << endl;
	}
	string data = "qwerty";
	
	while (true) {
		file >> data;
		//cout << data << endl;
		if (data[data.length() - 1] == 'v') {
			break;
		}
	}
	List<_Vector3> vertices;
	_Vector3 vertice;

	List<_Vector3> normals;
	_Vector3 normal;

	int num = 0;
	while (cut(data, -2) != "vn")
	{
		file >> data;
		string _data;
		_data = data;
		if (data[data.length() - 1] == 'v') {
			continue;
			//_data = cut(data, data.length() - 1);
		}

		if (data[data.length() - 2] == 'v') {
			break;
			_data = cut(data, data.length() - 2);
		}

		double value = stof(_data);

		switch (num)
		{
		case 0:
			vertice.x = value;
			break;
		case 1:
			vertice.y = value;
			break;
		case 2:
			vertice.z = value;
			vertices.append(vertice);
			num = -1;
			break;
		default:
			break;
		}
		num++;
	}

	/*while (data != "vn") {
		file >> data;
	}*/

	while (cut(data, -6) != "usemtl")
	{
		file >> data;
		string _data;
		_data = data;
		if (data[data.length() - 6] == 'u') {
			break;
			_data = cut(data, data.length() - 6);
		}

		if (data[data.length() - 2] == 'v') {
			continue;
			_data = cut(data, data.length() - 2);
		}

		double value = stof(_data);

		switch (num)
		{
		case 0:
			normal.x = value;
			break;
		case 1:
			normal.y = value;
			break;
		case 2:
			normal.z = value;
			normals.append(normal);
			num = -1;
			break;
		default:
			break;
		}
		num++;
	}

	while (data != "f") {
		file >> data;
	}
	List<Face> faces;
	Face face = Face();
	while (!file.eof()) {
		file >> data;
		if (data[data.length() - 1] == 'f') {
			continue;
			data = cut(data, data.length() - 1);
		}
		int i;
		for (i = 0; i < data.length(); i++)
		{
			if (data[i] == '/') {
				break;
			}
		}
		//int j
		
		string _data = cut(data, i);
		string _data_ = cut(data, i + 2 - data.length());

		int res = stoi(_data);
		int group = stoi(_data_);
		if (group-1 != face.normalNumber) {
			faces.append(face);
			face.verticesNumbers = List<int>();
			face.normalNumber = group-1;
		}
		face.verticesNumbers.append(res-1);
	}

	faces.append(face);
	//cout << "faces length: " << faces.length() << endl;
	List<Triangle> triangles = List<Triangle>();
	for (int i = 0; i < faces.length(); i++)
	{
		//cout << i << " : " << faces.get(i).verticesNumbers.length() << endl;
		for (int j = 1; j < faces.get(i).verticesNumbers.length()-1; j++)
		{
			Triangle tr = Triangle();
			tr.vertices.append(vertices.get(faces.get(i).verticesNumbers.get(0)));

			//cout << vertices.get(faces.get(i).verticesNumbers.get(0)).x << ", " << 
				//vertices.get(faces.get(i).verticesNumbers.get(0)).y << ", " << 
				//vertices.get(faces.get(i).verticesNumbers.get(0)).z  << "; ";

			tr.vertices.append(vertices.get(faces.get(i).verticesNumbers.get(j)));

			//cout << vertices.get(faces.get(i).verticesNumbers.get(j)).x << ", " <<
			//	vertices.get(faces.get(i).verticesNumbers.get(j)).y << ", " <<
				//vertices.get(faces.get(i).verticesNumbers.get(j)).z << "; ";

			tr.vertices.append(vertices.get(faces.get(i).verticesNumbers.get(j + 1)));

			//cout << vertices.get(faces.get(i).verticesNumbers.get(j + 1)).x << ", " <<
				//vertices.get(faces.get(i).verticesNumbers.get(j + 1)).y << ", " <<
			//	vertices.get(faces.get(i).verticesNumbers.get(j + 1)).z << "; ";
			//cout << endl;
			tr.color = Color(1, 255, 1);
			tr.recalculateNormal();
			if (tr.normal != normals.get(faces.get(i).normalNumber)) {
				tr.reverse();
				tr.recalculateNormal();
			}
			triangles.append(tr);
		}
	}
	//cout << triangles.length() << endl;
	Mesh result = Mesh();
	result.triangles = triangles;
	return(result);
	//cout << data;
}

#endif
