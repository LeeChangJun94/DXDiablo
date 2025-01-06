#pragma once
#include <Windows.h>
#include <string>
#include <functional>

#include <DirectXMath.h>
#include <DirectXCollision.h>

#include "EngineDefine.h"

// FVector로 통일하겠습니다.
// FVector xy
// FVector3D xyz
// FVector4D xyzw
// FVector4D == FVector;

// #include <DirectXMath.h>

// directx는 SIMD연산을 위해서
// directx는 아예 자료형을 새로 만들었습니다.
// xmmatrix
// xmvector


class ENGINEAPI  UEngineMath
{
public:
	// 상수 정의
	static inline const double DPI = 3.14159265358979323846264338327950288419716939937510;
	static inline const double DPI2 = DPI * 2.0;

	static inline const float PI = 3.14159265358979323846264f;
	static inline const float PI2 = PI * 2.0f;

	static inline const float D2R = UEngineMath::PI / 180.0f;
	static inline const float R2D = 180.0f / UEngineMath::PI;

	static float Sqrt(float _Value)
	{
		return ::sqrtf(_Value);
	}

	template <typename DataType>
	DataType ClampMax(DataType value, DataType maxValue)
	{
		return (value > maxValue) ? maxValue : value;
	}

	template <typename DataType>
	DataType ClampMin(DataType value, DataType minValue)
	{
		return (value < minValue) ? minValue : value;
	}

	template <typename DataType>
	static DataType Clamp(DataType value, DataType minValue, DataType maxValue)
	{
		if (value < minValue)
			return minValue;
		else if (value > maxValue)
			return maxValue;
		else
			return value;
	}

	template <typename DataType>
	static DataType Lerp(DataType A, DataType B, DataType Alpha)
	{
		return A * (1 - Alpha) + B * Alpha;
	}
};

class FQuat
{
public:
	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		float Arr2D[1][4];
		float Arr1D[4];
		// 다이렉트 simd 연산 전용 벡터.
		DirectX::XMVECTOR DirectVector;

	};

	class FVector QuaternionToEulerDeg() const;
	class FVector QuaternionToEulerRad() const;
};

