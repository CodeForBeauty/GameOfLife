#include <iostream>
#include "Types.h"

ApusCore::Color ApusCore::operator* (ApusCore::Color a, ApusCore::Color b) {
	return { a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a };
}
ApusCore::Color ApusCore::operator/ (ApusCore::Color a, ApusCore::Color b) {
	return { a.r / b.r, a.g / b.g, a.b / b.b, a.a / b.a };
}
ApusCore::Color ApusCore::operator+ (ApusCore::Color a, ApusCore::Color b) {
	return { a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a };
}
ApusCore::Color ApusCore::operator- (ApusCore::Color a, ApusCore::Color b) {
	return { a.r - b.r, a.g - b.g, a.b - b.b, a.a - b.a };
}

ApusCore::Color ApusCore::operator* (ApusCore::Color a, float b) {
	return { a.r * b, a.g * b, a.b * b, a.a * b };
}
ApusCore::Color ApusCore::operator/ (ApusCore::Color a, float b) {
	return { a.r / b, a.g / b, a.b / b, a.a / b };
}
ApusCore::Color ApusCore::operator+ (ApusCore::Color a, float b) {
	return { a.r + b, a.g + b, a.b + b, a.a + b };
}
ApusCore::Color ApusCore::operator- (ApusCore::Color a, float b) {
	return { a.r - b, a.g - b, a.b - b, a.a - b };
}

std::ostream& ApusCore::operator<< (std::ostream& stream, ApusCore::Color value) {
	stream << "R - " << value.r << ", G - " << value.g << ", B - " << value.b << ", A - " << value.a << std::endl;
	return stream;
}
