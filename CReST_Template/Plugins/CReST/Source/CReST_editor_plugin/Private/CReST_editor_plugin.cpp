// Copyright Epic Games, Inc. All Rights Reserved.

#include "CReST_editor_plugin.h"
#include "CReST_editor_pluginStyle.h"
#include "CReST_editor_pluginCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include <Runtime/Engine/Classes/Engine/Selection.h>
#include <string>
#include "Math/UnrealMathUtility.h"
#include <Editor/UnrealEd/Public/EditorLevelUtils.h>

static const FName CReST_editor_pluginTabName("CReST_editor_plugin");

#define LOCTEXT_NAMESPACE "FCReST_editor_pluginModule"

void FCReST_editor_pluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	// THIS PART BROKE STUFF BUT REMOVING IT DOES NOT SEEM TO CAUSE FURTHER PROBLEMS
	//FCReST_editor_pluginStyle::Initialize();
	//FCReST_editor_pluginStyle::ReloadTextures();

	FCReST_editor_pluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCReST_editor_pluginCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FCReST_editor_pluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCReST_editor_pluginModule::RegisterMenus));
}

void FCReST_editor_pluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	//FCReST_editor_pluginStyle::Shutdown();

	//FCReST_editor_pluginCommands::Unregister();
}

void FCReST_editor_pluginModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	/*
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FCReST_editor_pluginModule::PluginButtonClicked()")),
							FText::FromString(TEXT("CReST_editor_plugin.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	*/


	

	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AActor* Actor = static_cast<AActor*>(*It);
		if (Actor) {
			FText SomeText = FText::FromName(Actor->GetFName());
			FString SomeString = SomeText.ToString();
			UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *SomeString);
			if (!Actor->Tags.Contains("CReST_selection"))
			{
				Actor->Modify();
				Actor->Tags.Add("CReST_selection");
				if (!Actor->GetRootComponent()->ComponentHasTag("CReST_selection")) {
					FString SeedString = "abcdefghijklmnopqrstuvwxyz";
					FString S = "";

					for (int i = 0; i < 6; i++) {  // strings of 6 characters
						int N = FMath::RandRange(0, SeedString.Len() - 2);
						S += SeedString[N];
					}
					Actor->GetRootComponent()->ComponentTags.Add("CReST_selection");
					Actor->GetRootComponent()->ComponentTags.Add(FName(S));
				}
			}
		}
	}


}

void FCReST_editor_pluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCReST_editor_pluginCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCReST_editor_pluginCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCReST_editor_pluginModule, CReST_editor_plugin)