#include "stdafx.h"
#include "Elder.h"
#include "ElderState.h"
#include "ElderPatern.h"

ElderPatern::ElderPatern()
{
}

ElderPatern::~ElderPatern()
{
}

void ElderPatern::StompPatern(Elder* elder)
{
	
	if (elder->GetState() != E_OPENING)
	{
		if (elder->paternTime < 0)
		{
			float distance = (PLAYER->GetPlayer()->GetWorldPos() - elder->GetActor()->GetWorldPos()).Length();


			if (elder->GetState() == E_STOMP)
			{
				if (elder->GetActor()->anim->GetPlayTime() <= 0.45f)
				{
					elder->moveSpeed = 1.0f;
					elder->rotationScale = 1.0f;
					elder->RotationForMove();
				}
				else {}
			}
			else
			{
				elder->moveSpeed = 2.0f;
				elder->rotationScale = 0.4f;
				elder->MonsterMove();
				elder->RotationForMove();
			}

			if (distance > 4.0f && elder->GetState() != E_STOMP)
			{
				elder->GetState()->Walk(elder);
			}
			else if (distance <= 4.0f)
			{
				elder->GetState()->Stomp(elder);
			}
			if (elder->GetState() == E_STOMP && elder->GetActor()->anim->GetPlayTime() >= 1.0f)
			{
				elder->GetState()->Idle(elder);
				elder->paternTime = 2.0f;
			}
		}
		
	}
}
