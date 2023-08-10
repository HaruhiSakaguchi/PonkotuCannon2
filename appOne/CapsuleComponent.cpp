#include "CapsuleComponent.h"
#include "CharacterActor.h"
#include "mathUtil.h"
#include "Game.h"
#include "SEGMENT.h"
#include "ActorManager.h"

#ifdef _DEBUG
static float mAmbient = 0.0f;
static const int mNumCAng = 24;
static const int mNumCVtx = mNumCAng * (mNumCAng / 2) + 2;
static const int mNumSAng = 4;
static const int mNumSVtx = mNumSAng * 2;
static float mSegRadius = 0.0005f;
static float mBright[mNumCVtx];
static VECTOR mCOp[mNumCVtx];
static VECTOR mLightPos;
static VECTOR mSOp[mNumSVtx];
static VECTOR mCapP[mNumCVtx];
static float mOpX[2] = { 0.0f,1.0f };
#endif

CapsuleComponent::CapsuleComponent(CharacterActor* owner)
	: SpriteComponent(owner)
	, mSeg(nullptr)
	, mPos(0.0f, 0.0f, 0.0f)
	, mIsCollision(true)
{
	SetUp();
#ifdef _DEBUG
	createSegment();
	createCapsule();
#endif
	mOwner->GetGame()->GetActorManager()->AddCapsule(this);
}

CapsuleComponent::~CapsuleComponent()
{
	delete mSeg;

	while (!mNotCollisionTags.empty())
	{
		mNotCollisionTags.pop_back();
	}

	mOwner->GetGame()->GetActorManager()->RemoveCapsule(this);
}

int CapsuleComponent::SetUp()
{
	mSeg = new SEGMENT;
#ifdef _DEBUG
	mLightPos = mOwner->GetGame()->GetAllData()->rendererData.mLightPos;
	mAmbient = mOwner->GetGame()->GetAllData()->rendererData.mAmbient;
#endif
	return 1;
}

void CapsuleComponent::Update()
{
	auto owner = static_cast<CharacterActor*>(mOwner);
	mPos = owner->GetPosition() + owner->GetCapsulOffset();
	VECTOR osp = VECTOR(0.0f, 0.0f, 0.0f);
	VECTOR oep = VECTOR(0.0f, 0.0f, 0.0f);

	if (mOEp.x == 0.0f && mOEp.y == 0.0f && mOEp.z == 0.0f)
	{
		mOEp = oep;
	}
	if (mOSp.x == 0.0f && mOSp.y == 0.0f && mOSp.z == 0.0f)
	{
		mOSp = osp;
	}

	mSeg->update(mPos, owner->GetRotation(), mOSp, mOEp);

	for (auto capsule : mOwner->GetGame()->GetActorManager()->GetCapsules())
	{
		auto capOwner = static_cast<CharacterActor*>(capsule->GetOwner());

		bool isNotCollision = false;

		for (auto tags : mNotCollisionTags)
		{
			if (static_cast<CharacterActor::CharactersTag>(tags) == capOwner->GetTag())
			{
				isNotCollision = true;
			}
		}

		if (capsule == this || isNotCollision || capOwner->GetHp() <= 0)
		{
			continue;
		}


		VECTOR mp1;
		VECTOR mp2;
		float t1;
		float t2;
		float dist = 0;

		dist = calcSegmentSegmentDist(mSeg, capsule->GetSegment(), mp1, mp2, t1, t2);
		if (mIsCollision && capsule->IsCollision() && dist < owner->GetRadius() + static_cast<CharacterActor*>(capsule->GetOwner())->GetRadius())
		{
			capsule->GetOwner()->SetPosition(capsule->GetOwner()->GetPosition() + (mp2 - mp1).normalize() * 0.05f);
			if (capsule->GetOwner()->GetPosition().y < 0.0f && capsule->GetOwner()->PositionOnMap(capsule->GetOwner()->GetPosition(), static_cast<CharacterActor*>(capsule->GetOwner())->GetRadius()))
			{
				capsule->GetOwner()->SetPosition(capsule->GetOwner()->GetPosition().x, 0.0f, capsule->GetOwner()->GetPosition().z);
			}
		}
	}
}

