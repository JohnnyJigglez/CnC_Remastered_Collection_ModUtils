#ifndef PROJECTILE_H
#define PROJECTILE_H
//#include "CONST.CPP"
//#include "TYPE.H"
//#include "FUNCTION.h"
#include <vector>
/***************************************************************************
**	These are the text names for the various built-in bullet types a weapon
*   can possess.
*/
const char* const BulletTypeName[BULLET_COUNT] = {
"Invisible",
"Cannon",
"Ack",
"Torpedo",
"FROG",
"HeatSeeker",
"LaserGuided",
"Lobbed",
"Bomblet",
"Ballistic",
"Parachute",
"Fireball",
"LeapDog",
"Catapult",
"AAMissile",
"GPSSatellite",
"NukeUp",
"NukeDown"
};

class BulletTypeClass : public ObjectTypeClass
{
public:

	/*
	**	Does this bullet type fly over walls?
	*/
	unsigned IsHigh : 1;

	bool IsReadfromINI : 1;

	/*
	** Does this bullet need a shadow drawn under it?  Shadowed bullets
	** use the Height value to offset their Y position.
	*/
	unsigned IsShadow : 1;

	/*
	**	If this projectile is one that ballistically arcs from ground level, up into the air and
	**	then back to the ground, where it explodes. Typical uses of this are for grenades and
	**	artillery shells.
	*/
	unsigned IsArcing : 1;

	/*
	**	Certain projectiles do not travel horizontally, but rather, vertically -- they drop
	**	from a height. Bombs fall into this category and will have this value set to
	**	true. Dropping projectiles do not calculate collision with terrain (such as walls).
	*/
	unsigned IsDropping : 1;

	/*
	**	Is this projectile invisible?  Some bullets and weapon effects are not directly
	**	rendered. Small caliber bullets and flame thrower flames are treated like
	**	normal projectiles for damage purposes, but are displayed using custom
	**	rules.
	*/
	unsigned IsInvisible : 1;

	/*
	**	Does this bullet explode when near the target?  Some bullets only explode if
	**	it actually hits the target. Some explode even if nearby.
	*/
	unsigned IsProximityArmed : 1;

	/*
	**	Does this projectile spew puffs of smoke out its tail while it
	**	travels? Missiles are prime examples of this projectile type.
	*/
	unsigned IsFlameEquipped : 1;

	/*
	**	Should fuel consumption be tracked for this projectile?  Rockets are the primary
	**	projectile with this characteristic, but even for bullets it should be checked so that
	**	bullets don't travel too far.
	*/
	unsigned IsFueled : 1;

	/*
	**	Is this projectile without different facing visuals?  Most plain bullets do not change
	**	visual imagery if their facing changes. Rockets, on the other hand, are equipped with
	**	the full 32 facing imagery.
	*/
	unsigned IsFaceless : 1;

	/*
	**	If this is a typically inaccurate projectile, then this flag will be true. Artillery
	**	is a prime example of this type.
	*/
	unsigned IsInaccurate : 1;

	/*
	**	If the bullet contains translucent pixels, then this flag will be true. These
	**	translucent pixels really are "shadow" pixels in the same style as the shadow
	**	cast by regular ground units.
	*/
	unsigned IsTranslucent : 1;

	/*
	**	If this bullet can be fired on aircraft, then this flag will be true.
	*/
	unsigned IsAntiAircraft : 1;

	/*
	**	If this bullet can fire upon ground targets, then this flag will be true.
	*/
	unsigned IsAntiGround : 1;

	/*
	**	If this bullet can be fired upon submarines (that are submerged), then
	**	this flag will be true.
	*/
	unsigned IsAntiSub : 1;

	/*
	**	If this bullet should lose strength as it travels toward the target, then
	**	this flag will be true.
	*/
	unsigned IsDegenerate : 1;

	/*
	**	Does this projectile travel under the water? If so, then its imagery will be modified
	**	to look like it is doing so.
	*/
	unsigned IsSubSurface : 1;

	/*
	**	If this projectile is equipped with a parachute, then this flag will be set. Parachute
	**	bombs are usually the only one with this flag set.
	*/
	unsigned IsParachuted : 1;

	/*
	**	Is this unit of the humongous size?  Certain very large projectiles have
	**	this flag set. Typically, they require a special offset list so that the cells
	**	they overlap will be properly redrawn.
	*/
	unsigned IsGigundo : 1;

	/*
	**	This element is a unique identification number for the bullet
	**	type.
	*/
	//BulletType Type;

	/*
	**	This is the rotation speed of the bullet. It only has practical value
	**	for those projectiles that performing homing action during flight -- such
	**	as with rockets. If the ROT is zero, then no homing is performed. Otherwise
	**	the projectile is considered to be a homing type.
	*/
	unsigned char ROT;

	/*
	**	Some projectiles have a built in arming distance that must elapse before the
	**	projectile may explode. If this value is non-zero, then this override is
	**	applied.
	*/
	int Arming;

	/*
	**	If this bullet is of the tumbling type, then this is the modulo to factor
	**	into the game frame when determining what shape number to use for the
	**	imagery.
	*/
	int Tumble;

	/*
	**	Projectiles can be assigned an animation to display while in flight to target.
	*/
	AnimType Anim;

	/*
	**	Projectiles can be logically treated like another Projectile
	*/
	BulletType BehavesLike;

	//---------------------------------------------------------------------
	BulletTypeClass(NoInitClass const& x) : ObjectTypeClass(x) {};
	BulletTypeClass(char const* name);
	//~BulletTypeClass(void);

	void* operator new(size_t t) { return(malloc(t)); }
	//static void* operator new(size_t t) { return(malloc(t)); };
	//static void* operator new(size_t, void* ptr);
	//static void operator delete(void* ptr);

	static void Init_Heap(void);
	static const BulletTypeClass& As_Reference(BulletType type);
	static const BulletTypeClass* As_Pointer(BulletType bullet);
	static const BulletTypeClass* As_Pointer(char const* name);
	static void Init(TheaterType) {};
	static void One_Time(void);
	BulletType Type(void) const { return(BehavesLike); };
	virtual bool Read_INI(CCINIClass& ini);
	virtual bool Create_And_Place(CELL, HousesType = HOUSE_NONE) const { return false; };
	virtual ObjectClass* Create_One_Of(HouseClass*) const { return 0; }
    static void Clear_Heap(void);
	static const BulletTypeClass* findorcreate(CCINIClass& ini, const char* value, const BulletTypeClass* defptr = NULL);
	static BulletType findorcreate(CCINIClass& ini, const char* value, BulletType defvalue = BULLET_NONE);
	static void Dump(void);
};

#endif
