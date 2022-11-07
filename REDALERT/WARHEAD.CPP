//
// Copyright 2020 Electronic Arts Inc.
//
// TiberianDawn.DLL and RedAlert.dll and corresponding source code is free 
// software: you can redistribute it and/or modify it under the terms of 
// the GNU General Public License as published by the Free Software Foundation, 
// either version 3 of the License, or (at your option) any later version.

// TiberianDawn.DLL and RedAlert.dll and corresponding source code is distributed 
// in the hope that it will be useful, but with permitted additional restrictions 
// under Section 7 of the GPL. See the GNU General Public License in LICENSE.TXT 
// distributed with this program. You should have received a copy of the 
// GNU General Public License along with permitted additional restrictions 
// with this program. If not, see https://github.com/electronicarts/CnC_Remastered_Collection

/* $Header: /CounterStrike/WARHEAD.CPP 1     3/03/97 10:26a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : WARHEAD.CPP                                                  *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 05/20/96                                                     *
 *                                                                                             *
 *                  Last Update : July 19, 1996 [JLB]                                          *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   WarheadTypeClass::As_Pointer -- Convert a warhead type number into a pointer.             *
 *   WarheadTypeClass::Read_INI -- Fetches the warhead data from the INI database.             *
 *   WarheadTypeClass::WarheadTypeClass -- Default constructor for warhead objects.            *
 *   WarheadTypeClass::operator delete -- Returns warhead object back to special memory pool.  *
 *   WarheadTypeClass::operator new -- Allocate a warhead object from the special heap.        *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include <string>
#include    "WARHEAD.H"


/***************************************************************************
**	This is the warhead data object array.
*/
//TFixedIHeapClass<WarheadTypeClass> Warheads;
std::vector<WarheadTypeClass*> Warheads;
char ExplodingEntityWarheadName[16];
char FlamingEntityWarheadName[16];

/***********************************************************************************************
 * WarheadTypeClass::Init_Heap -- Initialize the warhead type class heap.                      *
 *                                                                                             *
 *    This initializes the warhead type class heap by pre-allocated all the known warhead types.*
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   Only call this once and call it before processing the rules.ini file.           *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/29/2022 JJ : Created.                                                                 *
 *=============================================================================================*/
void WarheadTypeClass::Init_Heap(void)
{
	//char message[128];
	//static char warheadpreop[WARHEAD_COUNT][16] = {"SA","HE","AP","Fire","HollowPoint","Super","Organic","Nuke","Mechanical"};
	for(unsigned short index = WARHEAD_FIRST; index < WARHEAD_COUNT; index++){
		new WarheadTypeClass(WarheadTypeName[index]);
	}
	/*for (unsigned short index = 0; index < Warheads.Count(); index++) {
		sprintf(message, "WTC.Init_Heap Loaded Warhead %s .\n", Warheads.Ptr(index)->Name());
		WWDebugString(message);
	}*/
	
}


/***********************************************************************************************
 * WarheadTypeClass::WarheadTypeClass -- Default constructor for warhead objects.              *
 *                                                                                             *
 *    This default constructor for a warhead object will fill in all the default values        *
 *    for a warhead. It is presumed that these values will be normal unless specifically       *
 *    overridden by the INI database.                                                          *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/19/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
WarheadTypeClass::WarheadTypeClass(char const* name) :
	ID(-1),
	IniName(name),
	SpreadFactor(1),
	IsReadfromINI(false),
	IsWallDestroyer(false),
	IsWoodDestroyer(false),
	IsTiberiumDestroyer(false),
	IsOrganic(false),
	ExplosionSet(0),
	InfantryDeath(0),
	Anim(ANIM_NONE),
	BehavesLike(WARHEAD_NONE)
{
	ID = (short)(Warheads.size());
	Warheads.push_back(this);
	BehavesLike = static_cast<WarheadType>(ID);
	/*for (WarheadType wht = WARHEAD_FIRST; wht < WARHEAD_COUNT; wht++) {
		if (strcmpi(IniName, WarheadTypeName[wht]) == 0) {
			BehavesLike = wht;
			break;
		}
	}*/
	for (ArmorType armor = ARMOR_FIRST; armor < ARMOR_COUNT; armor++) {
		Modifier[armor] = 1;
	}
	char message[64];
	sprintf(message, "Constructed Warhead %s with ID: %d.\n", IniName, ID);
	WWDebugString(message);
}

