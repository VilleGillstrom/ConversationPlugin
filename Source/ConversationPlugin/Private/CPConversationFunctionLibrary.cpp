// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationPlugin/Public/CPConversationFunctionLibrary.h"
#include "CPConversationSubsystem.h"
#include "CPSMConversation.h"

bool UCPConversationFunctionLibrary::IsInConversation(UObject* Context)
{
	UCPConversationSubsystem* SS = UCPConversationSubsystem::Get(Context);
	return SS ? SS->CurrentConversation != nullptr : false;
}

void UCPConversationFunctionLibrary::TryContinueConversation(UObject* Context)
{
	if (UCPConversationSubsystem* SS = UCPConversationSubsystem::Get(Context))
	{
		SS->TryContinueConversation();
	}
}

UCPSMConversation* UCPConversationFunctionLibrary::StartConversation(UObject* WorldContext, TSubclassOf<UCPSMConversation> ConversationClass, UObject* ConversationContext)
{
	UCPConversationSubsystem* SS = UCPConversationSubsystem::Get(WorldContext);
	return SS ? SS->StartConversation(ConversationClass, ConversationContext) : nullptr;
}