void CapsuleComponent::Draw()
{
	auto owner = static_cast<CharacterActor*>(mOwner);
#ifdef _DEBUG
	//segment(mSeg->GetSP(), mSeg->GetEP(), COLOR(255, 255, 255), 100);
	//capsule(mPos, owner->GetRotation(), mCapsuleColor, mOSp.y, mOEp.y, owner->GetRadius());
#endif
}

bool CapsuleComponent::OverlapSegment(SEGMENT* s1, SEGMENT* s2, float radius1, float radius2)
{
	VECTOR mp1;
	VECTOR mp2;
	float t1;
	float t2;
	float dist = 0;

	dist = calcSegmentSegmentDist(s1, s2, mp1, mp2, t1, t2);

	if (dist < radius1 + radius2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CapsuleComponent::OverlapActor(class CharacterActor* a1, class CharacterActor* a2)
{
	auto seg1 = a1->GetCapsule()->GetSegment();
	auto seg2 = a2->GetCapsule()->GetSegment();

	VECTOR a1Pos = a1->GetPosition() + a1->GetCapsulOffset();
	VECTOR a2Pos = a2->GetPosition() + a2->GetCapsulOffset();

	seg1->update(a1Pos, a1->GetRotation(), a1->GetCapsule()->GetOSp(), a1->GetCapsule()->GetOEp());
	seg2->update(a2Pos, a2->GetRotation(), a2->GetCapsule()->GetOSp(), a2->GetCapsule()->GetOEp());

	return OverlapSegment(seg1, seg2, a1->GetRadius(), a2->GetRadius());
}

bool CapsuleComponent::LineTraceHitActor(class SEGMENT* seg, CharacterActor** Actor, VECTOR* hitPos)
{
	auto owner = static_cast<CharacterActor*>(mOwner);
	VECTOR pos = owner->GetPosition() + owner->GetCapsulOffset();
	seg->update(pos, owner->GetRotation());

	bool flag = false;

	for (auto chara : owner->GetGame()->GetActorManager()->GetCharacters())
	{
		if (chara == owner || (!chara->GetCapsule() || chara->GetCategory() == CharacterActor::ActorsCategory::EObject))
		{
			continue;
		}

		auto Cseg = chara->GetCapsule()->GetSegment();
		Cseg->update(chara->GetPosition() + chara->GetCapsulOffset(), chara->GetRotation(), chara->GetCapsule()->GetOSp(), chara->GetCapsule()->GetOEp());
		VECTOR mp1;
		VECTOR mp2;
		float t1;
		float t2;
		float dist = 0;

		dist = calcSegmentSegmentDist(Cseg, seg, mp1, mp2, t1, t2);

		if ((0.1f + chara->GetRadius()) > dist)
		{
			seg->SetEP(seg->GetSP() + seg->GetV() * t2);
			flag = true;
			*Actor = chara;
			*hitPos = seg->GetEP();
			break;
		}
	}

	return flag;
}

#ifdef _DEBUG
void CapsuleComponent::createSegment()
{

	//原点から右へ伸びる角柱を作る
	float angle = 3.1415926f / (mNumSAng / 2);
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < mNumSAng; i++) {
			mSOp[mNumSAng * j + i].x = mOpX[j];
			mSOp[mNumSAng * j + i].y = Cos(angle * i) * mSegRadius;
			mSOp[mNumSAng * j + i].z = Sin(angle * i) * mSegRadius;
		}
	}
}
#endif

#ifdef _DEBUG
void CapsuleComponent::segment(const VECTOR& sp, const VECTOR& ep, const COLOR& col, float thickness)
{
	VECTOR* p = new VECTOR[mNumSVtx];
	VECTOR v = ep - sp;
	float len = v.mag();
	float angleY = Atan2(-v.z, v.x);
	v.normalize();
	float angleZ = Acos(-v.y) - 1.57f;
	gWorld.identity();
	gWorld.mulTranslate(sp.x, sp.y, sp.z);
	gWorld.mulRotateY(angleY);
	gWorld.mulRotateZ(angleZ);
	gWorld.mulScaling(len, thickness, thickness);
	for (int i = 0; i < mNumSVtx; i++) {
		p[i] = gWorld * mSOp[i];
		p[i] = mOwner->GetGame()->GetRenderer()->GetView() * p[i];
		p[i] = mOwner->GetGame()->GetRenderer()->GetProj() * p[i];
	}
	//描画
	for (int i = 0; i < mNumSAng; i++) {
		//側面である四角形
		int a = i;
		int b = i + mNumSAng;
		int c = (i + 1) % mNumSAng == 0 ? i + 1 - mNumSAng : i + 1;
		int d = (b + 1) % mNumSAng == 0 ? b + 1 - mNumSAng : b + 1;
		triangle3D(p[a], p[b], p[c], col, col, col);
		triangle3D(p[c], p[b], p[d], col, col, col);
	}

	delete[]p;
}
#endif

