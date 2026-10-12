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
/// \file paramactive.cc
/// \brief Unit tests for ParamActive::whichTrial
///
/// These tests cover the regression in rizinorg/rz-ghidra#385, where a
/// function with a one-byte parameter (e.g. a \e char stack argument) made
/// whichTrial() return -1 as soon as the first registered trial did not
/// overlap, instead of scanning the remaining trials.  Callers index the
/// trial vector with the return value, so the premature -1 aborted under
/// _GLIBCXX_ASSERTIONS and corrupted state otherwise.

#include "fspec.hh"
#include "test.hh"

namespace ghidra {

namespace {

/// \brief A stand-alone address space for constructing Address objects
AddrSpace *getTestSpace(void)
{
  static AddrSpace space((AddrSpaceManager *)0,(const Translate *)0,IPTR_PROCESSOR,
			 "testspace",false,8,1,0,0,0,0);
  return &space;
}

} // End anonymous namespace

/// A one-byte query must examine every trial, not just the first one.
/// Before the fix, whichTrial() returned -1 on the first mismatch, so a
/// one-byte trial registered after other trials was never found.
TEST(which_trial_scans_past_nonmatching_trials)
{
  AddrSpace *spc = getTestSpace();
  ParamActive active(false);
  active.registerTrial(Address(spc,0x1000),8);	// first trial does not overlap the query
  active.registerTrial(Address(spc,0x1008),4);
  active.registerTrial(Address(spc,0x2000),1);	// one-byte trial at the end

  ASSERT_EQUALS(active.whichTrial(Address(spc,0x2000),1),2);
}

/// A zero-length query must not underflow the address arithmetic and must
/// still scan every trial.
TEST(which_trial_zero_length_query)
{
  AddrSpace *spc = getTestSpace();
  ParamActive active(false);
  active.registerTrial(Address(spc,0x1000),8);
  active.registerTrial(Address(spc,0x2000),1);

  ASSERT_EQUALS(active.whichTrial(Address(spc,0x2000),0),1);
}

/// If several trials overlap the query, the first one in vector order wins,
/// matching the documented behavior of whichTrial().
TEST(which_trial_returns_first_overlapping_trial)
{
  AddrSpace *spc = getTestSpace();
  ParamActive active(false);
  active.registerTrial(Address(spc,0x2000),4);
  active.registerTrial(Address(spc,0x2002),4);	// also overlaps

  ASSERT_EQUALS(active.whichTrial(Address(spc,0x2001),1),0);
}

/// A multi-byte query that only reaches a trial with its last byte must
/// still find that trial.
TEST(which_trial_multibyte_query_checks_end_address)
{
  AddrSpace *spc = getTestSpace();
  ParamActive active(false);
  active.registerTrial(Address(spc,0x2000),4);

  ASSERT_EQUALS(active.whichTrial(Address(spc,0x1ffd),4),0);
  ASSERT_EQUALS(active.whichTrial(Address(spc,0x1ffc),4),-1);
}

/// A query that matches no trial still returns -1 after the loop.
TEST(which_trial_no_matching_trial)
{
  AddrSpace *spc = getTestSpace();
  ParamActive active(false);
  active.registerTrial(Address(spc,0x1000),8);
  active.registerTrial(Address(spc,0x2000),1);

  ASSERT_EQUALS(active.whichTrial(Address(spc,0x3000),1),-1);
  ASSERT_EQUALS(active.whichTrial(Address(spc,0x3000),8),-1);
}

} // End namespace ghidra
