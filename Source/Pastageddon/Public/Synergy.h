// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Synergy.generated.h"

UENUM(BlueprintType)
enum class EIngredientType : uint8
{
	Aglio UMETA(DisplayName = "Aglio"),
	Basilico UMETA(DisplayName = "Basilico"),
	Carne UMETA(DisplayName = "Carne"),
	Carota UMETA(DisplayName = "Carota"),
	Cipolla UMETA(DisplayName = "Cipolla"),
	Cozze UMETA(DisplayName = "Cozze"),
	Parmigiano UMETA(DisplayName = "Parmigiano"),
	Funghi UMETA(DisplayName = "Funghi"),
	Gamberi UMETA(DisplayName = "Gamberi"),
	Gorgonzola UMETA(DisplayName = "Gorgonzola"),
	Limone UMETA(DisplayName = "Limone"),
	Melanzane UMETA(DisplayName = "Melanzane"),
	Noci UMETA(DisplayName = "Noci"),
	Olive UMETA(DisplayName = "Olive"),
	Patate UMETA(DisplayName = "Patate"),
	Pecorino UMETA(DisplayName = "Pecorino"),
	Pepe UMETA(DisplayName = "Pepe"),
	Peperoncino UMETA(DisplayName = "Peperoncino"),
	Pinoli UMETA(DisplayName = "Pinoli"),
	Pomodoro UMETA(DisplayName = "Pomodoro"),
	Prezzemolo UMETA(DisplayName = "Prezzemolo"),
	Sarde UMETA(DisplayName = "Sarde"),
	Vongole UMETA(DisplayName = "Vongole"),
	Uova UMETA(DisplayName = "Uova"),
	Zucchine UMETA(DisplayName = "Zucchine")
};

USTRUCT(BlueprintType)
struct FIngredientSynergyRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Synergy")
	FName IngredientA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Synergy")
	FName IngredientB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Synergy")
	int32 Score;
};

/**
 * 
 */
UCLASS()
class USynergy : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Synergy")
	static int32 CalculateSynergyScore(
		const TArray<EIngredientType>& SelectedIngredients,
		const UDataTable* SynergyTable
	);

private:
	static int32 GetPairScoreByName(
		const FName A,
		const FName B,
		const UDataTable* SynergyTable
	);

	static FName EnumToName(EIngredientType Ingredient);
};
