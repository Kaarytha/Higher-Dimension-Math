/*Inverse Kinematics testing project
Using FABRIK with three joints, 180 degrees of rotation, with 1 horizontal and two vertical in that order.
	
	TODO:
		Cleanup Vector operator overloading
		Apply angle system to 3 dimensions and seek
		Apply to servos
			Vector3
		Update id system
		Cleanup comments and old code (Specifically code from before implementing templates)

	DONE:
		Apply IK to three dimensions
		Degree Limitations

	NOTE:
		For rectifyAngle, it should be a member function that is passed a reference to parent
		This should then be called at the end of seek
		This will require a robust id system
			Will probably use atomics to be thread safe for multithreading in the future
*/

#include "Segment.h"

void seg2testing() {
	std::vector<Segment2> initial;
	createBranch(initial, 3);

	for (Segment2 i : initial) {
		i.debugPrint();
	}
	std::cout << "\n";
	// Prints initial positions

	//for (int i = 0; i < initial.size(); i++) {
	//	initial[i].debugPrint();
	//}
	//std::cout << std::endl;

	int found = seek(initial, Vector2(1.5f, 0.89f), 2, .001);

	std::cout << found << std::endl;
}

void seg3testing() {
	//Segment3 test = Segment3();
	//test.debugPrint();

	//Segment3 copyTest = Segment3(test.mendB);
	//copyTest.debugPrint();

	std::vector<Segment3> seg3Test;
	createBranch(seg3Test, 3);

	for (int i = 0; i < seg3Test.size(); i++) {
		seg3Test[i].debugPrint();
	}

	int test = seek(seg3Test, Vector3(1.5f, 0.89f, 0.0f));

	std::cout << test << "\n";
}

// Doesn't work too well as it is not called in seek
void angleTesting() {
	// Application of rectifyAngle function

	Segment2 test1 = Segment2::Segment2();
	Segment2 test2 = Segment2::Segment2(test1.mendB, M_PI / 2, -M_PI / 2);
	std::vector<Segment2> test;
	test.emplace_back(test1);
	test.emplace_back(test2);
	test[1].mangle = test[1].findAngle(test[0]);
	test[1].rectifyAngle(test[0]);
	test[0].debugPrint();
	test[1].debugPrint();

	std::cout << seek(test, Vector2(-.3f, 0.), 20, .01) << std::endl;
}

int main() {
	 seg2testing();
	
	// seg3testing();

	// angleTesting();
}