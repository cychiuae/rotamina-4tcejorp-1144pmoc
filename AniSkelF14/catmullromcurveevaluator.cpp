#include "CatmullRomCurveEvaluator.h"
#include <assert.h>
#include <algorithm>
#include "modelerui.h"

static Mat4<float> BASIS = Mat4<float>(-1, 3, -3, 1,
									   2, -5, 4, -1,
									   -1, 0, 1, 0,
									   0, 2, 0, 0) / 2.0;
#define SEGMENT 40

void CatmullRomCurveEvaluator::evaluateCurve(const vector<Point> &ptvCtrlPts,
		vector<Point> &ptvEvaluatedCurvePts, const float &fAniLength,
		const bool &bWrap) const
{
	ptvEvaluatedCurvePts.clear();

	vector<Point> pts;
	if (bWrap) {
		pts.push_back(Point((ptvCtrlPts.end() - 2)->x - fAniLength, (ptvCtrlPts.end() - 2)->y));
		pts.push_back(Point(ptvCtrlPts.back().x - fAniLength, ptvCtrlPts.back().y));
		pts.insert(pts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		pts.push_back(Point(ptvCtrlPts.front().x + fAniLength, ptvCtrlPts.front().y));
		pts.push_back(Point((ptvCtrlPts.begin() + 1)->x + fAniLength, (ptvCtrlPts.begin() + 1)->y));
	}else {
		pts.push_back(Point(0, ptvCtrlPts[0].y));
		pts.insert(pts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		pts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
	}

	for (size_t cp = 0; cp + 3 < pts.size(); ++cp)
	{
		const Vec4f Px(pts[cp].x, pts[cp + 1].x, pts[cp + 2].x, pts[cp + 3].x);
		const Vec4f Py(pts[cp].y, pts[cp + 1].y, pts[cp + 2].y, pts[cp + 3].y);

		for (int seg = 0; seg < SEGMENT; seg++) {
			const float t = seg / (float)SEGMENT;
			const Vec4f T((float)pow(t, 3), (float)pow(t, 2), t, 1);
			Point p;
			p.x = T * BASIS * Px;
			p.y = T * BASIS * Py;
			if (ptvEvaluatedCurvePts.empty() || p.x > ptvEvaluatedCurvePts.back().x) {
				ptvEvaluatedCurvePts.push_back(p);
			}
		}
	}

	if (!bWrap) {
		if (ptvCtrlPts.back().x > ptvEvaluatedCurvePts.back().x) {
			ptvEvaluatedCurvePts.push_back(ptvCtrlPts.back());
		}
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts[0].y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
	}
}