#ifdef _DEBUG
void CapsuleComponent::createCapsule()
{
	VECTOR light = mLightPos;
	light.normalize();
	float radius = 0.2f;
	float angle = 3.1415926f / (mNumCAng / 2);
	int j, k = 0;
	//北極になる頂点
	mCOp[k].set(0, 1, 0);
	mBright[k] = dot(light, mCOp[k]);
	if (mBright[k] < mAmbient)mBright[k] = mAmbient;
	k++;
	//上半球
	for (j = 0; j < (mNumCAng / 4); j++) {
		float y = Cos(angle * (j + 1));
		float r = Sin(angle * (j + 1));
		//円の座標
		for (int i = 0; i < mNumCAng; i++) {
			mCOp[k].set(Cos(angle * i) * r, y, Sin(angle * i) * r);
			//op[k]を法線として頂点の明るさを計算
			mBright[k] = dot(light, mCOp[k]);
			if (mBright[k] < mAmbient)mBright[k] = mAmbient;
			k++;
		}
	}
	//下半球
	for (j -= 1; j < (mNumCAng / 2) - 1; j++) {
		float y = Cos(angle * (j + 1));
		float r = Sin(angle * (j + 1));
		//円の座標
		for (int i = 0; i < mNumCAng; i++) {
			mCOp[k].set(Cos(angle * i) * r, y, Sin(angle * i) * r);
			//op[k]を法線として頂点の明るさを計算
			mBright[k] = dot(light, mCOp[k]);
			if (mBright[k] < mAmbient)mBright[k] = mAmbient;
			k++;
		}
	}
	//南極になる頂点
	mCOp[k].set(0, -1, 0);
	mBright[k] = dot(light, mCOp[k]);
	if (mBright[k] < mAmbient)mBright[k] = mAmbient;
}
#endif
#ifdef _DEBUG
void CapsuleComponent::capsule(const VECTOR& t, const VECTOR& r,
	const COLOR& col, float segStartPos, float segEndPos, float radius)
{


	//上半球
	MATRIX world;
	world.identity();
	world.mulTranslate(t);
	world.mulRotateYXZ(r);
	world.mulTranslate(0, segStartPos, 0);
	world.mulScaling(radius, radius, radius);
	for (int i = 0; i < mNumCVtx / 2; i++) {
		mCapP[i] = world * mCOp[i];
		mCapP[i] = mOwner->GetGame()->GetRenderer()->GetView() * mCapP[i];
		mCapP[i] = mOwner->GetGame()->GetRenderer()->GetProj() * mCapP[i];
	}
	//下半球
	world.identity();
	world.mulTranslate(t);
	world.mulRotateYXZ(r);
	world.mulTranslate(0, segEndPos, 0);
	world.mulScaling(radius, radius, radius);
	for (int i = mNumCVtx / 2; i < mNumCVtx; i++) {
		mCapP[i] = world * mCOp[i];
		mCapP[i] = mOwner->GetGame()->GetRenderer()->GetView() * mCapP[i];
		mCapP[i] = mOwner->GetGame()->GetRenderer()->GetProj() * mCapP[i];
	}
	//描画
	//上蓋的な面は三角形で描画
	for (int i = 0; i < mNumCAng; i++) {
		int a = 0;
		int b = i + 1;
		int c = (i + 1) % mNumCAng == 0 ? i + 2 - mNumCAng : i + 2;
		VECTOR m = mCapP[b] - mCapP[a];
		VECTOR n = mCapP[c] - mCapP[a];
		//if (m.x * n.y - m.y * n.x <= 0)
		{
			triangle3D(mCapP[a], mCapP[b], mCapP[c], col * mBright[a], col * mBright[b], col * mBright[c]);
			//	print("p(" + (let)p[a].x + "," + (let)p[a].y + "," + (let)p[a].z + ")");
		}
	}
	//側面的な面は四角形で描画
	for (int i = 0; i < mNumCVtx - mNumCAng - 2; i++) {
		int a = i + 1;
		int b = a + mNumCAng;
		int c = (i + 1) % mNumCAng == 0 ? b + 1 - mNumCAng : b + 1;
		int d = (i + 1) % mNumCAng == 0 ? a + 1 - mNumCAng : a + 1;
		VECTOR m = mCapP[b] - mCapP[a];
		VECTOR n = mCapP[c] - mCapP[a];
		//if (m.x * n.y - m.y * n.x <= 0)
		//{
		triangle3D(mCapP[a], mCapP[b], mCapP[c], col * mBright[a], col * mBright[b], col * mBright[c]);
		triangle3D(mCapP[a], mCapP[c], mCapP[d], col * mBright[a], col * mBright[c], col * mBright[d]);
		//print("p(" + (let)p[a].x + "," + (let)p[a].y + "," + (let)p[a].z + ")");
	//}
	}
	////下蓋的な面は三角形で描画
	for (int i = mNumCVtx - mNumCAng - 1; i < mNumCVtx - 1; i++) {
		int a = mNumCVtx - 1;
		int b = i;
		int c = i % mNumCAng == 0 ? i + 1 - mNumCAng : i + 1;
		VECTOR m = mCapP[b] - mCapP[a];
		VECTOR n = mCapP[c] - mCapP[a];
		//if (m.x * n.y - m.y * n.x >= 0)
		{
			triangle3D(mCapP[a], mCapP[b], mCapP[c], col * mBright[a], col * mBright[b], col * mBright[c]);
		}
	}
}
#endif