class FVector
{
public:
	static const FVector ZERO;
	static const FVector LEFT;
	static const FVector RIGHT;
	static const FVector UP;
	static const FVector DOWN;
	static const FVector FORWARD;
	static const FVector BACK;


public:
	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		float Arr2D[1][4];
		float Arr1D[4];
		// 다이렉트 simd 연산 전용 벡터.
		DirectX::XMVECTOR DirectVector;
	};


	ENGINEAPI FVector()
		: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
	{

	}

	ENGINEAPI FVector(float _X, float _Y) : X(_X), Y(_Y), Z(0.0f), W(1.0f)
	{

	}

	ENGINEAPI FVector(float _X, float _Y, float _Z) : X(_X), Y(_Y), Z(_Z), W(1.0f)
	{

	}

	FVector(float _X, float _Y, float _Z, float _W) : X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}


	FVector(int _X, int _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	FVector(long _X, long _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	static float R2D(float _Value)
	{
		return _Value * (180.0f / 3.14159265358979323846264f);
	}

	static float GetVectorAngleDeg(const FVector& _Left, const FVector& _Right)
	{
		return R2D(GetVectorAngleRad(_Left, _Right));
	}

	static float GetVectorAngleRad(const FVector& _Left, const FVector& _Right)
	{
		FVector LCopy = _Left;
		FVector RCopy = _Right;
		LCopy.Normalize();
		RCopy.Normalize();

		// Cos은 라디안인가요?
		// cos(라디안) => CosRad
		// cos(라디안)
		float CosRad = Dot(LCopy, RCopy);

		// cos 의 역함수 
		// cos(각도) => 결과
		// acos(결과) => 각도
		// cos함수의 역함수
		return acos(CosRad);
	}

	static FVector Cross(const FVector& _Left, const FVector& _Right)
	{
		FVector Result;
		Result.X = _Left.Y * _Right.Z - _Left.Z * _Right.Y;
		Result.Y = _Left.Z * _Right.X - _Left.X * _Right.Z;
		Result.Z = _Left.X * _Right.Y - _Left.Y * _Right.X;
		return Result;
	}

	static float Dot(const FVector& _Left, const FVector& _Right)
	{
		float LeftLen = _Left.Length();
		float RightLen = _Right.Length();

		// LeftLen* RightLen* cosf(angle);

		return _Left.X * _Right.X + _Left.Y * _Right.Y + _Left.Z * _Right.Z;
	}

	static FVector Normalize(FVector _Value)
	{
		_Value.Normalize();
		return _Value;
	}

	// 360도 개념으로 넣어줘라.
	static FVector AngleToVectorDeg(float _Angle)
	{
		// 360분법을 => 라디안으로 바꾸는 값을 만들어야 한다.
		// 360 => 6.28

		// 라디안 각도체계를 기반으로 sinf(_Angle) cosf

		// 근본함수는 라디안 개념으로 만들고
		return AngleToVectorRad(_Angle * UEngineMath::D2R);
	}


	static FVector Lerp(FVector _A, FVector _B, float _Alpha)
	{
		FVector Result;
		_Alpha = UEngineMath::Clamp(_Alpha, 0.0f, 1.0f);
		Result.X = UEngineMath::Lerp(_A.X, _B.X, _Alpha);
		Result.Y = UEngineMath::Lerp(_A.Y, _B.Y, _Alpha);
		return Result;
	}

	//          Rad 라디안을 넣어주면 
	// 여기에서 나온 결과값이 리턴해줄수 있는건
	// 길이가 1인 벡터이다.
	// static입니까?
	static FVector AngleToVectorRad(float _Angle)
	{
		// 특정 각도를 가리키는 벡터를 만들수 있다고 해죠?
		// 벡터 길이와 방향을 생각해라.
		// 방향은 정해졌는데 길이는 1인 벡터를 만들어내는 겁니다.

		// 0도일때의 밑변      0도일대의 높이

		// cosf(_Angle) = 밑변
		return { cosf(_Angle), sinf(_Angle) };
	}

	// 일반적으로 벡터와 행렬이 곱해지는 것을 트랜스폼이라고 부릅니다.
	// 혹은 트랜슬레이션이라는 함수들이 있다.
	static FVector Transform(const FVector& _Vector, const class FMatrix& _Matrix);

	// 이동 적용할께
	static FVector TransformCoord(const FVector& _Vector, const class FMatrix& _Matrix);

	// 이동 적용하지 않을께.
	static FVector TransformNormal(const FVector& _Vector, const class FMatrix& _Matrix);

	int iX() const
	{
		return static_cast<int>(X);
	}

	int iY() const
	{
		return static_cast<int>(Y);
	}

	float hX() const
	{
		return X * 0.5f;
	}

	float hY() const
	{
		return Y * 0.5f;
	}

	// X든 Y든 0이있으면 터트리는 함수.
	bool IsZeroed() const
	{
		return X == 0.0f || Y == 0.0f;
	}

	FVector Half() const
	{
		return { X * 0.5f, Y * 0.5f };
	}

	// 빗변의 길이입니다.
	float Length() const
	{
		return UEngineMath::Sqrt(X * X + Y * Y + Z * Z);
	}

	POINT ConvertWindowPOINT()
	{
		return { iX(), iY() };
	}

	ENGINEAPI class FIntPoint ConvertToPoint() const;

	void Normalize()
	{
		float Len = Length();
		if (0.0f < Len && false == isnan(Len))
		{
			X = X / Len;
			Y = Y / Len;
			Z = Z / Len;
		}
		return;
	}

	FVector NormalizeReturn() const
	{
		FVector Result = *this;
		Result.Normalize();
		return Result;
	}

	// 
	void RotationXDeg(float _Angle)
	{
		RotationXRad(_Angle * UEngineMath::D2R);
	}

	void RotationXRad(float _Angle)
	{
		FVector Copy = *this;
		Z = (Copy.Z * cosf(_Angle)) - (Copy.Y * sinf(_Angle));
		Y = (Copy.Z * sinf(_Angle)) + (Copy.Y * cosf(_Angle));
	}

	FVector RotationXDegReturn(float _Angle)
	{
		return RotationXRadReturn(_Angle * UEngineMath::D2R);
	}

	FVector RotationXRadReturn(float _Angle)
	{
		FVector Result = *this;
		Result.Z = (Z * cosf(_Angle)) - (Y * sinf(_Angle));
		Result.Y = (Z * sinf(_Angle)) + (Y * cosf(_Angle));
		return Result;
	}


	// 
	void RotationYDeg(float _Angle)
	{
		RotationYRad(_Angle * UEngineMath::D2R);
	}

	void RotationYRad(float _Angle)
	{
		FVector Copy = *this;
		X = (Copy.X * cosf(_Angle)) - (Copy.Z * sinf(_Angle));
		Z = (Copy.X * sinf(_Angle)) + (Copy.Z * cosf(_Angle));
	}

	FVector RotationYDegReturn(float _Angle)
	{
		return RotationYRadReturn(_Angle * UEngineMath::D2R);
	}

	FVector RotationYRadReturn(float _Angle)
	{
		FVector Result = *this;
		Result.X = (X * cosf(_Angle)) - (Z * sinf(_Angle));
		Result.Z = (X * sinf(_Angle)) + (Z * cosf(_Angle));
		return Result;
	}

	// 
	void RotationZDeg(float _Angle)
	{
		RotationZRad(_Angle * UEngineMath::D2R);
	}

	void RotationZRad(float _Angle)
	{
		FVector Copy = *this;
		X = (Copy.X * cosf(_Angle)) - (Copy.Y * sinf(_Angle));
		Y = (Copy.X * sinf(_Angle)) + (Copy.Y * cosf(_Angle));
	}

	FVector RotationZDegReturn(float _Angle)
	{
		return RotationZRadReturn(_Angle * UEngineMath::D2R);
	}

	FVector RotationZRadReturn(float _Angle)
	{
		FVector Result = *this;
		Result.X = (X * cosf(_Angle)) - (Y * sinf(_Angle));
		Result.Y = (X * sinf(_Angle)) + (Y * cosf(_Angle));
		return Result;
	}

	float Dot(const FVector& other) const
	{
		return X * other.X + Y * other.Y;
	}

	FVector operator*(float _Value) const
	{
		FVector Result;
		Result.X = X * _Value;
		Result.Y = Y * _Value;
		Result.Z = Z * _Value;
		return Result;
	}

	FVector operator+(const FVector& _Other) const
	{
		FVector Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	// 선언과 구현이 분리된 녀석들만 붙여줘면 된다.
	ENGINEAPI FVector operator*(const class FMatrix& _Matrix) const;
	ENGINEAPI FVector& operator*=(const class FMatrix& _Matrix);

	FVector& operator-=(const FVector& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		return *this;
	}


	FVector operator-(const FVector& _Other) const
	{
		FVector Result;
		Result.X = X - _Other.X;
		Result.Y = Y - _Other.Y;
		return Result;
	}

	FVector operator-() const
	{
		FVector Result;
		Result.X = -X;
		Result.Y = -Y;
		Result.Z = -Z;
		return Result;
	}

	FVector operator/(int _Value) const
	{
		FVector Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}

	FVector operator/(const FVector& Other) const
	{
		FVector Result;
		Result.X = X / Other.X;
		Result.Y = Y / Other.Y;
		return Result;
	}

	// ture가 나오는 
	bool operator==(const FVector& _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	// float은 비교가 굉장히 위험
	// const가 붙은 함수에서는 const가 붙은 함수 호출할수 없다.
	bool EqualToInt(FVector _Other) const
	{
		// const FVector* const Ptr;
		// this = nullptr;
		return iX() == _Other.iX() && iY() == _Other.iY();
	}

	//bool Compare(FVector _Other, float _limite = 0.0f) const
	//{
	//	return X == _Other.X && Y == _Other.Y;
	//}

	FVector& operator+=(const FVector& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;
		return *this;
	}

	FVector& operator*=(const FVector& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;
		return *this;
	}

	FVector& operator*=(float _Other)
	{
		X *= _Other;
		Y *= _Other;
		Z *= _Other;
		return *this;
	}


	std::string ToString()
	{
		std::string Stream;

		Stream += "X : [";
		Stream += std::to_string(X);
		Stream += "] Y : [";
		Stream += std::to_string(Y);
		Stream += "] Z : [";
		Stream += std::to_string(Z);
		Stream += "] W : [";
		Stream += std::to_string(W);
		Stream += "]";
		return Stream;
	}

	FQuat DegAngleToQuaternion()
	{
		FQuat Result;
		Result.DirectVector = DirectX::XMQuaternionRotationRollPitchYawFromVector(DirectVector);
		return Result;
	}

};

using float4 = FVector;

// 행렬 은 보통 매트릭스 라고 합니다.
class FMatrix
{
public:
	union
	{
		float Arr2D[4][4] = { 0, };
		FVector ArrVector[4];
		float Arr1D[16];
		DirectX::XMMATRIX DirectMatrix;

		struct
		{
			float _00;
			float _01;
			float _02;
			float _03;
			float _10;
			float _11;
			float _12;
			float _13;
			float _20;
			float _21;
			float _22;
			float _23;
			float _30;
			float _31;
			float _32;
			float _33;
		};

	};

	FMatrix()
	{
		Identity();
	}

	// 그래픽스 프로그래밍 모든 행렬들은 만들어질때
	// 일단 항등행렬로 만듭니다.

	// 정규화 항등행렬 만드는 함수
	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();
	}

	FVector GetFoward()
	{
		FVector Dir = ArrVector[2];
		Dir.Normalize();
		return Dir;
	}

	FVector GetRight()
	{
		FVector Dir = ArrVector[0];
		Dir.Normalize();
		return Dir;
	}

	FVector GetUp()
	{
		FVector Dir = ArrVector[1];
		Dir.Normalize();
		return Dir;
	}

	ENGINEAPI FMatrix operator*(const FMatrix& _Value);

	void Scale(const FVector& _Value)
	{
		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value.DirectVector);
	}

	void Position(const FVector& _Value)
	{
		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value.DirectVector);
	}

	void RotationDeg(const FVector& _Angle)
	{
		RotationRad(_Angle * UEngineMath::D2R);
	}



	void RotationRad(const FVector& _Angle)
	{
		DirectMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(_Angle.DirectVector);
		// 쿼터니온을 기반으로한 행렬은 치명적인 문제가 많았다.

		// 짐벌락 현상 축이 겹치면서 덜덜덜덜덜 떨리는 현상등도 생겼고.
		// 만들어진 행렬 3축의 각도를 계산하는 순서에 따라서 오류가 나거나 안나는 등의 문제도 생겼습니다.
		// 그래서 짐벌락 축오류부터 수학자들이 이 오류를 해결하기 위해서 복소수 기반의 실수부와 허수부의 조합으로
		// 이루어진 1x4 행렬을 만들어냈다.
		// 복호화가 힘들어요.  30도, 50도, 80도 => 쿼터니온 , 0.12312, 0.323, -0.312f, 0.1312
		// 각도 => 쿼터니온으로 쉽니다.
		// 쿼터니온에서 => 각도로 빼는게 힘듭니다. 부정확합니다.
		// 하지만 회전축의 오류가 해결되어있기 때문에 그냥 각도로 회전행렬을 만드는것보다.
		// 퀀터니온으로 만드는 것을 좀더 추천합니다.

	}


	void Transpose()
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = y; x < 4; x++)
			{
				float Swap = Arr2D[y][x];
				Arr2D[y][x] = Arr2D[x][y];
				Arr2D[x][y] = Swap;
			}
		}
	}

	// View행렬의 인자입니다.
	void View(const FVector& _Pos, const FVector& _Dir, const FVector& _Up)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixLookToLH(_Pos.DirectVector, _Dir.DirectVector, _Up.DirectVector);
		return;
	}

	void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);
	}

	void PerspectiveFovDeg(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	{
		PerspectiveFovRad(_FovAngle * UEngineMath::D2R, _Width, _Height, _Near, _Far);
	}

	void PerspectiveFovRad(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngle, _Width / _Height, _Near, _Far);
	}

	// 화면 확대 -1~1사이의 값이 됐으니까
	// +좌표축 변경 중점 변경
	// 화면의 정중앙을 0,0으로 만듭니다
	// Y축 반전도 여기서 합니다.
	// 뷰포트는 directx에서는 내가 곱해줄 필요가 없다. 다이렉에 넣어주면 다이렉트가 자동으로 해주는 것이다.
	// directx::viewportsetting(ViewPort_desc);

	// 위치와 크기 양쪽영향을 주는 행렬이다.
	// 그것조차도 내마음대로 정할수 있어.

	//                 1280          720        640           360            누가 앞에 나오고 누가 뒤에 나올거냐
	void ViewPort(float _Width, float _Height, float _Left, float _Top, float _ZMin, float _ZMax)
	{
		Identity();
		Arr2D[0][0] = _Width * 0.5f;
		// Y축 반전
		Arr2D[1][1] = -_Height * 0.5f;

		// 화면 2~3뿌릴건데 그중에서 누가 앞에오고 뒤에오고를 결정하려면 
		Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;

		Arr2D[3][0] = Arr2D[0][0] + _Left;
		Arr2D[3][1] = -Arr2D[1][1] + _Top;
		Arr2D[3][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;
	}


	void RotationXDeg(float _Angle)
	{
		RotationXRad(_Angle * UEngineMath::D2R);
	}

	void RotationXRad(float _Angle)
	{
		Identity();
		Arr2D[1][1] = cosf(_Angle);
		Arr2D[1][2] = -sinf(_Angle);
		Arr2D[2][1] = sinf(_Angle);
		Arr2D[2][2] = cosf(_Angle);
	}

	void RotationYDeg(float _Angle)
	{
		RotationYRad(_Angle * UEngineMath::D2R);
	}

	void RotationYRad(float _Angle)
	{
		Identity();
		Arr2D[0][0] = cosf(_Angle);
		Arr2D[0][2] = sinf(_Angle);
		Arr2D[2][0] = -sinf(_Angle);
		Arr2D[2][2] = cosf(_Angle);
	}

	FMatrix InverseReturn()
	{
		FMatrix Result;

		Result.DirectMatrix = DirectX::XMMatrixInverse(nullptr, DirectMatrix);

		return Result;
	}

	void Decompose(FVector& _Scale, FQuat& _RotQuaternion, FVector& _Pos)
	{
		// 회전쪽을 보면 이제 쿼터니온을 설명받아야 하는데.
		DirectX::XMMatrixDecompose(&_Scale.DirectVector, &_RotQuaternion.DirectVector, &_Pos.DirectVector, DirectMatrix);
	}

	void RotationZDeg(float _Angle)
	{
		RotationZRad(_Angle * UEngineMath::D2R);
	}

	void RotationZRad(float _Angle)
	{
		Identity();
		Arr2D[0][0] = cosf(_Angle);
		Arr2D[0][1] = -sinf(_Angle);
		Arr2D[1][0] = sinf(_Angle);
		Arr2D[1][1] = cosf(_Angle);
	}

};

