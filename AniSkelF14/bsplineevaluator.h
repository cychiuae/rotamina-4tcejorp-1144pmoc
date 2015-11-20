#ifndef B_SPLINE_EVALUATOR_H
#define B_SPLINE_EVALUATOR_H

#pragma warning(disable : 4786) 

#include <vector>
#include "curveevaluator.h"

class BSplineEvaluator : public CurveEvaluator
{
public:
	void evaluateCurve(const std::vector<Point>& ptvCtrlPts,
		std::vector<Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const;
};

#endif