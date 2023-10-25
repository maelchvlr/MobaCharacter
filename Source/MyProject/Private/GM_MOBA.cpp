// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MOBA.h"
#include "GS_MOBA.h"
#include "HUD_MOBA.h"
#include "PC_MOBA.h"
#include "PS_MOBA.h"
#include "MOBA_CHARACTER.h"

AGM_MOBA::AGM_MOBA() : Super()
{
    PlayerControllerClass = APC_MOBA::StaticClass();
    GameStateClass = AGS_MOBA::StaticClass();
    HUDClass = AHUD_MOBA::StaticClass();
    PlayerStateClass = APS_MOBA::StaticClass();
    DefaultPawnClass = AMOBA_CHARACTER::StaticClass();
}

