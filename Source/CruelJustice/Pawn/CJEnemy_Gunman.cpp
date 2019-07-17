// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Gunman.h"

ACJEnemy_Gunman::ACJEnemy_Gunman()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_MESH(TEXT("/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/TwinBlast.TwinBlast"));
	CJCHECK(SK_MESH.Succeeded());
	mesh->SetSkeletalMesh(SK_MESH.Object);

}


