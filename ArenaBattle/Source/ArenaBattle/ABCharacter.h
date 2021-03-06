// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

UCLASS()
class ARENABATTLE_API AABCharacter : public ACharacter // APawn 클래스를 상속받고 있다. Capsule, SkeletalMesh, CharacterMovement 컴포넌트를 사용해서 움직임 관리: FloatingMovement와 구분됨
														// Floating Movement에 비해 CharacterMovement는 중력을 반영한 움직임을 제공한다.
														// 다양한 움직임을 설정할 수 있다. 걷기, 기어가기, 날아가기, 수영 등의 이동 모드 설정이 가능. 움직임에 대한 더 많은 정보를 전달한다.
														// 멀티 플레이 네트워크 환경에서 캐릭터들의 움직임을 자동으로 동기화한다.
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EControlMode {
		GTA,
		DIABLO
	};

	void SetControlMode(EControlMode NewControlMode);
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove = FVector::ZeroVector;

	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool CanSetWeapon(); // 현재 무기가 없는지, 즉 무기를 얻었을 때 착용할 수 있는지 상태 확인
	void SetWeapon(class AABWeapon* NewWeapon); // 무기 장착 로직

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AABWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UABCharacterStatComponent* CharacterStat;

	//UPROPERTY(VisibleAnywhere, Category = Weapon) // 무기 메쉬를 직접 설정할 때
	//USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = UI) // ~.Build.cs에서 UMG 모듈을 추가해줘야 사용할 수 있다.(언리얼 모듈은 C#으로 제작되었다)
	class UWidgetComponent* HPBarWidget;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	void ViewChange();
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UABAnimInstance* ABAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;
};
