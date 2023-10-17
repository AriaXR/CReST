// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CReST_editor_pluginStyle.h"

class FCReST_editor_pluginCommands : public TCommands<FCReST_editor_pluginCommands>
{
public:

	FCReST_editor_pluginCommands()
		: TCommands<FCReST_editor_pluginCommands>(TEXT("CReST_editor_plugin"), NSLOCTEXT("Contexts", "CReST_editor_plugin", "CReST_editor_plugin Plugin"), NAME_None, FCReST_editor_pluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
