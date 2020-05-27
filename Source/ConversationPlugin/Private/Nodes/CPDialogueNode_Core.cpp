// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationPlugin/Public/Nodes/CPDialogueNode_Core.h"


UCPDialogueNode_Core::UCPDialogueNode_Core() : Super()
{
#if WITH_EDITORONLY_DATA
    NodeDescription.Name = "Dialogue Node";
    NodeDescription.Category = FText::FromString("Dialogue");
    DialogueBody.WidgetInfo.DefaultText = FText::FromString("Dialogue");
    DialogueBody.WidgetInfo.bConsiderForDefaultWidget = true;
    DialogueBody.WidgetInfo.DisplayOrder = 1;
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

void UCPDialogueNode_Core::SetPreviousDialogueSpeaker(UObject* Speaker)
{
    PreviousDialogueSpeaker = Speaker;
}

UObject* UCPDialogueNode_Core::GetDialogueSpeaker_Implementation() const
{
    const_cast<UCPDialogueNode_Core*>(this)->EvaluateGraphProperties();
    return PreviousDialogueSpeaker;
}