using float4x4 = FMatrix;



enum class ECollisionType
{
	Point,
	Rect,
	CirCle, // 타원이 아닌 정방원 
	Max

	//AABB,
	//OBB,
};

// 대부분 오브젝트에서 크기와 위치는 한쌍입니다.
// 그래서 그 2가지를 모두 묶는 자료형을 만들어서 그걸 써요.
struct FTransform
{
	// transformupdate는 
	// 아래의 값들을 다 적용해서
	// WVP를 만들어내는 함수이다.
	// 변환용 벨류
	float4 Scale;
	float4 Rotation;
	FQuat Quat;
	float4 Location;

	// 릴리에티브 로컬
	float4 RelativeScale;
	float4 RelativeRotation;
	FQuat RelativeQuat;
	float4 RelativeLocation;

	// 월드
	float4 WorldScale;
	float4 WorldRotation;
	FQuat WorldQuat;
	float4 WorldLocation;

	float4x4 ScaleMat;
	float4x4 RotationMat;
	float4x4 LocationMat;
	float4x4 RevolveMat;
	float4x4 ParentMat;
	float4x4 LocalWorld;
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4x4 WVP;

	FTransform()
		: Scale({ 1.0f, 1.0f, 1.0f, 1.0f })
	{

	}


public:
	ENGINEAPI void TransformUpdate(bool _IsAbsolut = false);

