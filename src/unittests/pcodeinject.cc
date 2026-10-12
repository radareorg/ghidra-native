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
/// \file pcodeinject.cc
/// \brief Unit tests for dynamic p-code injection handling
///
/// Ghidra services <pcode inject="..." dynamic="true"/> declarations by
/// sending a <injectdebug> payload to the decompiler (InjectPayloadDynamic).
/// A native-only consumer, such as the processors shipped by this
/// repository, has no front-end to do this, so an unserviced dynamic
/// inject aborts decompilation with "Missing dynamic inject".  This is why
/// Java-dependent injects are removed from the compiler specification
/// rather than being carried along.

#include "inject_sleigh.hh"
#include "pcodeinject.hh"
#include "translate.hh"
#include "test.hh"

namespace ghidra {

namespace {

class NoopPcodeEmit : public PcodeEmit {
public:
  virtual void dump(const Address &addr,OpCode opc,VarnodeData *outvar,VarnodeData *vars,int4 isize) {}
};

class NoopInjectContext : public InjectContext {
public:
  virtual void encode(Encoder &encoder) const {}
};

class NoopInjectPayload : public InjectPayload {
public:
  NoopInjectPayload(void) : InjectPayload("regression",CALLMECHANISM_TYPE) {}
  virtual void inject(InjectContext &context,PcodeEmit &emit) const {}
  virtual void decode(Decoder &decoder) {}
  virtual void printTemplate(std::ostream &s) const {}
  virtual std::string getSource(void) const { return "regression"; }
};

} // End anonymous namespace

/// A dynamic injection with no front-end supplied payload is a fatal error,
/// not a silent no-op.  Decompilation of any function that triggers the
/// declaration (uponentry for every function, for instance) fails.
TEST(dynamic_inject_without_frontend_throws)
{
  NoopInjectPayload base;
  InjectPayloadDynamic payload((Architecture *)0,&base);
  NoopInjectContext context;
  NoopPcodeEmit emitter;

  bool threw = false;
  try {
    payload.inject(context,emitter);
  } catch(LowlevelError &err) {
    threw = true;
  }
  ASSERT(threw);
}

} // End namespace ghidra
