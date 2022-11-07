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

/* $Header: /CounterStrike/ADATA.CPP 3     3/07/97 4:27p Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : ADATA.CPP                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : May 30, 1994                                                 *
 *                                                                                             *
 *                  Last Update : July 9, 1996 [JLB]                                           *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   AnimTypeClass::AnimTypeClass -- Constructor for animation types.                          *
 *   AnimTypeClass::One_Time -- Performs one time action for animation types.                  *
 *   AnimTypeClass::Init -- Load any animation artwork that is theater specific.               *
 *   Anim_Name -- Fetches the ASCII name of the animation type specified.                      *
 *   AnimTypeClass::As_Reference -- Fetch a reference to the animation type specified.         *
 *   AnimTypeClass::Init_Heap -- Initialize the animation type system.                         *
 *   AnimTypeClass::operator new -- Allocate an animation type object from private pool.       *
 *   AnimTypeClass::operator delete -- Returns an anim type class object back to the pool.     *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include <string>
#include	"function.h"
//#include "ADATA.H"
std::vector<AnimTypeClass*> AnimTypes;

static AnimTypeClass const AtomBomb(
	ANIM_ATOM_BLAST,						// Animation number.
	"ATOMSFX",								// Data name of animation.
	72,										// Maximum dimension of animation.
	19,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	true,										// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE,
	75,										// Virtual stages
	0x300									// Virtual scale
);

static AnimTypeClass const SputDoor(
	ANIM_SPUTDOOR,							// Animation number.
	"SPUTDOOR",								// Data name of animation.
	42,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

// Electrocution death anim from Tesla coil
static AnimTypeClass const ElectricDie(
	ANIM_ELECT_DIE,						// Animation number.
	"ELECTRO",									// Data name of animation.
	16,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	true,										// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	3,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	5,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_FIRE_MED
);

// Electrocution death anim from Tesla coil for dog
static AnimTypeClass const DogElectricDie(
	ANIM_DOG_ELECT_DIE,					// Animation number.
	"ELECTDOG",								// Data name of animation.
	17,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	3,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	5,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_FIRE_MED
);

static AnimTypeClass const SAMN(
	ANIM_SAM_N,								// Animation number.
	"SAMFIRE",								// Data name of animation.
	55,										// Maximum dimension of animation.
	4,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	18*0,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	18,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const SAMNW(
	ANIM_SAM_NW,							// Animation number.
	"SAMFIRE",								// Data name of animation.
	55,										// Maximum dimension of animation.
	22,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	18*1,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	18,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const SAMW(
	ANIM_SAM_W,								// Animation number.
	"SAMFIRE",								// Data name of animation.
	55,										// Maximum dimension of animation.
	40,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	18*2,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	18,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const SAMSW(
	ANIM_SAM_SW,							// Animation number.
	"SAMFIRE",								// Data name of animation.
	55,										// Maximum dimension of animation.
	58,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	18*3,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	18,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const SAMS(
	ANIM_SAM_S,								// Animation number.
	"SAMFIRE",								// Data name of animation.
	55,										// Maximum dimension of animation.
	76,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	18*4,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	18,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const SAMSE(
	ANIM_SAM_SE,							// Animation number.
	"SAMFIRE",								// Data name of animation.
	55,										// Maximum dimension of animation.
	94,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	18*5,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	18,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const SAME(
	ANIM_SAM_E,								// Animation number.
	"SAMFIRE",								// Data name of animation.
	55,										// Maximum dimension of animation.
	112,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	18*6,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	18,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const SAMNE(
	ANIM_SAM_NE,							// Animation number.
	"SAMFIRE",								// Data name of animation.
	55,										// Maximum dimension of animation.
	130,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	18*7,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	18,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const LZSmoke(
	ANIM_LZ_SMOKE,						// Animation number.
	"SMOKLAND",								// Data name of animation.
	32,										// Maximum dimension of animation.
	72,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	72,										// Loop start frame number.
	91,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	127,										// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

/*
**	Flammable object burning animations. Primarily used on trees and buildings.
*/
static AnimTypeClass const BurnSmall(
	ANIM_BURN_SMALL,						// Animation number.
	"BURN-S",								// Data name of animation.
	11,										// Maximum dimension of animation.
	13,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 32),							// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	30,										// Loop start frame number.
	62,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	4,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const BurnMed(
	ANIM_BURN_MED,							// Animation number.
	"BURN-M",								// Data name of animation.
	14,										// Maximum dimension of animation.
	13,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 16),							// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	30,										// Loop start frame number.
	62,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	4,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const BurnBig(
	ANIM_BURN_BIG,							// Animation number.
	"BURN-L",								// Data name of animation.
	23,										// Maximum dimension of animation.
	13,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 10),							// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	30,										// Loop start frame number.
	62,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	4,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

/*
**	Flammable object burning animations that trail into smoke. Used for
**	buildings and the gunboat.
*/
static AnimTypeClass const OnFireSmall(
	ANIM_ON_FIRE_SMALL,					// Animation number.
	"BURN-S",								// Data name of animation.
	11,										// Maximum dimension of animation.
	13,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 32),							// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	30,										// Loop start frame number.
	62,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	4,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_SMOKE_M
);
static AnimTypeClass const OnFireMed(
	ANIM_ON_FIRE_MED,						// Animation number.
	"BURN-M",								// Data name of animation.
	14,										// Maximum dimension of animation.
	13,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 16),							// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	30,										// Loop start frame number.
	62,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	4,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_ON_FIRE_SMALL
);
static AnimTypeClass const OnFireBig(
	ANIM_ON_FIRE_BIG,						// Animation number.
	"BURN-L",								// Data name of animation.
	23,										// Maximum dimension of animation.
	13,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 10),							// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	30,										// Loop start frame number.
	62,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	4,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_ON_FIRE_MED
);
static AnimTypeClass const Parachute(
	ANIM_PARACHUTE,						// Animation number.
	"PARACH",								// Data name of animation.
	32,										// Maximum dimension of animation.
	15,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	4,											// Delay between frames.
	0,											// Starting frame number.
	7,											// Loop start frame number.
	-1,										// Loopback frame number.
	-1,										// Number of animation stages.
	15,										// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const ParaBomb(
	ANIM_PARA_BOMB,						// Animation number.
	"PARABOMB",								// Data name of animation.
	32,										// Maximum dimension of animation.
	8,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	4,											// Delay between frames.
	0,											// Starting frame number.
	7,											// Loop start frame number.
	-1,										// Loopback frame number.
	-1,										// Number of animation stages.
	15,										// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const FBall1(
	ANIM_FBALL1,							// Animation number.
	"FBALL1",								// Data name of animation.
	67,										// Maximum dimension of animation.
	6,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	true,										// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_KABOOM25,							// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Frag1(
	ANIM_FRAG1,								// Animation number.
	"FRAG1",									// Data name of animation.
	45,										// Maximum dimension of animation.
	3,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	true,										// Forms a crater?
	true,										// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_KABOOM30,							// Sound effect to play.
	ANIM_NONE,
	29										// Virtual stages
);

