#pragma once
#include "Entity.h"
#include "LoopbackPacketSender.h"
#include "TextHolder.h"
class Minecraft {
private:
	char pad_0x0000[0x58];  //0x0000
public:
	double* timer;       //0x58
	double* otherTimer;  //0x060

	void setTimerSpeed(float tps) {
		*this->timer = tps;
		*this->otherTimer = tps;
	}
};
class LevelRenderer {
};
class MinecraftGame {
private:
	char pad_0x0[0xD8];
public:
	bool canUseKeys;
public:
	const bool canUseKeybinds() {
		return canUseKeys;
	};
};
class GuiData {

private:
	char pad_0x0000[0x1C];  //0x0000
public:
	union {
		struct {
			float widthReal;   //0x0030
			float heightReal;  //0x0034
		};
		Vec2 windowSizeReal;  //0x0030
	};

	float widthReal2;   //0x0038
	float heightReal2;  //0x003C
	union {
		struct {
			float widthGame;   //0x0040
			float heightGame;  //0x0044
		};
		Vec2 windowSize;  //0x0040
	};
public:
	void displayClientMessageVA(const char* fmt, va_list lis);

	void displayClientMessageF(const char* fmt, ...);
	void displayClientMessageNoSendF(const char* fmt, ...);
	void displayClientMessage(std::string* a2);
};
class ClientInstance{
private:
	char pad_0x4[0x6C];
public:
	MinecraftGame* minecraftGame;  
	Minecraft* minecraft;      
private:
	char pad_74[0x4];
public:
	LevelRenderer* levelRenderer;  // 0x7c
private:
	char pad_7c[0x4];
public:
	LoopbackPacketSender* loopbackPacketSender;  // 0x84
public:
	glmatrixf* getRefDef() {
		return reinterpret_cast<glmatrixf*>((uintptr_t)(this) + 0x1D4);
	};
	Vec2* getMousePos() {
		return reinterpret_cast<Vec2*>((uintptr_t)(this) + 0x470);
	}
	Vec2 getFov() {
		Vec2 fov;
		fov.x = *reinterpret_cast<float*>((uintptr_t)(this) + 0x354);
		fov.y = *reinterpret_cast<float*>((uintptr_t)(this) + 0x368);
		return fov;
	}
	GuiData* getGuiData() {
		return (GuiData*)*reinterpret_cast<__int32*>(reinterpret_cast<GuiData*>(reinterpret_cast<__int32>(this) + 0x4C8));
	};
private:
	virtual void function_0(void); //0
	virtual void function_1(void); //1
	virtual void function_2(void); //2
	virtual void function_3(void); //3
	virtual void function_4(void); //4
	virtual void function_5(void); //5
	virtual void function_6(void); //6
	virtual void function_7(void); //7
	virtual void function_8(void); //8
	virtual void function_9(void); //9
	virtual void function_10(void); //10
	virtual void function_11(void); //11
	virtual void function_12(void); //12
	virtual void function_13(void); //13
	virtual void function_14(void); //14
	virtual void function_15(void); //15
	virtual void function_16(void); //16
	virtual void function_17(void); //17
	virtual void function_18(void); //18
	virtual void function_19(void); //19
	virtual void function_20(void); //20
	virtual void function_21(void); //21
	virtual void function_22(void); //22
	virtual void function_23(void); //23
	virtual void function_24(void); //24
	virtual void function_25(void); //25
	virtual void function_26(void); //26
	virtual void function_27(void);  //27
	virtual void function_28(void); //28
	virtual void function_29(void); //29
public:
	virtual Localplayer* getCILocalPlayer(void); //30
private:
	virtual void function_31(void); //31
	virtual void function_32(void); //32
	virtual void function_33(void); //33
	virtual void function_34(void); //34
	virtual void function_35(void); //35
	virtual void function_36(void); //36
	virtual void function_37(void); //37
	virtual void function_38(void); //38
	virtual void function_39(void); //39
	virtual void function_40(void); //40
};

