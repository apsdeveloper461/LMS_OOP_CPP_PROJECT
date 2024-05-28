#pragma once
#include "Add_Des.h"

//Club CLass

class Club:public Add_Des
{
public:
	Club();
	Club(int club_id,string title,string descr);
	~Club();


};


inline Club::Club():Add_Des()
{
}

inline Club::Club(int club_id, string name, string descr):Add_Des(club_id,name,descr)
{
}

inline Club::~Club()
{
	cout << endl << "CLub with id " << get_id() << " is remove from memeory ";
}

