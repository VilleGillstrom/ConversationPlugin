// Fill out your copyright notice in the Description page of Project Settings.


#include "Transitions/CPDialogueTransition.h"
#include "SMStateMachine.h"
#include "ConversationPlugin/Public/CPConversationSubsystem.h"
#include "Nodes/CPDialogueChoiceNode.h"

UCPDialogueTransition::UCPDialogueTransition() : Super()
{
#if WITH_EDITORONLY_DATA
	bUseCustomColors = true;
	NodeColor = FLinearColor(0.3f, 0.9f, 0.55f, 1.f);
#endif
}

bool UCPDialogueTransition::IsGoingToChoiceNode() const
{
	if(USMStateInstance_Base* Next = GetNextStateInstance())
	{
		return Next->GetClass()->IsChildOf<UCPDialogueChoiceNode>();
	}

	return false;
}

bool UCPDialogueTransition::IsLeavingChoiceNode() const
{
	if (USMStateInstance_Base* Previous = GetPreviousStateInstance())
	{
		return Previous->GetClass()->IsChildOf<UCPDialogueChoiceNode>();
	}

	return false;
}

bool UCPDialogueTransition::IsGoingToDialogueNode(bool bIncludeChoiceAsDialogue) const
{
	if (USMStateInstance_Base* Next = GetNextStateInstance())
	{
		return bIncludeChoiceAsDialogue ? Next->GetClass()->IsChildOf<UCPDialogueNode_Core>() : Next->GetClass()->IsChildOf<UCPDialogueNode>();
	}

	return false;
}

bool UCPDialogueTransition::IsLeavingDialogueNode(bool bIncludeChoiceAsDialogue) const
{
	if (USMStateInstance_Base* Previous = GetPreviousStateInstance())
	{
		return bIncludeChoiceAsDialogue ? Previous->GetClass()->IsChildOf<UCPDialogueNode_Core>() : Previous->GetClass()->IsChildOf<UCPDialogueNode>();
	}

	return false;
}

void UCPDialogueTransition::OnTransitionInitialized_Implementation()
{
	Super::OnTransitionInitialized_Implementation();

	if(IsGoingToChoiceNode())
	{
		SetCanEvaluate(false);
	}

	bCanGoToNextDialogue = false;
	if (UCPCoreNode* Previous = Cast<UCPCoreNode>(GetPreviousStateInstance()))
	{
		if( Previous->bAutoSkip)
		{
			bCanGoToNextDialogue = true;
		}
	}
	FConversationDelegates::OnTryContinueConversationEvent.AddUObject(this, &UCPDialogueTransition::TryContinue);
	
}

bool UCPDialogueTransition::CanEnterTransition_Implementation() const
{
	if(IsLeavingChoiceNode() || IsGoingToChoiceNode())
	{
		return true;
	}

	if(!bCanGoToNextDialogue)
	{
		return false;
	}
	
	if (USMStateInstance_Base* PreviousState = GetPreviousStateInstance())
	{
		// Don't want to exit a state machine early.
		if (PreviousState->IsStateMachine())
		{
			return PreviousState->IsInEndState();
		}
	}

	return true;
}

void UCPDialogueTransition::OnTransitionEntered_Implementation()
{
	Super::OnTransitionEntered_Implementation();

	if (UCPDialogueNode_Core* Previous = Cast<UCPDialogueNode_Core>(GetPreviousStateInstance()))
	{
		if (UCPDialogueNode_Core* Next = Cast<UCPDialogueNode_Core>(GetNextStateInstance()))
		{
			Next->SetPreviousDialogueSpeaker(Previous->GetDialogueSpeaker());
		}
	}

}

void UCPDialogueTransition::OnTransitionShutdown_Implementation()
{
	FConversationDelegates::OnTryContinueConversationEvent.RemoveAll(this);

}

void UCPDialogueTransition::OnDialogueUpdated_Implementation()
{
	USMStateInstance_Base* PreviousInstance = GetPreviousStateInstance();
	if(PreviousInstance->IsStateMachine())
	{
		bCanGoToNextDialogue = PreviousInstance->IsInEndState();
		return;
	}

	bCanGoToNextDialogue = true;
}

void UCPDialogueTransition::TryContinue()
{
	OnDialogueUpdated();
}