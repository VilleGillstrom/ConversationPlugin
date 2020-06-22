// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/CPDialogueNode_Core.h"
#include "CPDialogueNode.generated.h"

class UCPDialogueChoiceNode;
/**
 * 
 */
UCLASS()
class CONVERSATIONPLUGIN_API UCPDialogueNode : public UCPDialogueNode_Core
{
	GENERATED_BODY()

	
	public:

    UCPDialogueNode();

	/* Iterates over all transitions out leading to dialogue choices and evaluates them determining which choices are visible. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dialogue")
    virtual void GetAvailableChoices(TArray<UCPDialogueChoiceNode*>& Choices);

	/* Select the given choice and move to the next node. */
	virtual void SelectChoice(class UCPDialogueChoiceNode* Choice);

	/* Get all dialogue nodes in the hierarchy starting from this node. */
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void GetAllDialogueNodes(TArray<UCPDialogueNode*>& OutDialogueNodes) const;

	/**
	* Get all dialogue nodes that are connected to each other starting with this node.
	* @param OutDialogueNodes All connected nodes.
	* @param bBreakOnChoices If choice nodes should break the search.
	*/
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void GetAllConnectedDialogueNodes(TArray<UCPDialogueNode*>& OutDialogueNodes, bool bBreakOnChoices = false) const;

	/**
	* Get all speaker objects for dialogues.
	* @param Speakers All found speakers.
	* @param bConnectedOnly If only dialogue nodes connected to each other should be checked.
	* @param bBreakOnChoices If choice nodes should break the search.
	*/
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void GetAllDialogueSpeakers(TArray<UObject*>& Speakers, bool bConnectedOnly = true, bool bBreakOnChoices = false) const;

	protected:
	
    virtual void OnStateBegin_Implementation() override;
	virtual void OnStateUpdate_Implementation(float DeltaSeconds) override;
	virtual void OnStateEnd_Implementation() override;
	
	UObject* GetDialogueSpeaker_Implementation() const override;
	protected:
        /* If no speaker has been set the previous speaker will be used. */
        UPROPERTY(EditAnywhere, Category = "Speaker")
        bool bUsePreviousSpeakerIfNoneSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speaker")
    UObject* Speaker;
};
