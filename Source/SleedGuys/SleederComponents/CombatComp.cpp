// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComp.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "SleedGuys/Weapon/BaseWeapon.h"
#include "SleedGuys/Enums/CharacterEnums.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Net/UnrealNetwork.h"

UCombatComp::UCombatComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComp::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComp, EquippedWeapon);
}

void UCombatComp::EquipWeapon(ABaseWeapon* WeaponToEquip)
{
	if (Character == nullptr || WeaponToEquip == nullptr) return;

	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket"));
	if (HandSocket)
	{
		HandSocket->AttachActor(EquippedWeapon, Character->GetMesh());
	}
	EquippedWeapon->SetOwner(Character); // owner is replicated on its own
}
