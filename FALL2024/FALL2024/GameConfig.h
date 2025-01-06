#pragma once

#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <string>

#define LEFT_POSITION -0.75f
#define RIGHT_POSITION 0.75f
#define LOSE_FORCE 250.0f
#define MAX_HEALTH 3
#define DEFAULT_MOVESPEED 5.0f

const Vector3 DEFAULT_VISUAL_SCALE = Vector3(3.0f, 4.0f, 1.0f);
const Vector3 DEFAULT_VISUAL_POSITION = Vector3(-0.5f, -0.1f, 0.0f);

#pragma region Sounds

const std::string BGM_SOUND = "Street Fighter Alpha Ryu Theme.mp3";
const std::string URGH_SOUND = "ryuken-uggh-101soundboards.mp3";
const std::string HITCONFIRM_SOUND = "hitconfirm.wav";
const std::string YOUWIN_SOUND = "you-win-street-fighter-101soundboards.mp3";
const std::string HIT_SOUND = "hit.wav";
const std::string ATTACK_SOUND = "ryu_attack_sound.mp3";
const std::string GUARD_SOUND = "guard-101soundboards.mp3";
const std::string HADOKEN_SOUND = "ryuken-hadooken-101soundboards.mp3";
const std::string FIGHT_SOUND = "fight-101soundboards.mp3";
const std::string READY_SOUND = "ready-101soundboards.mp3";
const std::string RESULT_SOUND = "result.wav";

#pragma endregion


#endif // !GAMECONFIG_H