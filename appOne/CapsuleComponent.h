#pragma once
#include "SpriteComponent.h"
#include "VECTOR.h"
#include "graphic.h"
#include "MATRIX.h"
#include <vector>

class CapsuleComponent :
	public SpriteComponent
{
public:
	CapsuleComponent(class CharacterActor* owner);
	~CapsuleComponent();
	int SetUp();
	void Update()override;
	void Draw()override;
	bool OverlapSegment(class SEGMENT* s1, class SEGMENT* s2, float radius1, float radius2);
	bool OverlapActor(class CharacterActor* a1, class CharacterActor* a2);

	bool LineTraceHitActor(class SEGMENT* seg, CharacterActor** Actor, VECTOR* hitPos);
	class SEGMENT* GetSegment() { return mSeg; }
	const VECTOR& GetOSp() { return mOSp; }
	const VECTOR& GetOEp() { return mOEp; }
	void SetSpandEp(const VECTOR& sp, const VECTOR& ep) { mOSp = sp; mOEp = ep; }
	void SetIsCollision(bool flag) { mIsCollision = flag; }
	bool IsCollision() { return mIsCollision; }
	void AddNotCollisionTags(int tag) { mNotCollisionTags.emplace_back(tag); }
	//点と直線の最短距離
	float calcPointLineDist //最短距離
	(
		const VECTOR& p, //点 
		class SEGMENT* s, //線分（直線扱い）
		VECTOR& mp, //点pから直線に下ろした垂線の端点
		float& t //s.vの長さを1とした時の「s.spからmpまでの長さ」の割合
	);

	//点と線分の最短距離
	float calcPointSegmentDist//最短距離
	(
		const VECTOR& p, //点
		class SEGMENT* s, //線分
		VECTOR& mp, //点pから線分までの最短距離となる点(始点や終点になることもある)
		float& t //s.vの長さを1とした時の「s.spからmpまでの長さ」の割合
	);

	//直線と直線の最短距離
	float calcLineLineDist
	(
		class SEGMENT* s1,//直線１
		class SEGMENT* s2,//直線２
		VECTOR& mp1, //最短線の端点１
		VECTOR& mp2, //最短線の端点２
		float& t1, //s1.vの長さを1とした時の「s1.spからmp1までの長さ」の割合
		float& t2  //s2.vの長さを1とした時の「s2.spからmp2までの長さ」の割合
	);

	//0～1の間にクランプ(値を強制的にある範囲内にすること)
	void clamp0to1(float& v) {
		if (v < 0.0f)  v = 0.0f;
		else if (v > 1.0f)  v = 1.0f;
	};

	//2線分間の最短距離
	float calcSegmentSegmentDist
	(
		class SEGMENT* s1,//線分1
		class SEGMENT* s2,//線分2
		VECTOR& mp1, //最短線の端点1(始点や終点になることもある)
		VECTOR& mp2, //最短線の端点2(始点や終点になることもある)
		float& t1, //s1.vの長さを1とした時の「s1.spからmp1までの長さ」の割合
		float& t2  //s2.vの長さを1とした時の「s2.spからmp2までの長さ」の割合
	);


	//デバッグ用描画関数

#ifdef _DEBUG
	void createCapsule();
	void capsule(const VECTOR& t, const VECTOR& r, const COLOR& col, float segStartPos, float segEndPos, float radius);
	void createSegment();
	void segment(const VECTOR& sp, const VECTOR& ep, const COLOR& col, float thickness = 1);
	float calcSegmentSegmentDist_
	(
		class SEGMENT* s1,//線分1
		class SEGMENT* s2,//線分2
		VECTOR& mp1, //最短線の端点1(始点や終点になることもある)
		VECTOR& mp2, //最短線の端点2(始点や終点になることもある)
		float& t1, //s1.vの長さを1とした時の「s1.spからmp1までの長さ」の割合
		float& t2 //s2.vの長さを1とした時の「s2.spからmp2までの長さ」の割合
	);
#endif

private:
	MATRIX gWorld;
	class SEGMENT* mSeg;
	VECTOR mPos;
	VECTOR mOSp;
	VECTOR mOEp;
	COLOR mCapsuleColor;
	bool mIsCollision;
	std::vector<int>mNotCollisionTags;
};