static AnimTypeClass const VehHit1(
	ANIM_VEH_HIT1,							// Animation number.
	"VEH-HIT1",								// Data name of animation.
	30,										// Maximum dimension of animation.
	4,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	true,										// Forms a crater?
	true,										// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_KABOOM25,							// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const VehHit2(
	ANIM_VEH_HIT2,							// Animation number.
	"VEH-HIT2",								// Data name of animation.
	21,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	true,										// Forms a crater?
	true,										// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_KABOOM12,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const VehHit3(
	ANIM_VEH_HIT3,							// Animation number.
	"VEH-HIT3",								// Data name of animation.
	19,										// Maximum dimension of animation.
	3,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	true,										// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_KABOOM12,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const ArtExp1(
	ANIM_ART_EXP1,							// Animation number.
	"ART-EXP1",								// Data name of animation.
	41,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	true,										// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_KABOOM22,							// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Napalm1(
	ANIM_NAPALM1,							// Animation number.
	"NAPALM1",								// Data name of animation.
	21,										// Maximum dimension of animation.
	5,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_FIRE_EXPLODE,						// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Napalm2(
	ANIM_NAPALM2,							// Animation number.
	"NAPALM2",								// Data name of animation.
	41,										// Maximum dimension of animation.
	5,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_FIRE_EXPLODE,						// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Napalm3(
	ANIM_NAPALM3,							// Animation number.
	"NAPALM3",								// Data name of animation.
	78,										// Maximum dimension of animation.
	5,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_FIRE_LAUNCH,							// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const SmokePuff(
	ANIM_SMOKE_PUFF,						// Animation number.
	"SMOKEY",								// Data name of animation.
	24,										// Maximum dimension of animation.
	2,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	true,										// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const FireBallFade(
	ANIM_FBALL_FADE,						// Animation number.
	"FB2",									// Data name of animation.
	24,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Piff(
	ANIM_PIFF,								// Animation number.
	"PIFF",									// Data name of animation.
	13,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const PiffPiff(
	ANIM_PIFFPIFF,							// Animation number.
	"PIFFPIFF",								// Data name of animation.
	20,										// Maximum dimension of animation.
	2,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Fire3(
	ANIM_FIRE_SMALL,						// Animation number.
	"FIRE3",									// Data name of animation.
	23,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 32),							// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	2,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE,
	-1,										// Virtual stages
	0x100,									// Virtual scale
	NULL,									// Virtual name
	ANIM_FIRE_SMALL_VIRTUAL					// Virtual anim
);

static AnimTypeClass const Fire3Virtual(
	ANIM_FIRE_SMALL_VIRTUAL,				// Animation number.
	"FIRE3",									// Data name of animation.
	23,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,										// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	10,											// Loop start frame number.
	21,										// Ending frame of loop back.
	29,										// Number of animation stages.
	2,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Fire1(
	ANIM_FIRE_MED2,		 				// Animation number.
	"FIRE1",									// Data name of animation.
	23,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 16),							// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	3,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE,
	-1,										// Virtual stages
	0x100,									// Virtual scale
	NULL,									// Virtual name
	ANIM_FIRE_MED2_VIRTUAL					// Virtual anim
);

static AnimTypeClass const Fire1Virtual(
	ANIM_FIRE_MED2_VIRTUAL,		 			// Animation number.
	"FIRE1",									// Data name of animation.
	23,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,										// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	10,											// Loop start frame number.
	21,										// Ending frame of loop back.
	29,										// Number of animation stages.
	3,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Fire4(
	ANIM_FIRE_TINY,		 				// Animation number.
	"FIRE4",									// Data name of animation.
	7,											// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 32),							// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	3,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE,
	-1,										// Virtual stages
	0x100,									// Virtual scale
	NULL,									// Virtual name
	ANIM_FIRE_TINY_VIRTUAL					// Virtual anim
);

static AnimTypeClass const Fire4Virtual(
	ANIM_FIRE_TINY_VIRTUAL,		 			// Animation number.
	"FIRE4",									// Data name of animation.
	7,											// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,										// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	10,											// Loop start frame number.
	21,										// Ending frame of loop back.
	29,										// Number of animation stages.
	3,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Fire2(
	ANIM_FIRE_MED,							// Animation number.
	"FIRE2",									// Data name of animation.
	23,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	fixed(1, 16),							// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	3,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE,
	-1,										// Virtual stages
	0x100,									// Virtual scale
	NULL,									// Virtual name
	ANIM_FIRE_MED_VIRTUAL					// Virtual anim
);

static AnimTypeClass const Fire2Virtual(
	ANIM_FIRE_MED_VIRTUAL,					// Animation number.
	"FIRE2",									// Data name of animation.
	23,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	true,										// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,										// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	10,											// Loop start frame number.
	21,										// Ending frame of loop back.
	29,										// Number of animation stages.
	3,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const OilFieldBurn(
	ANIM_OILFIELD_BURN,					// Animation number.
	"FLMSPT",								// Data name of animation.
	42,										// Maximum dimension of animation.
	58,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	33,										// Loop start frame number.
	99,										// Ending frame of loop back.
	66,										// Number of animation stages.
	127,									// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Gunfire(
	ANIM_MUZZLE_FLASH,					// Animation number.
	"GUNFIRE",								// Data name of animation.
	16,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	true,										// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Number of times the animation loops.
	1,											// Number of animation stages.
	1,											// Ending frame of loop back.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE,
	10										// Virtual stages
);

static AnimTypeClass const SmokeM(
	ANIM_SMOKE_M,							// Animation number.
	"SMOKE_M",								// Data name of animation.
	28,										// Maximum dimension of animation.
	30,										// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	67,										// Loop start frame number.
	-1,										// Loopback frame number.
	-1,										// Number of animation stages.
	6,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE,
	105										// Virtual stages
);

/*
**	Mini-gun fire effect -- used by guard towers.
*/
static AnimTypeClass const GUNN(
	ANIM_GUN_N,								// Animation number.
	"MINIGUN",								// Data name of animation.
	18,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Number of times the animation loops.
	6,											// Number of animation stages.
	0,											// Ending frame of loop back.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const GUNNW(
	ANIM_GUN_NW,							// Animation number.
	"MINIGUN",								// Data name of animation.
	18,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	6,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Number of times the animation loops.
	6,											// Number of animation stages.
	0,											// Ending frame of loop back.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const GUNW(
	ANIM_GUN_W,								// Animation number.
	"MINIGUN",								// Data name of animation.
	18,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	12,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Number of times the animation loops.
	6,											// Number of animation stages.
	0,											// Ending frame of loop back.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const GUNSW(
	ANIM_GUN_SW,							// Animation number.
	"MINIGUN",								// Data name of animation.
	18,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	18,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Number of times the animation loops.
	6,											// Number of animation stages.
	0,											// Ending frame of loop back.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const GUNS(
	ANIM_GUN_S,								// Animation number.
	"MINIGUN",								// Data name of animation.
	18,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	24,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Number of times the animation loops.
	6,											// Number of animation stages.
	0,											// Ending frame of loop back.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const GUNSE(
	ANIM_GUN_SE,							// Animation number.
	"MINIGUN",								// Data name of animation.
	18,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	30,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Number of times the animation loops.
	6,											// Number of animation stages.
	0,											// Ending frame of loop back.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const GUNE(
	ANIM_GUN_E,								// Animation number.
	"MINIGUN",								// Data name of animation.
	18,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	36,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Number of times the animation loops.
	6,											// Number of animation stages.
	0,											// Ending frame of loop back.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const GUNNE(
	ANIM_GUN_NE,							// Animation number.
	"MINIGUN",								// Data name of animation.
	18,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,									// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	42,										// Starting frame number.
	0,											// Loop start frame number.
	0,											// Number of times the animation loops.
	6,											// Number of animation stages.
	0,											// Ending frame of loop back.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const CDeviator(
	ANIM_CRATE_DEVIATOR,					// Animation number.
	"DEVIATOR",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);

static AnimTypeClass const CrateArmor(
	ANIM_CRATE_ARMOR,						// Animation number.
	"ARMOR",									// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const CrateSpeed(
	ANIM_CRATE_SPEED,						// Animation number.
	"SPEED",									// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);

static AnimTypeClass const CrateFPower(
	ANIM_CRATE_FPOWER,					// Animation number.
	"FPOWER",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const CrateTQuake(
	ANIM_CRATE_TQUAKE,					// Animation number.
	"TQUAKE",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);

static AnimTypeClass const CDollar(
	ANIM_CRATE_DOLLAR,					// Animation number.
	"DOLLAR",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const CEarth(
	ANIM_CRATE_EARTH,						// Animation number.
	"EARTH",									// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const CEmpulse(
	ANIM_CRATE_EMPULSE,					// Animation number.
	"EMPULSE",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const CInvun(
	ANIM_CRATE_INVUN,						// Animation number.
	"INVUN",									// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const CMine(
	ANIM_CRATE_MINE,						// Animation number.
	"MINE",									// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const CRapid(
	ANIM_CRATE_RAPID,						// Animation number.
	"RAPID",									// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const CStealth(
	ANIM_CRATE_STEALTH,					// Animation number.
	"STEALTH2",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const ChronoBox(
	ANIM_CHRONO_BOX,						// Animation number.
	"CHRONBOX",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const GPSBox(
	ANIM_GPS_BOX,							// Animation number.
	"GPSBOX",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const InvulBox(
	ANIM_INVUL_BOX,						// Animation number.
	"INVULBOX",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const ParaBox(
	ANIM_PARA_BOX,							// Animation number.
	"PARABOX",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);
static AnimTypeClass const SonarBox(
	ANIM_SONAR_BOX,						// Animation number.
	"SONARBOX",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);

static AnimTypeClass const CMissile(
	ANIM_CRATE_MISSILE,					// Animation number.
	"MISSILE2",								// Data name of animation.
	48,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	2,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);

static AnimTypeClass const MoveFlash(
	ANIM_MOVE_FLASH,							// Animation number.
	"MOVEFLSH",								// Data name of animation.
	24,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	true,										// Theater specific art imagery?
	true,										// Normalized animation rate?
	true,										// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE								// Follow up animation.
);

static AnimTypeClass const Corpse1(
	ANIM_CORPSE1,							// Animation number.
	"CORPSE1",								// Data name of animation.
	24,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	true,										// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	true,										// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	15,										// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Corpse2(
	ANIM_CORPSE2,							// Animation number.
	"CORPSE2",								// Data name of animation.
	24,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	true,										// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	true,										// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	15,										// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Corpse3(
	ANIM_CORPSE3,							// Animation number.
	"CORPSE3",								// Data name of animation.
	24,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	true,										// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	true,										// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	15,										// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	0,											// Ending frame of loop back.
	-1,										// Number of animation stages.
	0,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Twinkle1(
	ANIM_TWINKLE1,							// Animation number.
	"TWINKLE1",								// Data name of animation.
	8,											// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const Twinkle2(
	ANIM_TWINKLE2,							// Animation number.
	"TWINKLE2",								// Data name of animation.
	8,											// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const Twinkle3(
	ANIM_TWINKLE3,							// Animation number.
	"TWINKLE3",								// Data name of animation.
	8,											// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const Flak(
	ANIM_FLAK,								// Animation number.
	"FLAK",									// Data name of animation.
	8,											// Maximum dimension of animation.
	7,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_NONE,								// Sound effect to play.
	ANIM_NONE,
	17										// Virtual stages
);
static AnimTypeClass const WaterExp1(
	ANIM_WATER_EXP1,						// Animation number.
	"H2O_EXP1",								// Data name of animation.
	64,										// Maximum dimension of animation.
	3,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_SPLASH,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const WaterExp2(
	ANIM_WATER_EXP2,						// Animation number.
	"H2O_EXP2",								// Data name of animation.
	40,										// Maximum dimension of animation.
	3,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_SPLASH,								// Sound effect to play.
	ANIM_NONE
);
static AnimTypeClass const WaterExp3(
	ANIM_WATER_EXP3,						// Animation number.
	"H2O_EXP3",								// Data name of animation.
	32,										// Maximum dimension of animation.
	3,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_SPLASH,								// Sound effect to play.
	ANIM_NONE
);


static AnimTypeClass const MineExp1(
	ANIM_MINE_EXP1,						// Animation number.
	"VEH-HIT2",								// Data name of animation.
	21,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	true,										// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_MINEBLOW,							// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Flag(
	ANIM_FLAG,						// Animation number.
	"FLAGFLY",								// Data name of animation.
	21,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,										// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	-1,										// Number of times the animation loops.
	VOC_NONE,							// Sound effect to play.
	ANIM_NONE
);

static AnimTypeClass const Beacon(
	ANIM_BEACON,							// Animation number.
	"MOVEFLSH",								// Data name of animation.
	21,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	true,									// Theater specific art imagery?
	false,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,										// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	1,										// Number of animation stages.
	-1,										// Number of times the animation loops.
	VOC_NONE,							// Sound effect to play.
	ANIM_NONE,
	-1,										// Virtual stages
	0x100,									// Virtual scale
	NULL,									// Virtual name
	ANIM_BEACON_VIRTUAL			// Virtual anim
);

static AnimTypeClass const BeaconVirtual(
	ANIM_BEACON_VIRTUAL,					// Animation number.
	"BEACON",								// Data name of animation.
	21,										// Maximum dimension of animation.
	0,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	false,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,										// Forms a crater?
	false,									// Sticks to unit in square?
	false,									// Ground level animation?
	false,									// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	1,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	1,										// Number of animation stages.
	-1,										// Number of times the animation loops.
	VOC_NONE,							// Sound effect to play.
	ANIM_NONE
);

#ifdef FIXIT_ANTS
static AnimTypeClass const Ant1Death(
	ANIM_ANT1_DEATH,						// Animation number.
	"ANTDIE",								// Data name of animation.
	28,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	true,										// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	4,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_ANTDIE,								// Sound effect to play.
	ANIM_NONE,
	-1,
	0x100,
	"ANTDIE1"
);

static AnimTypeClass const Ant2Death(
	ANIM_ANT2_DEATH,						// Animation number.
	"ANTDIE",								// Data name of animation.
	28,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	true,										// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	4,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_ANTDIE,								// Sound effect to play.
	ANIM_NONE,
	-1,
	0x100,
	"ANTDIE2"
);

static AnimTypeClass const Ant3Death(
	ANIM_ANT3_DEATH,						// Animation number.
	"ANTDIE",								// Data name of animation.
	28,										// Maximum dimension of animation.
	1,											// Biggest animation stage.
	false,									// Theater specific art imagery?
	true,										// Normalized animation rate?
	false,									// Uses white translucent table?
	false,									// Scorches the ground?
	false,									// Forms a crater?
	false,									// Sticks to unit in square?
	true,										// Ground level animation?
	true,										// Translucent colors in this animation?
	false,									// Is this a flame thrower animation?
	0,											// Damage to apply per tick (fixed point).
	4,											// Delay between frames.
	0,											// Starting frame number.
	0,											// Loop start frame number.
	-1,										// Ending frame of loop back.
	-1,										// Number of animation stages.
	1,											// Number of times the animation loops.
	VOC_ANTDIE,								// Sound effect to play.
	ANIM_NONE,
	-1,
	0x100,
	"ANTDIE3"
);
#endif

/***********************************************************************************************
 * AnimTypeClass::AnimTypeClass -- Constructor for animation types.                            *
 *                                                                                             *
 *    This is the constructor for static objects that elaborate the various animation types    *
 *    allowed in the game. Each animation in the game is of one of these types.                *
 *                                                                                             *
 * INPUT:   see below...                                                                       *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/23/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
AnimTypeClass::AnimTypeClass(
	AnimType anim,
	char const* name,
	int size,
	int biggest,
	bool istheater,
	bool isnormal,
	bool iswhitetrans,
	bool isscorcher,
	bool iscrater,
	bool issticky,
	bool ground,
	bool istrans,
	bool isflame,
	fixed damage,
	int delaytime,
	int start,
	int loopstart,
	int loopend,
	int stages,
	int loops,
	VocType soundid,
	AnimType chainto,
	int virtualstages,
	int scale,
	char const* virtualname,
	AnimType virtualanim) :
ObjectTypeClass(RTTI_ANIMTYPE,
		static_cast<int>(anim),
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
	IsNormalized(isnormal),
	IsGroundLayer(ground),
	IsTranslucent(istrans),
	IsWhiteTrans(iswhitetrans),
	IsFlameThrower(isflame),
	IsScorcher(isscorcher),
	IsCraterForming(iscrater),
	IsSticky(issticky),
	IsTheater(istheater),
	Size(size),
	Biggest(biggest),
	Damage(damage),
	Delay(delaytime),
	Start(start),
	LoopStart(loopstart),
	LoopEnd(loopend),
	Stages(stages),
	Loops(loops),
	Sound(soundid),
	ChainTo(chainto),
	VirtualStages(virtualstages),
	VirtualName(virtualname),
	VirtualAnim(virtualanim)
{
	Scale = (scale / 0x0100) * 1.0f;
	char message[64];
	if (ID == -1) {
		ID = (int)(AnimTypes.size());
		sprintf(message, "Constructed NEW Animation %s with ID: %d .\n", IniName, ID);
	}
	else {
		sprintf(message, "Constructed BUILT-IN Animation %s with ID: %d .\n", IniName, ID);
	}
	AnimTypes.push_back(this);
	WWDebugString(message);
}
/***********************************************************************************************
 * AnimTypeClass::AnimTypeClass -- Constructor for animation types.                            *
 *                                                                                             *
 *    This is the constructor for static objects that elaborate the various animation types    *
 *    allowed in the game. Each animation in the game is of one of these types.                *
 *                                                                                             *
 * INPUT:   see below...                                                                       *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/27/2021 JJ : Created.                                                                 *
 *=============================================================================================*/
	AnimTypeClass::AnimTypeClass(char const* name) :
		AnimTypeClass(ANIM_NONE,
			name,
			0,
			0,
			false,
			false,
			false,
		false,
		false,
		false,
		false,
		false,
		false,
		1.0f,
		1,
		0,
		0,
		0,
		-1,
		0,
		VOC_NONE,
		ANIM_NONE)
{
}

/***********************************************************************************************
 * AnimTypeClass::operator new -- Allocate an animation type object from private pool.         *
 *                                                                                             *
 *    This routine will allocate an animation type class object.                               *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the newly allocated anim type object. If no anim type    *
 *          could be allocated, then NULL is returned.                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/09/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
//void* AnimTypeClass::operator new(size_t t)
//{
//	return(malloc(t));//yes I know this is a dynamic memory allocation - JJ
//}
/*void* AnimTypeClass::operator new(size_t, void* ptr)
{
		char message[64];
		sprintf(message, "NEW.ptr invoked for AnimType %s .\n", ((AnimTypeClass*)ptr)->IniName);
		WWDebugString(message);
		return(ptr);
}*/

/***********************************************************************************************
 * AnimTypeClass::operator delete -- Returns an anim type class object back to the pool.       *
 *                                                                                             *
 *    This will return the anim type class object back to the memory pool from whence it was   *
 *    previously allocated.                                                                    *
 *                                                                                             *
 * INPUT:   pointer  -- Pointer to the anim type class object to return to the memory pool.    *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/09/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
/*void AnimTypeClass::operator delete(void* ptr)
{
	//char message[128];
	//sprintf(message, "ATC.Delete %s with ID: %d - vector size: %d.\n", ((AnimTypeClass*)ptr)->Name(), ((AnimTypeClass*)ptr)->ID, (int)(AnimTypes.size()));
	//WWDebugString(message);
	//ptr == NULL;/*
	for (short x = 0; x < (short)AnimTypes.size(); x++) {
		if ((AnimTypeClass *)ptr == AnimTypes.at(x))
		{	
			
				//AnimTypes.at(x) = NULL;
			//AnimTypes.at(x) = AnimTypes.back();
			//AnimTypes.pop_back();
			if (x >= ANIM_COUNT) {
				std::free(ptr);
				//sprintf(message, "ATC.Delete FREE!");
				//WWDebugString(message);
			}
			break;
		}
	}
	//delete ptr;
	// std::free((AnimTypeClass *)ptr);
	//sprintf(message, "ATC.Deleted. Vector size: %d\n", (int)(AnimTypes.size()));
	//WWDebugString(message);
}*/

AnimTypeClass::~AnimTypeClass(void)
{
	//char message[64];
	//sprintf(message, "AnimTypeClass.Destroy %s with ID: %d.\n", IniName, ID);
	//WWDebugString(message);
	VirtualName = NULL;
}
/***********************************************************************************************
 * AnimTypeClass::Init_Heap -- Initialize the animation type system.                           *
 *                                                                                             *
 *    This routine is called to initialize the animation type class heap. It allocates all     *
 *    known animation types.                                                                   *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/09/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void AnimTypeClass::Init_Heap(void)
{
	/*
	**	These anim type class objects must be allocated in the exact order that they
	**	are specified in the AnimType enumeration. This is necessary because the heap
	**	allocation block index serves double duty as the type number index.
	*/
	
	new AnimTypeClass(FBall1);
	new AnimTypeClass(FireBallFade);
	new AnimTypeClass(Frag1);
	new AnimTypeClass(VehHit1);
	new AnimTypeClass(VehHit2);
	new AnimTypeClass(VehHit3);
	new AnimTypeClass(ArtExp1);
	new AnimTypeClass(Napalm1);
	new AnimTypeClass(Napalm2);
	new AnimTypeClass(Napalm3);
	new AnimTypeClass(SmokePuff);
	new AnimTypeClass(Piff);
	new AnimTypeClass(PiffPiff);
	new AnimTypeClass(Fire3);
	new AnimTypeClass(Fire2);
	new AnimTypeClass(Fire1);
	new AnimTypeClass(Fire4);
	new AnimTypeClass(Gunfire);
	new AnimTypeClass(SmokeM);
	new AnimTypeClass(BurnSmall);
	new AnimTypeClass(BurnMed);
	new AnimTypeClass(BurnBig);
	new AnimTypeClass(OnFireSmall);
	new AnimTypeClass(OnFireMed);
	new AnimTypeClass(OnFireBig);
	new AnimTypeClass(SAMN);
	new AnimTypeClass(SAMNE);
	new AnimTypeClass(SAME);
	new AnimTypeClass(SAMSE);
	new AnimTypeClass(SAMS);
	new AnimTypeClass(SAMSW);
	new AnimTypeClass(SAMW);
	new AnimTypeClass(SAMNW);
	new AnimTypeClass(GUNN);
	new AnimTypeClass(GUNNE);
	new AnimTypeClass(GUNE);
	new AnimTypeClass(GUNSE);
	new AnimTypeClass(GUNS);
	new AnimTypeClass(GUNSW);
	new AnimTypeClass(GUNW);
	new AnimTypeClass(GUNNW);
	new AnimTypeClass(LZSmoke);
	new AnimTypeClass(CDeviator);
	new AnimTypeClass(CDollar);
	new AnimTypeClass(CEarth);
	new AnimTypeClass(CEmpulse);
	new AnimTypeClass(CInvun);
	new AnimTypeClass(CMine);
	new AnimTypeClass(CRapid);
	new AnimTypeClass(CStealth);
	new AnimTypeClass(CMissile);
	new AnimTypeClass(MoveFlash);
	new AnimTypeClass(OilFieldBurn);
	new AnimTypeClass(ElectricDie);
	new AnimTypeClass(Parachute);
	new AnimTypeClass(DogElectricDie);
	new AnimTypeClass(Corpse1);
	new AnimTypeClass(Corpse2);
	new AnimTypeClass(Corpse3);
	new AnimTypeClass(SputDoor);
	new AnimTypeClass(AtomBomb);
	new AnimTypeClass(ChronoBox);
	new AnimTypeClass(GPSBox);
	new AnimTypeClass(InvulBox);
	new AnimTypeClass(ParaBox);
	new AnimTypeClass(SonarBox);
	new AnimTypeClass(Twinkle1);
	new AnimTypeClass(Twinkle2);
	new AnimTypeClass(Twinkle3);
	new AnimTypeClass(Flak);
	new AnimTypeClass(WaterExp1);
	new AnimTypeClass(WaterExp2);
	new AnimTypeClass(WaterExp3);
	new AnimTypeClass(CrateArmor);
	new AnimTypeClass(CrateSpeed);
	new AnimTypeClass(CrateFPower);
	new AnimTypeClass(CrateTQuake);
	new AnimTypeClass(ParaBomb);
	new AnimTypeClass(MineExp1);
	new AnimTypeClass(Flag);
	new AnimTypeClass(Beacon);
#ifdef FIXIT_ANTS
	new AnimTypeClass(Ant1Death);
	new AnimTypeClass(Ant2Death);
	new AnimTypeClass(Ant3Death);
#endif
	new AnimTypeClass(Fire3Virtual);
	new AnimTypeClass(Fire2Virtual);
	new AnimTypeClass(Fire1Virtual);
	new AnimTypeClass(Fire4Virtual);
	new AnimTypeClass(BeaconVirtual);
}

/***********************************************************************************************
 * AnimTypeClass::One_Time -- Performs one time action for animation types.                    *
 *                                                                                             *
 *    This will load the animation shape data. It is called by the game initialization         *
 *    process.                                                                                 *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   This routine should be called ONLY once.                                        *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/02/1994 JLB : Created.                                                                 *
 *   07/18/2021 JJ  : Updated to use a non-static HEAP size                                    *
 *=============================================================================================*/
void AnimTypeClass::One_Time(void)
{
	char message[64];
	sprintf(message, "AnimTypeClass.One_Time executing... - vector size: %d\n", (int)(AnimTypes.size()));
	WWDebugString(message);
	for (short index = 0; index < (short)(AnimTypes.size()); index++) {
		char fullname[_MAX_FNAME+_MAX_EXT];
		
		//AnimTypeClass const& anim = *AnimTypes.at(index);
		AnimTypeClass * anim = AnimTypes.at(index);
		if (!anim->IsTheater) {
			_makepath(fullname, NULL, NULL, anim->Graphic_Name(), ".SHP");

			#ifndef NDEBUG
				RawFileClass file(fullname);
				if (file.Is_Available()) {
					((void const *&)As_Reference((AnimType)index).ImageData) = Load_Alloc_Data(file);
				} else {
					((void const *&)As_Reference((AnimType)index).ImageData) = MFCD::Retrieve(fullname);
				}
			#else
			anim->ImageData = MFCD::Retrieve(fullname);
			//((void const*&)anim.ImageData) = MFCD::Retrieve(fullname);
			#endif
		}
	}
	sprintf(message, "AnimTypeClass.One_Time executed. - vector size: %d\n", (int)(AnimTypes.size()));
	WWDebugString(message);
}

/*void AnimTypeClass::Parse_Graphics(short which)
{
	if (IsTheater)
		return;
	char message[64];
	sprintf(message, "ATC.Parse_Graphics for %s and ID %d executing...\n", Name(), ID);
	WWDebugString(message);
	char fullname[_MAX_FNAME + _MAX_EXT];
	switch(which) {
		case 0 :
			_makepath(fullname, NULL, NULL, Graphic_Name(), ".SHP");
			ImageData = MFCD::Retrieve(fullname);
			break;
		case 1:
			_makepath(fullname, NULL, NULL, Secondary_Graphic_Name(), ".SHP");
			SecondaryImageData = MFCD::Retrieve(fullname);
			break;
		default:
			break;
	}
	sprintf(message, "ATC.Parse_Graphics executed.\n");
	WWDebugString(message);
}*/
/***********************************************************************************************
 * AnimTypeClass::Init -- Load any animation artwork that is theater specific.                 *
 *                                                                                             *
 *    This routine will examine all the animation types and for any that are theater           *
 *    specific, it will fetch a pointer to the artwork appropriate for the theater specified.  *
 *                                                                                             *
 * INPUT:   theater  -- The theater to align the animation artwork with.                       *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   Call this routine when the theater changes.                                     *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.																   *
 *   07/18/2021 JJ  : Updated to use a non-static HEAP size									   *
 *=============================================================================================*/
void AnimTypeClass::Init(TheaterType theater)
{
	if (theater != LastTheater) {
		for (short index = 0; index < (short)AnimTypes.size(); index++) {

			AnimTypeClass const& anim = *AnimTypes.at(index);
			if (anim.IsTheater) {
				char fullname[_MAX_FNAME+_MAX_EXT];	// Fully constructed iconset name.
				if (anim.VirtualName != NULL)
				    _makepath(fullname, NULL, NULL, anim.VirtualName, Theaters[theater].Suffix);
				else
					_makepath(fullname, NULL, NULL, anim.Name(), Theaters[theater].Suffix);
				((void const *&)anim.ImageData) = MFCD::Retrieve(fullname);
			}
		}

		// Set up beacon image data manually since they're new animations only available in the virtual renderer
		((void const *&)As_Reference(ANIM_BEACON_VIRTUAL).ImageData) = As_Reference(ANIM_BEACON).ImageData;
	}
}


/***********************************************************************************************
 * Anim_Name -- Fetches the ASCII name of the animation type specified.                        *
 *                                                                                             *
 *    This will convert the animation type specified into a text name. This name can be used   *
 *    for uniquely identifying the animation.                                                  *
 *                                                                                             *
 * INPUT:   anim  -- The anim type to convert to a text string.                                *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the ASCII string that identifies this animation.         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
/*char const* Anim_Name(AnimType anim)
{
	if (anim == ANIM_NONE) return("");
	AnimTypeClass* atc = AnimTypeClass::As_Pointer(anim);
	if (atc != NULL)
		return(atc->Name());
	return("");
}*/


/***********************************************************************************************
 * AnimTypeClass::As_Reference -- Fetch a reference to the animation type specified.           *
 *                                                                                             *
 *    This routine will convert the animation type specified into a reference to the           *
 *    animation type class object.                                                             *
 *                                                                                             *
 * INPUT:   type  -- The animation type to convert into a reference.                           *
 *                                                                                             *
 * OUTPUT:  Returns with a reference to the animation type class object.                       *
 *                                                                                             *
 * WARNINGS:   Be sure that the animation type specified is legal. If it isn't then the        *
 *             results of this routine are undefined.                                          *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
const AnimTypeClass & AnimTypeClass::As_Reference(AnimType type)
{
	return(*AnimTypeClass::As_Pointer(type));
}

/***********************************************************************************************
 * AnimTypeClass::As_Pointer -- Fetch a pointer to the animation type specified.               *
 *                                                                                             *
 *    This routine will convert the animation type specified into a pointer to the           *
 *    animation type class object.                                                             *
 *                                                                                             *
 * INPUT:   type  -- The animation type to convert into a pointer.                           *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the animation type class object.                       *
 *                                                                                             *
 * WARNINGS:   Be sure that the animation type specified is legal. If it isn't then the        *
 *             results of this routine are undefined.                                          *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/23/2021 JJ : Created.                                                                 *
 *=============================================================================================*/
const AnimTypeClass * AnimTypeClass::As_Pointer(AnimType type)
{
	if (type == ANIM_NONE) { return(NULL); }
	const AnimTypeClass* atc;
	for (short anim = 0; anim < (short)AnimTypes.size(); anim++) {
		atc = AnimTypes.at(anim);
		if (atc->ID == type) {
			return(atc);
		}
	}
	return(NULL);
}

/***********************************************************************************************
 * AnimTypeClass::As_Pointer -- Fetch a pointer to the animation type specified.               *
 *                                                                                             *
 *    This routine will convert the animation type specified into a pointer to the           *
 *    animation type class object.                                                             *
 *                                                                                             *
 * INPUT:   type  -- The animation type to convert into a pointer.                           *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the animation type class object.                       *
 *                                                                                             *
 * WARNINGS:   Be sure that the animation type specified is legal. If it isn't then the        *
 *             results of this routine are undefined.                                          *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/23/2021 JJ : Created.                                                                 *
 *=============================================================================================*/
const AnimTypeClass * AnimTypeClass::As_Pointer(const char * name)
{
	if (name == NULL || !strlen(name)) return(NULL);
	const AnimTypeClass * atc;
	for (short index = 0; index < (short)AnimTypes.size(); index++) {
		atc = AnimTypes.at(index);
		if (stricmp(atc->Name(), name) == 0) {
			return(atc);
		}
	}
	return(NULL);
}

/***********************************************************************************************
 * AnimTypeClass::Anim_From_Name -- Given a name, this finds the corresponding anim type.       *
 *                                                                                             *
 *    This routine will convert the supplied ASCII name into the animation type that it        *
 *    represents.                                                                              *
 *                                                                                             *
 * INPUT:   name  -- Pointer to the ASCII name to convert.                                     *
 *                                                                                             *
 * OUTPUT:  Returns with the animation type that matches the name specified. If no match could *
 *          be found, then ANIM_NONE is returned.                                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *   09/21/2021 JJ  : Modified to use heap and moved to the ADATA.CPP                          *
 *=============================================================================================*/
AnimType AnimTypeClass::As_Type(char const* name)
{
	if (name == NULL) return(ANIM_NONE);
	const AnimTypeClass * atc = AnimTypeClass::As_Pointer(name);
	if (atc != NULL)
		return(atc->Type());
	return(ANIM_NONE);
}

/***********************************************************************************************
 * AnimTypeClass::AnimType_From_Name -- Given a name, this finds the corresponding anim type   *
 *                                      class.												   *
 *                                                                                             *
 *    This routine will convert the supplied ASCII name into the animation type that it        *
 *    represents.                                                                              *
 *                                                                                             *
 * INPUT:   name  -- Pointer to the ASCII name to convert.                                     *
 *                                                                                             *
 * OUTPUT:  Returns with the animation type class that matches the name specified. If no match *
 *          could be found, then NULL is returned.                                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/21/2021 JJ  : Created.                                                                 *
 *=============================================================================================*/
/*AnimTypeClass* AnimType_From_Name(char const* name)
{
	if (name == NULL) return(NULL);

	for (int anim = 0; anim < AnimTypes.Count(); anim++) {
		if (!stricmp(AnimTypes.Ptr(anim)->Name(), name)) {
			return(AnimTypes.Ptr(anim));
		}
	}
	return(NULL);
}*/

/***********************************************************************************************
 * AnimTypeClass::Read_INI -- Fetch the anim type data from the INI database.              *
 *                                                                                             *
 *    Use this routine to fetch override information about this anim type class object       *
 *    from the INI database specified.                                                         *
 *                                                                                             *
 * INPUT:   ini   -- Reference to the INI database to examine.                                 *
 *                                                                                             *
 * OUTPUT:  bool; Was the section for this anim type found and the data extracted?             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/29/2021 JJ : Created.                                                                 *
 *=============================================================================================*/
bool AnimTypeClass::Read_INI(CCINIClass& ini)
{

	if (ObjectTypeClass::Read_INI(ini)) {
		char message[128];
		sprintf(message, "AnimTypeClass.Read_INI parsing %s ...\n", Name());
		WWDebugString(message);
		IsNormalized = ini.Get_Bool(Name(), "Normalized", IsNormalized);
		IsGroundLayer = ini.Get_Bool(Name(), "GroundLayer", IsGroundLayer);
		IsTranslucent = ini.Get_Bool(Name(), "Translucent", IsTranslucent);
		IsWhiteTrans = ini.Get_Bool(Name(), "WhiteTrans", IsWhiteTrans);
		IsFlameThrower = ini.Get_Bool(Name(), "FlameThrower", IsFlameThrower);
		IsScorcher = ini.Get_Bool(Name(), "Scorcher", IsScorcher);
		IsCraterForming = ini.Get_Bool(Name(), "CraterForming", IsCraterForming);
		IsSticky = ini.Get_Bool(Name(), "Sticky", IsSticky);
		IsTheater = ini.Get_Bool(Name(), "Theater", IsTheater);
		Size = ini.Get_Short(Name(), "Size", Size);
		Biggest = ini.Get_Short(Name(), "Biggest", Biggest);
		Damage = ini.Get_Float(Name(), "Damage", Damage);
		Delay = ini.Get_Short(Name(), "Delay", Delay);
		Start = ini.Get_Short(Name(), "Start", Start);
		LoopStart = ini.Get_Short(Name(), "LoopStart", LoopStart);
		LoopEnd = ini.Get_Short(Name(), "LoopEnd", LoopEnd);
		Stages = ini.Get_Short(Name(), "Stages", Stages);
		Loops = ini.Get_Short(Name(), "Loops", Loops);
		Sound = ini.Get_VocType(Name(), "Sound", Sound);
		char buffer[_MAX_FNAME];
		//const AnimTypeClass* ptr = NULL;
		ChainTo = findorcreate(ini, ini.Get_Value(Name(), "ChainTo"), ChainTo);
		/*if (ini.Get_String(Name(), "ChainTo", "", buffer, sizeof(buffer))) {
			Chainto_findorcreate(ini, buffer, ANIM_NONE);
			ptr = AnimTypeClass::As_Pointer(buffer);
			if (ptr)
				ChainTo = ptr->Type();
		}*/
		VirtualStages = ini.Get_Short(Name(), "VirtualStages", VirtualStages);
		//VirtualScale = ini.Get_Float(Name(), "Scale", VirtualScale);
		if (ini.Get_String(Name(), "VirtualName", "", buffer, sizeof(buffer))) {
			if (strlen(buffer) > 0) {
				memcpy(SecondaryGraphicName, buffer, sizeof(buffer));
				VirtualName = SecondaryGraphicName;
			}
		}
		VirtualAnim = findorcreate(ini, ini.Get_Value(Name(), "VirtualAnim"), VirtualAnim);
		/*if (ini.Get_String(Name(), "VirtualAnim", "", buffer, sizeof(buffer))) {
			ptr = AnimTypeClass::As_Pointer(buffer);
			if (ptr)
				VirtualAnim = ptr->Type();
		}*/
		NextAnim = findorcreate(ini, ini.Get_Value(Name(), "NextAnim"), NextAnim);
		sprintf(message, "AnimTypeClass.Read_INI parsed %s .\n", Name());
		WWDebugString(message);
		return(true);
	}
	return(false);
}

void AnimTypeClass::Clear_Heap(void) {
	for (short index = 0; index < (short)AnimTypes.size(); index++) {
		if (index >= ANIM_COUNT)
			std::free(AnimTypes.at(index));
	}
	AnimTypes.clear();
}
using std::string;
char const * AnimTypeClass::to_string(void) const
{
	string out = "";
	out += ("Name=" + string(Name()) + '\n');
	out += ("ID=" + std::to_string(ID) + '\n');
	out += ("Normalized=" + std::to_string(IsNormalized) + '\n');
	out += ("GroundLayer=" + std::to_string(IsGroundLayer) + '\n');
	out += ("Translucent=" + std::to_string(IsTranslucent) + '\n');
	out += ("WhiteTrans=" + std::to_string(IsWhiteTrans) + '\n');
	out += ("FlameThrower=" + std::to_string(IsFlameThrower) + '\n');
	out += ("Scorcher=" + std::to_string(IsScorcher) + '\n');
	out += ("CraterForming=" + std::to_string(IsCraterForming) + '\n');
	out += ("Sticky=" + std::to_string(IsSticky) + '\n');
	out += ("Theater=" + std::to_string(IsTheater) + '\n');
	out += ("Size=" + std::to_string(Size) + '\n');
	out += ("Biggest=" + std::to_string(Biggest) + '\n');
	out += ("Damage=" + std::to_string(Damage) + '\n');
	out += ("Delay=" + std::to_string(Delay) + '\n');
	out += ("Start=" + std::to_string(Start) + '\n');
	out += ("LoopStart=" + std::to_string(LoopStart) + '\n');
	out += ("LoopEnd=" + std::to_string(LoopEnd) + '\n');
	out += ("Stages=" + std::to_string(Stages) + '\n');
	out += ("Loops=" + std::to_string(Loops) + '\n');
	out += ("Sound=" + string(Voc_Name(Sound)) + '\n');
	out += ("ChainTo=" + std::to_string(ChainTo) + '\n');
	//out += ("ChainTo=" + (As_Pointer(ChainTo) ? string(As_Pointer(ChainTo)->Name()) : std::to_string(ChainTo)) + '\n');
	out += ("VirtualStages=" + std::to_string(VirtualStages) + '\n');
	//out += ("VirtualName=" + string(SecondaryGraphicName) + '\n');
	//out += ("VirtualAnim=" + (As_Pointer(VirtualAnim) ? string(As_Pointer(VirtualAnim)->Name()) : std::to_string(VirtualAnim)) + '\n');
	out += ("VirtualAnim=" + std::to_string(VirtualAnim) + '\n');
	//WWDebugString(strdup(out.c_str()));
	out += ObjectTypeClass::to_string();
	//WWDebugString(strdup(out.c_str()));
	return out.c_str();
}

const AnimTypeClass* AnimTypeClass::findorcreate(CCINIClass& ini, const char* value, const AnimTypeClass* defptr)
{
	if (value == NULL || &ini == NULL || strlen(value) < 2)
		return defptr;
	if (strcmpi(value, "none") == 0)
		return NULL;
	if ((defptr != NULL && stricmp(defptr->Name(), value) != 0) || defptr == NULL)//if we are changing it
	{
		const AnimTypeClass* ptr = As_Pointer(value);
		if (ptr == NULL)//did we find this new weapon that is referenced in the ini?
		{
			if (ini.Section_Present(value))//does this new weapon exist in the ini 
			{
				AnimTypeClass* newptr = new AnimTypeClass(value);
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
AnimType AnimTypeClass::findorcreate(CCINIClass& ini, const char* value, AnimType defvalue)
{
	if (value == NULL || strlen(value) < 2 || &ini == NULL)//send me something proper
		return defvalue;
	if (strcmpi(value, "none") == 0) //this inbound value is set to none, we're clearing this
		return ANIM_NONE;
	const AnimTypeClass* ptr = As_Pointer(value);
	if (ptr != NULL) //if it exists, then send it
		return static_cast<AnimType>(ptr->ID);
	if (ini.Section_Present(value)) {
		AnimTypeClass* newptr = new AnimTypeClass(value);
		newptr->Read_INI(ini);
		return static_cast<AnimType>(newptr->ID);
	}
	return defvalue;
}

