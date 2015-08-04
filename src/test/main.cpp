#include <iostream>
#include <vector>
using namespace std;


// Tester object includes
#include "tester.h"
#include "libusb_usb_device_tester.h"
#include "ngp_cartridge_tester.h"


// Function forward declarations
bool run_tests(vector<tester*>& tests);
void delete_tests(vector<tester*>& tests);


int main()
{
  // Define inputs and outputs
  istream& in = cin;
  ostream& out = cout;
  ostream& err = cerr;
  
  // Allocate tester objects and add to vector
  vector<tester*> tests;
  tests.push_back(new libusb_usb_device_tester(in, out, err));
//  tests.push_back(new ngp_cartridge_tester(in, out, err));
  
  
  // Run the tests and print summary
  if (run_tests(tests))
  {
    out << "------------------------------" << endl;
    out << "All tests passed successfully." << endl;
  }
  else
  {
    out << "---------------------------------" << endl;
    out << "Test failures occured. See above." << endl;
  }
  
  // Free up memory
  delete_tests(tests);

  return 0;
}

// Function to run all tests
bool run_tests(vector<tester*>& tests)
{
  bool success = true;
  
  for (tester* test : tests)
  {
    if (!test->prepare())
    {
      success = false;
      continue;
    }
    
    test->pretests();
    
    if (!test->run_tests())
    {
      success = false;
    }
    
    test->posttests();
    
    test->results();
  }
  
  return success;
}

// Function to delete test objects
void delete_tests(vector<tester*>& tests)
{
  for (tester* test : tests)
  {
    delete test;
  }
}
