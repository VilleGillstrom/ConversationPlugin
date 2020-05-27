// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPDialogueNode.h"
#include "Nodes/CPDialogueNode_Core.h"
#include "CPDialogueChoiceNode.generated.h"

/**
 * 
 */

UCLASS()
class CONVERSATIONPLUGIN_API UCPDialogueChoiceNode : public UCPDialogueNode_Core
{
	GENERATED_BODY()
	public:

    UCPDialogueChoiceNode();

	/* Signals the dialogue node owner to take this choice. This can only be valid if the choice was retrieved from the dialogue node owner method GetAvailableChoices. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue")
    void SelectChoice();
	
	/* Returns the dialogue node this choice currently belongs to.
	* This can change if more than one node leads to this choice. */
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
    UCPDialogueNode* GetCurrentDialogueOwner() const { return CurrentDialogueOwner; }
	void SetCurrentDialogueOwner(UCPDialogueNode* Owner);

	protected:
        virtual void OnStateBegin_Implementation() override;
	virtual void OnStateUpdate_Implementation(float DeltaSeconds) override;
	virtual void OnStateEnd_Implementation() override;

	virtual void SelectChoice_Implementation();

	protected:
    UPROPERTY()
    UCPDialogueNode* CurrentDialogueOwner;
};
