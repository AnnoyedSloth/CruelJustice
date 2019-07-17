// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(CruelJustice, Log, All);

#define CJLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define CJLOG_S(Verbosity) UE_LOG(CruelJustice, Verbosity, TEXT("%s"), *CJLOG_CALLINFO)
#define CJLOG(Verbosity, Format, ...) UE_LOG(CruelJustice, Verbosity, TEXT("%s%s"), *CJLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define CJCHECK(Expr, ...) { if(!(Expr)) {CJLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}
