#include "Tensor.h"
#include "StridedTensor.h"
#include <utility>
#include <iostream>

//#include "Segment.h"
//
//void seg2testing() {
//	std::vector<Segment2> initial;
//	createBranch(initial, 3);
//
//	for (Segment2 i : initial) {
//		i.debugPrint();
//	}
//	std::cout << "\n";
//	// Prints initial positions
//
//	//for (int i = 0; i < initial.size(); i++) {
//	//	initial[i].debugPrint();
//	//}
//	//std::cout << std::endl;
//
//	int found = seek(initial, Vector2(1.5f, 0.89f), 2, .001);
//
//	std::cout << found << std::endl;
//}
//
//void seg3testing() {
//	//Segment3 test = Segment3();
//	//test.debugPrint();
//
//	//Segment3 copyTest = Segment3(test.mendB);
//	//copyTest.debugPrint();
//
//	std::vector<Segment3> seg3Test;
//	createBranch(seg3Test, 3);
//
//	for (int i = 0; i < seg3Test.size(); i++) {
//		seg3Test[i].debugPrint();
//	}
//
//	int test = seek(seg3Test, Vector3(1.5f, 0.89f, 0.0f));
//
//	std::cout << test << "\n";
//}
//
//// Doesn't work too well as it is not called in seek
//void angleTesting() {
//	// Application of rectifyAngle function
//
//	Segment2 test1 = Segment2::Segment2();
//	Segment2 test2 = Segment2::Segment2(test1.mendB, M_PI / 2, -M_PI / 2);
//	std::vector<Segment2> test;
//	test.emplace_back(test1);
//	test.emplace_back(test2);
//	test[1].mangle = test[1].findAngle(test[0]);
//	test[1].rectifyAngle(test[0]);
//	test[0].debugPrint();
//	test[1].debugPrint();
//
//	std::cout << seek(test, Vector2(-.3f, 0.), 20, .01) << std::endl;
//}

void printSpace(int n = 1) {
	for (int i = 0; i < n; ++i) {
		std::cout << "\n" << std::endl;
	}
}

void TensorTesting() {
	tap::ArrayShape test{ 2,3 };
	tap::Tensor<int> temp = tap::Tensor(test, { 1, 2, 3, 4, 5, 6 });
	temp.describe();
	tap::ArrayShape target{ 2,2 };

	std::cout << temp[target] << std::endl;

	tap::ArrayShape three{ 3,2,3 };
	tap::Tensor<int> large = tap::Tensor(three, { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });
	large.describe();
}
void TensorExprTesting() {
	tap::ArrayShape addtestshape{ 2,3 };
	tap::Tensor<int> addtest = tap::Tensor(std::move(addtestshape), { 1, 1, 1, 1, 1, 1 });

	tap::ArrayShape addtestshape2{ 2,3 };
	tap::Tensor<int> addtest2 = tap::Tensor(std::move(addtestshape), { 1, 1, 1, 1, 1, 1 });

	tap::ArrayShape addtestshape3{ 2,3 };
	tap::Tensor<int> addtest3 = tap::Tensor(addtestshape3, { 1, 1, 1, 1, 1, 1 });

	tap::ArrayShape addtestshape4{ 2,3 };
	tap::Tensor<int> addtest4 = tap::Tensor(addtestshape4, { 1, 1, 1, 1, 1, 1 });

	printSpace();
	tap::Tensor<int> testing{};
	testing = addtest + addtest2 + addtest3 + addtest4;
	testing.describe();

	printSpace();

	testing = addtest - addtest2 - addtest3 - addtest4;
	testing.describe();

	printSpace();

	tap::Tensor<int> moveConst{ std::move(testing) };

	moveConst.describe();

	printSpace();

	tap::Tensor<int> imp{ addtest + addtest2 };
	imp.describe();

	tap::StridedTensor<int> testToStrided = imp.toStrided();
	testToStrided.describe();

	std::cout << std::is_trivially_move_constructible_v<tap::Tensor<int>>;

	for (auto it : addtestshape) {
		std::cout << it;
	}

	for (auto it : addtestshape2) {
		std::cout << it;
	}

	for (auto it : addtestshape3) {
		std::cout << it;
	}
}

void StridedTesting() {
	tap::ArrayShape test{ 2,3 };
	tap::StridedTensor<int> temp = tap::StridedTensor(test, { 1, 2, 3, 4, 5, 6 });
	temp.describe();
	tap::ArrayShape target{ 2,2 };

	std::cout << temp[target] << std::endl;

	tap::ArrayShape three{ 3,2,3 };
	tap::StridedTensor<int> large = tap::StridedTensor(three, { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });
	large.describe();
}

void StridedExprTesting() {
	tap::ArrayShape addtestshape{ 2,3 };
	tap::StridedTensor<int> addtest = tap::StridedTensor(std::move(addtestshape), { 1, 2, 1, 3, 1, 1 });


	tap::ArrayShape addtestshape2{ 2,3 };
	tap::StridedTensor<int> addtest2 = tap::StridedTensor(std::move(addtestshape2), { 1, 2, 1, 3, 1, 1 });

	tap::ArrayShape addtestshape3{ 2,3 };
	tap::Tensor<int> addtest3 = tap::Tensor(addtestshape3, { 1, 1, 1, 1, 1, 1 });

	tap::ArrayShape addtestshape4{ 2,3 };
	tap::Tensor<int> addtest4 = tap::Tensor(addtestshape4, { 1, 1, 1, 1, 1, 1 });

	printSpace();
	tap::StridedTensor<int> testing{};
	testing = addtest + addtest2 + addtest3 + addtest4;
	testing.describe();

	printSpace();

	testing = addtest - addtest2 - addtest3 - addtest4;
	testing.describe();

	printSpace();

	tap::StridedTensor<int> moveConst{ std::move(testing) };

	moveConst.describe();

	printSpace();

	tap::StridedTensor<int> imp{ addtest + addtest2 };
	imp.describe();

	std::cout << std::is_trivially_move_constructible_v<tap::StridedTensor<int>>;

	for (auto it : addtestshape) {
		std::cout << it;
	}

	for (auto it : addtestshape2) {
		std::cout << it;
	}

	for (auto it : addtestshape3) {
		std::cout << it;
	}

	printSpace();

	tap::StridedTensor<int> fromTensor = addtest3 + addtest4;
	fromTensor.describe();
//	(addtest - addtest2).describe();
}

int main() {
	std::cout << "begin" << std::endl;
	std::cout << "Tensor:" << std::endl;
	TensorTesting();
	printSpace();
	TensorExprTesting();
	printSpace(2);

	std::cout << "Strided:" << std::endl;

	StridedTesting();
	printSpace();
	StridedExprTesting();
}