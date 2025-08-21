#include "gmock/gmock.h"

#if defined(_DEBUG)
int main() {
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#endif