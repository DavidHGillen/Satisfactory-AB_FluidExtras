// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABJunctionHologram.h"
#include "FGPipeConnectionComponent.h"

AABJunctionHologram::AABJunctionHologram() {
}

bool AABJunctionHologram::TrySnapToActor(const FHitResult& hitResult) {
	bool result = Super::TrySnapToActor(hitResult);

	RotateFromSnappedElement();

	return result;
}

bool AABJunctionHologram::DoMultiStepPlacement(bool isInputFromARelease) {
	return Super::DoMultiStepPlacement(isInputFromARelease);
}

void AABJunctionHologram::ScrollRotate(int32 delta, int32 step) {
	Super::ScrollRotate(delta, step);

	RotateFromSnappedElement();
}

int32 AABJunctionHologram::GetRotationStep() const {
	return 15;
}

void AABJunctionHologram::RotateFromSnappedElement() {
	//UE_LOG(LogTemp, Warning, TEXT("SPIN: %d, %d] %d"), delta, step, mSnappedConnectionComponent);

	if (mSnappedConnectionComponent != NULL) {
		UFGPipeConnectionComponent* myConnector = mPipeConnectionComponents[mSnapConnectionIndex];
		SetActorRotation(FRotator(0));
		AddActorLocalRotation(myConnector->GetRelativeRotation());
		AddActorWorldRotation(mSnappedConnectionComponent->GetComponentRotation());
		//AddActorLocalRotation(myConnector->GetComponentRotation());
		/*
		FRotator::

		GetScrollRotateValue() * -1;

		SetActorRotation();

		mSnappedConnectionComponent->GetComponentRotation();
		*/
	} /*else if (mSnappedPipeline != NULL) {

	}*/
}

		/*
bool AABJunctionHologram::VanillaTrySnap(const FHitResult& hitResult) {
	code* pcVar2;
	undefined auVar3[12];
	undefined auVar4[16];
	undefined uVar6;
	undefined extraout_AL;
	AFGBuildablePipeline* hitPipeRef;
	FFGHologramGuidelineSnapResult* guideSnapResult;
	FMatrix* someMatrix;
	FVector* someVector;
	FRotator* someRotator;
	FTransform* someTransform;
	UObject* hitUObjRef;
	AFGBuildableWall* hitWallRef;
	FVector* pFVar17;
	int iVar18;
	USceneComponent* sceneComponent;
	undefined8* puVar20;
	float fVar21;
	float fVar25;
	undefined auVar23[16];
	unsigned int uVar28;
	unsigned int uVar29;
	unsigned int uVar30;
	float fVar31;
	float fVar34;
	float fVar35;
	float fVar37;
	float fVar39;
	float fVar41;
	float fVar42;
	unsigned int uVar43;
	unsigned int uVar44;
	unsigned int uVar45;
	float fVar46;
	float fVar47;
	float fVar48;
	float fVar49;
	float in_xmmTmp2_Dd;
	undefined auStackY_608[32];
	FVector local_5b8;
	FVector foundSnapNormal;
	FVector local_598;
	FRotator snapRotator;
	FVector foundSnapLocation;
	undefined local_558[16];
	undefined local_548[4];
	undefined auStack_544[4];
	undefined8 uStack_540;
	undefined local_538[4];
	undefined auStack_534[4];
	undefined8 uStack_530;
	undefined local_528[16];
	undefined local_518[8];
	undefined8 uStack_510;
	undefined local_508[8];
	undefined8 uStack_500;
	undefined local_4f8[8];
	undefined8 uStack_4f0;
	undefined local_4e8[16];
	FVector local_4d8;
	FVector local_4cc;
	undefined4 local_4b4;
	undefined4 local_4b0;
	undefined4 local_4ac;
	FVector local_4a8;
	FVector local_498;
	FRotator local_488;
	FVector local_478;
	FRotator local_468;
	FVector local_458;
	FRotator local_448;
	FRotator local_438;
	FVector local_428;
	unsigned int* local_418;
	TArray<UFGPipeConnectionComponent*, TSizedDefaultAllocator<32>>* local_410;
	unsigned int* local_408;
	TArray<UFGPipeConnectionComponent*, TSizedDefaultAllocator<32>>* local_400;
	FVector local_3f8;
	FRotator local_3e8;
	FQuat local_3d8;
	float local_3c8;
	float fStack_3c4;
	float fStack_3c0;
	float fStack_3bc;
	FQuat local_3b8;
	float local_3a8;
	float fStack_3a4;
	float fStack_3a0;
	float fStack_39c;
	FRotator local_398;
	FVector local_38c;
	FVector local_380;
	FVector local_374;
	FMatrix local_368;
	FMatrix local_2e8;
	FMatrix local_2a8;
	FMatrix local_268;
	FTransform local_228;
	undefined local_1f8[16];
	undefined local_1e8[16];
	undefined local_1d8[16];
	FTransform local_1c8;
	undefined local_1b8[16];
	undefined local_1a8[16];
	FTransform local_168;
	FFGHologramGuidelineSnapResult local_138;

	if (this->mBuildStep == EPipelineAttachmentBuildStep::PABS_PlacementAndDirection) {
		///*(undefined8*)&this->field_0x460 = 0;
		this->mSnappedPipeline = (AFGBuildablePipeline*)0x0;
		this->mSnappedConnectionComponent = (UFGPipeConnectionComponent*)0x0;
		this->mSnappedPipelineOffset = 0.0;

		// PIPE //
		hitPipeRef = (AFGBuildablePipeline*)&(hitResult.Actor);
		if (hitPipeRef != NULL) {
			this->mSnappedPipeline = hitPipeRef;
		
			fVar21 = (float)(**(code**)(*(long long*)hitPipeRef + 0x7a0))(hitPipeRef, hitResult.Location);
			this->mSnappedPipelineOffset = fVar21;
			(**(code**)(*(long long*)this->mSnappedPipeline + 0x7a8))();

			TrySnapToConnection(50.0, foundSnapLocation, foundSnapNormal);

			if ((this->field_0x470 == NULL) && (this->field_0x2d1 != NULL)) {
				guideSnapResult = &SnapHologramLocationToGuidelines(foundSnapLocation);
				_func__thiscall_FFGHologramGuidelineSnapResult_ptr_FFGHologramGuidelineSnapResult_ptr(&this->field_0x400, guideSnapResult);
				if (this->field_0x45c != NULL) {
					fVar21 = (float)(**(code**)(*(long long*)hitPipeRef + 0x7a0))(hitPipeRef, &this->field_0x450);
					this->mSnappedPipelineOffset = fVar21;
					(**(code**)(*(long long*)this->mSnappedPipeline + 0x7a8))();
				}
			}

			someMatrix = &FRotationMatrix::MakeFromX(foundSnapNormal);
			snapRotator = someMatrix->Rotator();

			EAxis::Type eRotAxis = this->mRotationAxis;
			if (eRotAxis == EAxis::X) {
				fVar21 = AFGHologram::ApplyScrollRotationTo(0.0, false);
				snapRotator._0_8_ = snapRotator._0_8_ & 0xffffffff00000000 | (unsigned long long)(uint)(snapRotator.Pitch + fVar21);

			} else if (eRotAxis == EAxis::Y) {
				fVar21 = AFGHologram::ApplyScrollRotationTo(0.0, false);
				snapRotator.Roll = snapRotator.Roll + fVar21;

			} else if ((eRotAxis == EAxis::Z) && ((this->mSnappedConnectionComponent == NULL || (this->mIncrementSnappedConnectionOnScroll == false)))) {
				FRotationMatrix::MakeFromX(&local_368, (FVector*)&foundSnapNormal);
				someVector = _func__thiscall_FVector_Type(&local_368, &local_374, Z);
				fVar21 = AFGHologram::ApplyScrollRotationTo(0.0, false);

				someVector = _func__thiscall_FVector_float_FVector_ptr(&foundSnapNormal, &local_380, fVar21, someVector);
				foundSnapNormal._0_8_ = *(undefined8*)someVector;
				foundSnapNormal.Z = someVector->Z;

				someMatrix = (FMatrix*)FRotationMatrix::MakeFromX(&local_2e8, (FVector*)&foundSnapNormal);
				someRotator = FMatrix::Rotator(someMatrix, &local_398);
				snapRotator._0_8_ = *(unsigned long long*)someRotator;
				snapRotator.Roll = someRotator->Roll;
			}

			pcVar2 = OneVector_exref;
			local_3d8 = snapRotator.Quaternion();
			local_228.Translation.V = (float[4])ZEXT1216((undefined[12])foundSnapLocation);

			local_228.Rotation.V[0] = local_3d8.X;
			local_228.Rotation.V[1] = local_3d8.Y;
			local_228.Rotation.V[2] = local_3d8.Z;
			local_228.Rotation.V[3] = local_3d8.W;

			local_228.Scale3D.V = (float[4])ZEXT1216(*(undefined(*)[12])pcVar2);

			if (this->mSnappedConnectionComponent == NULL) {
				someTransform = &local_228;

			} else {
				float fLocal_6;
				float fLocal_7;
				float fLocal_10;
				float fLocal_8;
				float fLocal_12;
				float fLocal_13;
				float fLocal_14;
				float fLocal_15;
				float fLocal_16;
				float fLocal_4;
				float fLocal_17;
				float fLocal_5;

				unsigned int snapIndex = this->mSnapConnectionIndex;
				local_400 = &this->mPipeConnectionComponents;
				uVar28 = 0;

				if (snapIndex < mPipeConnectionComponents.Num()) {
					uVar28 = ~snapIndex >> 0x1f;
				}

				if (uVar28 == 0) {
					local_408 = snapIndex;
					_func__cdecl_void_<lambda_e564da29fc75c0aef1975a3dea611db9>_ptr((<lambda_e564da29fc75c0aef1975a3dea611db9> *) & local_408);
					pcVar2 = (code*)swi(3);
					uVar6 = (*pcVar2)();
					return (bool)uVar6;
				}

				sceneComponent = *(USceneComponent**)((local_400->AllocatorInstance).Data + (long long)(int)local_560[0] * 8);
				someTransform = sceneComponent->GetRelativeTransform();

				uVar28 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x20, 0);
				uVar29 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x40, 0);
				uVar30 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x60, 0);

				fLocal_15 = SUB164((undefined[16])GlobalVectorConstants::SmallNumber >> 0x20, 0);
				fLocal_17 = SUB164((undefined[16])GlobalVectorConstants::SmallNumber >> 0x60, 0);

				uVar43 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x20, 0);
				uVar44 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x40, 0);
				uVar45 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x60, 0);

				auVar23 = *(undefined(*)[16])(someTransform->Scale3D).V;

				fLocal_16 = SUB164(auVar23, 0);
				fLocal_4 = SUB164(auVar23 >> 0x20, 0);
				fLocal_5 = SUB164(auVar23 >> 0x40, 0);

				fLocal_12 = (float)((uint)fLocal_16 & SUB164((undefined[16])GlobalVectorConstants::SignMask.m128_u32, 0));
				fLocal_13 = (float)((uint)fLocal_4 & uVar28);
				fLocal_14 = (float)(SUB164(auVar23 >> 0x60, 0) & uVar30);

				iVar18 = movmskps((int)sceneComponent,
					CONCAT412(-(uint)(fLocal_17 < in_xmmTmp2_Dd),
						CONCAT48(-(uint)(SUB164((undefined[16])
							GlobalVectorConstants::SmallNumber >>
							0x40, 0) < fLocal_14),
							CONCAT44(-(uint)(fLocal_15 < fLocal_13),
								-(uint)(SUB164((undefined[16])
									GlobalVectorConstants::
									SmallNumber.m128_f32, 0) <
									fLocal_12))))
				);
					
				fVar21 = SUB164((undefined[16])GlobalVectorConstants::FloatOne >> 0x60, 0);
				if (iVar18 == 0) {
					fLocal_6 = *(float*)Identity_exref;
					fLocal_7 = *(float*)(Identity_exref + 4);
					fLocal_10 = *(float*)(Identity_exref + 8);
					fLocal_8 = *(float*)(Identity_exref + 0xc);

					fLocal_12 = *(float*)(Identity_exref + 0x10);
					fLocal_13 = *(float*)(Identity_exref + 0x14);
					fLocal_14 = *(float*)(Identity_exref + 0x18);
					fLocal_15 = *(float*)(Identity_exref + 0x1c);

					fLocal_16 = *(float*)(Identity_exref + 0x20);
					fLocal_4 = *(float*)(Identity_exref + 0x24);
					fLocal_17 = *(float*)(Identity_exref + 0x28);
					fLocal_5 = *(float*)(Identity_exref + 0x2c);

					someTransform = (FTransform*)Identity_exref;

				} else {
					fLocal_6 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK.m128_f32, 0) * (someTransform->Rotation).V[0];
					fLocal_7 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x20, 0) * (someTransform->Rotation).V[1];
					fLocal_10 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x40, 0) * (someTransform->Rotation).V[2];
					fLocal_8 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x60, 0) * (someTransform->Rotation).V[3];
					auVar23 = rcpps(CONCAT412(fLocal_14, CONCAT48((uint)fLocal_5 & uVar29, CONCAT44(fLocal_13, fLocal_12))), CONCAT412(fVar21, SUB1612(auVar23, 0)));
					// rcpps, vec norm, reciprocal, ps means SIMD

					fLocal_12 = SUB164(auVar23, 0);
					fLocal_13 = SUB164(auVar23 >> 0x20, 0);
					fLocal_14 = SUB164(auVar23 >> 0x40, 0);
					fLocal_9 = SUB164(auVar23 >> 0x60, 0);

					fLocal_12 = (fLocal_12 + fLocal_12) - fLocal_12 * fLocal_12 * fLocal_16;
					fLocal_13 = (fLocal_13 + fLocal_13) - fLocal_13 * fLocal_13 * fLocal_4;
					fLocal_14 = (fLocal_14 + fLocal_14) - fLocal_14 * fLocal_14 * fLocal_5;
					fLocal_9 = (fLocal_9 + fLocal_9) - fLocal_9 * fLocal_9 * fVar21;

					fLocal_12 = (fLocal_12 + fLocal_12) - fLocal_12 * fLocal_12 * fLocal_16;
					fLocal_13 = (fLocal_13 + fLocal_13) - fLocal_13 * fLocal_13 * fLocal_4;
					fLocal_14 = (fLocal_14 + fLocal_14) - fLocal_14 * fLocal_14 * fLocal_5;
					fLocal_9 = (fLocal_9 + fLocal_9) - fLocal_9 * fLocal_9 * fVar21;

					fLocal_16 = (float)((-(uint)((float)((uint)fLocal_16 &
						SUB164((undefined[16])
							GlobalVectorConstants::SignMask.m128_u32, 0)) <=
						SUB164((undefined[16])
							GlobalVectorConstants::SmallNumber.m128_f32, 0)) &
						(uint)fLocal_12 ^ (uint)fLocal_12) &
						SUB164((undefined[16])GlobalVectorConstants::XYZMask.m128_u32, 0));
					fLocal_4 = (float)((-(uint)((float)((uint)fLocal_4 & uVar28) <= fLocal_15) & (uint)fLocal_13 ^
						(uint)fLocal_13) & uVar43);
					fLocal_17 = (float)((-(uint)((float)((uint)fLocal_5 & uVar29) <= fLocal_17) & (uint)fLocal_14 ^
						(uint)fLocal_14) & uVar44);
					fLocal_5 = (float)((-(uint)((float)((uint)fVar21 & uVar30) <= in_xmmTmp2_Dd) &
						(uint)fLocal_9 ^ (uint)fLocal_9) & uVar45);

					fLocal_12 = fLocal_16 * (someTransform->Translation).V[0];
					fLocal_13 = fLocal_4 * (someTransform->Translation).V[1];
					fLocal_0 = fLocal_17 * (someTransform->Translation).V[2];
					fLocal_1 = fLocal_5 * (someTransform->Translation).V[3];

					fLocal_14 = fLocal_7 * 0.0 - fLocal_13 * 0.0;
					fLocal_15 = fLocal_12 * fLocal_10 - fLocal_0 * fLocal_6;
					fLocal_9 = fLocal_13 * fLocal_6 - fLocal_12 * fLocal_7;
					fLocal_11 = fLocal_1 * fLocal_8 - fLocal_1 * fLocal_8;

					fLocal_14 = fLocal_14 + fLocal_14;
					fLocal_15 = fLocal_15 + fLocal_15;
					fLocal_9 = fLocal_9 + fLocal_9;
					fLocal_11 = fLocal_11 + fLocal_11;
					fLocal_12 = (float)((uint)(0.0 - ((fLocal_7 * 0.0 - fLocal_15 * 0.0) + fLocal_8 * fLocal_14 + fLocal_12)
						) &
						SUB164((undefined[16])GlobalVectorConstants::XYZMask.m128_u32, 0));
					fLocal_13 = (float)((uint)(0.0 - ((fLocal_14 * fLocal_10 - fLocal_9 * fLocal_6) + fLocal_8 * fLocal_15 + fLocal_13)) & uVar43);
					fLocal_14 = (float)((uint)(0.0 - ((fLocal_15 * fLocal_6 - fLocal_14 * fLocal_7) + fLocal_8 * fLocal_9 + fLocal_0)) & uVar44);
					fLocal_15 = (float)((uint)(0.0 - ((fLocal_11 * fLocal_8 - fLocal_11 * fLocal_8) + fLocal_8 * fLocal_11 + fLocal_1)) & uVar45);
				}

				fLocal_9 = SUB164((undefined[16])local_228.Scale3D.V, 0);
				fLocal_11 = SUB164((undefined[16])local_228.Scale3D.V >> 0x20, 0);
				fLocal_0 = SUB164((undefined[16])local_228.Scale3D.V >> 0x40, 0);
				fLocal_1 = SUB164((undefined[16])local_228.Scale3D.V >> 0x60, 0);
				auVar23 = minps(CONCAT412(fLocal_5, CONCAT48(fLocal_17, CONCAT44(fLocal_4, fLocal_16))), (undefined[16])local_228.Scale3D.V);
				fLocal_2 = SUB164((undefined[16])GlobalVectorConstants::FloatZero >> 0x60, 0);
				iVar18 = movmskps((int)someTransform,
					CONCAT412(-(uint)(SUB164(auVar23 >> 0x60, 0) < fLocal_2),
						CONCAT48(-(uint)(SUB164(auVar23 >> 0x40, 0) <
							SUB164((undefined[16])
								GlobalVectorConstants::FloatZero >>
								0x40, 0)),
							CONCAT44(-(uint)(SUB164(auVar23 >> 0x20, 0) <
								SUB164((undefined[16])
									GlobalVectorConstants::
									FloatZero >> 0x20, 0)),
								-(uint)(SUB164(auVar23, 0) <
									SUB164((undefined[16])
										GlobalVectorConstants::
										FloatZero.m128_f32, 0)))))
				);
					
				if (iVar18 == 0) {
					someTransform = (FTransform*)local_1f8;
					fLocal_12 = fLocal_12 * fLocal_9;
					fLocal_13 = fLocal_13 * fLocal_11;
					fLocal_15 = fLocal_15 * fLocal_1;
					local_1d8 = CONCAT412(fLocal_5 * fLocal_1, CONCAT48(fLocal_17 * fLocal_0, CONCAT44(fLocal_4 * fLocal_11, fLocal_16 * fLocal_9) ));
					local_1f8 = CONCAT412(fLocal_6 * local_228.Rotation.V[0] *
						SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK0
							>> 0x60, 0) + fLocal_8 * local_228.Rotation.V[3] +
						fLocal_7 * local_228.Rotation.V[1] *
						SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK1
							>> 0x60, 0) +
						SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK2
							>> 0x60, 0) * 0.0,
						CONCAT48(fLocal_7 * local_228.Rotation.V[0] *
							SUB164((undefined[16])
								GlobalVectorConstants::QMULTI_SIGN_MASK0 >> 0x40, 0
							) + fLocal_10 * local_228.Rotation.V[3] +
							fLocal_6 * local_228.Rotation.V[1] *
							SUB164((undefined[16])
								GlobalVectorConstants::QMULTI_SIGN_MASK1 >> 0x40, 0
							) + fLocal_8 * 0.0 *
							SUB164((undefined[16])
								GlobalVectorConstants::QMULTI_SIGN_MASK2
								>> 0x40, 0),
							CONCAT44(local_228.Rotation.V[0] * 0.0 *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK0
									>> 0x20, 0) +
								fLocal_7 * local_228.Rotation.V[3] +
								fLocal_8 * local_228.Rotation.V[1] *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK1
									>> 0x20, 0) +
								fLocal_6 * local_228.Rotation.V[2] *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK2
									>> 0x20, 0),
								fLocal_8 * local_228.Rotation.V[0] *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK0.
									m128_f32, 0) +
								fLocal_6 * local_228.Rotation.V[3] +
								fLocal_10 * local_228.Rotation.V[1] *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK1.
									m128_f32, 0) +
								fLocal_7 * local_228.Rotation.V[2] *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK2.
									m128_f32, 0))));
					fVar21 = local_228.Rotation.V[1] * 0.0 - fLocal_13 * 0.0;
					fLocal_17 = fLocal_12 * 0.0 - fLocal_14 * fLocal_0 * local_228.Rotation.V[0];
					fLocal_16 = fLocal_13 * local_228.Rotation.V[0] - fLocal_12 * local_228.Rotation.V[1];
					fLocal_4 = fLocal_15 * local_228.Rotation.V[3] - fLocal_15 * local_228.Rotation.V[3];
					fVar21 = fVar21 + fVar21;
					fLocal_17 = fLocal_17 + fLocal_17;
					fLocal_16 = fLocal_16 + fLocal_16;
					fLocal_4 = fLocal_4 + fLocal_4;
					local_1e8 = CONCAT412((fLocal_4 * local_228.Rotation.V[3] -
						fLocal_4 * local_228.Rotation.V[3]) +
						local_228.Rotation.V[3] * fLocal_4 + fLocal_15 +
						local_228.Translation.V[3],
						CONCAT48((fLocal_17 * local_228.Rotation.V[0] -
							fVar21 * local_228.Rotation.V[1]) +
							local_228.Rotation.V[3] * fLocal_16 + fLocal_14 * fLocal_0 +
							local_228.Translation.V[2],
							CONCAT44((fVar21 * 0.0 - fLocal_16 * local_228.Rotation.V[0]
								) + local_228.Rotation.V[3] * fLocal_17 + fLocal_13 +
								local_228.Translation.V[1],
								(fLocal_16 * local_228.Rotation.V[1] - fLocal_17 * 0.0
									) + local_228.Rotation.V[3] * fVar21 + fLocal_12 +
								local_228.Translation.V[0])));

				} else {
					fLocal_15 = local_228.Rotation.V[1] + local_228.Rotation.V[1];
					fVar34 = (local_228.Rotation.V[0] + local_228.Rotation.V[0]) * local_228.Rotation.V[0];
					fLocal_3 = SUB164((undefined[16])GlobalVectorConstants::FloatOne >> 0x40, 0);
					fVar48 = (local_228.Rotation.V[3] * 0.0 + fLocal_15 * local_228.Rotation.V[0]) * fLocal_9;
					fVar49 = ((local_228.Rotation.V[0] + local_228.Rotation.V[0]) * local_228.Rotation.V[3]
						+ local_228.Rotation.V[1] * 0.0) * fLocal_11;
					fVar37 = fLocal_11 * (fLocal_15 * local_228.Rotation.V[0] - local_228.Rotation.V[3] * 0.0);
					fVar39 = fLocal_9 * (local_228.Rotation.V[0] * 0.0 - fLocal_15 * local_228.Rotation.V[3]);
					fVar25 = (float)((uint)((fLocal_3 - (fLocal_15 * local_228.Rotation.V[1] + fVar34)) * fLocal_0)
						& uVar44);
					fVar34 = (float)((uint)((fVar21 - (fVar34 + fVar34)) * fLocal_1) & uVar45);
					fLocal_15 = fLocal_7 + fLocal_7;
					fLocal_10 = fLocal_10 + fLocal_10;
					fVar31 = (fLocal_6 + fLocal_6) * fLocal_6;
					uVar29 = SUB164((undefined[16])GlobalVectorConstants::FloatOne.m128_u32, 0);
					auVar23 = (undefined[16])GlobalVectorConstants::FloatOne >> 0x20;
					fVar41 = (fLocal_8 * fLocal_10 + fLocal_6 * fLocal_15) * fLocal_16;
					fVar42 = (fLocal_8 * (fLocal_6 + fLocal_6) + fLocal_7 * fLocal_10) * fLocal_4;
					fVar35 = fLocal_4 * (fLocal_6 * fLocal_15 - fLocal_8 * fLocal_10);
					fLocal_10 = fLocal_16 * (fLocal_6 * fLocal_10 - fLocal_8 * fLocal_15);
					fLocal_15 = (float)((uint)((fLocal_3 - (fLocal_15 * fLocal_7 + fVar31)) * fLocal_17) & uVar44);
					fLocal_6 = (float)((uint)((fVar21 - (fVar31 + fVar31)) * fLocal_5) & uVar45);
					_local_518 = CONCAT412(fVar41 * fVar34 + fVar34 * 0.0 + fVar34 * 0.0 + fLocal_6 * fVar21,
						CONCAT48(fVar41 * fVar49 +
							SUB164(ZEXT1216(ZEXT812(0)) >> 0x40, 0) * fVar39 +
							fVar25 * 0.0 + fLocal_6 * local_228.Translation.V[2],
							CONCAT44(fVar41 * 0.0 + fVar48 * 0.0 + fLocal_10 * 0.0 +
								fLocal_6 * local_228.Translation.V[1],
								fVar41 * fVar37 + 0.0 + fLocal_10 * 0.0 +
								fLocal_6 * local_228.Translation.V[0])));
					_local_508 = CONCAT412(fVar34 * 0.0 + fVar35 * fVar34 + fVar34 * 0.0 + fLocal_6 * fVar21,
						CONCAT48(fVar49 * 0.0 + fVar35 * fVar39 + fVar25 * 0.0 +
							fLocal_6 * local_228.Translation.V[2],
							CONCAT44(fVar35 * fVar48 + 0.0 + fVar42 * 0.0 +
								fLocal_6 * local_228.Translation.V[1],
								fVar37 * 0.0 + fVar35 * 0.0 + fVar42 * 0.0 +
								fLocal_6 * local_228.Translation.V[0])));
					_local_4f8 = CONCAT412(fVar34 * 0.0 + fVar34 * 0.0 + fVar34 * 0.0 + fLocal_6 * fVar21,
						CONCAT48(fVar49 * 0.0 +
							SUB164(ZEXT1216(ZEXT812(0)) >> 0x40, 0) * fVar39 +
							fVar25 * 0.0 + fLocal_6 * local_228.Translation.V[2],
							CONCAT44(fVar48 * 0.0 + 0.0 + fLocal_15 * 0.0 +
								fLocal_6 * local_228.Translation.V[1],
								fVar37 * 0.0 + 0.0 + fLocal_15 * 0.0 +
								fLocal_6 * local_228.Translation.V[0])));
					local_4e8 = CONCAT412(fLocal_13 * fVar34 + fLocal_12 * fVar34 + fVar34 * 0.0 + fVar21 * fVar21
						, CONCAT48(fLocal_13 * fVar49 + fLocal_12 * fVar39 + fVar25 * 0.0 +
							fVar21 * local_228.Translation.V[2],
							CONCAT44(fLocal_13 * 0.0 + fLocal_12 * fVar48 + fLocal_14 * 0.0 +
								fVar21 * local_228.Translation.V[1],
								fLocal_13 * fVar37 + fLocal_12 * 0.0 + fLocal_14 * 0.0 +
								fVar21 * local_228.Translation.V[0])));
					_func__thiscall_void_float(local_518, 1e-08);
					auVar4 = _local_518;
					uVar28 = SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne >> 0x20, 0);
					fVar21 = (float)(-(uint)(SUB164((undefined[16])
						GlobalVectorConstants::FloatZero.m128_f32, 0) <=
						fLocal_16 * fLocal_9) &
						(SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne.m128_u32,
							0) ^ uVar29) ^
						SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne.m128_u32, 0)
						);
					fLocal_12 = (float)(-(uint)(SUB164((undefined[16])GlobalVectorConstants::FloatZero >>
						0x20, 0) <= fLocal_4 * fLocal_11) &
						(uVar28 ^ SUB164(auVar23, 0)) ^ uVar28);
					_local_518 = CONCAT124(stack0xfffffffffffffaec, local_518._0_4_ * fVar21);
					local_518 = (undefined[8])
						((unsigned long long)local_518 & 0xffffffff |
							(unsigned long long)(uint)(local_518._4_4_ * fVar21) << 0x20);
					_local_508 = CONCAT124(CONCAT84(uStack_500, local_508._4_4_ * fLocal_12),
						local_508._0_4_ * fLocal_12);
					local_4f8 = (undefined[8])CONCAT44(local_4f8._4_4_ * 0.0, local_4f8._0_4_ * 0.0);
					_func__thiscall_undefined_fLocal_ptr(&local_3c8, (FMatrix*)local_518);
					someTransform = (FTransform*)local_1f8;
					fLocal_6 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf.m128_f32, 0);
					fLocal_7 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x20, 0);
					fLocal_10 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x40, 0);
					fLocal_8 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x60, 0);
					local_1d8 = CONCAT412(fLocal_5 * fLocal_1,
						CONCAT48(fLocal_17 * fLocal_0, CONCAT44(fLocal_4 * fLocal_11, fLocal_16 * fLocal_9)
						));
					fVar21 = local_3c8 * local_3c8 + fStack_3c0 * fStack_3c0;
					fLocal_12 = fStack_3c4 * fStack_3c4 + fStack_3bc * fStack_3bc;
					fLocal_13 = fStack_3c0 * fStack_3c0 + local_3c8 * local_3c8;
					fLocal_14 = fStack_3bc * fStack_3bc + fStack_3c4 * fStack_3c4;
					fLocal_17 = fLocal_12 + fVar21;
					fLocal_16 = fLocal_12 + 0.0;
					fLocal_15 = fLocal_14 + fLocal_13;
					fLocal_4 = fVar21 + fLocal_14;
					auVar23 = rsqrtps(CONCAT412(fLocal_14, CONCAT48(fLocal_13, CONCAT44(fLocal_12, fVar21))),
						CONCAT412(fLocal_4, CONCAT48(fLocal_15, CONCAT44(fLocal_16, fLocal_17))));
					fLocal_15 = fLocal_15 * fLocal_10;
					fVar21 = SUB164(auVar23, 0);
					fLocal_12 = SUB164(auVar23 >> 0x20, 0);
					fLocal_13 = SUB164(auVar23 >> 0x40, 0);
					fLocal_14 = SUB164(auVar23 >> 0x60, 0);
					fVar21 = (fLocal_6 - fVar21 * fVar21 * fLocal_17 * fLocal_6) * fVar21 + fVar21;
					fLocal_12 = (fLocal_7 - fLocal_12 * fLocal_12 * fLocal_16 * fLocal_7) * fLocal_12 + fLocal_12;
					fLocal_13 = (fLocal_10 - fLocal_13 * fLocal_13 * fLocal_15) * fLocal_13 + fLocal_13;
					fLocal_14 = (fLocal_8 - fLocal_14 * fLocal_14 * fLocal_4 * fLocal_8) * fLocal_14 + fLocal_14;
					local_1e8 = local_4e8 & (undefined[16])0xffffffffffffffff;
					uVar28 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x20, 0);
					uVar29 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x40, 0);
					uVar30 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x60, 0);
					local_1f8 = CONCAT412(((uint)(((fLocal_8 - fLocal_14 * fLocal_14 * fLocal_4 * fLocal_8) * fLocal_14 +
						fLocal_14) * fStack_3bc) ^ uVar30) & -(uint)(1e-08 <= fLocal_2)
						^ uVar30, CONCAT48(((uint)(((fLocal_10 - fLocal_13 * fLocal_13 * fLocal_15) *
							fLocal_13 + fLocal_13) * fStack_3c0) ^ uVar29
							) & -(uint)(1e-08 <= fLocal_4) ^ uVar29,
							CONCAT44(((uint)(((fLocal_7 - fLocal_12 * fLocal_12 *
								fLocal_16 * fLocal_7) *
								fLocal_12 + fLocal_12) * fStack_3c4)
								^ uVar28) & -(uint)(1e-08 <= fLocal_16) ^
								uVar28, ((uint)(((fLocal_6 - fVar21 *
									fVar21 * fLocal_17 * fLocal_6) * fVar21 + fVar21) *
									local_3c8) ^
									SUB164((undefined[16])
										GlobalVectorConstants::Float0001.m128_u32, 0
									)) & -(uint)(1e-08 <= fLocal_17) ^
								SUB164((undefined[16])
									GlobalVectorConstants::Float0001.m128_u32, 0
								)))
					);
				}
			}
				
			SetActorTransform(*someTransform);
			goto LAB_180511897;
		}

		// UOBJ //
		hitUObjRef = (UObject*)&(hitResult.Actor);
		if (hitUObjRef != NULL && hitUObjRef->ImplementsInterface(UFGPipeAttachmentSnapTargetInterface)) {

			local_598.Z = *(float*)(hitResult.Location).field_0x8;
			local_598._0_8_ = *(undefined8*)hitResult.Location;

			local_5b8._0_8_ = *(undefined8*)ForwardVector_exref;
			local_5b8.Z = *(float*)(ForwardVector_exref + 8);

			TrySnapToConnection(this, 300.0, &local_598, &local_5b8);

			if (this->mSnappedConnectionComponent != (UFGPipeConnectionComponent*)0x0) {
				if (this->mSnappedConnectionComponent->field_0x200 == '\x03') {
					if ((*(float*)hitResult.Location - local_598.X) * local_5b8.X +
						local_5b8.Y * (*(float*)(hitResult.Location).field_0x4 - local_598.Y) +
						(*(float*)(hitResult.Location).field_0x8 - local_598.Z) * local_5b8.Z < 0.0) {
						fVar21 = 1.0;
					} else {
						fVar21 = -1.0;
					}
					local_5b8.Z = local_5b8.Z * fVar21;
					local_5b8._0_8_ = CONCAT44(local_5b8.Y * fVar21, local_5b8.X * fVar21);
				}
				someMatrix = (FMatrix*)FRotationMatrix::MakeFromX(&local_2a8, (FVector*)&local_5b8);
				local_3e8 = someMatrix->Rotator();
				pcVar2 = OneVector_exref;
				FRotator::Quaternion(&local_3e8, &local_3b8);
				fLocal_12 = local_598.Z;
				local_410 = &this->mPipeConnectionComponents;
				fLocal_13 = (float)*(undefined8*)pcVar2;
				fLocal_14 = (float)((unsigned long long) * (undefined8*)pcVar2 >> 0x20);
				fLocal_15 = (float)local_598._0_8_;
				fLocal_17 = (float)((unsigned long long)local_598._0_8_ >> 0x20);
				fVar21 = *(float*)(pcVar2 + 8);
				auVar3 = *(undefined(*)[12])pcVar2;

				unsigned int snapIndex = this->mSnapConnectionIndex;
				uVar28 = 0;
				if (snapIndex < mPipeConnectionComponents.Num()) {
					uVar28 = ~snapIndex >> 0x1f;
				}

				if (uVar28 == 0) {
					local_418 = snapIndex;
					_func__cdecl_void_<lambda_e564da29fc75c0aef1975a3dea611db9>_ptr((<lambda_e564da29fc75c0aef1975a3dea611db9> *) & local_418);
					pcVar2 = (code*)swi(3);
					uVar6 = (*pcVar2)();
					return (bool)uVar6;
				}

				sceneComponent = *(USceneComponent**)((local_410->AllocatorInstance).Data + snapIndex * 8);
				someTransform = USceneComponent::GetRelativeTransform(sceneComponent, &local_168);

				uVar28 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x20, 0);
				uVar29 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x40, 0);
				uVar30 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x60, 0);

				fLocal_7 = SUB164((undefined[16])GlobalVectorConstants::SmallNumber >> 0x20, 0);
				fLocal_10 = SUB164((undefined[16])GlobalVectorConstants::SmallNumber >> 0x60, 0);

				uVar43 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x20, 0);
				uVar44 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x40, 0);
				uVar45 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x60, 0);

				auVar23 = *(undefined(*)[16])(someTransform->Scale3D).V;

				fLocal_8 = SUB164(auVar23, 0);
				fLocal_9 = SUB164(auVar23 >> 0x20, 0);
				fLocal_11 = SUB164(auVar23 >> 0x40, 0);

				fLocal_4 = (float)((uint)fLocal_8 & SUB164((undefined[16])GlobalVectorConstants::SignMask.m128_u32, 0));
				fLocal_5 = (float)((uint)fLocal_9 & uVar28);
				fLocal_6 = (float)(SUB164(auVar23 >> 0x60, 0) & uVar30);

				//Extract Packed Single-Precision Floating-Point Sign Mask
				iVar18 = movmskps((int)sceneComponent,
					CONCAT412(-(uint)(fLocal_10 < in_xmmTmp2_Dd),
						CONCAT48(-(uint)(SUB164((undefined[16])
							GlobalVectorConstants::SmallNumber >>
							0x40, 0) < fLocal_6),
							CONCAT44(-(uint)(fLocal_7 < fLocal_5),
								-(uint)(SUB164((undefined[16])
									GlobalVectorConstants::
									SmallNumber.m128_f32, 0) <
									fLocal_4)))));

				fLocal_16 = SUB164((undefined[16])GlobalVectorConstants::FloatOne >> 0x60, 0);
				if (iVar18 == 0) {
					fLocal_0 = *(float*)Identity_exref;
					fLocal_1 = *(float*)(Identity_exref + 4);
					fLocal_2 = *(float*)(Identity_exref + 8);
					fLocal_3 = *(float*)(Identity_exref + 0xc);
					fLocal_4 = *(float*)(Identity_exref + 0x10);
					fLocal_5 = *(float*)(Identity_exref + 0x14);
					fLocal_6 = *(float*)(Identity_exref + 0x18);
					fLocal_7 = *(float*)(Identity_exref + 0x1c);
					fLocal_8 = *(float*)(Identity_exref + 0x20);
					fLocal_9 = *(float*)(Identity_exref + 0x24);
					fLocal_10 = *(float*)(Identity_exref + 0x28);
					fLocal_11 = *(float*)(Identity_exref + 0x2c);
					someTransform = (FTransform*)Identity_exref;
				} else {
					fLocal_0 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK.m128_f32, 0) * (someTransform->Rotation).V[0];
					fLocal_1 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x20, 0) * (someTransform->Rotation).V[1];
					fLocal_2 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x40, 0) * (someTransform->Rotation).V[2];
					fLocal_3 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x60, 0) * (someTransform->Rotation).V[3];
					auVar23 = rcpps(CONCAT412(fLocal_6, CONCAT48((uint)fLocal_11 & uVar29, CONCAT44(fLocal_5, fLocal_4))), CONCAT412(fLocal_16, SUB1612(auVar23, 0)));

					fLocal_4 = SUB164(auVar23, 0);
					fLocal_5 = SUB164(auVar23 >> 0x20, 0);
					fLocal_6 = SUB164(auVar23 >> 0x40, 0);
					fVar25 = SUB164(auVar23 >> 0x60, 0);

					fLocal_4 = (fLocal_4 + fLocal_4) - fLocal_4 * fLocal_4 * fLocal_8;
					fLocal_5 = (fLocal_5 + fLocal_5) - fLocal_5 * fLocal_5 * fLocal_9;
					fLocal_6 = (fLocal_6 + fLocal_6) - fLocal_6 * fLocal_6 * fLocal_11;
					fVar25 = (fVar25 + fVar25) - fVar25 * fVar25 * fLocal_16;

					fLocal_4 = (fLocal_4 + fLocal_4) - fLocal_4 * fLocal_4 * fLocal_8;
					fLocal_5 = (fLocal_5 + fLocal_5) - fLocal_5 * fLocal_5 * fLocal_9;
					fLocal_6 = (fLocal_6 + fLocal_6) - fLocal_6 * fLocal_6 * fLocal_11;
					fVar25 = (fVar25 + fVar25) - fVar25 * fVar25 * fLocal_16;

					fLocal_8 = (float)((-(uint)((float)((uint)fLocal_8 &
						SUB164((undefined[16])
							GlobalVectorConstants::SignMask.m128_u32, 0)) <=
						SUB164((undefined[16])
							GlobalVectorConstants::SmallNumber.m128_f32, 0)) &
						(uint)fLocal_4 ^ (uint)fLocal_4) &
						SUB164((undefined[16])GlobalVectorConstants::XYZMask.m128_u32, 0));
					fLocal_9 = (float)((-(uint)((float)((uint)fLocal_9 & uVar28) <= fLocal_7) & (uint)fLocal_5 ^
						(uint)fLocal_5) & uVar43);
					fLocal_10 = (float)((-(uint)((float)((uint)fLocal_11 & uVar29) <= fLocal_10) & (uint)fLocal_6 ^
						(uint)fLocal_6) & uVar44);
					fLocal_11 = (float)((-(uint)((float)((uint)fLocal_16 & uVar30) <= in_xmmTmp2_Dd) &
						(uint)fVar25 ^ (uint)fVar25) & uVar45);

					fLocal_4 = fLocal_8 * (someTransform->Translation).V[0];
					fLocal_5 = fLocal_9 * (someTransform->Translation).V[1];
					fVar31 = fLocal_10 * (someTransform->Translation).V[2];
					fVar35 = fLocal_11 * (someTransform->Translation).V[3];
					fLocal_6 = fLocal_1 * 0.0 - fLocal_5 * 0.0;
					fLocal_7 = fLocal_4 * fLocal_2 - fVar31 * fLocal_0;
					fVar25 = fLocal_5 * fLocal_0 - fLocal_4 * fLocal_1;
					fVar34 = fVar35 * fLocal_3 - fVar35 * fLocal_3;
					fLocal_6 = fLocal_6 + fLocal_6;
					fLocal_7 = fLocal_7 + fLocal_7;
					fVar25 = fVar25 + fVar25;
					fVar34 = fVar34 + fVar34;
					fLocal_4 = (float)((uint)(0.0 - ((fLocal_1 * 0.0 - fLocal_7 * 0.0) + fLocal_3 * fLocal_6 + fLocal_4)
						) &
						SUB164((undefined[16])GlobalVectorConstants::XYZMask.m128_u32, 0));
					fLocal_5 = (float)((uint)(0.0 - ((fLocal_6 * fLocal_2 - fVar25 * fLocal_0) +
						fLocal_3 * fLocal_7 + fLocal_5)) & uVar43);
					fLocal_6 = (float)((uint)(0.0 - ((fLocal_7 * fLocal_0 - fLocal_6 * fLocal_1) +
						fLocal_3 * fVar25 + fVar31)) & uVar44);
					fLocal_7 = (float)((uint)(0.0 - ((fVar34 * fLocal_3 - fVar34 * fLocal_3) +
						fLocal_3 * fVar34 + fVar35)) & uVar45);
				}
				auVar23 = minps(CONCAT412(fLocal_11, CONCAT48(fLocal_10, CONCAT44(fLocal_9, fLocal_8))),
					ZEXT1216(auVar3));
				fVar25 = SUB164((undefined[16])GlobalVectorConstants::FloatZero >> 0x60, 0);
				iVar18 = movmskps((int)someTransform,
					CONCAT412(-(uint)(SUB164(auVar23 >> 0x60, 0) < fVar25),
						CONCAT48(-(uint)(SUB164(auVar23 >> 0x40, 0) <
							SUB164((undefined[16])
								GlobalVectorConstants::FloatZero >>
								0x40, 0)),
							CONCAT44(-(uint)(SUB164(auVar23 >> 0x20, 0) <
								SUB164((undefined[16])
									GlobalVectorConstants::
									FloatZero >> 0x20, 0)),
								-(uint)(SUB164(auVar23, 0) <
									SUB164((undefined[16])
										GlobalVectorConstants::
										FloatZero.m128_f32, 0))))));
				if (iVar18 == 0) {
					fLocal_4 = fLocal_4 * fLocal_13;
					fLocal_5 = fLocal_5 * fLocal_14;
					fLocal_7 = fLocal_7 * 0.0;
					local_1a8 = CONCAT412(fLocal_11 * 0.0,
						CONCAT48(fLocal_10 * fVar21, CONCAT44(fLocal_9 * fLocal_14, fLocal_8 * fLocal_13)
						));
					local_1c8 = CONCAT412(fLocal_0 * local_3b8.X *
						SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK0
							>> 0x60, 0) + local_3b8.W * fLocal_3 +
						fLocal_1 * local_3b8.Y *
						SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK1
							>> 0x60, 0) +
						SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK2
							>> 0x60, 0) * 0.0,
						CONCAT48(fLocal_1 * local_3b8.X *
							SUB164((undefined[16])
								GlobalVectorConstants::QMULTI_SIGN_MASK0 >> 0x40, 0
							) + local_3b8.W * fLocal_2 +
							fLocal_0 * local_3b8.Y *
							SUB164((undefined[16])
								GlobalVectorConstants::QMULTI_SIGN_MASK1 >> 0x40, 0
							) + fLocal_3 * 0.0 *
							SUB164((undefined[16])
								GlobalVectorConstants::QMULTI_SIGN_MASK2
								>> 0x40, 0),
							CONCAT44(local_3b8.X * 0.0 *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK0
									>> 0x20, 0) + local_3b8.W * fLocal_1 +
								fLocal_3 * local_3b8.Y *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK1
									>> 0x20, 0) +
								fLocal_0 * local_3b8.Z *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK2
									>> 0x20, 0),
								fLocal_3 * local_3b8.X *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK0.
									m128_f32, 0) + local_3b8.W * fLocal_0 +
								fLocal_2 * local_3b8.Y *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK1.
									m128_f32, 0) +
								fLocal_1 * local_3b8.Z *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK2.
									m128_f32, 0))));
					fLocal_13 = local_3b8.Y * 0.0 - fLocal_5 * 0.0;
					fLocal_14 = fLocal_4 * 0.0 - fLocal_6 * fVar21 * local_3b8.X;
					fLocal_16 = fLocal_5 * local_3b8.X - fLocal_4 * local_3b8.Y;
					fLocal_10 = fLocal_7 * local_3b8.W - fLocal_7 * local_3b8.W;
					fLocal_13 = fLocal_13 + fLocal_13;
					fLocal_14 = fLocal_14 + fLocal_14;
					fLocal_16 = fLocal_16 + fLocal_16;
					fLocal_10 = fLocal_10 + fLocal_10;
					local_1b8 = CONCAT412((fLocal_10 * local_3b8.W - fLocal_10 * local_3b8.W) +
						local_3b8.W * fLocal_10 + fLocal_7 + 0.0,
						CONCAT48((fLocal_14 * local_3b8.X - fLocal_13 * local_3b8.Y) +
							local_3b8.W * fLocal_16 + fLocal_6 * fVar21 + fLocal_12,
							CONCAT44((fLocal_13 * 0.0 - fLocal_16 * local_3b8.X) +
								local_3b8.W * fLocal_14 + fLocal_5 + fLocal_17,
								(fLocal_16 * local_3b8.Y - fLocal_14 * 0.0) +
								local_3b8.W * fLocal_13 + fLocal_4 + fLocal_15)));
				} else {
					fLocal_7 = local_3b8.Y + local_3b8.Y;
					local_3b8.Z = local_3b8.Z + local_3b8.Z;
					fVar35 = (local_3b8.X + local_3b8.X) * local_3b8.X;
					fVar34 = SUB164((undefined[16])GlobalVectorConstants::FloatOne >> 0x40, 0);
					fVar46 = (local_3b8.W * local_3b8.Z + local_3b8.X * fLocal_7) * fLocal_13;
					fVar47 = (local_3b8.W * (local_3b8.X + local_3b8.X) + local_3b8.Y * local_3b8.Z) *
						fLocal_14;
					fVar39 = fLocal_14 * (local_3b8.X * fLocal_7 - local_3b8.W * local_3b8.Z);
					fVar42 = fLocal_13 * (local_3b8.X * local_3b8.Z - local_3b8.W * fLocal_7);
					fVar31 = (float)((uint)((fVar34 - (fLocal_7 * local_3b8.Y + fVar35)) * fVar21) & uVar44);
					fVar35 = (float)((uint)((fLocal_16 - (fVar35 + fVar35)) * 0.0) & uVar45);
					fLocal_7 = fLocal_1 + fLocal_1;
					fLocal_2 = fLocal_2 + fLocal_2;
					fVar37 = (fLocal_0 + fLocal_0) * fLocal_0;
					uVar29 = SUB164((undefined[16])GlobalVectorConstants::FloatOne.m128_u32, 0);
					auVar23 = (undefined[16])GlobalVectorConstants::FloatOne >> 0x20;
					fVar48 = (fLocal_3 * fLocal_2 + fLocal_0 * fLocal_7) * fLocal_8;
					fVar49 = (fLocal_3 * (fLocal_0 + fLocal_0) + fLocal_1 * fLocal_2) * fLocal_9;
					fVar41 = fLocal_9 * (fLocal_0 * fLocal_7 - fLocal_3 * fLocal_2);
					fLocal_2 = fLocal_8 * (fLocal_0 * fLocal_2 - fLocal_3 * fLocal_7);
					fLocal_7 = (float)((uint)((fVar34 - (fLocal_7 * fLocal_1 + fVar37)) * fLocal_10) & uVar44);
					fLocal_0 = (float)((uint)((fLocal_16 - (fVar37 + fVar37)) * fLocal_11) & uVar45);
					local_558 = CONCAT412(fVar48 * fVar35 + fVar35 * 0.0 + fVar35 * 0.0 + fLocal_0 * fLocal_16,
						CONCAT48(fVar48 * fVar47 +
							SUB164(ZEXT1216(ZEXT812(0)) >> 0x40, 0) * fVar42 +
							fVar31 * 0.0 + fLocal_0 * fLocal_12,
							CONCAT44(fVar48 * 0.0 + fVar46 * 0.0 + fLocal_2 * 0.0 +
								fLocal_0 * fLocal_17,
								fVar48 * fVar39 + 0.0 + fLocal_2 * 0.0 +
								fLocal_0 * fLocal_15)));
					_local_548 = CONCAT412(fVar35 * 0.0 + fVar41 * fVar35 + fVar35 * 0.0 + fLocal_0 * fLocal_16,
						CONCAT48(fVar47 * 0.0 + fVar41 * fVar42 + fVar31 * 0.0 +
							fLocal_0 * fLocal_12,
							CONCAT44(fVar41 * fVar46 + 0.0 + fVar49 * 0.0 +
								fLocal_0 * fLocal_17,
								fVar39 * 0.0 + fVar41 * 0.0 + fVar49 * 0.0 +
								fLocal_0 * fLocal_15)));
					_local_538 = CONCAT412(fVar35 * 0.0 + fVar35 * 0.0 + fVar35 * 0.0 + fLocal_0 * fLocal_16,
						CONCAT48(fVar47 * 0.0 +
							SUB164(ZEXT1216(ZEXT812(0)) >> 0x40, 0) * fVar42 +
							fVar31 * 0.0 + fLocal_0 * fLocal_12,
							CONCAT44(fVar46 * 0.0 + 0.0 + fLocal_7 * 0.0 +
								fLocal_0 * fLocal_17,
								fVar39 * 0.0 + 0.0 + fLocal_7 * 0.0 +
								fLocal_0 * fLocal_15)));
					local_528 = CONCAT412(fLocal_5 * fVar35 + fLocal_4 * fVar35 + fVar35 * 0.0 + fLocal_16 * fLocal_16
						, CONCAT48(fLocal_5 * fVar47 + fLocal_4 * fVar42 + fVar31 * 0.0 +
							fLocal_16 * fLocal_12,
							CONCAT44(fLocal_5 * 0.0 + fLocal_4 * fVar46 + fLocal_6 * 0.0 +
								fLocal_16 * fLocal_17,
								fLocal_5 * fVar39 + fLocal_4 * 0.0 + fLocal_6 * 0.0 +
								fLocal_16 * fLocal_15)));
					_func__thiscall_void_float(local_558, 1e-08);
					uVar28 = SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne >> 0x20, 0);
					fLocal_12 = (float)(-(uint)(SUB164((undefined[16])
						GlobalVectorConstants::FloatZero.m128_f32, 0) <=
						fLocal_8 * fLocal_13) &
						(SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne.m128_u32,
							0) ^ uVar29) ^
						SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne.m128_u32, 0)
						);
					fLocal_15 = (float)(-(uint)(SUB164((undefined[16])GlobalVectorConstants::FloatZero >>
						0x20, 0) <= fLocal_9 * fLocal_14) &
						(uVar28 ^ SUB164(auVar23, 0)) ^ uVar28);
					_local_548 = CONCAT124(_auStack_544, (float)local_548 * fLocal_15);
					_local_538 = CONCAT124(_auStack_534, (float)local_538 * 0.0);
					_func__thiscall_undefined_fLocal_ptr(&local_3a8, (FMatrix*)local_558);
					fLocal_5 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf.m128_f32, 0);
					fLocal_6 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x20, 0);
					fLocal_7 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x40, 0);
					fLocal_0 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x60, 0);
					local_1a8 = CONCAT412(fLocal_11 * 0.0,
						CONCAT48(fLocal_10 * fVar21, CONCAT44(fLocal_9 * fLocal_14, fLocal_8 * fLocal_13)
						));
					fVar21 = local_3a8 * local_3a8 + fStack_3a0 * fStack_3a0;
					fLocal_12 = fStack_3a4 * fStack_3a4 + fStack_39c * fStack_39c;
					fLocal_13 = fStack_3a0 * fStack_3a0 + local_3a8 * local_3a8;
					fLocal_14 = fStack_39c * fStack_39c + fStack_3a4 * fStack_3a4;
					fLocal_17 = fLocal_12 + fVar21;
					fLocal_16 = fLocal_12 + 0.0;
					fLocal_15 = fLocal_14 + fLocal_13;
					fLocal_4 = fVar21 + fLocal_14;
					auVar23 = rsqrtps(CONCAT412(fLocal_14, CONCAT48(fLocal_13, CONCAT44(fLocal_12, fVar21))),
						CONCAT412(fLocal_4, CONCAT48(fLocal_15, CONCAT44(fLocal_16, fLocal_17))));
					fLocal_15 = fLocal_15 * fLocal_7;
					fVar21 = SUB164(auVar23, 0);
					fLocal_12 = SUB164(auVar23 >> 0x20, 0);
					fLocal_13 = SUB164(auVar23 >> 0x40, 0);
					fLocal_14 = SUB164(auVar23 >> 0x60, 0);
					fVar21 = (fLocal_5 - fVar21 * fVar21 * fLocal_17 * fLocal_5) * fVar21 + fVar21;
					fLocal_12 = (fLocal_6 - fLocal_12 * fLocal_12 * fLocal_16 * fLocal_6) * fLocal_12 + fLocal_12;
					fLocal_13 = (fLocal_7 - fLocal_13 * fLocal_13 * fLocal_15) * fLocal_13 + fLocal_13;
					fLocal_14 = (fLocal_0 - fLocal_14 * fLocal_14 * fLocal_4 * fLocal_0) * fLocal_14 + fLocal_14;
					local_1b8 = local_528 & (undefined[16])0xffffffffffffffff;
					uVar28 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x20, 0);
					uVar29 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x40, 0);
					uVar30 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x60, 0);
					local_1c8 = CONCAT412(((uint)(((fLocal_0 - fLocal_14 * fLocal_14 * fLocal_4 * fLocal_0) * fLocal_14 +
						fLocal_14) * fStack_39c) ^ uVar30) & -(uint)(1e-08 <= fVar25)
						^ uVar30, CONCAT48(((uint)(((fLocal_7 - fLocal_13 * fLocal_13 * fLocal_15) *
							fLocal_13 + fLocal_13) * fStack_3a0) ^ uVar29
							) & -(uint)(1e-08 <= fLocal_4) ^ uVar29,
							CONCAT44(((uint)(((fLocal_6 - fLocal_12 * fLocal_12 *
								fLocal_16 * fLocal_6) *
								fLocal_12 + fLocal_12) * fStack_3a4)
								^ uVar28) & -(uint)(1e-08 <= fLocal_16) ^
								uVar28, ((uint)(((fLocal_5 - fVar21 *
									fVar21 * fLocal_17 * fLocal_5) * fVar21 + fVar21) *
									local_3a8) ^
									SUB164((undefined[16])
										GlobalVectorConstants::Float0001.m128_u32, 0
									)) & -(uint)(1e-08 <= fLocal_17) ^
								SUB164((undefined[16])
									GlobalVectorConstants::Float0001.m128_u32, 0
								))));
				}
				AActor::SetActorTransform(local_1c8, false);
			}
			goto LAB_180511897;
		}


		// WALL //
		hitWallRef = (AFGBuildableWall*)&(hitResult.Actor);
		if (hitWallRef != NULL) {
			*(AFGBuildableWall**)&this->field_0x460 = hitWallRef;
			iVar18 = (**(code**)(*(long long*)this + 0x7a0))(this);
			fVar21 = AFGHologram::ApplyScrollRotationTo(0.0, false);
			local_4d8.Y = (this->mWallSnapOffset).X;
			local_4cc.Y = *(float*)&(hitResult->TraceStart).field_0x4 - *(float*)&(hitResult->Location).field_0x4;
			local_4d8.X = 200.0;
			local_4d8.Z = (this->mWallSnapOffset).Y;
			local_4cc.X = *(float*)&hitResult->TraceStart - *(float*)&(hitResult->Location).field_0x0;
			local_4cc.Z = *(float*)&(hitResult->TraceStart).field_0x8 - *(float*)&(hitResult->Location).field_0x8;

			SnapToWall(
				hitWallRef,
				local_4cc,
				hitResult.Location,
				EAxis::Z,
				local_4d8,
				(float)(((int)ROUND(fVar21 * (2.0 / (float)iVar18) + 0.5) >> 1) * iVar18),
				local_478,
				local_488
			);

			local_468._0_8_ = local_488._0_8_;
			local_468.Roll = local_488.Roll;
			local_458.V._0_8_ = local_478._0_8_;
			local_458.V[2] = local_478.Z;

			SetActorLocationAndRotation(local_458, local_468);
		}
	
	}
	else if (mBuildStep == EPipelineAttachmentBuildStep::PABS_AdjustRotation && this->mSnappedPipeline != NULL) {

		sceneComponent = *(USceneComponent**)&this->field_0x170;
		if (sceneComponent == (USceneComponent*)0x0) {
			puVar20 = (undefined8*)&local_4b4;
			pFVar17 = &local_4a8;
			local_4b4 = *(undefined4*)&this->field_0x40;
			local_4b0 = *(undefined4*)&this->field_0x44;
			fVar21 = (float)((uint) * (float*)&this->field_0x34 ^ 0x80000000);
			local_4ac = *(undefined4*)&this->field_0x48;
			fVar21 = fVar21 + fVar21;
			local_4a8.X = (fVar21 * *(float*)&this->field_0x34 - 0.0) + 1.0;
			local_4a8.Z = *(float*)&this->field_0x30 * 0.0 + fVar21 * *(float*)&this->field_0x3c;
			local_4a8.Y = *(float*)&this->field_0x3c * 0.0 - fVar21 * *(float*)&this->field_0x30;
		}
		else {
			float compX = (sceneComponent->ComponentToWorld).Translation.X;
			float compY = (sceneComponent->ComponentToWorld).Translation.Y;
			float compZ = (sceneComponent->ComponentToWorld).Translation.Z;
			puVar20 = (undefined8*)&compX;
			pFVar17 = sceneComponent->GetForwardVector(&local_38c);
		}

		local_498._0_8_ = *(undefined8*)pFVar17->V;
		local_498.Z = pFVar17->V[2];
		fVar21 = ApplyScrollRotationTo(0.0, false);
		_func__thiscall_FVector_float_FVector_ptr
		(&this->mBuildStepUpVector, &local_3f8, fVar21, &local_498);
		someMatrix = (FMatrix*)FRotationMatrix::MakeFromXZ(&local_268, (FVector*)&local_498, (FVector*)&local_3f8);
		local_448 = someMatrix->Rotator();
		local_438._0_8_ = local_448._0_8_;
		local_428.V._0_8_ = *puVar20;
		local_438.Roll = local_448.Roll;
		local_428.V[2] = *(float*)(puVar20 + 1);
		SetActorLocationAndRotation(local_428, local_438);
	}
}
//*/