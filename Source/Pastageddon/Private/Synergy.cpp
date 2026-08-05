// Fill out your copyright notice in the Description page of Project Settings.


#include "Synergy.h"

FName USynergy::EnumToName(EIngredientType Ingredient)
{
	const UEnum* EnumObj = StaticEnum<EIngredientType>();
	if (!EnumObj)
	{
		return NAME_None;
	}

	return FName(*EnumObj->GetNameStringByValue((int64)Ingredient));
}

int32 USynergy::GetPairScoreByName(
	const FName A,
	const FName B,
	const UDataTable* SynergyTable)
{
	if (!SynergyTable)
	{
		return 0;
	}

	const TArray<FName> RowNames = SynergyTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		const FIngredientSynergyRow* Row =
			SynergyTable->FindRow<FIngredientSynergyRow>(RowName, TEXT("Lookup"));

		if (!Row)
		{
			continue;
		}

		if ((Row->IngredientA == A && Row->IngredientB == B) ||
			(Row->IngredientA == B && Row->IngredientB == A))
		{
			return Row->Score;
		}
	}

	return 0;
}

int32 USynergy::CalculateSynergyScore(
	const TArray<EIngredientType>& SelectedIngredients,
	const UDataTable* SynergyTable)
{
	if (!SynergyTable || SelectedIngredients.Num() < 2)
	{
		return 0;
	}

	TArray<FName> Names;
	Names.Reserve(SelectedIngredients.Num());

	for (EIngredientType Ingredient : SelectedIngredients)
	{
		Names.Add(EnumToName(Ingredient));
	}

	int32 TotalScore = 0;

	for (int32 i = 0; i < Names.Num(); ++i)
	{
		for (int32 j = i + 1; j < Names.Num(); ++j)
		{
			TotalScore += GetPairScoreByName(Names[i], Names[j], SynergyTable);
		}
	}

	return TotalScore;
}