/***********************************************************************************************
 * WarheadTypeClass::WarheadTypeClass -- Default constructor for warhead objects.              *
 *                                                                                             *
 *    This default constructor for a warhead object will fill in all the default values        *
 *    for a warhead. It is presumed that these values will be normal unless specifically       *
 *    overridden by the INI database.                                                          *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/05/2021 JJ : Created.                                                                  *
 *=============================================================================================*/
//WarheadTypeClass::WarheadTypeClass(char const* name) : WarheadTypeClass(name) {}

/***********************************************************************************************
 * WeaponTypeClass::~WeaponTypeClass -- Destructor for weapon type class objects.              *
 *                                                                                             *
 *    This destructor really doesn't do anything but set the pointers to NULL. This is a       *
 *    general purposes safety tactic but is otherwise useless.                                 *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/17/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
WarheadTypeClass::~WarheadTypeClass(void)
{
	IniName = NULL;
}

/***********************************************************************************************
 * Warhead_From_Name -- Convert ASCII name to warhead type ID number.                           *
 *                                                                                             *
 *    This will find the warhead whos name matches that specified and then it will return the  *
 *    warhead ID number associated with it.                                                    *
 *                                                                                             *
 * INPUT:   name  -- Pointer to the ASCII name of the warhead type.                            *
 *                                                                                             *
 * OUTPUT:  Returns with the warhead type ID number that matches the name specified. If no     *
 *          match could be found, then WARHEAD_NONE is returned.                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/16/2021 JJ  : Created.                                                                 *
 *=============================================================================================
WarheadType Warhead_From_Name(char const* name)
{
	if(name == NULL) return(WARHEAD_NONE);
	WarheadTypeClass* ptr = WarheadTypeClass::As_Pointer(name);
	if(ptr == NULL)
		return(WARHEAD_NONE);
	return ptr->Type;

}*/

/***********************************************************************************************
 * WarheadTypeClass_From_Name -- Convert ASCII name to warheadtype class pointer.               *
 *                                                                                             *
 *    This will find the warhead whos name matches that specified and then it will return the  *
 *    pointer associated with it.                                                              *
 *                                                                                             *
 * INPUT:   name  -- Pointer to the ASCII name of the warhead type.                            *
 *                                                                                             *
 * OUTPUT:  Returns with the warhead type ID number that matches the name specified. If no     *
 *          match could be found, then WARHEAD_NONE is returned.                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/27/2021 JJ  : Created.                                                                 *
 *=============================================================================================*/
const WarheadTypeClass* WarheadTypeClass::As_Pointer(char const* name)
{
	if (name == NULL) return(NULL);

	for (short index = 0; index < (short)(Warheads.size()); index++) {
		if (!stricmp(Warheads.at(index)->Name(), name)) {
			return(Warheads.at(index));
		}
	}
	return(NULL);
}


/***********************************************************************************************
 * WarheadTypeClass::operator new -- Allocate a warhead object from the special heap.          *
 *                                                                                             *
 *    This will allocate a warhead object from the special heap that is maintained for         *
 *    this purpose.                                                                            *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the newly allocated warhead type object. If there is     *
 *          insufficient memory for the allocation, then NULL is returned.                     *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/19/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
/*void* WarheadTypeClass::operator new(size_t, void* ptr)
{
	//char message[64];
	//sprintf(message, "NEW.ptr invoked for Warhead %s .\n", ((WarheadTypeClass*)ptr)->IniName);
	//WWDebugString(message);
	return(ptr);
}*/


/***********************************************************************************************
 * WarheadTypeClass::operator delete -- Returns warhead object back to special memory pool.    *
 *                                                                                             *
 *    This routine will return the warhead object to the memory pool from whence it came.      *
 *                                                                                             *
 * INPUT:   pointer  -- Pointer to the warhead object to return to the memory pool.            *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/19/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
/*void WarheadTypeClass::operator delete(void* pointer)
{
	Warheads.at(((WarheadTypeClass*)pointer)->ID) = NULL;
	Warheads.at(((WarheadTypeClass*)pointer)->ID) = Warheads.back();
	Warheads.pop_back();
}*/


