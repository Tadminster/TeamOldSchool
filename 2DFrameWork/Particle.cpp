#include "framework.h"

void Particle::UpdateParticle()
{
	if (isPlaying)
	{
		playTime += DELTA;
		if (playTime > duration)
		{
			Stop();
		}
	}
}

void Particle::Gui()
{
	if (ImGui::Button("Play"))
	{
		Play();
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		Stop();
	}
	//현재 재생 시간
	ImGui::Text("Playtime : %f", PlayTime());
	//총 재생할 시간
	ImGui::SliderFloat("duration", &duration, 0.0f, 100.0f);
}


