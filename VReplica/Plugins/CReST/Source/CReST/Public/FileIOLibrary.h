// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileIOLibrary.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CREST_API UFileIOLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FileIO")
	FString participantSavePath;

	UFUNCTION(BlueprintCallable, Category = "FileIO")
	int GetNewParticipantIndex();

	UFUNCTION(BlueprintCallable, Category = "FileIO")
	void WriteToFile(FString FileName, FString content);

	UFUNCTION(BlueprintCallable, Category = "FileIO")
	int GetInProgressCounter();

	UFUNCTION(BlueprintCallable, Category = "FileIO")
	int SetActiveDirectoryToPrevious();

	UFUNCTION(BlueprintCallable, Category = "FileIO")
	bool WriteStringToPath(FString FileName, FString content);

	UFUNCTION(BlueprintCallable, Category = "FileIO")
	FString ReadStringFromPath(FString FileName);
	
};
