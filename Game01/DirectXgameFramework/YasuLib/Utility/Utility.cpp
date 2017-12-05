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
	// @>概　要:Vector3の補間移動
	//
	// @>引　数:初期値,終了値, 補間時間
	//
	// @>戻り値:補間値
	// ======================================================================================

	Vector3 Utility::Lerp(const DirectX::SimpleMath::Vector3& startPosition, const DirectX::SimpleMath::Vector3& targetPosition, const float t)
	{
		Vector3 lerpPosition = Vector3::Zero;

		lerpPosition = (1 - t) * startPosition + t * targetPosition;

		return lerpPosition;
	}

	// ======================================================================================
	// @>概　要:Vector4の補間移動
	//
	// @>引　数:初期値,終了値, 補間時間
	//
	// @>戻り値:補間値
	// ======================================================================================

	Vector4 Utility::Lerp(const DirectX::SimpleMath::Vector4& startPosition, const DirectX::SimpleMath::Vector4& targetPosition, const float t)
	{
		Vector4 lerpPosition = Vector4::Zero;

		lerpPosition = (1 - t) * startPosition + t * targetPosition;

		return lerpPosition;
	}

	// ======================================================================================
	// @>概　要:int, floatの補間移動
	//
	// @>引　数:初期値,終了値, 補間時間
	//
	// @>戻り値:補間値
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
	// @>概　要:float型を指定の桁数で四捨五入する
	//
	// @>引　数:四捨五入前の値,四捨五入する位
	//
	// @>戻り値:補間値
	// ======================================================================================
	float Utility::Roundf(const float num, const int place)
	{
		const int FLOAT_DIGITS = 6;
		const int ROUND_UP = 5;


		float rounded;
		int integer = num * pow(10, FLOAT_DIGITS);
		int _array[FLOAT_DIGITS + 1] = { 0 };

		int i = 0;
		// 配列に格納
		while (integer)
		{
			_array[FLOAT_DIGITS - i] = integer % 10;
			integer /= 10;
			i++;
		}

		// 繰り上げ
		if (_array[place] >= ROUND_UP)
			_array[place - 1]++;
		if (_array[place] <= -ROUND_UP)
			_array[place - 1]--;

		// 切り捨て
		for (int i = 0; i < FLOAT_DIGITS + 1; i++)
		{
			if (i >= place)
			{
				_array[i] = 0;
			}
		}

		// 再び小数化
		for (int i = 0; i < FLOAT_DIGITS + 1; i++)
		{
			integer += _array[i] * pow(10, (FLOAT_DIGITS - i));
		}
		rounded = integer / 1000000.0f;

		return rounded;
	}

	/**
	* @fn　RondomRange
	* @brief 指定範囲の乱数を取得
	* @param (float  min) 最小値
	* @param (float max) 最大値
	* @return (float　得た乱数)
	*/
	float Utility::RandomRange(float min, float max)
	{
		std::random_device rd;
		std::mt19937 mt(rd());

		// 最小値 が最大値より大きい場合値を入れ替える
		if (min > max)	Swap(&min, &max);

		std::uniform_real_distribution<float> myRand(min, max);
		return myRand(mt);
	}


}