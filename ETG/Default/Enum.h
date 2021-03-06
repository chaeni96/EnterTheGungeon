#pragma once

enum DIRECTION {DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN ,DIR_END};

enum OBJID {OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_PET, OBJ_BOSS, OBJ_MONSTER_BULLET, OBJ_MOUSE, OBJ_ITEM,OBJ_WEAPON, OBJ_MONSTER1_BULLET, OBJ_BUTTON,OBJ_HP,OBJ_INVEN, OBJ_END };

enum TYPE { TYPE_WEAPON_GUN, TYPE_WEAPON_COMANDO, TYPE_WEAPON_SHARK,  TYPE_WEAPON_LAMP,  TYPE_END };


enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_HIDDEN, SC_ENDING, SC_END };

enum RENDERID { RENDER_BACKGROUND, RENDER_ITEM, RENDER_GAMEOBJECT, RENDER_UI, RENDER_SCENE, RENDER_END };

// 최대 32개 채널까지 동시 재생이 가능
enum CHANNELID { SOUND_EFFECT, SOUND_BGM, SOUND_PLAYER, SOUND_MONSTER, SC_BULLET, MAXCHANNEL };