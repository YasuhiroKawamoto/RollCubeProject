#pragma once
#include "../../Framework/Game.h"

#include <random>
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
		static float RandomRange(float min, float max);

		/**
		* @fn�@Swap
		* @brief 2�̕ϐ��̒l�����ւ���
		* @param (float  x)�@�ϐ�1
		* @param (float y) �ϐ�2
		* @return �Ȃ�
		*/
		template <typename T>
		static void Swap(T* x, T* y)
		{
			T tmp;
			if (x && y)
			{
				tmp = *x;
				*x = *y;
				*y = tmp;
			}
		}

		// ======================================================================================
		// @>�T�@�v:�l���ۂߍ���
		//
		// @>���@��:�ۂߍ��ޒl,�ŏ��l ,�ő�l
		//
		// @>�߂�l:�ۂߍ��߂��l
		// ======================================================================================
		template <typename T>
		static T Clamp(T num, T min, T max)
		{
			return num > max ? max : num < min ? min : num;
		}
	};
}