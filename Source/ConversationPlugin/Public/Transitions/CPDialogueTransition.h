// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/Transitions/SMTransitionInstance.h"
#include "CPDialogueTransition.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, classGroup = "Dialogue", hideCategories = (SMDialogueTransition), meta = (DisplayName = "Dialogue Transition"))
class CONVERSATIONPLUGIN_API UCPDialogueTransition : public USMTransitionInstance
{
	GENERATED_BODY()
public:
	UCPDialogueTransition();
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool IsGoingToChoiceNode() const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool IsLeavingChoiceNode() const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool IsGoingToDialogueNode(bool bIncludeChoiceAsDialogue = true) const;
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool IsLeavingDialogueNode(bool bIncludeChoiceAsDialogue = true) const;

	/* Should be called when a dialogue is updated. Recommended usage is binding to an event. Override for custom implementations. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue")
    void OnDialogueUpdated();
protected:

	void OnTransitionInitialized_Implementation() override;
	bool CanEnterTransition_Implementation() const override;
	void OnTransitionEntered_Implementation() override;

	virtual void OnDialogueUpdated_Implementation();
	
	protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
        bool bCanGoToNextDialogue;
	
};
