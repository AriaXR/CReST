// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"
#include "WebSocketGameInstance.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class CREST_API UWebSocketGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void MessageReceived(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent)
	void ConnectionError();

	UFUNCTION(BlueprintCallable, Category = "WebSockets")
	FString GetMessage();

	UFUNCTION(BlueprintCallable, Category = "WebSockets")
	float DecodeToFloat(uint8 a, uint8 b, uint8 c, uint8 d);

	UFUNCTION(BlueprintCallable, Category = "WebSockets")
	void StartConnection(FString HostName);
	UFUNCTION(BlueprintCallable, Category = "WebSockets")
	void SendMessage(FString Message);
	virtual void Shutdown() override;
	TSharedPtr<IWebSocket> WebSocket;

private:
	FString MessageText;

};
