// Fill out your copyright notice in the Description page of Project Settings.


#include "TRMLib.h"

FString UTRMLib::EMoveStateToString(EMoveState value)
{
	switch (value)
	{
	case Walking: return "Walking";
	case Running: return "Running";
	case Crouching: return "Crouching";
	case CrouchRunning: return "CrouchRunning";
	default: return "unknown";
	}
}
