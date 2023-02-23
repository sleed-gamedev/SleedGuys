// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SleedGuys/Enums/CharacterEnums.h"
#include "SleedCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ABaseWeapon;
class UCombatComp;
class ASleedPlayerController;

UCLASS()
class SLEEDGUYS_API ASleedCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASleedCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

	/* 
	*	Callbacks for input 
	*/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void EquipButtonPressed();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* SleedContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EquipAction;

private:
	// Controller
	//
	//

	ASleedPlayerController* SleedPlayerController;

	// Camera
	//
	//
	UPROPERTY(EditAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	// Jump Logic
	//
	//
	UPROPERTY(EditAnywhere, Category = "Jump")
	float firstJumpHeight = 420.f;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float secondJumpHeight = 600.f;

	UPROPERTY(Replicated)
	bool bShouldDoubleJump;

	// Weapon Logic
	//
	//
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_OverlappingWeapon)
	ABaseWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(ABaseWeapon* LastWeapon);

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	// Combat Logic
	//
	//
	UPROPERTY(VisibleAnywhere)
	UCombatComp* Combat;

	// Character Attributes
	//
	//
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, EditAnywhere, Category = "Player Stats")
	float Health = 100.f;

	UFUNCTION()
	void OnRep_Health();

public:
	// Place for Getters/Setters only
	//
	//
	void SetOverlappingWeapon(ABaseWeapon* Weapon);
	FORCEINLINE bool getShouldDoubleJump() { return this->bShouldDoubleJump; }
	bool IsWeaponEquipped();

};
