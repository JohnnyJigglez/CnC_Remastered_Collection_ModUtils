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

/* $Header: /CounterStrike/BBDATA.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : BBDATA.CPP                                                   *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : May 23, 1994                                                 *
 *                                                                                             *
 *                  Last Update : July 19, 1996 [JLB]                                          *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   BulletTypeClass::As_Reference -- Returns with a reference to the bullet type object specif*
 *   BulletTypeClass::BulletTypeClass -- Constructor for bullet type objects.                  *
 *   BulletTypeClass::Init_Heap -- Initialize the heap objects for the bullet type.            *
 *   BulletTypeClass::Load_Shapes -- Load shape data for bullet types.                         *
 *   BulletTypeClass::One_Time -- Performs the one time processing for bullets.                *
 *   BulletTypeClass::Read_INI -- Fetch the bullet type data from the INI database.            *
 *   BulletTypeClass::operator delete -- Deletes a bullet type object from the special heap.   *
 *   BulletTypeClass::operator new -- Allocates a bullet type object from the special heap.    *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include	"function.h"



/***********************************************************************************************
 * BulletTypeClass::BulletTypeClass -- Constructor for bullet type objects.                    *
 *                                                                                             *
 *    This is basically a constructor for static type objects used by bullets. All bullets     *
 *    are of a type constructed by this routine at game initialization time.                   *
 *                                                                                             *
 * INPUT:   see below...                                                                       *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/17/1994 JLB : Created.                                                                 *
 *   07/17/1996 JLB : Uses correct default values.                                             *
 *   09/25/2021 JJ  : now Type identifier is specified as part of the instantiation            *
 *=============================================================================================*/
BulletTypeClass::BulletTypeClass(int bullettype, char const* name) :
		ObjectTypeClass(	RTTI_BULLETTYPE,
								BulletTypes.ID(this),
								true,
								true,
								false,
								false,
								true,
								true,
								false,
								TXT_NONE,
								name
								),
	IsHigh(false),
	IsShadow(true),
	IsArcing(false),
	IsDropping(false),
	IsInvisible(false),
	IsProximityArmed(false),
	IsFlameEquipped(false),
	IsFueled(false),
	IsFaceless(true),
	IsInaccurate(false),
	IsTranslucent(false),
	IsAntiAircraft(false),
	IsAntiGround(true),
	IsAntiSub(false),
	IsDegenerate(false),
	IsSubSurface(false),
	IsParachuted(false),
	IsGigundo(false),
	Type(static_cast<BulletType>(bullettype)),
	ROT(0),
	Arming(0),
	Tumble(0)
{
	//char message[64];
	//sprintf(message, "Instantiated Projectile %s .\n", IniName);
	//WWDebugString(message);
}


/***********************************************************************************************
 * BulletTypeClass::operator new -- Allocates a bullet type object from the special heap.      *
 *                                                                                             *
 *    This allocates a bullet type object from a special heap that is used just for            *
 *    objects of this type.                                                                    *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to an allocated block or NULL if the allocation could not   *
 *          occur.                                                                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void * BulletTypeClass::operator new(size_t)
{
	return(BulletTypes.Alloc());
}


/***********************************************************************************************
 * BulletTypeClass::operator delete -- Deletes a bullet type object from the special heap.     *
 *                                                                                             *
 *    This is the counterpart to the operator new function for bullet type objects. It will    *
 *    return the bullet type object back to the special heap used for bullet type object       *
 *    allocation.                                                                              *
 *                                                                                             *
 * INPUT:   ptr   -- Pointer to the bullet type object to free.                                *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void BulletTypeClass::operator delete(void * ptr)
{
	BulletTypes.Free((BulletTypeClass *)ptr);
}


/***********************************************************************************************
 * BulletTypeClass::Init_Heap -- Initialize the heap objects for the bullet type.              *
 *                                                                                             *
 *    This performs any necessary initialization for the bullet types.                         *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *   10/01/2021 JJ : Modified to work with new constructor sig.                                *
 *=============================================================================================*/
