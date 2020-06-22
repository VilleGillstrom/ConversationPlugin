// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationPlugin/Public/Nodes/CPDialogueNode_Core.h"

#include "CPConversationPieceInterface.h"
#include "CPSMConversation.h"
#include "CPTypes.h"
#include "ConversationPlugin/Public/CPConversationSubsystem.h"


UCPDialogueNode_Core::UCPDialogueNode_Core() : Super()
{
#if WITH_EDITORONLY_DATA
    NodeDescription.Name = "Dialogue Node";
    NodeDescription.Category = FText::FromString("Dialogue");
    DialogueBody.WidgetInfo.DefaultText = FText::FromString("Dialogue");
    DialogueBody.WidgetInfo.bConsiderForDefaultWidget = true;
    DialogueBody.WidgetInfo.DisplayOrder = 1;
    DialogueBody.TextSerializer.ToTextFunctionNames.Add("ToConversationText");
    bDisplayNameWidget = false;
    bUseCustomColors = true;
    NodeColor = FLinearColor(0.1f, 0.62f, 1.f, 0.7f);
    NodeEndStateColor = FLinearColor(1.f, 1.f, 1.f, 0.7f);
#endif
}

const FText& UCPDialogueNode_Core::GetDialogueText() const
{
    const_cast<UCPDialogueNode_Core*>(this)->DialogueBody.Execute();
    return DialogueBody.Result;
}

FText UCPDialogueNode_Core::GetDialogueSpeakerAsText() const
{
    UObject* CurrentSpeaker = GetDialogueSpeaker();
    return CurrentSpeaker ? ICPConversationPieceInterface::TryConversationText(CurrentSpeaker) : FText::FromString("");
}

void UCPDialogueNode_Core::SetPreviousDialogueSpeaker(UObject* Speaker)
{
    PreviousDialogueSpeaker = Speaker;
}

UObject* UCPDialogueNode_Core::GetDialogueSpeaker_Implementation() const
{
    const_cast<UCPDialogueNode_Core*>(this)->EvaluateGraphProperties();
    return PreviousDialogueSpeaker;
}

void UCPDialogueNode_Core::OnStateBegin_Implementation()
{
   
}

void UCPDialogueNode_Core::OnStateEnd_Implementation()
{
}

void UCPDialogueNode_Core::OnTryContinue()
{
    
}

