// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/CompressionFunctionLibrary.h"

TArray<uint8> UCompressionFunctionLibrary::PackJudgements(const TArray<EJudgement>& Judgements)
{
	TArray<uint8> PackedData;
	if (Judgements.IsEmpty()) return PackedData;

	const int32 NumBytes = FMath::CeilToInt(Judgements.Num() / 2.0f);
	PackedData.AddZeroed(NumBytes);

	for (int32 i = 0; i < Judgements.Num(); ++i)
	{
		const int32 ByteIndex = i / 2;
		const int32 BitShift = (i % 2) * 4;

		const uint8 JudgementValue = static_cast<uint8>(Judgements[i]);
		PackedData[ByteIndex] |= (JudgementValue << BitShift);
	}
	
	return PackedData;
}

TArray<EJudgement> UCompressionFunctionLibrary::UnpackJudgements(const TArray<uint8>& PackedData, int32 TotalJudgements)
{
	TArray<EJudgement> UnpackedJudgements;
	if (PackedData.IsEmpty() || TotalJudgements == 0) return UnpackedJudgements;

	UnpackedJudgements.Reserve(TotalJudgements);

	for (int32 i = 0; i < TotalJudgements; ++i)
	{
		const int32 ByteIndex = i / 2;
		const int32 BitShift = (i % 2) * 4;

		const uint8 ExtractedValue = (PackedData[ByteIndex] >> BitShift) & 0b1111;

		if (ExtractedValue < 16)
		{
			UnpackedJudgements.Add(static_cast<EJudgement>(ExtractedValue));
		}
		else
		{
			 UnpackedJudgements.Add(EJudgement::Miss);
		}
	}

	return UnpackedJudgements;
}
