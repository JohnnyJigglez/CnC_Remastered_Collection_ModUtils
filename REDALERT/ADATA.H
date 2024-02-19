
#ifndef ADATA_H
#define ADATA_H
#include "TYPE.H"
#include "DEFINES.H"


/****************************************************************************
**	All the animation objects are controlled by this class. It holds the static
**	data associated with each animation type.
*/
class AnimTypeClass : public ObjectTypeClass
{
public:

	/*
	**	If this animation should run at a constant apparent rate regardless
	**	of game speed setting, then this flag will be set to true.
	*/
	unsigned IsNormalized:1;

	/*
	**	If this animation should be rendered and sorted with the other ground
	**	units, then this flag is true. Typical of this would be fire and other
	**	low altitude animation effects.
	*/
	unsigned IsGroundLayer : 1;

	/*
	**	If this animation should be rendered in a translucent fashion, this flag
	**	will be true. Translucent colors are some of the reds and some of the
	**	greys. Typically, smoke and some fire effects have this flag set.
	*/
	//bool IsTranslucent : 1;
	unsigned IsTranslucent : 1;

	/*
	**	If this animation uses the white translucent table, then this flag
	**	will be true.
	*/
	//bool IsWhiteTrans : 1;
	unsigned IsWhiteTrans : 1;

	/*
	**	If this is the special flame thrower animation, then custom affects
	**	occur as it is playing. Specifically, scorch marks and little fire
	**	pieces appear as the flame jets forth.
	*/
	//bool IsFlameThrower : 1;
	unsigned IsFlameThrower : 1;

	/*
	**	Some animations leave a scorch mark behind. Napalm and other flame
	**	type explosions are typical of this type.
	*/
	//bool IsScorcher : 1;
	unsigned IsScorcher : 1;

	/*
	**	Some explosions are of such violence that they leave craters behind.
	**	This flag will be true for those types.
	*/
	//bool IsCraterForming : 1;
	unsigned IsCraterForming : 1;

	/*
	**	If this animation should attach itself to any unit that is in the same
	**	location as itself, then this flag will be true. Most vehicle impact
	**	explosions are of this type.
	*/
	//bool IsSticky : 1;
	unsigned IsSticky : 1;

	/*
	**	If this animation is theater specific, then this flag will be
	**	set to true. Most animations are not theater specific.
	*/
	//bool IsTheater : 1;
	unsigned IsTheater : 1;
	/*
	**	This is the type number for this animation kind. It can be used as
	**	a unique identifier for animation types.
	*/
	//AnimType Type;

	/*
	**	This specified the maximum dimension of the shape (edge to edge). This dimension
	**	is used to build the appropriate cell refresh list. Keep this value as small
	**	as possible to ensure maximum performance. This is especially critical, since
	**	animations always cause the cells under them to be redrawn every frame.
	*/
	//short Size;
	int Size;

	/*
	**	This is the frame that the animation is biggest. The biggest frame of animation
	**	will hide any changes to underlying ground (e.g., craters) that the animation
	**	causes, so these effects are delayed until this frame is reached. The end result
	**	is to prevent the player from seeing craters "pop" into existence.
	*/
	//short Biggest;
	int Biggest;

	/*
	**	Some animations (when attached to another object) damage the object it
	**	is in contact with. Fire is a good example of this. This value is a
	**	fixed point number of the damage that is applied to the attached object
	**	every game tick. The damage is expressed as damage points per game frame.
	**	Because it is a fixed point fraction, the damage can be very slight.
	**
	*/
	fixed Damage;
	//float Damage;

	/*
	**	Simple animation delay value between advancing of frames. This can
	**	be overridden by the control list.
	*/
	//short Delay;
	int Delay;

	/*
	**	The starting frame number for each animation sequence. Usually this is
	**	zero, but can sometimes be different if this animation is a sub sequence
	**	of a larger animation file.
	*/
	//short Start;
	int Start;

	/*
	**	Looping animations might start at a different frame than the initial one.
	**	This is true for smoke effects that have a startup sequence followed by a
	**	continuous looping sequence.
	*/
	//short LoopStart;
	int LoopStart;

	/*
	**	For looping animations, this is the frame that will end all the middle loops
	**	of the animation. The last loop of the animation will proceed until the Stages
	**	has been fully completed.
	*/
	//short LoopEnd;
	int LoopEnd;
	/*
	**	The number of stages that this animation sequence will progress through
	**	before it loops or ends.
	*/
	//short Stages;
	int Stages;

	/*
	**	This is the normal loop count for this animation. Usually this is one, but
	**	for some animations, it may be larger.
	*/
	int Loops;

	short Width;
	short Height;

	/*
	**	This is the sound effect to play when this animation starts. Usually, this
	**	applies to explosion animations.
	*/
	VocType Sound;
	char SoundName[16];

	/*
	**	If the animation is to launch into another animation, then
	**	the secondary animation will be defined here in ID;
	*/
	AnimType ChainTo;

	/*
	**	If this is a directional weapon firing animation let us declare here the next animation in the list a weapon will need of anims.
	*/
	AnimType NextAnim;

	/*
	**	The number of virtual animation stages. Keeps the animation alive longer for the purpose
	**  of 4K rendering, but is ignored by legacy rendering.
	*/
	//short VirtualStages;
	int VirtualStages;

	/*
	**	The scale of the virtual animation. Allows for higher-resolution art to appear larger.
	*/
	//float VirtualScale;

	/*
	**	The shape name to used for 4K virtual rendering, overrides the INI name
	*/
	char const * VirtualName;

	/*
	**	The Animation ID to use specifically for virtual rendering (implies this animation only for legacy).
	*/
	AnimType VirtualAnim;

	//---------------------------------------------------------------------------
	AnimTypeClass(NoInitClass const& x) : ObjectTypeClass(x) {}
	AnimTypeClass(AnimType anim,
		char const* name,
		int size,
		int biggest,
		bool istheater,
		bool isnormal,
		bool iswhite,
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
		VocType sound,
		AnimType chainto,
		int virtualstages = -1,
		int scale = 0x0100,
		char const* virtualname = NULL,
		AnimType virtualanim = ANIM_NONE);
	AnimTypeClass(char const* name);
	~AnimTypeClass(void);
	static void Init_Heap(void);
	static void Clear_Heap(void);
	static void* operator new(size_t t) { return std::malloc(t); }
	//static void* operator new(size_t, void* ptr);
	//static void operator delete(void* ptr);

	static const AnimTypeClass& As_Reference(AnimType type);
	static const AnimTypeClass* As_Pointer(AnimType type);
	static const AnimTypeClass* As_Pointer(const char* name);
	//static AnimTypeClass * As_Pointer(int index);
	static AnimType As_Type(const char* name);
	AnimType Type(void) const { return (static_cast<AnimType>(ID)); }
	static void Init(TheaterType theater);
	static void One_Time(void);
	//void Parse_Graphics(short which=0);
	virtual bool Create_And_Place(CELL, HousesType = HOUSE_NONE) const { return false; };
	virtual ObjectClass* Create_One_Of(HouseClass*) const { return 0; };
	virtual bool Read_INI(CCINIClass& ini);
	virtual char const* to_string(void) const;
	static const AnimTypeClass* findorcreate(CCINIClass& ini, const char* value, const AnimTypeClass* defptr = NULL);
	static AnimType findorcreate(CCINIClass& ini, const char* value, AnimType defvalue = ANIM_NONE);
};
#pragma once
#endif
