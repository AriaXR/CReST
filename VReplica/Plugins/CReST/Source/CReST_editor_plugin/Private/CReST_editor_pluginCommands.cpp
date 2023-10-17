// Copyright Epic Games, Inc. All Rights Reserved.

#include "CReST_editor_pluginCommands.h"

#define LOCTEXT_NAMESPACE "FCReST_editor_pluginModule"

void FCReST_editor_pluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Tag", "Tag Selected Actors/Components", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
