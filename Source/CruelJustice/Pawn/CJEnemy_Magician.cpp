// Fill out your copyright notice in the Description page of Project Settings.

#include "CJEnemy_Magician.h"

ACJEnemy_Magician::ACJEnemy_Magician()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_MESH(TEXT("/Game/ParagonFey/Characters/Heroes/Fey/Meshes/Fey_GDC.Fey_GDC"));
	CJCHECK(SK_MESH.Succeeded());
	mesh->SetSkeletalMesh(SK_MESH.Object);


}