	// 역분해 크기 회전 위치를 뜯어내는 함수

	ENGINEAPI void Decompose();

private:
	friend class CollisionFunctionInit;

	static std::function<bool(const FTransform&, const FTransform&)> AllCollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)];

public:
	static bool Collision(ECollisionType _LeftType, const FTransform& _Left, ECollisionType _RightType, const FTransform& _Right);

	// 완전히 같은 형의 함수죠?
	static bool PointToCirCle(const FTransform& _Left, const FTransform& _Right);
	static bool PointToRect(const FTransform& _Left, const FTransform& _Right);

	static bool RectToRect(const FTransform& _Left, const FTransform& _Right);
	static bool RectToCirCle(const FTransform& _Left, const FTransform& _Right);

	static bool CirCleToCirCle(const FTransform& _Left, const FTransform& _Right);
	static bool CirCleToRect(const FTransform& _Left, const FTransform& _Right);

	FVector ZAxisCenterLeftTop() const
	{
		return Location - Scale.Half();
	}

	FVector ZAxisCenterLeftBottom() const
	{
		FVector Result;
		Result.X = Location.X - Scale.hX();
		Result.Y = Location.Y + Scale.hY();
		return Result;
	}

	float ZAxisCenterLeft() const
	{
		return Location.X - Scale.hX();
	}

	float ZAxisCenterTop() const
	{
		return Location.Y - Scale.hY();
	}

	FVector ZAxisCenterRightTop() const
	{
		FVector Result;
		Result.X = Location.X + Scale.hX();
		Result.Y = Location.Y - Scale.hY();
		return Result;
	}

	FVector ZAxisCenterRightBottom() const
	{
		return Location + Scale.Half();
	}

	float ZAxisCenterRight() const
	{
		return Location.X + Scale.hX();
	}

	float ZAxisCenterBottom() const
	{
		return Location.Y + Scale.hY();
	}
};

class FIntPoint
{
public:
	int X = 0;
	int Y = 0;

	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;

	ENGINEAPI FIntPoint()
	{

	}

	FIntPoint(int _X, int _Y) : X(_X), Y(_Y)
	{

	}

	FIntPoint operator+(FIntPoint _Other) const
	{
		FIntPoint Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FIntPoint operator/(int _Value) const
	{
		FIntPoint Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}


	bool operator==(FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	FIntPoint& operator+=(FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}


};


class UColor
{
public:
	static const UColor WHITE;
	static const UColor BLACK;

	union
	{
		int Color;
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
	};

	UColor(unsigned long _Value)
		:Color(_Value)
	{

	}

	bool operator==(const UColor& _Other)
	{
		return R == _Other.R && G == _Other.G && B == _Other.B;
	}


	UColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}
};

