// Fill out your copyright notice in the Description page of Project Settings.


#include "WebSocketGameInstance.h"
#include "WebSocketsModule.h"


FString UWebSocketGameInstance::GetMessage()
{
	return MessageText;
}

float UWebSocketGameInstance::DecodeToFloat(uint8 a, uint8 b, uint8 c, uint8 d) {
	TArray<uint8> Bytes;
	Bytes.Add(a);
	Bytes.Add(b);
	Bytes.Add(c);
	Bytes.Add(d);

	return *reinterpret_cast<float*>(Bytes.GetData());
}

/*
TArray<uint8> ATcpSocketConnection::Conv_FloatToBytes(float InFloat)
{
	TArray<uint8> result;

	unsigned char const * p = reinterpret_cast<unsigned char const *>(&InFloat);
	for (int i = 0; i != sizeof(float); i++)
	{
		result.Add((uint8)p[i]);
	}
	return result;
}*/

void UWebSocketGameInstance::StartConnection(FString HostName)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Trying to start connection.");

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
		FModuleManager::Get().LoadModule("WebSockets");
	}


	WebSocket = FWebSocketsModule::Get().CreateWebSocket(HostName);
	

	WebSocket->OnConnected().AddLambda([]() {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Connected");
	});

	WebSocket->OnConnectionError().AddLambda([&](const FString& Error) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
		//ConnectionError();
	});

	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Closed: "+Reason);
	});

	WebSocket->OnMessage().AddLambda([&](const FString& MessageString) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, MessageString);
		MessageText = MessageString;
		MessageReceived(MessageString);
	});

	WebSocket->Connect();
}

void UWebSocketGameInstance::SendMessage(FString Message)
{
	if (WebSocket) {
		WebSocket->Send(Message);
	}
}

void UWebSocketGameInstance::Shutdown()
{

	if (WebSocket && WebSocket->IsConnected()) {
		WebSocket->Close();
	}
	Super::Shutdown();
}