//点と直線の最短距離
float CapsuleComponent::calcPointLineDist //最短距離
(
	const VECTOR& p, //点 
	SEGMENT* s, //線分（直線扱い）
	VECTOR& mp, //点pから直線に下ろした垂線の端点
	float& t //s.vの長さを1とした時の「s.spからmpまでの長さ」の割合
)
{
	t = 0.0f;
	float dvv = s->GetV().magSq();//dot(s.v, s.v)と同じ
	if (dvv > 0.0f) {
		t = dot(s->GetV(), p - s->GetSP()) / dvv;
		// 上の式の説明
		// dot(s.v, p-s.sp) は |s.v||p-s.sp|cosΘ
		// dvvは|s.v|の２乗
		// 上の計算で、tは |p-s.sp|cosΘ / |s.v|となる。
		// つまりtは「dotで投影した長さ÷s.vの長さ」という割合になる
	}
	mp = s->GetSP() + s->GetV() * t;
	return (p - mp).mag();
}

//点と線分の最短距離
float CapsuleComponent::calcPointSegmentDist//最短距離
(
	const VECTOR& p, //点
	SEGMENT* s, //線分
	VECTOR& mp, //点pから線分までの最短距離となる点(始点や終点になることもある)
	float& t //s.vの長さを1とした時の「s.spからmpまでの長さ」の割合
)
{
	//とりあえず点から直線までの最短距離やmp,tを求めてみる
	float dist = calcPointLineDist(p, s, mp, t);
	//mpが線分の外にある(始点寄り)
	if (t < 0.0f) {
		//点から線分の始点までの距離が最短
		mp = s->GetSP();
		return (p - mp).mag();
	}
	//mpが線分の外にある(終点寄り)
	if (t > 1.0f) {
		//点から線分の終点までの距離が最短
		mp = s->GetEP();
		return(p - mp).mag();
	}
	//mpが線分内にある
	//0 <= t <= 1
	return dist;
}

