// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPCoreNode.h"
#include "SMTextGraphProperty.h"
#include "Nodes/States/SMStateInstance.h"
#include "CPDialogueNode_Core.generated.h"

/**
 * 
 */
UCLASS()
class CONVERSATIONPLUGIN_API UCPDialogueNode_Core : public UCPCoreNode
{
	GENERATED_BODY()
public:
	UCPDialogueNode_Core();

	/* Evaluates the dialogue graph and returns formatted text. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dialogue")
    const FText& GetDialogueText() const;

	/* The speaker this dialogue belongs to. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure, Category = "Dialogue")
    UObject* GetDialogueSpeaker() const;

	/* The speaker this dialogue belongs to. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dialogue")
    FText GetDialogueSpeakerAsText() const;
	
	/* Set from previous node during transition. */
	void SetPreviousDialogueSpeaker(UObject* Speaker);

	
	protected:
    virtual UObject* GetDialogueSpeaker_Implementation() const;
	
	protected:
    UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
    FSMTextGraphProperty DialogueBody;

	UPROPERTY()
    UObject* PreviousDialogueSpeaker;

	virtual void OnStateBegin_Implementation() override;

	virtual void OnStateEnd_Implementation() override;

	UFUNCTION()
	void OnTryContinue();
};
