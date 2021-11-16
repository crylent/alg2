#include "pch.h"
#include "CppUnitTest.h"
#include "../../alg2/alg2/alg2.cpp"
#include <sstream>

#define LOG(msg) Logger::WriteMessage(msg)
#define SORT_AND_LOG(SORT_FUNCTION) log_array(arr, len, "Initial:\t\t"); SORT_FUNCTION(arr, len); log_array(arr, len, "Result:\t\t"); log_array(expected, len, "Expected:\t");

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace alg2unittest
{
	TEST_CLASS(alg2unittest)
	{
	private:
		// write array to logs
		void log_array(void* arr, int len, char* description = nullptr, bool characters = false) {
			if (description != nullptr) {
				LOG(description);
			}
			for (int i = 0; i < len; i++) {
				char* elem = new char[4]; // maximum 3-digit numbers allowed for unit test
				if (!characters) {
					_itoa_s(((int*)arr)[i], elem, 4, 10);
				}
				else {
					elem[0] = ((unsigned char*)arr)[i];
					elem[1] = '\0';
				}
				LOG(elem); LOG("; ");
			}
			LOG("\n");
		}

		// return true if arrays are equal, else false
		template<typename Elem>
		bool compare_arrays(Elem* a, Elem* b, int len) {
			for (int i = 0; i < len; i++) {
				if (a[i] != b[i]) { // i-elements are equal?
					return false;
				}
			}
			return true;
		}

		const int len = 11;
		int* arr = new int[len] { 12, 12, 1, 12, 15, 22, 5, 19, 23, 3, 3 };
		int* expected = new int[len] { 1, 3, 3, 5, 12, 12, 12, 15, 19, 22, 23 };

	public:
		
		TEST_METHOD(TestBinarySearch)
		{
			const int len = 9;
			int* arr = new int[len]{ 1, 2, 6, 6, 6, 9, 12, 13, 23 };
			log_array(arr, len, "Array: ");
			stringstream log_str;

			int pos = BinarySearch(arr, len, 1);
			log_str << "Searching number 1\t\tExpected: 0\t\tResult: " << pos << '\n';
			Assert::AreEqual(0, pos);

			pos = BinarySearch(arr, len, 2);
			log_str << "Searching number 2\t\tExpected: 1\t\tResult: " << pos << '\n';
			Assert::AreEqual(1, pos);

			pos = BinarySearch(arr, len, 6);
			log_str << "Searching number 6\t\tExpected: 2-4\t\tResult: " << pos << '\n';
			Assert::IsTrue(pos >= 2 && pos <= 4);

			pos = BinarySearch(arr, len, 9);
			log_str << "Searching number 9\t\tExpected: 5\t\tResult: " << pos << '\n';
			Assert::AreEqual(5, pos);

			pos = BinarySearch(arr, len, 12);
			log_str << "Searching number 12\t\tExpected: 6\t\tResult: " << pos << '\n';
			Assert::AreEqual(6, pos);

			pos = BinarySearch(arr, len, 13);
			log_str << "Searching number 13\t\tExpected: 7\t\tResult: " << pos << '\n';
			Assert::AreEqual(7, pos);

			pos = BinarySearch(arr, len, 23);
			log_str << "Searching number 23\t\tExpected: 8\t\tResult: " << pos << '\n';
			Assert::AreEqual(8, pos);

			LOG(log_str.str().c_str());

			// Exception
			try {
				BinarySearch(arr, len, 3);
			}
			catch (exception err) {
				Assert::AreEqual("No such element in array", err.what());
			}
		}

		TEST_METHOD(TestQuickSort)
		{
			SORT_AND_LOG(QuickSort);
			Assert::IsTrue(compare_arrays(arr, expected, len));
		}

		TEST_METHOD(TestBubbleSort)
		{
			SORT_AND_LOG(BubbleSort);
			Assert::IsTrue(compare_arrays(arr, expected, len));
		}

		TEST_METHOD(TestBogoSort)
		{
			SORT_AND_LOG(BogoSort);
			Assert::IsTrue(compare_arrays(arr, expected, len));
		}

		TEST_METHOD(TestCountingSort)
		{
			int len = 20;
			unsigned char* arr = new unsigned char[len] { 'M', 'A', 'X', 'I', 'M', 'B', 'M', 'A', 'R', 'Y', 'M', 'L', 'c', 'r', 'y', 'l', 'e', 'n', 'c', 'e' };
			unsigned char* expected = new unsigned char[len]{ 'A', 'A', 'B', 'I', 'L', 'M', 'M', 'M', 'M', 'R', 'X', 'Y', 'c', 'c', 'e', 'e', 'l', 'n', 'r', 'y' };
			log_array(arr, len, "Initial:\t\t", true);
			CountingSort(arr, len);
			log_array(arr, len, "Result:\t\t", true);
			log_array(expected, len, "Expected:\t", true);
			Assert::IsTrue(compare_arrays(arr, expected, len));
		}
	};
}
