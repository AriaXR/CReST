// Fill out your copyright notice in the Description page of Project Settings.


#include "FileIOLibrary.h"
#include "HAL/FileManagerGeneric.h"
#include "GenericPlatform/GenericPlatformFile.h"

int UFileIOLibrary::GetNewParticipantIndex()
{
    TArray<FString> FileNames;
    FFileManagerGeneric FileMgr;
    FileMgr.SetSandboxEnabled(true);// don't ask why, I don't know :P
    FString search_path(FPaths::Combine(*FPaths::ProjectDir(), TEXT("Data"), TEXT("")));

    /*
    FileMgr.FindFiles(FileNames, *search_path,
        false,  // to skip files
        true); // to list directories
    */
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    

    FFileManagerGeneric::Get().FindFilesRecursive(FileNames, *search_path, TEXT("*"), false, true, true);


    participantSavePath = FPaths::Combine(*FPaths::ProjectDir(), TEXT("Data"), FString::FromInt(FileNames.Num()));

    PlatformFile.CreateDirectory(*participantSavePath);
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FPaths::Combine(*FPaths::ProjectDir(), TEXT("Data"), FString::FromInt(FileNames.Num())));


    return FileNames.Num();
}


void UFileIOLibrary::WriteToFile(FString FileName, FString content)
{
    FFileHelper::SaveStringToFile(content, *(participantSavePath+"/"+ FileName), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

int UFileIOLibrary::GetInProgressCounter()
{
    TArray<FString> FileNames;
    FFileManagerGeneric FileMgr;
    FileMgr.SetSandboxEnabled(true);// don't ask why, I don't know :P
    FString search_path(FPaths::Combine(*FPaths::ProjectDir(), TEXT("Data"), TEXT("")));

    /*
    FileMgr.FindFiles(FileNames, *search_path,
        false,  // to skip files
        true); // to list directories
    */
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();


    FFileManagerGeneric::Get().FindFilesRecursive(FileNames, *search_path, TEXT("*"), false, true, true);

    FString previousPath = FPaths::Combine(*FPaths::ProjectDir(), TEXT("Data"), FString::FromInt(FileNames.Num()-1));

    FString content = "";
    FFileHelper::LoadFileToString(content, *(previousPath + "/progress.txt"));

    FString left;
    FString right;

    content.Split("\n", &left, &right, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

    
    return FCString::Atoi(*right);
}

int UFileIOLibrary::SetActiveDirectoryToPrevious()
{
    TArray<FString> FileNames;
    FFileManagerGeneric FileMgr;
    FileMgr.SetSandboxEnabled(true);// don't ask why, I don't know :P
    FString search_path(FPaths::Combine(*FPaths::ProjectDir(), TEXT("Data"), TEXT("")));

    /*
    FileMgr.FindFiles(FileNames, *search_path,
        false,  // to skip files
        true); // to list directories
    */
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();


    FFileManagerGeneric::Get().FindFilesRecursive(FileNames, *search_path, TEXT("*"), false, true, true);

    participantSavePath = FPaths::Combine(*FPaths::ProjectDir(), TEXT("Data"), FString::FromInt(FileNames.Num() - 1));

    return FileNames.Num() - 1;
}

bool UFileIOLibrary::WriteStringToPath(FString FileName, FString content)
{

    return FFileHelper::SaveStringToFile(content, *FileName);
}

FString UFileIOLibrary::ReadStringFromPath(FString FileName)
{
    FString content = "";
    FFileHelper::LoadFileToString(content, *FileName);

    return content;
}