void BulletTypeClass::Init_Heap(void)
{
	/*	These bullet type class objects must be allocated in the exact order that they
	**	are specified in the BulletType enumeration. This is necessary because the heap
	**	allocation block index serves double duty as the type number index.
	**But not really true anymore since we use the TYPE variable for that, they just sit in a dynamic heap now
	**and maybe someday I'll wrote the code that sorts an assumed-unsorted list so we can get on with our lives
	**and not hold onto so many pointers when we instantiate the BULLET class and other classes like it.
	*/
	new BulletTypeClass(0,"Invisible");	//	BULLET_INVISIBLE
	new BulletTypeClass(1,"Cannon");		//	BULLET_CANNON
	new BulletTypeClass(2,"Ack");			//	BULLET_ACK
	new BulletTypeClass(3,"Torpedo");		//	BULLET_TORPEDO
	new BulletTypeClass(4,"FROG");			//	BULLET_FROG
	new BulletTypeClass(5,"HeatSeeker");	//	BULLET_HEAT_SEEKER
	new BulletTypeClass(6,"LaserGuided");	//	BULLET_LASER_GUIDED
	new BulletTypeClass(7,"Lobbed");		//	BULLET_LOBBED
	new BulletTypeClass(8,"Bomblet");		//	BULLET_BOMBLET
	new BulletTypeClass(9,"Ballistic");	//	BULLET_BALLISTIC
	new BulletTypeClass(11,"Parachute");	//	BULLET_PARACHUTE
	new BulletTypeClass(12, "Fireball");		//	BULLET_FIREBALL
	new BulletTypeClass(13, "LeapDog");		//	BULLET_DOG
	new BulletTypeClass(14, "Catapult");		//	BULLET_CATAPULT
	new BulletTypeClass(15, "AAMissile");	//	BULLET_AAMISSILE
	new BulletTypeClass(16, "GPSSatellite");//	BULLET_GPS_SATELLITE
	new BulletTypeClass(17, "NukeUp");		//	BULLET_NUKE_UP
	new BulletTypeClass(18, "NukeDown");		//	BULLET_NUKE_DOWN
}


/***********************************************************************************************
 * BulletTypeClass::One_Time -- Performs the one time processing for bullets.                  *
 *                                                                                             *
 *    This routine is used to perform any one time processing for the bullet type class. It    *
 *    handles loading of the shape files.                                                      *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   This routine must be called before any rendering of bullets occurs and should   *
 *             only be called once.                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/28/1994 JLB : Created. 
 *   07/17/2021 JJ  : Updated to use non-static HEAP size and more efficient logics.
 *=============================================================================================*/
void BulletTypeClass::One_Time(void)
{
	/*
	**	Load the bullet shapes.
	*/
	BulletTypeClass* btc = NULL;
	for (int index = 0; index < BulletTypes.Count(); index++) {
		btc = BulletTypes.Ptr(index);
		if (!(btc->IsInvisible)) {
			char	fullname[_MAX_FNAME + _MAX_EXT];
			_makepath(fullname, NULL, NULL, btc->Graphic_Name(), ".SHP");
			#ifdef NDEBUG
			    ((void const*&)btc->ImageData) = MFCD::Retrieve(fullname);
			#else
				RawFileClass file(fullname);

				if (file.Is_Available()) {
					((void const *&)btc->ImageData) = Load_Alloc_Data(file);
				} else {
					((void const *&)btc->ImageData) =	MFCD::Retrieve(fullname);
				}
			#endif
		}
	}
}


/***********************************************************************************************
 * BulletTypeClass::As_Reference -- Returns with a reference to the bullet type object         *
 *                                  specified.											       *
 *                                                                                             *
 *    Given a bullet type identifier, this routine will return a reference to the bullet type  *
 *    object it refers to.                                                                     *
 *                                                                                             *
 * INPUT:   type  -- The bullet type identifier to convert to a reference.                     *
 *                                                                                             *
 * OUTPUT:  Returns with a reference to the bullet type class object.                          *
 *                                                                                             *
 * WARNINGS:   Make sure that the type parameter specified is a valid bullet type. If not,     *
 *             then the result is a reference to the first BTC                                 *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
BulletTypeClass & BulletTypeClass::As_Reference(BulletType type)
{
	return *BulletTypeClass::As_Pointer(type);

}

/***********************************************************************************************
 * BulletTypeClass::As_Pointer -- Convert a bullet type number into a pointer to its BTC.      *
 *                                                                                             *
 *    This will locate the bullet type specified and return a pointer to its BTC.              *
 *                                                                                             *
 * INPUT:   bullet  -- The bullet to convert into a pointer.                                   *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the bullet type class that is represented by the         *
 *          bullet type number specified.                                                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/17/2021 JJ : Created.                                                                  *
 *=============================================================================================*/
BulletTypeClass* BulletTypeClass::As_Pointer(BulletType bullet)
{
	if (bullet == BULLET_NONE) {
		return(NULL);
	}
	for (int index = 0; index < BulletTypes.Count(); index++) {
		if (bullet == BulletTypes.Ptr(index)->Type) {
			return BulletTypes.Ptr(index);
		}
	}
	return(NULL);
}


