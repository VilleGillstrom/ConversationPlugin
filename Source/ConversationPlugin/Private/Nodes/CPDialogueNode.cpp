// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationPlugin/Public/Nodes/CPDialogueNode.h"
#include "SMState.h"
#include "SMTransition.h"
#include "Nodes/CPDialogueChoiceNode.h"

UCPDialogueNode::UCPDialogueNode() : Super()
{
	//bUsePreviousSpeakerIfNoneSet = true;
}

void UCPDialogueNode::GetAllDialogueNodes(TArray<UCPDialogueNode*>& OutDialogueNodes) const
{
	TArray<USMNodeInstance*> OutNodes;
	//GetAllNodesOfType(OutNodes, UCPDialogueNode::StaticClass(), true);

	for(USMNodeInstance* OutNode : OutNodes)
	{
		if(UCPDialogueNode* Node = Cast<UCPDialogueNode>(OutNode))
		{
			OutDialogueNodes.Add(Node);
		}
	}
}

void UCPDialogueNode::GetAllConnectedDialogueNodes(TArray<UCPDialogueNode*>& OutDialogueNodes,
	bool bBreakOnChoices) const
{
	TArray<UClass*> RequiredTypes;
	RequiredTypes.Add(UCPDialogueNode::StaticClass());

	if (!bBreakOnChoices)
	{
		//RequiredTypes.Add(USMDialogueChoiceNode::StaticClass());
	}

	TArray<USMNodeInstance*> OutNodes;
	GetAllNodesOfType(OutNodes, UCPDialogueNode::StaticClass(), true, RequiredTypes);
	for (USMNodeInstance* OutNode : OutNodes)
	{
		if (UCPDialogueNode* Node = Cast<UCPDialogueNode>(OutNode))
		{
			OutDialogueNodes.Add(Node);
		}
	}
}

void UCPDialogueNode::GetAllDialogueSpeakers(TArray<UObject*>& Speakers, bool bConnectedOnly,
                                             bool bBreakOnChoices) const
{
	TArray<UCPDialogueNode*> DialogueNodes;
	if(bConnectedOnly)
	{
		GetAllConnectedDialogueNodes(DialogueNodes, bBreakOnChoices);
	}
	else
	{
		GetAllDialogueNodes(DialogueNodes);
	}
	
	for(UCPDialogueNode* Node : DialogueNodes)
	{
		if (UObject* DialogueSpeaker = Node->GetDialogueSpeaker())
		{
			Speakers.AddUnique(DialogueSpeaker);
		}
	}
}

void UCPDialogueNode::OnStateBegin_Implementation()
{
}

void UCPDialogueNode::OnStateUpdate_Implementation(float DeltaSeconds)
{
}

void UCPDialogueNode::OnStateEnd_Implementation()
{
}

UObject* UCPDialogueNode::GetDialogueSpeaker_Implementation() const
{
	Super::GetDialogueSpeaker_Implementation();
	return (Speaker || !bUsePreviousSpeakerIfNoneSet) ? Speaker : PreviousDialogueSpeaker;
}

void UCPDialogueNode::GetAvailableChoices(TArray<UCPDialogueChoiceNode*>& Choices)
{
	if (const FSMState_Base* Node = (FSMState_Base*)GetOwningNode())
	{
		for (FSMTransition* Transition : Node->GetOutgoingTransitions())
		{
			if (UCPDialogueChoiceNode* Choice = Cast<UCPDialogueChoiceNode>(Transition->GetToState()->GetNodeInstance()))
			{
				const bool bCanEval = Transition->bCanEvaluate;
				Transition->bCanEvaluate = true;
				if (Transition->DoesTransitionPass())
				{
					Choice->SetCurrentDialogueOwner(this);
					Choices.Add(Choice);
				}
				Transition->bCanEvaluate = bCanEval;
			}
		}
	}
}

void UCPDialogueNode::SelectChoice(UCPDialogueChoiceNode* Choice)
{
	SwitchToLinkedState(Choice, false);
}
