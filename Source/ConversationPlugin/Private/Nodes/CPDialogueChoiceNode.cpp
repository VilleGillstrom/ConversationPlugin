// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/CPDialogueChoiceNode.h"
#include "Nodes/CPDialogueNode.h"
UCPDialogueChoiceNode::UCPDialogueChoiceNode() : Super()
{
#if WITH_EDITORONLY_DATA
    NodeDescription.Name = "Dialogue Choice";
    bDisplayNameWidget = false;
    DialogueBody.WidgetInfo.MinWidth = 75;
    DialogueBody.WidgetInfo.MinHeight = 25;
    DialogueBody.WidgetInfo.DisplayOrder = 1;
    NodeColor = FLinearColor(0.5f, 0.9f, 1.f, 0.7f);
#endif
}

void UCPDialogueChoiceNode::SetCurrentDialogueOwner(UCPDialogueNode* Owner)
{
    CurrentDialogueOwner = Owner;
}

void UCPDialogueChoiceNode::OnStateBegin_Implementation()
{
    Super::OnStateBegin_Implementation();
}

void UCPDialogueChoiceNode::OnStateUpdate_Implementation(float DeltaSeconds)
{
    Super::OnStateUpdate_Implementation(DeltaSeconds);
}

void UCPDialogueChoiceNode::OnStateEnd_Implementation()
{
    Super::OnStateEnd_Implementation();
}

void UCPDialogueChoiceNode::SelectChoice_Implementation()
{
    if (UCPDialogueNode* Dialogue = GetCurrentDialogueOwner())
    {
        Dialogue->SelectChoice(this);
    }
}