//直線と直線の最短距離
float CapsuleComponent::calcLineLineDist
(
	SEGMENT* s1,//直線１
	SEGMENT* s2,//直線２
	VECTOR& mp1, //最短線の端点１
	VECTOR& mp2, //最短線の端点２
	float& t1, //s1.vの長さを1とした時の「s1.spからmp1までの長さ」の割合
	float& t2  //s2.vの長さを1とした時の「s2.spからmp2までの長さ」の割合
)
{
	//2直線が平行
	if (cross(s1->GetV(), s2->GetV()).magSq() < 0.000001f) {
		//線分1の始点から直線2までの最短距離問題に帰着する
		t1 = 0.0f;
		mp1 = s1->GetSP();
		float dist = calcPointLineDist(mp1, s2, mp2, t2);
		return dist;
	}

	float dv1v2 = dot(s1->GetV(), s2->GetV());
	float dv1v1 = s1->GetV().magSq();//dot(s1.v,s1.v)と同じ
	float dv2v2 = s2->GetV().magSq();//dot(s2.v,s2.v)と同じ
	VECTOR vp2p1 = s1->GetSP() - s2->GetSP();
	t1 = (dv1v2 * dot(s2->GetV(), vp2p1) - dv2v2 * dot(s1->GetV(), vp2p1))
		/ (dv1v1 * dv2v2 - dv1v2 * dv1v2);
	mp1 = s1->GetSP() + s1->GetV() * t1;
	t2 = dot(s2->GetV(), mp1 - s2->GetSP()) / dv2v2;
	mp2 = s2->GetSP() + s2->GetV() * t2;
	return (mp2 - mp1).mag();
}

//2線分間の最短距離
float CapsuleComponent::calcSegmentSegmentDist
(
	SEGMENT* s1,//線分1
	SEGMENT* s2,//線分2
	VECTOR& mp1, //最短線の端点1(始点や終点になることもある)
	VECTOR& mp2, //最短線の端点2(始点や終点になることもある)
	float& t1, //s1.vの長さを1とした時の「s1.spからmp1までの長さ」の割合
	float& t2  //s2.vの長さを1とした時の「s2.spからmp2までの長さ」の割合
)
{
	float dist = 0;
	{
		// s1.vが縮退している？
		if (s1->GetV().magSq() < 0.000001f) {
			// s2.vも縮退？
			if (s2->GetV().magSq() < 0.000001f) {
				// 点と点の距離の問題に帰着
				dist = (s2->GetSP() - s1->GetSP()).mag();
				mp1 = s1->GetSP();
				mp2 = s2->GetSP();
				t1 = t2 = 0.0f;
				//segment(mp1, mp2, COLOR(255, 255, 255), 10);
				return dist;
			}
			else {
				// s1.spとs2.vの最短問題に帰着
				dist = calcPointSegmentDist(s1->GetSP(), s2, mp2, t2);
				mp1 = s1->GetSP();
				t1 = 0.0f;
				clamp0to1(t2);
				//segment(mp1, mp2, COLOR(255, 255, 255), 10);
				return dist;
			}
		}
		// s2.vが縮退している？
		else if (s2->GetV().magSq() < 0.000001f) {
			// s2.spとsv1の最短問題に帰着
			float dist = calcPointSegmentDist(s2->GetSP(), s1, mp1, t1);
			mp2 = s2->GetSP();
			clamp0to1(t1);
			t2 = 0.0f;
			//segment(mp1, mp2, COLOR(255, 255, 255), 10);
			return dist;
		}
	}

	//----------------------------------------------------------------
	//とりあえず2直線間の最短距離,mp1,mp2,t1,t2を求めてみる
	dist = calcLineLineDist(s1, s2, mp1, mp2, t1, t2);
	if (0.0f <= t1 && t1 <= 1.0f &&
		0.0f <= t2 && t2 <= 1.0f) {
		//mp1,mp2が両方とも線分内にあった
		return dist;
	}
	//mp1,mp2の両方、またはどちらかが線分内になかったので次へ

	//----------------------------------------------------------------
	//mp1,t1を求め直す ⇒ t2を0～1にクランプしてmp2からs1.vに垂線を降ろしてみる
	clamp0to1(t2);
	mp2 = s2->GetSP() + s2->GetV() * t2;
	dist = calcPointLineDist(mp2, s1, mp1, t1);
	if (0.0f <= t1 && t1 <= 1.0f) {
		//mp1が線分内にあった
		return dist;
	}
	//mp1が線分内になかったので次へ

	//----------------------------------------------------------------
	//mp2,t2を求め直す ⇒ t1を0～1にクランプしてmp1からs2.vに垂線を降ろしてみる
	clamp0to1(t1);
	mp1 = s1->GetSP() + s1->GetV() * t1;
	dist = calcPointLineDist(mp1, s2, mp2, t2);
	if (0.0f <= t2 && t2 <= 1.0f) {
		//mp2が線分内にあった
		return dist;
	}
	//mp2が線分内になかったので次へ

	//----------------------------------------------------------------
	//t2をクランプしてmp2を再計算すると、mp1からmp2までが最短
	clamp0to1(t2);
	mp2 = s2->GetSP() + s2->GetV() * t2;
	return (mp2 - mp1).mag();
}

