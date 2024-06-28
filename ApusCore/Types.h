#pragma once
#include <cmath>


namespace ApusCore {
	enum ImageType {
		png, jpeg, bmp, tga
	};

	struct Color {
	public:
		float r, g, b, a;

		static Color pow(Color a, Color b) {
			return {std::powf(a.r, b.r), std::powf(a.g, b.g), std::powf(a.b, b.b), std::powf(a.a, b.a)};
		}
		static Color pow(Color a, float b) {
			return { std::powf(a.r, b), std::powf(a.g, b), std::powf(a.b, b), std::powf(a.a, b) };
		}
		static Color sqrt(Color a) {
			return { std::sqrtf(a.r), std::sqrtf(a.g), std::sqrtf(a.b), std::sqrtf(a.a) };
		}
	};

	ApusCore::Color operator* (ApusCore::Color a, ApusCore::Color b);
	ApusCore::Color operator/ (ApusCore::Color a, ApusCore::Color b);
	ApusCore::Color operator+ (ApusCore::Color a, ApusCore::Color b);
	ApusCore::Color operator- (ApusCore::Color a, ApusCore::Color b);

	ApusCore::Color operator* (ApusCore::Color a, float b);
	ApusCore::Color operator/ (ApusCore::Color a, float b);
	ApusCore::Color operator+ (ApusCore::Color a, float b);
	ApusCore::Color operator- (ApusCore::Color a, float b);

	std::ostream& operator<< (std::ostream& stream, ApusCore::Color value);
}