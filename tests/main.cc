/* ###
 * IP: GHIDRA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/// \file main.cc
/// \brief Test driver for the ghidra-native unit tests
///
/// This is a cut down version of src/decompiler/test.cc that runs the
/// tests registered with the TEST macro and nothing else, so the tests
/// build without the data-test machinery (file management, BFD, ...).

#include "error.hh"
#include "test.hh"

namespace ghidra {

int UnitTest::run(set<string> &testNames)

{
  int total = 0;
  int passed = 0;

  for(auto &t : UnitTest::tests()) {
    if (testNames.size() > 0 && testNames.find(t->name) == testNames.end())
      continue;
    cerr << "testing : " << t->name << " ..." << endl;
    ++total;
    try {
      t->func();
      ++passed;
      cerr << "  passed." << endl;
    } catch(LowlevelError &err) {
      cerr << "  fail: " << err.explain << endl;
    } catch(...) {
      cerr << "  fail" << endl;
    }
  }
  cerr << "==============================" << endl;
  cerr << passed << "/" << total << " tests passed." << endl;
  return total - passed;
}

} // End namespace ghidra

int main(int argc,char **argv)

{
  using namespace ghidra;

  set<string> testNames;
  for(int4 i=1;i<argc;++i)
    testNames.insert(argv[i]);
  return UnitTest::run(testNames);
}
