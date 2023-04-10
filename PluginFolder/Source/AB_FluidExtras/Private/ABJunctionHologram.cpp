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

		FRotator::

		GetScrollRotateValue() * -1;

		SetActorRotation();

		mSnappedConnectionComponent->GetComponentRotation();

	} else if(mSnappedPipeline != NULL) {
		
	}
}

		/*
bool AABJunctionHologram::VanillaTrySnap(const FHitResult& hitResult) {
	char uVar1;
	code* pcVar2;
	undefined auVar3[12];
	undefined auVar4[16];
	undefined uVar6;
	undefined extraout_AL;
	AFGBuildablePipeline* hitPipeRef;
	UClass* hitClass;
	FFGHologramGuidelineSnapResult* pFVar9;
	FMatrix* pFVar10;
	FVector* pFVar11;
	FRotator* pFVar12;
	FTransform* pFVar13;
	UObject* hitUObjRef;
	UClass* pUVar15;
	AFGBuildableWall* hitWallRef;
	FVector* pFVar17;
	int iVar18;
	USceneComponent* sceneComponent;
	undefined8* puVar20;
	float fVar21;
	float fVar22;
	float fVar24;
	float fVar25;
	float fVar26;
	undefined auVar23[16];
	float fVar27;
	unsigned int uVar28;
	unsigned int uVar29;
	unsigned int uVar30;
	float fVar31;
	float fVar32;
	float fVar33;
	float fVar34;
	float fVar35;
	float fVar36;
	float fVar37;
	float fVar38;
	float fVar39;
	float fVar40;
	float fVar41;
	float fVar42;
	unsigned int uVar43;
	unsigned int uVar44;
	unsigned int uVar45;
	float fVar46;
	float fVar47;
	float fVar48;
	float fVar49;
	float fVar50;
	float fVar51;
	float fVar52;
	float fVar53;
	float fVar54;
	float fVar55;
	float fVar56;
	float fVar57;
	float in_xmmTmp2_Dd;
	float fVar58;
	undefined auStackY_608[32];
	FVector local_5b8;
	FVector local_5a8;
	FVector local_598;
	FRotator local_588;
	FVector local_578;
	unsigned int local_568[2];
	unsigned int local_560[2];
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
	FMatrix local_328;
	FMatrix local_2e8;
	FMatrix local_2a8;
	FMatrix local_268;
	FTransform local_228;
	undefined local_1f8[16];
	undefined local_1e8[16];
	undefined local_1d8[16];
	undefined local_1c8[16];
	undefined local_1b8[16];
	undefined local_1a8[16];
	FTransform local_198;
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

			hitClass = AFGBuildablePipeline::GetPrivateStaticClass();

			bool valid = UStruct::IsChildOf(*(UStruct**)&hitPipeRef->field_0x10, (UStruct*)hitClass);
			if (valid) {
				this->mSnappedPipeline = hitPipeRef;
				fVar21 = (float)(**(code**)(*(long long*)hitPipeRef + 0x7a0))(hitPipeRef, hitResult.Location);
				this->mSnappedPipelineOffset = fVar21;
				(**(code**)(*(long long*)this->mSnappedPipeline + 0x7a8))();
				TrySnapToConnection(this, 50.0, &local_578, &local_5a8);
				if ((this->field_0x470 == '\0') && (this->field_0x2d1 != '\0')) {
					pFVar9 = AFGBuildableHologram::SnapHologramLocationToGuidelines
					((AFGBuildableHologram*)this, &local_138, &local_578);
					_func__thiscall_FFGHologramGuidelineSnapResult_ptr_FFGHologramGuidelineSnapResult_ptr
					(&this->field_0x400, pFVar9);
					if (this->field_0x45c != '\0') {
						fVar21 = (float)(**(code**)(*(long long*)hitPipeRef + 0x7a0))(hitPipeRef, &this->field_0x450);
						this->mSnappedPipelineOffset = fVar21;
						(**(code**)(*(long long*)this->mSnappedPipeline + 0x7a8))();
					}
				}
				pFVar10 = (FMatrix*)FRotationMatrix::MakeFromX(&local_328, (FVector*)&local_5a8);
				FMatrix::Rotator(pFVar10, &local_588);
				uVar1 = (this->mRotationAxis).Value;

				if (uVar1 == '\x01') {
					fVar21 = AFGHologram::ApplyScrollRotationTo((AFGHologram*)this, 0.0, false);
					local_588._0_8_ =
						local_588._0_8_ & 0xffffffff00000000 | (unsigned long long)(uint)(local_588.Pitch + fVar21);

				} else if (uVar1 == '\x02') {
					fVar21 = AFGHologram::ApplyScrollRotationTo((AFGHologram*)this, 0.0, false);
					local_588.Roll = local_588.Roll + fVar21;

				} else if ((uVar1 == '\x03') &&
					((this->mSnappedConnectionComponent == (UFGPipeConnectionComponent*)0x0 ||
						(this->mIncrementSnappedConnectionOnScroll == false)))) {
					FRotationMatrix::MakeFromX(&local_368, (FVector*)&local_5a8);
					pFVar11 = _func__thiscall_FVector_Type(&local_368, &local_374, Z);
					fVar21 = AFGHologram::ApplyScrollRotationTo((AFGHologram*)this, 0.0, false);
					pFVar11 = _func__thiscall_FVector_float_FVector_ptr(&local_5a8, &local_380, fVar21, pFVar11);
					local_5a8._0_8_ = *(undefined8*)pFVar11;
					local_5a8.Z = pFVar11->Z;
					pFVar10 = (FMatrix*)FRotationMatrix::MakeFromX(&local_2e8, (FVector*)&local_5a8);
					pFVar12 = FMatrix::Rotator(pFVar10, &local_398);
					local_588._0_8_ = *(unsigned long long*)pFVar12;
					local_588.Roll = pFVar12->Roll;
				}

				pcVar2 = OneVector_exref;
				FRotator::Quaternion(&local_588, &local_3d8);
				local_228.Translation.V = (float[4])ZEXT1216((undefined[12])local_578);
				local_228.Rotation.V[0] = local_3d8.X;
				local_228.Rotation.V[1] = local_3d8.Y;
				local_228.Rotation.V[2] = local_3d8.Z;
				local_228.Rotation.V[3] = local_3d8.W;
				local_228.Scale3D.V = (float[4])ZEXT1216(*(undefined(*)[12])pcVar2);
				if (this->mSnappedConnectionComponent == (UFGPipeConnectionComponent*)0x0) {
					pFVar13 = &local_228;

				} else {
					local_560[0] = this->mSnapConnectionIndex;
					local_400 = &this->mPipeConnectionComponents;
					uVar28 = 0;

					if ((int)local_560[0] < (this->mPipeConnectionComponents).ArrayNum) {
						uVar28 = ~local_560[0] >> 0x1f;
					}

					if (uVar28 == 0) {
						local_408 = local_560;
						_func__cdecl_void_<lambda_e564da29fc75c0aef1975a3dea611db9>_ptr
						((<lambda_e564da29fc75c0aef1975a3dea611db9> *) & local_408);
						pcVar2 = (code*)swi(3);
						uVar6 = (*pcVar2)();
						return (bool)uVar6;
					}

					sceneComponent = *(USceneComponent**)((local_400->AllocatorInstance).Data + (long long)(int)local_560[0] * 8);
					pFVar13 = USceneComponent::GetRelativeTransform(sceneComponent, &local_198);
					uVar28 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x20, 0);
					uVar29 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x40, 0);
					uVar30 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x60, 0);
					fVar32 = SUB164((undefined[16])GlobalVectorConstants::SmallNumber >> 0x20, 0);
					fVar33 = SUB164((undefined[16])GlobalVectorConstants::SmallNumber >> 0x60, 0);
					uVar43 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x20, 0);
					uVar44 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x40, 0);
					uVar45 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x60, 0);
					auVar23 = *(undefined(*)[16])(pFVar13->Scale3D).V;
					fVar50 = SUB164(auVar23, 0);
					fVar51 = SUB164(auVar23 >> 0x20, 0);
					fVar52 = SUB164(auVar23 >> 0x40, 0);
					fVar22 = (float)((uint)fVar50 & SUB164((undefined[16])GlobalVectorConstants::SignMask.m128_u32, 0));
					fVar24 = (float)((uint)fVar51 & uVar28);
					fVar26 = (float)(SUB164(auVar23 >> 0x60, 0) & uVar30);
					iVar18 = movmskps((int)sceneComponent,
						CONCAT412(-(uint)(fVar33 < in_xmmTmp2_Dd),
							CONCAT48(-(uint)(SUB164((undefined[16])
								GlobalVectorConstants::SmallNumber >>
								0x40, 0) < fVar26),
								CONCAT44(-(uint)(fVar32 < fVar24),
									-(uint)(SUB164((undefined[16])
										GlobalVectorConstants::
										SmallNumber.m128_f32, 0) <
										fVar22))))
					);
					
					fVar21 = SUB164((undefined[16])GlobalVectorConstants::FloatOne >> 0x60, 0);
					if (iVar18 == 0) {
						fVar54 = *(float*)Identity_exref;
						fVar55 = *(float*)(Identity_exref + 4);
						fVar56 = *(float*)(Identity_exref + 8);
						fVar57 = *(float*)(Identity_exref + 0xc);
						fVar22 = *(float*)(Identity_exref + 0x10);
						fVar24 = *(float*)(Identity_exref + 0x14);
						fVar26 = *(float*)(Identity_exref + 0x18);
						fVar32 = *(float*)(Identity_exref + 0x1c);
						fVar50 = *(float*)(Identity_exref + 0x20);
						fVar51 = *(float*)(Identity_exref + 0x24);
						fVar33 = *(float*)(Identity_exref + 0x28);
						fVar52 = *(float*)(Identity_exref + 0x2c);
						pFVar13 = (FTransform*)Identity_exref;

					} else {
						fVar54 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK.m128_f32, 0) *
							(pFVar13->Rotation).V[0];
						fVar55 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x20, 0) *
							(pFVar13->Rotation).V[1];
						fVar56 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x40, 0) *
							(pFVar13->Rotation).V[2];
						fVar57 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x60, 0) *
							(pFVar13->Rotation).V[3];
						auVar23 = rcpps(CONCAT412(fVar26, CONCAT48((uint)fVar52 & uVar29, CONCAT44(fVar24, fVar22))
						), CONCAT412(fVar21, SUB1612(auVar23, 0)));
						fVar22 = SUB164(auVar23, 0);
						fVar24 = SUB164(auVar23 >> 0x20, 0);
						fVar26 = SUB164(auVar23 >> 0x40, 0);
						fVar27 = SUB164(auVar23 >> 0x60, 0);
						fVar22 = (fVar22 + fVar22) - fVar22 * fVar22 * fVar50;
						fVar24 = (fVar24 + fVar24) - fVar24 * fVar24 * fVar51;
						fVar26 = (fVar26 + fVar26) - fVar26 * fVar26 * fVar52;
						fVar27 = (fVar27 + fVar27) - fVar27 * fVar27 * fVar21;
						fVar22 = (fVar22 + fVar22) - fVar22 * fVar22 * fVar50;
						fVar24 = (fVar24 + fVar24) - fVar24 * fVar24 * fVar51;
						fVar26 = (fVar26 + fVar26) - fVar26 * fVar26 * fVar52;
						fVar27 = (fVar27 + fVar27) - fVar27 * fVar27 * fVar21;
						fVar50 = (float)((-(uint)((float)((uint)fVar50 &
							SUB164((undefined[16])
								GlobalVectorConstants::SignMask.m128_u32, 0)) <=
							SUB164((undefined[16])
								GlobalVectorConstants::SmallNumber.m128_f32, 0)) &
							(uint)fVar22 ^ (uint)fVar22) &
							SUB164((undefined[16])GlobalVectorConstants::XYZMask.m128_u32, 0));
						fVar51 = (float)((-(uint)((float)((uint)fVar51 & uVar28) <= fVar32) & (uint)fVar24 ^
							(uint)fVar24) & uVar43);
						fVar33 = (float)((-(uint)((float)((uint)fVar52 & uVar29) <= fVar33) & (uint)fVar26 ^
							(uint)fVar26) & uVar44);
						fVar52 = (float)((-(uint)((float)((uint)fVar21 & uVar30) <= in_xmmTmp2_Dd) &
							(uint)fVar27 ^ (uint)fVar27) & uVar45);
						fVar22 = fVar50 * (pFVar13->Translation).V[0];
						fVar24 = fVar51 * (pFVar13->Translation).V[1];
						fVar38 = fVar33 * (pFVar13->Translation).V[2];
						fVar40 = fVar52 * (pFVar13->Translation).V[3];
						fVar26 = fVar55 * 0.0 - fVar24 * 0.0;
						fVar32 = fVar22 * fVar56 - fVar38 * fVar54;
						fVar27 = fVar24 * fVar54 - fVar22 * fVar55;
						fVar36 = fVar40 * fVar57 - fVar40 * fVar57;
						fVar26 = fVar26 + fVar26;
						fVar32 = fVar32 + fVar32;
						fVar27 = fVar27 + fVar27;
						fVar36 = fVar36 + fVar36;
						fVar22 = (float)((uint)(0.0 - ((fVar55 * 0.0 - fVar32 * 0.0) + fVar57 * fVar26 + fVar22)
							) &
							SUB164((undefined[16])GlobalVectorConstants::XYZMask.m128_u32, 0));
						fVar24 = (float)((uint)(0.0 - ((fVar26 * fVar56 - fVar27 * fVar54) +
							fVar57 * fVar32 + fVar24)) & uVar43);
						fVar26 = (float)((uint)(0.0 - ((fVar32 * fVar54 - fVar26 * fVar55) +
							fVar57 * fVar27 + fVar38)) & uVar44);
						fVar32 = (float)((uint)(0.0 - ((fVar36 * fVar57 - fVar36 * fVar57) +
							fVar57 * fVar36 + fVar40)) & uVar45);
					}

					fVar27 = SUB164((undefined[16])local_228.Scale3D.V, 0);
					fVar36 = SUB164((undefined[16])local_228.Scale3D.V >> 0x20, 0);
					fVar38 = SUB164((undefined[16])local_228.Scale3D.V >> 0x40, 0);
					fVar40 = SUB164((undefined[16])local_228.Scale3D.V >> 0x60, 0);
					auVar23 = minps(CONCAT412(fVar52, CONCAT48(fVar33, CONCAT44(fVar51, fVar50))),
						(undefined[16])local_228.Scale3D.V);
					fVar58 = SUB164((undefined[16])GlobalVectorConstants::FloatZero >> 0x60, 0);
					iVar18 = movmskps((int)pFVar13,
						CONCAT412(-(uint)(SUB164(auVar23 >> 0x60, 0) < fVar58),
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
						pFVar13 = (FTransform*)local_1f8;
						fVar22 = fVar22 * fVar27;
						fVar24 = fVar24 * fVar36;
						fVar32 = fVar32 * fVar40;
						local_1d8 = CONCAT412(fVar52 * fVar40, CONCAT48(fVar33 * fVar38, CONCAT44(fVar51 * fVar36, fVar50 * fVar27) ));
						local_1f8 = CONCAT412(fVar54 * local_228.Rotation.V[0] *
							SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK0
								>> 0x60, 0) + fVar57 * local_228.Rotation.V[3] +
							fVar55 * local_228.Rotation.V[1] *
							SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK1
								>> 0x60, 0) +
							SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK2
								>> 0x60, 0) * 0.0,
							CONCAT48(fVar55 * local_228.Rotation.V[0] *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK0 >> 0x40, 0
								) + fVar56 * local_228.Rotation.V[3] +
								fVar54 * local_228.Rotation.V[1] *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK1 >> 0x40, 0
								) + fVar57 * 0.0 *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK2
									>> 0x40, 0),
								CONCAT44(local_228.Rotation.V[0] * 0.0 *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK0
										>> 0x20, 0) +
									fVar55 * local_228.Rotation.V[3] +
									fVar57 * local_228.Rotation.V[1] *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK1
										>> 0x20, 0) +
									fVar54 * local_228.Rotation.V[2] *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK2
										>> 0x20, 0),
									fVar57 * local_228.Rotation.V[0] *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK0.
										m128_f32, 0) +
									fVar54 * local_228.Rotation.V[3] +
									fVar56 * local_228.Rotation.V[1] *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK1.
										m128_f32, 0) +
									fVar55 * local_228.Rotation.V[2] *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK2.
										m128_f32, 0))));
						fVar21 = local_228.Rotation.V[1] * 0.0 - fVar24 * 0.0;
						fVar33 = fVar22 * 0.0 - fVar26 * fVar38 * local_228.Rotation.V[0];
						fVar50 = fVar24 * local_228.Rotation.V[0] - fVar22 * local_228.Rotation.V[1];
						fVar51 = fVar32 * local_228.Rotation.V[3] - fVar32 * local_228.Rotation.V[3];
						fVar21 = fVar21 + fVar21;
						fVar33 = fVar33 + fVar33;
						fVar50 = fVar50 + fVar50;
						fVar51 = fVar51 + fVar51;
						local_1e8 = CONCAT412((fVar51 * local_228.Rotation.V[3] -
							fVar51 * local_228.Rotation.V[3]) +
							local_228.Rotation.V[3] * fVar51 + fVar32 +
							local_228.Translation.V[3],
							CONCAT48((fVar33 * local_228.Rotation.V[0] -
								fVar21 * local_228.Rotation.V[1]) +
								local_228.Rotation.V[3] * fVar50 + fVar26 * fVar38 +
								local_228.Translation.V[2],
								CONCAT44((fVar21 * 0.0 - fVar50 * local_228.Rotation.V[0]
									) + local_228.Rotation.V[3] * fVar33 + fVar24 +
									local_228.Translation.V[1],
									(fVar50 * local_228.Rotation.V[1] - fVar33 * 0.0
										) + local_228.Rotation.V[3] * fVar21 + fVar22 +
									local_228.Translation.V[0])));

					} else {
						fVar32 = local_228.Rotation.V[1] + local_228.Rotation.V[1];
						fVar34 = (local_228.Rotation.V[0] + local_228.Rotation.V[0]) * local_228.Rotation.V[0];
						fVar53 = SUB164((undefined[16])GlobalVectorConstants::FloatOne >> 0x40, 0);
						fVar48 = (local_228.Rotation.V[3] * 0.0 + fVar32 * local_228.Rotation.V[0]) * fVar27;
						fVar49 = ((local_228.Rotation.V[0] + local_228.Rotation.V[0]) * local_228.Rotation.V[3]
							+ local_228.Rotation.V[1] * 0.0) * fVar36;
						fVar37 = fVar36 * (fVar32 * local_228.Rotation.V[0] - local_228.Rotation.V[3] * 0.0);
						fVar39 = fVar27 * (local_228.Rotation.V[0] * 0.0 - fVar32 * local_228.Rotation.V[3]);
						fVar25 = (float)((uint)((fVar53 - (fVar32 * local_228.Rotation.V[1] + fVar34)) * fVar38)
							& uVar44);
						fVar34 = (float)((uint)((fVar21 - (fVar34 + fVar34)) * fVar40) & uVar45);
						fVar32 = fVar55 + fVar55;
						fVar56 = fVar56 + fVar56;
						fVar31 = (fVar54 + fVar54) * fVar54;
						uVar29 = SUB164((undefined[16])GlobalVectorConstants::FloatOne.m128_u32, 0);
						auVar23 = (undefined[16])GlobalVectorConstants::FloatOne >> 0x20;
						fVar41 = (fVar57 * fVar56 + fVar54 * fVar32) * fVar50;
						fVar42 = (fVar57 * (fVar54 + fVar54) + fVar55 * fVar56) * fVar51;
						fVar35 = fVar51 * (fVar54 * fVar32 - fVar57 * fVar56);
						fVar56 = fVar50 * (fVar54 * fVar56 - fVar57 * fVar32);
						fVar32 = (float)((uint)((fVar53 - (fVar32 * fVar55 + fVar31)) * fVar33) & uVar44);
						fVar54 = (float)((uint)((fVar21 - (fVar31 + fVar31)) * fVar52) & uVar45);
						_local_518 = CONCAT412(fVar41 * fVar34 + fVar34 * 0.0 + fVar34 * 0.0 + fVar54 * fVar21,
							CONCAT48(fVar41 * fVar49 +
								SUB164(ZEXT1216(ZEXT812(0)) >> 0x40, 0) * fVar39 +
								fVar25 * 0.0 + fVar54 * local_228.Translation.V[2],
								CONCAT44(fVar41 * 0.0 + fVar48 * 0.0 + fVar56 * 0.0 +
									fVar54 * local_228.Translation.V[1],
									fVar41 * fVar37 + 0.0 + fVar56 * 0.0 +
									fVar54 * local_228.Translation.V[0])));
						_local_508 = CONCAT412(fVar34 * 0.0 + fVar35 * fVar34 + fVar34 * 0.0 + fVar54 * fVar21,
							CONCAT48(fVar49 * 0.0 + fVar35 * fVar39 + fVar25 * 0.0 +
								fVar54 * local_228.Translation.V[2],
								CONCAT44(fVar35 * fVar48 + 0.0 + fVar42 * 0.0 +
									fVar54 * local_228.Translation.V[1],
									fVar37 * 0.0 + fVar35 * 0.0 + fVar42 * 0.0 +
									fVar54 * local_228.Translation.V[0])));
						_local_4f8 = CONCAT412(fVar34 * 0.0 + fVar34 * 0.0 + fVar34 * 0.0 + fVar54 * fVar21,
							CONCAT48(fVar49 * 0.0 +
								SUB164(ZEXT1216(ZEXT812(0)) >> 0x40, 0) * fVar39 +
								fVar25 * 0.0 + fVar54 * local_228.Translation.V[2],
								CONCAT44(fVar48 * 0.0 + 0.0 + fVar32 * 0.0 +
									fVar54 * local_228.Translation.V[1],
									fVar37 * 0.0 + 0.0 + fVar32 * 0.0 +
									fVar54 * local_228.Translation.V[0])));
						local_4e8 = CONCAT412(fVar24 * fVar34 + fVar22 * fVar34 + fVar34 * 0.0 + fVar21 * fVar21
							, CONCAT48(fVar24 * fVar49 + fVar22 * fVar39 + fVar25 * 0.0 +
								fVar21 * local_228.Translation.V[2],
								CONCAT44(fVar24 * 0.0 + fVar22 * fVar48 + fVar26 * 0.0 +
									fVar21 * local_228.Translation.V[1],
									fVar24 * fVar37 + fVar22 * 0.0 + fVar26 * 0.0 +
									fVar21 * local_228.Translation.V[0])));
						_func__thiscall_void_float(local_518, 1e-08);
						auVar4 = _local_518;
						uVar28 = SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne >> 0x20, 0);
						fVar21 = (float)(-(uint)(SUB164((undefined[16])
							GlobalVectorConstants::FloatZero.m128_f32, 0) <=
							fVar50 * fVar27) &
							(SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne.m128_u32,
								0) ^ uVar29) ^
							SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne.m128_u32, 0)
							);
						fVar22 = (float)(-(uint)(SUB164((undefined[16])GlobalVectorConstants::FloatZero >>
							0x20, 0) <= fVar51 * fVar36) &
							(uVar28 ^ SUB164(auVar23, 0)) ^ uVar28);
						_local_518 = CONCAT124(stack0xfffffffffffffaec, local_518._0_4_ * fVar21);
						local_518 = (undefined[8])
							((unsigned long long)local_518 & 0xffffffff |
								(unsigned long long)(uint)(local_518._4_4_ * fVar21) << 0x20);
						_local_508 = CONCAT124(CONCAT84(uStack_500, local_508._4_4_ * fVar22),
							local_508._0_4_ * fVar22);
						local_4f8 = (undefined[8])CONCAT44(local_4f8._4_4_ * 0.0, local_4f8._0_4_ * 0.0);
						_func__thiscall_undefined_FMatrix_ptr(&local_3c8, (FMatrix*)local_518);
						pFVar13 = (FTransform*)local_1f8;
						fVar54 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf.m128_f32, 0);
						fVar55 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x20, 0);
						fVar56 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x40, 0);
						fVar57 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x60, 0);
						local_1d8 = CONCAT412(fVar52 * fVar40,
							CONCAT48(fVar33 * fVar38, CONCAT44(fVar51 * fVar36, fVar50 * fVar27)
							));
						fVar21 = local_3c8 * local_3c8 + fStack_3c0 * fStack_3c0;
						fVar22 = fStack_3c4 * fStack_3c4 + fStack_3bc * fStack_3bc;
						fVar24 = fStack_3c0 * fStack_3c0 + local_3c8 * local_3c8;
						fVar26 = fStack_3bc * fStack_3bc + fStack_3c4 * fStack_3c4;
						fVar33 = fVar22 + fVar21;
						fVar50 = fVar22 + 0.0;
						fVar32 = fVar26 + fVar24;
						fVar51 = fVar21 + fVar26;
						auVar23 = rsqrtps(CONCAT412(fVar26, CONCAT48(fVar24, CONCAT44(fVar22, fVar21))),
							CONCAT412(fVar51, CONCAT48(fVar32, CONCAT44(fVar50, fVar33))));
						fVar32 = fVar32 * fVar56;
						fVar21 = SUB164(auVar23, 0);
						fVar22 = SUB164(auVar23 >> 0x20, 0);
						fVar24 = SUB164(auVar23 >> 0x40, 0);
						fVar26 = SUB164(auVar23 >> 0x60, 0);
						fVar21 = (fVar54 - fVar21 * fVar21 * fVar33 * fVar54) * fVar21 + fVar21;
						fVar22 = (fVar55 - fVar22 * fVar22 * fVar50 * fVar55) * fVar22 + fVar22;
						fVar24 = (fVar56 - fVar24 * fVar24 * fVar32) * fVar24 + fVar24;
						fVar26 = (fVar57 - fVar26 * fVar26 * fVar51 * fVar57) * fVar26 + fVar26;
						local_1e8 = local_4e8 & (undefined[16])0xffffffffffffffff;
						uVar28 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x20, 0);
						uVar29 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x40, 0);
						uVar30 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x60, 0);
						local_1f8 = CONCAT412(((uint)(((fVar57 - fVar26 * fVar26 * fVar51 * fVar57) * fVar26 +
							fVar26) * fStack_3bc) ^ uVar30) & -(uint)(1e-08 <= fVar58)
							^ uVar30, CONCAT48(((uint)(((fVar56 - fVar24 * fVar24 * fVar32) *
								fVar24 + fVar24) * fStack_3c0) ^ uVar29
								) & -(uint)(1e-08 <= fVar51) ^ uVar29,
								CONCAT44(((uint)(((fVar55 - fVar22 * fVar22 *
									fVar50 * fVar55) *
									fVar22 + fVar22) * fStack_3c4)
									^ uVar28) & -(uint)(1e-08 <= fVar50) ^
									uVar28, ((uint)(((fVar54 - fVar21 *
										fVar21 * fVar33 * fVar54) * fVar21 + fVar21) *
										local_3c8) ^
										SUB164((undefined[16])
											GlobalVectorConstants::Float0001.m128_u32, 0
										)) & -(uint)(1e-08 <= fVar33) ^
									SUB164((undefined[16])
										GlobalVectorConstants::Float0001.m128_u32, 0
									)))
						);
					}
				}
				AActor::SetActorTransform((AActor*)this, pFVar13, false, (FHitResult*)0x0, None);
				goto LAB_180511897;
			}
		}

		// UOBJ //
		hitUObjRef = (UObject*)&(hitResult.Actor);
		if (hitUObjRef != NULL) {
			hitUObjRef = FWeakObjectPtr::Get((FWeakObjectPtr*)hitResult.Actor);
			hitClass = *(UClass**)&hitUObjRef->field_0x10;
			pUVar15 = UFGPipeAttachmentSnapTargetInterface::GetPrivateStaticClass();
			bool valid = UClass::ImplementsInterface(hitClass, pUVar15);
			if (valid) {
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
						}
						else {
							fVar21 = -1.0;
						}
						local_5b8.Z = local_5b8.Z * fVar21;
						local_5b8._0_8_ = CONCAT44(local_5b8.Y * fVar21, local_5b8.X * fVar21);
					}
					pFVar10 = (FMatrix*)FRotationMatrix::MakeFromX(&local_2a8, (FVector*)&local_5b8);
					FMatrix::Rotator(pFVar10, &local_3e8);
					pcVar2 = OneVector_exref;
					FRotator::Quaternion(&local_3e8, &local_3b8);
					fVar22 = local_598.Z;
					local_410 = &this->mPipeConnectionComponents;
					fVar24 = (float)*(undefined8*)pcVar2;
					fVar26 = (float)((unsigned long long) * (undefined8*)pcVar2 >> 0x20);
					fVar32 = (float)local_598._0_8_;
					fVar33 = (float)((unsigned long long)local_598._0_8_ >> 0x20);
					fVar21 = *(float*)(pcVar2 + 8);
					auVar3 = *(undefined(*)[12])pcVar2;
					local_568[0] = this->mSnapConnectionIndex;
					uVar28 = 0;
					if ((int)local_568[0] < (this->mPipeConnectionComponents).ArrayNum) {
						uVar28 = ~local_568[0] >> 0x1f;
					}
					if (uVar28 == 0) {
						local_418 = local_568;
						_func__cdecl_void_<lambda_e564da29fc75c0aef1975a3dea611db9>_ptr
						((<lambda_e564da29fc75c0aef1975a3dea611db9> *) & local_418);
						pcVar2 = (code*)swi(3);
						uVar6 = (*pcVar2)();
						return (bool)uVar6;
					}
					sceneComponent = *(USceneComponent**)
						((local_410->AllocatorInstance).Data + (long long)(int)local_568[0] * 8);
					pFVar13 = USceneComponent::GetRelativeTransform(sceneComponent, &local_168);
					uVar28 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x20, 0);
					uVar29 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x40, 0);
					uVar30 = SUB164((undefined[16])GlobalVectorConstants::SignMask >> 0x60, 0);
					fVar55 = SUB164((undefined[16])GlobalVectorConstants::SmallNumber >> 0x20, 0);
					fVar56 = SUB164((undefined[16])GlobalVectorConstants::SmallNumber >> 0x60, 0);
					uVar43 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x20, 0);
					uVar44 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x40, 0);
					uVar45 = SUB164((undefined[16])GlobalVectorConstants::XYZMask >> 0x60, 0);
					auVar23 = *(undefined(*)[16])(pFVar13->Scale3D).V;
					fVar57 = SUB164(auVar23, 0);
					fVar27 = SUB164(auVar23 >> 0x20, 0);
					fVar36 = SUB164(auVar23 >> 0x40, 0);
					fVar51 = (float)((uint)fVar57 &
						SUB164((undefined[16])GlobalVectorConstants::SignMask.m128_u32, 0));
					fVar52 = (float)((uint)fVar27 & uVar28);
					fVar54 = (float)(SUB164(auVar23 >> 0x60, 0) & uVar30);
					iVar18 = movmskps((int)sceneComponent,
						CONCAT412(-(uint)(fVar56 < in_xmmTmp2_Dd),
							CONCAT48(-(uint)(SUB164((undefined[16])
								GlobalVectorConstants::SmallNumber >>
								0x40, 0) < fVar54),
								CONCAT44(-(uint)(fVar55 < fVar52),
									-(uint)(SUB164((undefined[16])
										GlobalVectorConstants::
										SmallNumber.m128_f32, 0) <
										fVar51)))));
					fVar50 = SUB164((undefined[16])GlobalVectorConstants::FloatOne >> 0x60, 0);
					if (iVar18 == 0) {
						fVar38 = *(float*)Identity_exref;
						fVar40 = *(float*)(Identity_exref + 4);
						fVar58 = *(float*)(Identity_exref + 8);
						fVar53 = *(float*)(Identity_exref + 0xc);
						fVar51 = *(float*)(Identity_exref + 0x10);
						fVar52 = *(float*)(Identity_exref + 0x14);
						fVar54 = *(float*)(Identity_exref + 0x18);
						fVar55 = *(float*)(Identity_exref + 0x1c);
						fVar57 = *(float*)(Identity_exref + 0x20);
						fVar27 = *(float*)(Identity_exref + 0x24);
						fVar56 = *(float*)(Identity_exref + 0x28);
						fVar36 = *(float*)(Identity_exref + 0x2c);
						pFVar13 = (FTransform*)Identity_exref;
					}
					else {
						fVar38 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK.m128_f32, 0) *
							(pFVar13->Rotation).V[0];
						fVar40 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x20, 0) *
							(pFVar13->Rotation).V[1];
						fVar58 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x40, 0) *
							(pFVar13->Rotation).V[2];
						fVar53 = SUB164((undefined[16])GlobalVectorConstants::QINV_SIGN_MASK >> 0x60, 0) *
							(pFVar13->Rotation).V[3];
						auVar23 = rcpps(CONCAT412(fVar54, CONCAT48((uint)fVar36 & uVar29, CONCAT44(fVar52, fVar51))
						), CONCAT412(fVar50, SUB1612(auVar23, 0)));
						fVar51 = SUB164(auVar23, 0);
						fVar52 = SUB164(auVar23 >> 0x20, 0);
						fVar54 = SUB164(auVar23 >> 0x40, 0);
						fVar25 = SUB164(auVar23 >> 0x60, 0);
						fVar51 = (fVar51 + fVar51) - fVar51 * fVar51 * fVar57;
						fVar52 = (fVar52 + fVar52) - fVar52 * fVar52 * fVar27;
						fVar54 = (fVar54 + fVar54) - fVar54 * fVar54 * fVar36;
						fVar25 = (fVar25 + fVar25) - fVar25 * fVar25 * fVar50;
						fVar51 = (fVar51 + fVar51) - fVar51 * fVar51 * fVar57;
						fVar52 = (fVar52 + fVar52) - fVar52 * fVar52 * fVar27;
						fVar54 = (fVar54 + fVar54) - fVar54 * fVar54 * fVar36;
						fVar25 = (fVar25 + fVar25) - fVar25 * fVar25 * fVar50;
						fVar57 = (float)((-(uint)((float)((uint)fVar57 &
							SUB164((undefined[16])
								GlobalVectorConstants::SignMask.m128_u32, 0)) <=
							SUB164((undefined[16])
								GlobalVectorConstants::SmallNumber.m128_f32, 0)) &
							(uint)fVar51 ^ (uint)fVar51) &
							SUB164((undefined[16])GlobalVectorConstants::XYZMask.m128_u32, 0));
						fVar27 = (float)((-(uint)((float)((uint)fVar27 & uVar28) <= fVar55) & (uint)fVar52 ^
							(uint)fVar52) & uVar43);
						fVar56 = (float)((-(uint)((float)((uint)fVar36 & uVar29) <= fVar56) & (uint)fVar54 ^
							(uint)fVar54) & uVar44);
						fVar36 = (float)((-(uint)((float)((uint)fVar50 & uVar30) <= in_xmmTmp2_Dd) &
							(uint)fVar25 ^ (uint)fVar25) & uVar45);
						fVar51 = fVar57 * (pFVar13->Translation).V[0];
						fVar52 = fVar27 * (pFVar13->Translation).V[1];
						fVar31 = fVar56 * (pFVar13->Translation).V[2];
						fVar35 = fVar36 * (pFVar13->Translation).V[3];
						fVar54 = fVar40 * 0.0 - fVar52 * 0.0;
						fVar55 = fVar51 * fVar58 - fVar31 * fVar38;
						fVar25 = fVar52 * fVar38 - fVar51 * fVar40;
						fVar34 = fVar35 * fVar53 - fVar35 * fVar53;
						fVar54 = fVar54 + fVar54;
						fVar55 = fVar55 + fVar55;
						fVar25 = fVar25 + fVar25;
						fVar34 = fVar34 + fVar34;
						fVar51 = (float)((uint)(0.0 - ((fVar40 * 0.0 - fVar55 * 0.0) + fVar53 * fVar54 + fVar51)
							) &
							SUB164((undefined[16])GlobalVectorConstants::XYZMask.m128_u32, 0));
						fVar52 = (float)((uint)(0.0 - ((fVar54 * fVar58 - fVar25 * fVar38) +
							fVar53 * fVar55 + fVar52)) & uVar43);
						fVar54 = (float)((uint)(0.0 - ((fVar55 * fVar38 - fVar54 * fVar40) +
							fVar53 * fVar25 + fVar31)) & uVar44);
						fVar55 = (float)((uint)(0.0 - ((fVar34 * fVar53 - fVar34 * fVar53) +
							fVar53 * fVar34 + fVar35)) & uVar45);
					}
					auVar23 = minps(CONCAT412(fVar36, CONCAT48(fVar56, CONCAT44(fVar27, fVar57))),
						ZEXT1216(auVar3));
					fVar25 = SUB164((undefined[16])GlobalVectorConstants::FloatZero >> 0x60, 0);
					iVar18 = movmskps((int)pFVar13,
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
						fVar51 = fVar51 * fVar24;
						fVar52 = fVar52 * fVar26;
						fVar55 = fVar55 * 0.0;
						local_1a8 = CONCAT412(fVar36 * 0.0,
							CONCAT48(fVar56 * fVar21, CONCAT44(fVar27 * fVar26, fVar57 * fVar24)
							));
						local_1c8 = CONCAT412(fVar38 * local_3b8.X *
							SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK0
								>> 0x60, 0) + local_3b8.W * fVar53 +
							fVar40 * local_3b8.Y *
							SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK1
								>> 0x60, 0) +
							SUB164((undefined[16])GlobalVectorConstants::QMULTI_SIGN_MASK2
								>> 0x60, 0) * 0.0,
							CONCAT48(fVar40 * local_3b8.X *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK0 >> 0x40, 0
								) + local_3b8.W * fVar58 +
								fVar38 * local_3b8.Y *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK1 >> 0x40, 0
								) + fVar53 * 0.0 *
								SUB164((undefined[16])
									GlobalVectorConstants::QMULTI_SIGN_MASK2
									>> 0x40, 0),
								CONCAT44(local_3b8.X * 0.0 *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK0
										>> 0x20, 0) + local_3b8.W * fVar40 +
									fVar53 * local_3b8.Y *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK1
										>> 0x20, 0) +
									fVar38 * local_3b8.Z *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK2
										>> 0x20, 0),
									fVar53 * local_3b8.X *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK0.
										m128_f32, 0) + local_3b8.W * fVar38 +
									fVar58 * local_3b8.Y *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK1.
										m128_f32, 0) +
									fVar40 * local_3b8.Z *
									SUB164((undefined[16])
										GlobalVectorConstants::QMULTI_SIGN_MASK2.
										m128_f32, 0))));
						fVar24 = local_3b8.Y * 0.0 - fVar52 * 0.0;
						fVar26 = fVar51 * 0.0 - fVar54 * fVar21 * local_3b8.X;
						fVar50 = fVar52 * local_3b8.X - fVar51 * local_3b8.Y;
						fVar56 = fVar55 * local_3b8.W - fVar55 * local_3b8.W;
						fVar24 = fVar24 + fVar24;
						fVar26 = fVar26 + fVar26;
						fVar50 = fVar50 + fVar50;
						fVar56 = fVar56 + fVar56;
						local_1b8 = CONCAT412((fVar56 * local_3b8.W - fVar56 * local_3b8.W) +
							local_3b8.W * fVar56 + fVar55 + 0.0,
							CONCAT48((fVar26 * local_3b8.X - fVar24 * local_3b8.Y) +
								local_3b8.W * fVar50 + fVar54 * fVar21 + fVar22,
								CONCAT44((fVar24 * 0.0 - fVar50 * local_3b8.X) +
									local_3b8.W * fVar26 + fVar52 + fVar33,
									(fVar50 * local_3b8.Y - fVar26 * 0.0) +
									local_3b8.W * fVar24 + fVar51 + fVar32)));
					}
					else {
						fVar55 = local_3b8.Y + local_3b8.Y;
						local_3b8.Z = local_3b8.Z + local_3b8.Z;
						fVar35 = (local_3b8.X + local_3b8.X) * local_3b8.X;
						fVar34 = SUB164((undefined[16])GlobalVectorConstants::FloatOne >> 0x40, 0);
						fVar46 = (local_3b8.W * local_3b8.Z + local_3b8.X * fVar55) * fVar24;
						fVar47 = (local_3b8.W * (local_3b8.X + local_3b8.X) + local_3b8.Y * local_3b8.Z) *
							fVar26;
						fVar39 = fVar26 * (local_3b8.X * fVar55 - local_3b8.W * local_3b8.Z);
						fVar42 = fVar24 * (local_3b8.X * local_3b8.Z - local_3b8.W * fVar55);
						fVar31 = (float)((uint)((fVar34 - (fVar55 * local_3b8.Y + fVar35)) * fVar21) & uVar44);
						fVar35 = (float)((uint)((fVar50 - (fVar35 + fVar35)) * 0.0) & uVar45);
						fVar55 = fVar40 + fVar40;
						fVar58 = fVar58 + fVar58;
						fVar37 = (fVar38 + fVar38) * fVar38;
						uVar29 = SUB164((undefined[16])GlobalVectorConstants::FloatOne.m128_u32, 0);
						auVar23 = (undefined[16])GlobalVectorConstants::FloatOne >> 0x20;
						fVar48 = (fVar53 * fVar58 + fVar38 * fVar55) * fVar57;
						fVar49 = (fVar53 * (fVar38 + fVar38) + fVar40 * fVar58) * fVar27;
						fVar41 = fVar27 * (fVar38 * fVar55 - fVar53 * fVar58);
						fVar58 = fVar57 * (fVar38 * fVar58 - fVar53 * fVar55);
						fVar55 = (float)((uint)((fVar34 - (fVar55 * fVar40 + fVar37)) * fVar56) & uVar44);
						fVar38 = (float)((uint)((fVar50 - (fVar37 + fVar37)) * fVar36) & uVar45);
						local_558 = CONCAT412(fVar48 * fVar35 + fVar35 * 0.0 + fVar35 * 0.0 + fVar38 * fVar50,
							CONCAT48(fVar48 * fVar47 +
								SUB164(ZEXT1216(ZEXT812(0)) >> 0x40, 0) * fVar42 +
								fVar31 * 0.0 + fVar38 * fVar22,
								CONCAT44(fVar48 * 0.0 + fVar46 * 0.0 + fVar58 * 0.0 +
									fVar38 * fVar33,
									fVar48 * fVar39 + 0.0 + fVar58 * 0.0 +
									fVar38 * fVar32)));
						_local_548 = CONCAT412(fVar35 * 0.0 + fVar41 * fVar35 + fVar35 * 0.0 + fVar38 * fVar50,
							CONCAT48(fVar47 * 0.0 + fVar41 * fVar42 + fVar31 * 0.0 +
								fVar38 * fVar22,
								CONCAT44(fVar41 * fVar46 + 0.0 + fVar49 * 0.0 +
									fVar38 * fVar33,
									fVar39 * 0.0 + fVar41 * 0.0 + fVar49 * 0.0 +
									fVar38 * fVar32)));
						_local_538 = CONCAT412(fVar35 * 0.0 + fVar35 * 0.0 + fVar35 * 0.0 + fVar38 * fVar50,
							CONCAT48(fVar47 * 0.0 +
								SUB164(ZEXT1216(ZEXT812(0)) >> 0x40, 0) * fVar42 +
								fVar31 * 0.0 + fVar38 * fVar22,
								CONCAT44(fVar46 * 0.0 + 0.0 + fVar55 * 0.0 +
									fVar38 * fVar33,
									fVar39 * 0.0 + 0.0 + fVar55 * 0.0 +
									fVar38 * fVar32)));
						local_528 = CONCAT412(fVar52 * fVar35 + fVar51 * fVar35 + fVar35 * 0.0 + fVar50 * fVar50
							, CONCAT48(fVar52 * fVar47 + fVar51 * fVar42 + fVar31 * 0.0 +
								fVar50 * fVar22,
								CONCAT44(fVar52 * 0.0 + fVar51 * fVar46 + fVar54 * 0.0 +
									fVar50 * fVar33,
									fVar52 * fVar39 + fVar51 * 0.0 + fVar54 * 0.0 +
									fVar50 * fVar32)));
						_func__thiscall_void_float(local_558, 1e-08);
						uVar28 = SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne >> 0x20, 0);
						fVar22 = (float)(-(uint)(SUB164((undefined[16])
							GlobalVectorConstants::FloatZero.m128_f32, 0) <=
							fVar57 * fVar24) &
							(SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne.m128_u32,
								0) ^ uVar29) ^
							SUB164((undefined[16])GlobalVectorConstants::FloatMinusOne.m128_u32, 0)
							);
						fVar32 = (float)(-(uint)(SUB164((undefined[16])GlobalVectorConstants::FloatZero >>
							0x20, 0) <= fVar27 * fVar26) &
							(uVar28 ^ SUB164(auVar23, 0)) ^ uVar28);
						_local_548 = CONCAT124(_auStack_544, (float)local_548 * fVar32);
						_local_538 = CONCAT124(_auStack_534, (float)local_538 * 0.0);
						_func__thiscall_undefined_FMatrix_ptr(&local_3a8, (FMatrix*)local_558);
						fVar52 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf.m128_f32, 0);
						fVar54 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x20, 0);
						fVar55 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x40, 0);
						fVar38 = SUB164((undefined[16])GlobalVectorConstants::FloatOneHalf >> 0x60, 0);
						local_1a8 = CONCAT412(fVar36 * 0.0,
							CONCAT48(fVar56 * fVar21, CONCAT44(fVar27 * fVar26, fVar57 * fVar24)
							));
						fVar21 = local_3a8 * local_3a8 + fStack_3a0 * fStack_3a0;
						fVar22 = fStack_3a4 * fStack_3a4 + fStack_39c * fStack_39c;
						fVar24 = fStack_3a0 * fStack_3a0 + local_3a8 * local_3a8;
						fVar26 = fStack_39c * fStack_39c + fStack_3a4 * fStack_3a4;
						fVar33 = fVar22 + fVar21;
						fVar50 = fVar22 + 0.0;
						fVar32 = fVar26 + fVar24;
						fVar51 = fVar21 + fVar26;
						auVar23 = rsqrtps(CONCAT412(fVar26, CONCAT48(fVar24, CONCAT44(fVar22, fVar21))),
							CONCAT412(fVar51, CONCAT48(fVar32, CONCAT44(fVar50, fVar33))));
						fVar32 = fVar32 * fVar55;
						fVar21 = SUB164(auVar23, 0);
						fVar22 = SUB164(auVar23 >> 0x20, 0);
						fVar24 = SUB164(auVar23 >> 0x40, 0);
						fVar26 = SUB164(auVar23 >> 0x60, 0);
						fVar21 = (fVar52 - fVar21 * fVar21 * fVar33 * fVar52) * fVar21 + fVar21;
						fVar22 = (fVar54 - fVar22 * fVar22 * fVar50 * fVar54) * fVar22 + fVar22;
						fVar24 = (fVar55 - fVar24 * fVar24 * fVar32) * fVar24 + fVar24;
						fVar26 = (fVar38 - fVar26 * fVar26 * fVar51 * fVar38) * fVar26 + fVar26;
						local_1b8 = local_528 & (undefined[16])0xffffffffffffffff;
						uVar28 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x20, 0);
						uVar29 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x40, 0);
						uVar30 = SUB164((undefined[16])GlobalVectorConstants::Float0001 >> 0x60, 0);
						local_1c8 = CONCAT412(((uint)(((fVar38 - fVar26 * fVar26 * fVar51 * fVar38) * fVar26 +
							fVar26) * fStack_39c) ^ uVar30) & -(uint)(1e-08 <= fVar25)
							^ uVar30, CONCAT48(((uint)(((fVar55 - fVar24 * fVar24 * fVar32) *
								fVar24 + fVar24) * fStack_3a0) ^ uVar29
								) & -(uint)(1e-08 <= fVar51) ^ uVar29,
								CONCAT44(((uint)(((fVar54 - fVar22 * fVar22 *
									fVar50 * fVar54) *
									fVar22 + fVar22) * fStack_3a4)
									^ uVar28) & -(uint)(1e-08 <= fVar50) ^
									uVar28, ((uint)(((fVar52 - fVar21 *
										fVar21 * fVar33 * fVar52) * fVar21 + fVar21) *
										local_3a8) ^
										SUB164((undefined[16])
											GlobalVectorConstants::Float0001.m128_u32, 0
										)) & -(uint)(1e-08 <= fVar33) ^
									SUB164((undefined[16])
										GlobalVectorConstants::Float0001.m128_u32, 0
									))));
					}
					AActor::SetActorTransform
					((AActor*)this, (FTransform*)local_1c8, false, (FHitResult*)0x0, None);
				}
				goto LAB_180511897;
			}
		}

		// WALL //
		hitWallRef = (AFGBuildableWall*)&(hitResult.Actor);
		if (hitWallRef != NULL) {
			hitClass = AFGBuildableWall::GetPrivateStaticClass();
			bool valid = UStruct::IsChildOf(*(UStruct**)&hitWallRef->field_0x10, (UStruct*)hitClass);
			if (valid) {
				*(AFGBuildableWall**)&this->field_0x460 = hitWallRef;
				iVar18 = (**(code**)(*(long long*)this + 0x7a0))(this);
				fVar21 = AFGHologram::ApplyScrollRotationTo((AFGHologram*)this, 0.0, false);
				local_4d8.Y = (this->mWallSnapOffset).X;
				local_4cc.Y = *(float*)&(hitResult->TraceStart).field_0x4 -
					*(float*)&(hitResult->Location).field_0x4;
				local_4d8.X = 200.0;
				local_4d8.Z = (this->mWallSnapOffset).Y;
				local_4cc.X = *(float*)&hitResult->TraceStart - *(float*)&(hitResult->Location).field_0x0;
				local_4cc.Z = *(float*)&(hitResult->TraceStart).field_0x8 -
					*(float*)&(hitResult->Location).field_0x8;
				AFGBuildableHologram::SnapToWall
				((AFGBuildableHologram*)this, hitWallRef, &local_4cc, (FVector*)&hitResult->Location, Z,
					&local_4d8,
					(float)(((int)ROUND(fVar21 * (2.0 / (float)iVar18) + 0.5) >> 1) * iVar18),
					&local_478, &local_488);
				local_468._0_8_ = local_488._0_8_;
				local_468.Roll = local_488.Roll;
				local_458.V._0_8_ = local_478._0_8_;
				local_458.V[2] = local_478.Z;
				AActor::SetActorLocationAndRotation
				((AActor*)this, &local_458, &local_468, false, (FHitResult*)0x0, None);
			}
		}
	
	} else if (
		(this->mBuildStep == EPipelineAttachmentBuildStep::PABS_AdjustRotation) &&
		(this->mSnappedPipeline != (AFGBuildablePipeline*)0x0)
	){

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
		} else {
			float compX = (sceneComponent->ComponentToWorld).Translation.X;
			float compY = (sceneComponent->ComponentToWorld).Translation.Y;
			float compZ = (sceneComponent->ComponentToWorld).Translation.Z;
			puVar20 = (undefined8*)&compX;
			pFVar17 = USceneComponent::GetForwardVector(sceneComponent, &local_38c);
		}

		local_498._0_8_ = *(undefined8*)pFVar17->V;
		local_498.Z = pFVar17->V[2];
		fVar21 = AFGHologram::ApplyScrollRotationTo((AFGHologram*)this, 0.0, false);
		_func__thiscall_FVector_float_FVector_ptr
		(&this->mBuildStepUpVector, &local_3f8, fVar21, &local_498);
		pFVar10 = (FMatrix*)FRotationMatrix::MakeFromXZ(&local_268, (FVector*)&local_498, (FVector*)&local_3f8);
		FMatrix::Rotator(pFVar10, &local_448);
		local_438._0_8_ = local_448._0_8_;
		local_428.V._0_8_ = *puVar20;
		local_438.Roll = local_448.Roll;
		local_428.V[2] = *(float*)(puVar20 + 1);
		AActor::SetActorLocationAndRotation
		((AActor*)this, &local_428, &local_438, false, (FHitResult*)0x0, None);
}
//*/