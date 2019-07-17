// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Axeman.h"
#include "CJEnemyState.h"
#include "ConstructorHelpers.h"

ACJEnemy_Axeman::ACJEnemy_Axeman()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_MESH(TEXT("/Game/ParagonNarbash/Characters/Heroes/Narbash/Meshes/Narbash.Narbash"));
	CJCHECK(SK_MESH.Succeeded());
	mesh->SetSkeletalMesh(SK_MESH.Object);


}