#pragma once

#include <vector>
#include <list>
#include <memory>

#include "QuadObjectContainer.h"
#include "../Primitive/Primitive.h"
#include "../Math/Morton.h"
#include "../Renderer.h"

template<class T>
class QuadTree {
	std::vector<std::vector<T*>> mList;
	Point mOrigin;
	Point mEnd;
	int mLevel;
	int mCellX, mCellY;
public:
	template<class Obj>
	void forEachChildren(int morton, Obj* object) {
		if (morton >= mList.size())return;
		if (morton < 0)return;
		for (auto it : mList[morton])object->Collided(*it);
		forEachChildren(morton * 4 + 1, object);
		forEachChildren(morton * 4 + 2, object);
		forEachChildren(morton * 4 + 3, object);
		forEachChildren(morton * 4 + 4, object);
	}

	template<class Obj>
	void forEachChildren(int morton, Obj* object, void(*callback)(const Obj&, const T&)) {
		if (morton >= mList.size())return;
		if (morton < 0)return;
		for (auto it : mList[morton])callback(*object, *it);
		forEachChildren(morton * 4 + 1, object, callback);
		forEachChildren(morton * 4 + 2, object, callback);
		forEachChildren(morton * 4 + 3, object, callback);
		forEachChildren(morton * 4 + 4, object, callback);
	}

	template<class Obj>
	void forEachParent(int morton, Obj* object) {
		if (morton <= 0)return;
		if (morton >= mList.size())return;
		for (int i = (morton - 1) / 4; i > 0; i /= 4) {
			for (auto it : mList[i]) {
				object->Collided(*it);
			}
		}
		for (auto it : mList[0]) object->Collided(*it);
	}

	template<class Obj>
	void forEachParent(int morton, Obj* object, void(*callback)(const Obj&, const T&)) {
		if (morton <= 0)return;
		if (morton >= mList.size())return;
		for (int i = (morton - 1) / 4; i > 0; i /= 4) {
			for (auto it : mList[i]) {
				callback(*object, *it);
			}
		}
		for (auto it : mList[0]) callback(*object, *it);
	}

	template<class Obj>
	void forEachThis(int morton, Obj* object) {
		if (morton < 0)return;
		if (morton >= mList.size())return;
		for (auto it : mList[morton]) object->Collided(*it);
	}

	template<class Obj>
	void forEachThis(int morton, Obj* object, void(*callback)(const Obj&, const T&)) {
		if (morton < 0)return;
		if (morton >= mList.size())return;
		for (auto it : mList[morton]) callback(*object, *it);
	}

	QuadTree(int level, const Rect& region) noexcept
		: mLevel(level), mOrigin(region.tl), mList((pow(4, level + 1) - 1) / 3), mEnd(region.br()){
		int s = pow(2, level); 
		mCellX = region.width / s;
		mCellY = region.height / s;
	}
	void push(int morton, T* obj) {
		if (morton < 0)morton = 0;
		if (morton >= mList.size())morton = 0;
		mList[morton].push_back(obj);
	}
	void push(T* obj) {
		push(GetMorton(obj), obj);
	}
	void clear() noexcept {
		for (auto& list : mList) list.clear();
	}
	template<class Obj>
	void Collided(Obj* object) {
		int morton = getMorton(object, mOrigin, mCellX, mCellY);
		//parent
		forEachParent(morton, object);
		//child and this node
		forEachChildren(morton, object);
	}

	template<class Obj>
	int GetMorton(Obj* obj) {
		return getMorton(obj, mOrigin, mCellX, mCellY);
	}

	void DrawGrid(int color) {
		for (int x = mOrigin.x; x < mEnd.x; x+=mCellX) {
			DxWrp::DrawLine(x, mOrigin.y,x,mEnd.y , color);
		}
		for (int y = mOrigin.y; y < mEnd.y; y += mCellY) {
			DxWrp::DrawLine(mOrigin.x, y, mEnd.x, y, color);
		}
	}
	void DrawMortonRect(const Circle& p, int L0color, int L1color, int L2color) {
		const Point tl = { p.p.x - p.r,p.p.y - p.r };
		const Point br = { p.p.x + p.r,p.p.y + p.r };
		int tlmtn = getMorton(tl, mOrigin, mCellX, mCellY);
		int brmtn = getMorton(br, mOrigin, mCellX, mCellY);
		int mtn = tlmtn ^ brmtn;
		int level = 3 - getMortonLevel(mtn);
		Point a = p.p - mOrigin;
		Rect rect(mOrigin, mEnd);
		int cWidth = rect.width / (pow(2, level));
		int cHeight = rect.height / (pow(2, level));
		int xIndex = a.x / cWidth;
		int yIndex = a.y / cHeight;
		int color;
		switch (level) {
		case 0:color = L0color; break;
		case 1:color = L1color; break;
		case 2:color = L2color; break;
		default:color = L2color;
		}
		DxWrp::DrawBox(
			mOrigin.x + xIndex * cWidth, mOrigin.y + yIndex * cHeight,
			mOrigin.x + (xIndex + 1) * cWidth, mOrigin.y + (yIndex + 1) * cHeight,
			color);
		int parentmtn=(mtn - 1) / 4;
		int pxIndex = a.x / (cWidth*2);
		int pyIndex = a.y / (cHeight*2);
		DxWrp::DrawBox(
			mOrigin.x + pxIndex * cWidth*2, mOrigin.y + pyIndex * cHeight*2,
			mOrigin.x + (pxIndex + 1) * cWidth*2, mOrigin.y + (pyIndex + 1) * cHeight*2,
			color);
	}
};




/*template<class Func, class Obj>
void forEachChild(int morton, Func& function, Obj& object) {
for (auto it = mList[morton].begin(), ite = mList[morton].end(); it != ite;) {
function(it, object);
}
if (morton * 4 + 1 >= mList.size())return;
forEachChild(morton * 4 + 1, function, object);
forEachChild(morton * 4 + 2, function, object);
forEachChild(morton * 4 + 3, function, object);
forEachChild(morton * 4 + 4, function, object);
}*/