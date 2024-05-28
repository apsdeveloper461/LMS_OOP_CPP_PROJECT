#pragma once

#include"Add_Des.h"

//Project Class

class Project:public Add_Des
{
public:
	Project();
	Project(int project_id,string title,string desc);
	~Project();



};

inline Project::Project():Add_Des()
{
}

inline Project::Project(int project_id, string title, string desc) :Add_Des(project_id, title, desc)
{
}
inline Project::~Project()
{
	cout << endl << "Project/Project with id " << get_id() << " is remove from memeory ";
}

