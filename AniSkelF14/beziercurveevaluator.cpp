#include "beziercurveevaluator.h"

void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& control_points, 
										 std::vector<Point>& evaluated_curve_points, 
										 const float& animation_length, 
										 const bool& wrap_control_points) const {
	// Connect the point if no more than 4 control points
	evaluated_curve_points.clear();

	if (control_points.size() < 4) {
		for (int i = 0; i < control_points.size(); i++) {
			evaluated_curve_points.push_back(control_points[i]);
		}
		
		float x = 0.0f, y = 0.0f;

		if (wrap_control_points) {
			if (control_points[0].x + animation_length - control_points[control_points.size() - 1].x > 0.0f) {
				y = (control_points[0].y * (animation_length - control_points[control_points.size() - 1].x) + control_points[control_points.size() - 1].y * control_points[0].y) / (control_points[0].x + animation_length - control_points[control_points.size() - 1].x);
			} else {
				y = control_points[0].y;
			}
		} else {
			y = control_points[0].y;;
		}

		evaluated_curve_points.insert(evaluated_curve_points.begin(), Point(x, y));

		x = animation_length;
		if (!wrap_control_points) {
			y = control_points[control_points.size() - 2].y; // Added one point before, so size - 2
		} 
		evaluated_curve_points.push_back(Point(x, y));

	} else {
		const Mat4d M(-1, 3, -3, 1,
					   3, -6, 3, 0,
				      -3, 3, 0, 0,
					   1, 0, 0, 0);
	
		std::vector<Point> controlPoints;
		for (int i = 0; i < control_points.size();i++) {
			controlPoints.push_back(control_points[i]);
		}

		if (wrap_control_points) {
			for (int i = 0; i < 3; i++) {
				controlPoints.push_back(Point(control_points[0].x + animation_length, control_points[0].y));
				controlPoints.insert(controlPoints.begin(), Point(control_points[control_points.size() - 1].x - animation_length, control_points[control_points.size() - 1].y));
			}
		} /*else {
			for (int i = 0; i < 3; i++) {
				controlPoints.insert(controlPoints.begin(), Point(control_points[0].x - animation_length, control_points[0].y));
				controlPoints.push_back(Point(control_points[control_points.size() - 1].x + animation_length, control_points[control_points.size() - 1].y));
			}
		}*/

		int numberOfControlPoint = controlPoints.size();
		for (int i = 0; i < numberOfControlPoint - 3; i += 3) {
			Point points[4];
			for (int j = 0; j < 4; j++) {
				points[j] = controlPoints[i + j];
			}
			Vec4d Px(points[0].x, points[1].x, points[2].x, points[3].x);
			Vec4d Py(points[0].y, points[1].y, points[2].y, points[3].y);
			for (int j = 0; j < 100; j++) {
				float t = j / 100.0f;
				const Vec4d T(t*t*t, t*t, t, 1);
				Point Q;
				Q.x = T * M * Px;
				Q.y = T * M * Py;
				evaluated_curve_points.push_back(Q);
			}
		}

		if (!wrap_control_points) {
			evaluated_curve_points.insert(evaluated_curve_points.begin(), Point(0, evaluated_curve_points[0].y));
			evaluated_curve_points.push_back(Point(animation_length, evaluated_curve_points[evaluated_curve_points.size() - 1].y));
		}
	}
}
