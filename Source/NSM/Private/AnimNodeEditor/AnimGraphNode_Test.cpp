#include "AnimNodeEditor/AnimGraphNode_Test.h"

#define LOCTEXT_NAMESPACE "A3Nodes"

UAnimGraphNode_Test::UAnimGraphNode_Test(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
}

FLinearColor UAnimGraphNode_Test::GetNodeTitleColor() const
{
    return FLinearColor::Green;
}

FText UAnimGraphNode_Test::GetTooltipText() const
{
    return LOCTEXT("UAnimGraphNode_Test", "UAnimGraphNode_Test");
}

FText UAnimGraphNode_Test::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return LOCTEXT("UAnimGraphNode_Test", "UAnimGraphNode_Test");
}

FString UAnimGraphNode_Test::GetNodeCategory() const
{
    return TEXT("UAnimGraphNode_Test");
}

#undef LOCTEXT_NAMESPACE