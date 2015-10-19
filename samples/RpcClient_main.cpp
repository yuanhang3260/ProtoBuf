#include <iostream>
#include <memory>

#include "Compiler/Message.h"
#include "Compiler/ProtoParser.h"
#include "Proto/MessageReflection.h"
#include "Proto/MessageFactory.h"
#include "Proto/SerializedMessage.h"
#include "Proto/SerializedPrimitive.h"
#include "RPC/Rpc.h"
#include "RPC/RpcClientChannel.h"

#include "simple_pb.h"

int main(int argc, char** argv) {
  RPC::RpcClientChannel channel("localhost", 9090);
  (void)channel;
}
