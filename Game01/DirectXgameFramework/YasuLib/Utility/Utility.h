#pragma once
#include "../../Framework/Game.h"

namespace utl
{
	class Utility
	{
	public:
		Utility();
		~Utility();

		
		static DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float time);
		static DirectX::SimpleMath::Vector4 Lerp(const DirectX::SimpleMath::Vector4& start, const DirectX::SimpleMath::Vector4& end, const float time);
		static float Lerp(const float start, const float end, float time);
		static DirectX::SimpleMath::Vector2 VRotate2D(const DirectX::SimpleMath::Vector2& vec, float ang);
		static float Roundf(const float num, const int place);


		// ======================================================================================
		// @>概　要:値を丸め込む
		//
		// @>引　数:丸め込む値,最小値 ,最大値
		//
		// @>戻り値:丸め込めた値
		// ======================================================================================
		template <typename T>
		static T Clamp(T num, T min, T max)
		{
			return num > max ? max : num < min ? min : num;
		}
	};



}