#ifdef _DEBUG
//補助線バージョン
COLOR Yellow(255, 255, 0);
COLOR Red(255, 0, 0);
COLOR Green(0, 255, 0);
COLOR Cyan(0, 255, 255);
float CapsuleComponent::calcSegmentSegmentDist_
(
	SEGMENT* s1,//線分1
	SEGMENT* s2,//線分2
	VECTOR& mp1, //最短線の端点1(始点や終点になることもある)
	VECTOR& mp2, //最短線の端点2(始点や終点になることもある)
	float& t1, //s1.vの長さを1とした時の「s1.spからmp1までの長さ」の割合
	float& t2 //s2.vの長さを1とした時の「s2.spからmp2までの長さ」の割合
)
{
	//直線に見せるための補助線
	segment(s1->GetSP() - s1->GetV() * 3, s1->GetEP() + s1->GetV() * 3, COLOR(90, 90, 90), 2);
	segment(s2->GetSP() - s2->GetV() * 3, s2->GetEP() + s2->GetV() * 3, COLOR(90, 90, 90), 2);

	float dist = 0;

	//------------------------------------------------------------------------
	//check1:とりあえず2直線間の最短距離,mp1,mp2,t1,t2を求めてみる
	dist = calcLineLineDist(s1, s2, mp1, mp2, t1, t2);
	fill(Yellow);
	if (0.0f <= t1 && t1 <= 1.0f &&
		0.0f <= t2 && t2 <= 1.0f) {
		//mp1,mp2が両方とも線分内にあった
		print((let)"check1〇：t1=" + t1 + " t2=" + t2);
		segment(mp1, mp2, Yellow, 10);
		point(mp1, Yellow, 30);
		point(mp2, Yellow, 30);
		return dist;
		//return 0;

	}
	print((let)"check1×：t1=" + t1 + " t2=" + t2);
	segment(mp1, mp2, Yellow, 2);
	point(mp2, Yellow, 12);
	point(mp1, Yellow, 12);
	//mp1,mp2の両方、またはどちらかが線分内になかったので次へ

	//------------------------------------------------------------------------
	//check2:mp1,t1を求め直す ⇒ t2を0～1にクランプしてmp2からs1.vに垂線を降ろしてみる
	clamp0to1(t2);
	mp2 = s2->GetSP() + s2->GetV() * t2;
	dist = calcPointLineDist(mp2, s1, mp1, t1);
	fill(Red);
	if (0.0f <= t1 && t1 <= 1.0f) {
		//mp1が線分内にあった
		print((let)"check2〇：t1=" + t1 + " t2=" + t2);
		segment(mp1, mp2, Red, 10);
		point(mp1, Red, 30);
		return dist;
		//return 0;

	}
	print((let)"check2×：t1=" + t1 + " t2=" + t2);
	segment(mp1, mp2, Red, 2);
	point(mp1, Red, 12);
	//mp1が線分内になかったので次へ

	//------------------------------------------------------------------------
	//check3:mp2,t2を求め直す ⇒ t1を0～1にクランプしてmp1からs2.vに垂線を降ろしてみる
	clamp0to1(t1);
	mp1 = s1->GetSP() + s1->GetV() * t1;
	dist = calcPointLineDist(mp1, s2, mp2, t2);
	fill(Green);
	if (0.0f <= t2 && t2 <= 1.0f) {
		//mp2が線分内にあった
		print((let)"check3〇：t1=" + t1 + " t2=" + t2);
		segment(mp1, mp2, Green, 10);
		point(mp2, Green, 30);
		return dist;
		//return 0;
	}
	print((let)"check3×：t1=" + t1 + " t2=" + t2);
	segment(mp1, mp2, Green, 2);
	point(mp2, Green, 12);
	//mp2が線分内になかったので次へ

	//-----------------------------------------------------------------------
	clamp0to1(t2);
	mp2 = s2->GetSP() + s2->GetV() * t2;
	fill(Cyan);
	print((let)"last  　：t1=" + t1 + " t2=" + t2);
	segment(mp1, mp2, COLOR(Cyan), 10);
	//ここまで来たら、mp1からmp2までが最短
	return (mp2 - mp1).mag();
}

#endif