/***********************************************************************************************
 * BulletTypeClass::Read_INI -- Fetch the bullet type data from the INI database.              *
 *                                                                                             *
 *    Use this routine to fetch override information about this bullet type class object       *
 *    from the INI database specified.                                                         *
 *                                                                                             *
 * INPUT:   ini   -- Reference to the INI database to examine.                                 *
 *                                                                                             *
 * OUTPUT:  bool; Was the section for this bullet found and the data extracted?                *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/19/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool BulletTypeClass::Read_INI(CCINIClass & ini)
{
	if (ini.Is_Present(Name())) {
		char message[128];
		sprintf(message, "ReadINI BulletType %s ...\n", Name());
		WWDebugString(message);
		Arming = ini.Get_Int(Name(), "Arm", Arming);
		ROT = ini.Get_Int(Name(), "ROT", ROT);
		Tumble = ini.Get_Int(Name(), "Frames", Tumble);
		IsHigh = ini.Get_Bool(Name(), "High", IsHigh);
		IsShadow = ini.Get_Bool(Name(), "Shadow", IsShadow);
		IsArcing = ini.Get_Bool(Name(), "Arcing", IsArcing);
		IsDropping = ini.Get_Bool(Name(), "Dropping", IsDropping);
		IsInvisible = ini.Get_Bool(Name(), "Inviso", IsInvisible);
		IsProximityArmed = ini.Get_Bool(Name(), "Proximity", IsProximityArmed);
		IsFlameEquipped = ini.Get_Bool(Name(), "Animates", IsFlameEquipped);
		IsFueled = ini.Get_Bool(Name(), "Ranged", IsFueled);
		IsInaccurate = ini.Get_Bool(Name(), "Inaccuate", IsInaccurate);
		IsAntiAircraft = ini.Get_Bool(Name(), "AA", IsAntiAircraft);
		IsAntiGround = ini.Get_Bool(Name(), "AG", IsAntiGround);
		IsAntiSub = ini.Get_Bool(Name(), "ASW", IsAntiSub);
		IsDegenerate = ini.Get_Bool(Name(), "Degenerates", IsDegenerate);
		IsSubSurface = ini.Get_Bool(Name(), "UnderWater", IsSubSurface);
		IsParachuted = ini.Get_Bool(Name(), "Parachuted", IsParachuted);
		IsFaceless = !ini.Get_Bool(Name(), "Rotates", !IsFaceless);
		IsTranslucent = ini.Get_Bool(Name(), "Translucent", IsTranslucent);
		IsGigundo = ini.Get_Bool(Name(), "Gigundo", IsGigundo);
		ini.Get_String(Name(), "Image", GraphicName, GraphicName, sizeof(GraphicName));
		return(true);
	}
	return(false);
}

/***********************************************************************************************
 * Bullet_From_Name -- Convert ASCII name to bullet type ID number.                            *
 *                                                                                             *
 *    This will find the bullet whos name matches that specified and then it will return the   *
 *    bullet ID number associated with it.                                                     *
 *                                                                                             *
 * INPUT:   name  -- Pointer to the ASCII name of the bullet type.                             *
 *                                                                                             *
 * OUTPUT:  Returns with the bullet type ID number that matches the name specified. If no      *
 *          match could be found, then BULLET_NONE is returned.                                *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/16/2021 JJ : Created.                                                                 *
 *=============================================================================================*/
BulletType Bullet_From_Name(char const* name)
{
	if (!name) return(BULLET_NONE);
	return BulletTypeClass::From_Name(name)->Type;
}

/***********************************************************************************************
 * BulletTC_From_Name -- Convert ASCII name to pointer to bullet type class .                  *
 *                                                                                             *
 *    This will find the bullet whos name matches that specified and then it will return the   *
 *    bullet type class pointer associated with it.                                            *
 *                                                                                             *
 * INPUT:   name  -- Pointer to the ASCII name of the bullet type class.                       *
 *                                                                                             *
 * OUTPUT:  Returns with the bullet type class pointer that matches the name specified. If no   *
 *          match could be found, then NULL is returned.                                       *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/27/2021 JJ : Created.                                                                 *
 *=============================================================================================*/
BulletTypeClass * BulletTypeClass::From_Name(char const* name)
{
	if (!name) return(NULL);

	for (int index = 0; index < BulletTypes.Count(); index++) {
		if (stricmp(BulletTypes.Ptr(index)->Name(), name) == 0) {
			return(BulletTypes.Ptr(index));
		}
	}
	return(NULL);
}
