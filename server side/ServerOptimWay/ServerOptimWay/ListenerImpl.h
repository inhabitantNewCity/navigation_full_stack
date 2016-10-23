#pragma once
#include "Listener.h"
#include "graph_dll.h"

#include <Windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

class ListenerOptimWay: public Listener
{
private:
	bool graph;
	FILE *f;
	char* namebase;
	Coord start;
	Coord finish;
public:
	ListenerOptimWay(Coord start, Coord finish, char* namebase):Listener(){
		this->start = start;
		this->finish = finish;
		this->namebase = namebase;
	};
	virtual Coord* calculate(int* countVertex) {
		int error_1;
		HINSTANCE hdll00;
		char* graphname;
		int len = strlen(namebase);
		cout << "len " << len << endl;
		graphname = new char[len + 2];
		for (int j = 0; j<len; j++)
		{
			graphname[j] = namebase[j];
			graphname[len] = '.';
			graphname[len + 1] = 'g';
			graphname[len + 2] = 0;
		}
		cout << "graphname " << graphname << endl;
		hdll00 = BaseFun(&error_1, NULL);
		if (hdll00 == NULL)
		{
			printf("Library not found");
			return 0;
		}
		else
			printf("Library Graph_DLL_Project.dll  - OK\n");

		f = fopen(graphname, "rb");
		if (!f)
		{
			cout << "not_graph_file" << endl;
			return 0;
		}
		else
		{
			_Load_Graph(graphname);
			//  Close_Graph();	  
			int pointsCount = 0;
			Coord *path;
			pointsCount = _FindPath_Make(start, finish);
			*countVertex = pointsCount;
			if (pointsCount == -1)
			{
				printf("pCount==-1\n");
			}
			path = new Coord[pointsCount];
			_GetResultPath(path);
			return path;	
		}
	};
	virtual ~ListenerOptimWay() {
		delete[] namebase;
		delete[] f;
	};
};