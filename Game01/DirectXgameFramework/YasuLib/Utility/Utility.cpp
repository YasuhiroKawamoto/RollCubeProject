#include "Utility.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

namespace utl
{
	Utility::Utility()
	{
	}


	Utility::~Utility()
	{
	}


	// ======================================================================================
	// @>�T�@�v:Vector3�̕�Ԉړ�
	//
	// @>���@��:�����l,�I���l, ��Ԏ���
	//
	// @>�߂�l:��Ԓl
	// ======================================================================================

	Vector3 Utility::Lerp(const DirectX::SimpleMath::Vector3& startPosition, const DirectX::SimpleMath::Vector3& targetPosition, const float t)
	{
		Vector3 lerpPosition = Vector3::Zero;

		lerpPosition = (1 - t) * startPosition + t * targetPosition;

		return lerpPosition;
	}

	// ======================================================================================
	// @>�T�@�v:Vector4�̕�Ԉړ�
	//
	// @>���@��:�����l,�I���l, ��Ԏ���
	//
	// @>�߂�l:��Ԓl
	// ======================================================================================

	Vector4 Utility::Lerp(const DirectX::SimpleMath::Vector4& startPosition, const DirectX::SimpleMath::Vector4& targetPosition, const float t)
	{
		Vector4 lerpPosition = Vector4::Zero;

		lerpPosition = (1 - t) * startPosition + t * targetPosition;

		return lerpPosition;
	}

	// ======================================================================================
	// @>�T�@�v:int, float�̕�Ԉړ�
	//
	// @>���@��:�����l,�I���l, ��Ԏ���
	//
	// @>�߂�l:��Ԓl
	// ======================================================================================
	float Utility::Lerp(const float start, const float end, float time)
	{
		float lerpVal = 0;

		lerpVal = (1 - time) * start + time * end;

		return lerpVal;
	}

	Vector2 Utility::VRotate2D(const Vector2& vec, float ang)
	{
		Vector2 _vec;
		_vec.x = vec.x*cosf(ang) - vec.y*sinf(ang);
		_vec.y = vec.x*sinf(ang) + vec.y*cos(ang);

		return _vec;
	}


	// ======================================================================================
	// @>�T�@�v:float�^���w��̌����Ŏl�̌ܓ�����
	//
	// @>���@��:�l�̌ܓ��O�̒l,�l�̌ܓ������
	//
	// @>�߂�l:��Ԓl
	// ======================================================================================
	float Utility::Roundf(const float num, const int place)
	{
		const int FLOAT_DIGITS = 6;
		const int ROUND_UP = 5;


		float rounded;
		int integer = num * pow(10, FLOAT_DIGITS);
		int _array[FLOAT_DIGITS + 1] = { 0 };

		int i = 0;
		// �z��Ɋi�[
		while (integer)
		{
			_array[FLOAT_DIGITS - i] = integer % 10;
			integer /= 10;
			i++;
		}

		// �J��グ
		if (_array[place] >= ROUND_UP)
			_array[place - 1]++;
		if (_array[place] <= -ROUND_UP)
			_array[place - 1]--;

		// �؂�̂�
		for (int i = 0; i < FLOAT_DIGITS + 1; i++)
		{
			if (i >= place)
			{
				_array[i] = 0;
			}
		}

		// �Ăя�����
		for (int i = 0; i < FLOAT_DIGITS + 1; i++)
		{
			integer += _array[i] * pow(10, (FLOAT_DIGITS - i));
		}
		rounded = integer / 1000000.0f;

		return rounded;
	}

	/**
	* @fn�@RondomRange
	* @brief �w��͈̗͂������擾
	* @param (float  min) �ŏ��l
	* @param (float max) �ő�l
	* @return (float�@��������)
	*/
	float Utility::RandomRange(float min, float max)
	{
		std::random_device rd;
		std::mt19937 mt(rd());

		// �ŏ��l ���ő�l���傫���ꍇ�l�����ւ���
		if (min > max)	Swap(&min, &max);

		std::uniform_real_distribution<float> myRand(min, max);
		return myRand(mt);
	}


}