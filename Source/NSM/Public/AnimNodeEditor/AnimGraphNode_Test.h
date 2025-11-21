#pragma once
#include "AnimGraph/Classes/AnimGraphNode_Base.h"
#include "AnimNode/AnimNode_Test.h"
#include "AnimGraphNode_Test.generated.h"

UCLASS()
class NSM_API UAnimGraphNode_Test : public UAnimGraphNode_Base
{
    GENERATED_BODY()

public:
    UAnimGraphNode_Test() = default;

    UPROPERTY(EditAnywhere, Category = Settings)
    FAnimNode_Test Node;

    //~ Begin UEdGraphNode Interface.
    virtual FLinearColor GetNodeTitleColor() const override;
    virtual FText GetTooltipText() const override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    //~ End UEdGraphNode Interface.

    //~ Begin UAnimGraphNode_Base Interface
    virtual FString GetNodeCategory() const override;
    //~ End UAnimGraphNode_Base Interface

    UAnimGraphNode_Test(const FObjectInitializer& ObjectInitializer);
    
};