/***********************************************************************************************
 * WarheadTypeClass::As_Pointer -- Convert a warhead type number into a pointer.               *
 *                                                                                             *
 *    This will locate the warhead type specified and return a pointer to it.                  *
 *                                                                                             *
 * INPUT:   warhead  -- The warhead to convert into a pointer.                                 *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the warhead type object that is represented by the       *
 *          warhead type number specified.                                                     *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/19/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
const WarheadTypeClass * WarheadTypeClass::As_Pointer(WarheadType warhead)
{
	if (warhead != WARHEAD_NONE) {
		for (short index = 0; index < (short)(Warheads.size()); index++) {
			if (Warheads.at(index)->ID == warhead) {
				return(Warheads.at(index));
			}
		}
	}
	return(NULL);
}


/***********************************************************************************************
 * WarheadTypeClass::Read_INI -- Fetches the warhead data from the INI database.               *
 *                                                                                             *
 *    Use this routine to retrieve the data specific to this warhead type class object from    *
 *    the INI database specified. Typical use of this is when processing the rules.ini         *
 *    file.                                                                                    *
 *                                                                                             *
 * INPUT:   ini   -- Reference to the INI database to fetch the values from.                   *
 *                                                                                             *
 * OUTPUT:  bool; Was the warhead entry found and the data retrieved?                          *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/19/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool WarheadTypeClass::Read_INI(CCINIClass & ini)
{
	char message[128];
	//sprintf(message, "WTC.Read_INI ENTRY WarheadType %s ...\n", Name());
	//WWDebugString(message);
	if (ini.Section_Present(Name())) {
		sprintf(message, "WarheadTypeClass.Read_INI parsing %s ...\n", Name());
		WWDebugString(message);
		SpreadFactor = ini.Get_Int(Name(), "Spread", SpreadFactor);
		IsWallDestroyer = ini.Get_Bool(Name(), "Wall", IsWallDestroyer);
		IsWoodDestroyer = ini.Get_Bool(Name(), "Wood", IsWoodDestroyer);
		IsTiberiumDestroyer = ini.Get_Bool(Name(), "Ore", IsTiberiumDestroyer);
		ExplosionSet = ini.Get_Int(Name(), "Explosion", ExplosionSet);
		SelfHarm = ini.Get_Int(Name(), "SelfHarm", SelfHarm);
		InfantryDeath = ini.Get_Int(Name(), "InfDeath", InfantryDeath);
		Anim = AnimTypeClass::findorcreate(ini, ini.Get_Value(Name(), "Anim"), Anim);
		BehavesLike = findorcreate(ini, ini.Get_Value(Name(), "BehavesLike"), BehavesLike);
		char buffer[128];
		if (ini.Get_String(Name(), "Verses", "100%%,100%%,100%%,100%%,100%%", buffer, sizeof(buffer))) {
			char * aval = strtok(buffer, ",");
			for (ArmorType armor = ARMOR_FIRST; armor < ARMOR_COUNT; armor++) {
				Modifier[armor] = fixed(aval);
				aval = strtok(NULL, ",");
			}
		}
		IsOrganic = (Modifier[ARMOR_STEEL] == 0);
		if(ExplosionSet > 0 && SelfHarm != ExplosionSet)
		IsReadfromINI = true;
		sprintf(message, "WarheadTypeClass.Read_INI parsed %s .\n", Name());
		WWDebugString(message);
		return(true);
	}
	return(false);
}
void WarheadTypeClass::Clear_Heap(void) {
	for (short index = 0; index < (short)Warheads.size(); index++) {

		std::free(Warheads.at(index));
	}
	Warheads.clear();
}

const WarheadTypeClass* WarheadTypeClass::findorcreate(CCINIClass& ini, const char* value, const WarheadTypeClass* defptr)
{
	if (value == NULL || &ini == NULL || strlen(value) < 2)
		return defptr;
	if (strcmpi(value, "none") == 0)
		return NULL;
	if ((defptr != NULL && stricmp(defptr->Name(), value) != 0) || defptr == NULL)//if we are changing it
	{
		const WarheadTypeClass* ptr = As_Pointer(value);
		if (ptr == NULL)//did we find this new weapon that is referenced in the ini?
		{
			if (ini.Section_Present(value))//does this new weapon exist in the ini 
			{
				WarheadTypeClass* newptr = new WarheadTypeClass(value);
				newptr->Read_INI(ini);
				defptr = As_Pointer(value);
				//sprintf(message, "TTC.ReadINI %s obtained pri %s\n", Name(), PrimaryWeapon ? PrimaryWeapon->Name() : "None");
				//WWDebugString(message);
				newptr = NULL;
			}
		}
		else
		{
			defptr = ptr;
			//sprintf(message, "TTC.ReadINI %s obtained pri %s\n", Name(), PrimaryWeapon ? PrimaryWeapon->Name() : "None");
			//WWDebugString(message);
		}
		ptr = NULL;
	}
	return(defptr);
}
WarheadType WarheadTypeClass::findorcreate(CCINIClass& ini, const char* value, WarheadType defvalue)
{
	if (value == NULL || strlen(value) < 2 || &ini == NULL)//send me something proper
		return defvalue;
	if (strcmpi(value, "none") == 0) //this inbound value is set to none, we're clearing this
		return WARHEAD_NONE;
	const WarheadTypeClass* ptr = As_Pointer(value);
	if (ptr != NULL) //if it exists, then send it
		return static_cast<WarheadType>(ptr->ID);
	if (ini.Section_Present(value)) {
		WarheadTypeClass* newptr = new WarheadTypeClass(value);
		newptr->Read_INI(ini);
		return static_cast<WarheadType>(newptr->ID);
	}
	return defvalue;
}

bool WarheadTypeClass::nameMatches(WarheadType defvalue) const
{
	if (defvalue > WARHEAD_COUNT)
		return false;
	return !stricmp(WarheadTypeName[defvalue], this->IniName);
}


char const* WarheadTypeClass::to_string(void) const {
	std::string out = "";
	out += ("Name=" + std::string(Name()) + '\n');
	out += ("ID=" + std::to_string(ID) + '\n');
	out += ("Anim=" + std::to_string(Anim) + '\n');
	out += ("BehavesLike=" + std::to_string(BehavesLike) + '\n');
	out += ("Spread=" + std::to_string(SpreadFactor) + '\n');
	out += ("Wall=" + std::to_string(IsWallDestroyer) + '\n');
	out += ("Wood=" + std::to_string(IsWoodDestroyer) + '\n');
	out += ("Ore=" + std::to_string(IsTiberiumDestroyer) + '\n');
	out += ("Explosion=" + std::to_string(ExplosionSet) + '\n');
	out += ("InfDeath=" + std::to_string(InfantryDeath) + '\n');
	return out.c_str();
}
//using std::string;
//using std::to_string;
void WarheadTypeClass::Dump(void) {
	char message[256];
	//sprintf(message, "[Warheads]\n");
	WWDebugString("[Warheads]\n");
	WarheadTypeClass* ptr = NULL;
	std::string out = "";
	for(int x = 0; x < (int)(Warheads.size()); x++) {
		WarheadTypeClass* ptr = Warheads.at(x);
		out = "";
		out += ("Name=" + std::string(ptr->Name()) + '\n');
		out += ("ID=" + std::to_string(ptr->ID) + '\n');
		out += ("Anim=" + std::string(ptr->Anim == ANIM_NONE ? "none" : AnimTypeClass::As_Pointer(ptr->Anim)->Name()) +'\n');
		out += ("BehavesLike=" + std::to_string(ptr->BehavesLike) + '\n');
		out += ("Spread=" + std::to_string(ptr->SpreadFactor) + '\n');
		out.c_str();
		sprintf(message, out.c_str());
		WWDebugString(message);
		out = "";
		out += ("Wall=" + std::to_string(ptr->IsWallDestroyer) + '\n');
		out += ("Wood=" + std::to_string(ptr->IsWoodDestroyer) + '\n');
		out += ("Ore=" + std::to_string(ptr->IsTiberiumDestroyer) + '\n');
		out += ("Explosion=" + std::to_string(ptr->ExplosionSet) + '\n');
		out += ("InfDeath=" + std::to_string(ptr->InfantryDeath) + '\n' + '\n');
		sprintf(message, out.c_str());
		WWDebugString(message);
	}
}




