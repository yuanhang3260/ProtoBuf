#ifndef RPC_BASE
#define RPC_BASE

#include <memory>
#include <mutex>
#include <condition_variable>

#include "Base/MacroUtils.h"
#include "Proto/Message.h"
#include "Utility/CallBack.h"
#include "RpcPacket_pb.h"

namespace RPC {

class Rpc {
 public:
  enum ClientStatus {
    INIT = 0,
    SUCCESS = 1,
    INTERNAL_CHANNEL_ERROR = 2,
    CHECK_NUM_ERROR = 3,
    RESPONSE_HEADER_SIZE_ERROR = 4,
    RESPONSE_SIZE_ERROR = 5,
    BAD_RESPONSE_HEADER = 6,
    BAD_RESPONSE = 7,
  };

  Rpc() = default;
  virtual ~Rpc() {}

  void SetRpcReturnCode(RpcResponseHeader::RpcReturnCode code) {
    rpc_return_code_ = code;
  }
  RpcResponseHeader::RpcReturnCode RpcReturnCode() const {
    return rpc_return_code_;
  }

  std::string RpcReturnMessage() const;
  void SetRpcReturnMesssage(std::string msg) { return_msg_ = msg; }

  proto::Message* internal_request() { return request_.get(); }
  void set_internal_request(proto::Message* req) { request_.reset(req); }

  proto::Message* internal_response() { return response_.get(); }
  void set_internal_response(proto::Message* res) { response_.reset(res); }

  proto::Message* internal_stream() { return stream_.get(); }
  void set_internal_stream(proto::Message* stream) { stream_.reset(stream); }

  Base::Closure* cb_final() { return cb_final_.get(); }
  void set_cb_final(Base::Closure* cb_final) { cb_final_.reset(cb_final); }

  ClientStatus client_status() const { return client_status_; }
  void set_client_status(ClientStatus status) { client_status_ = status; }
  bool isOk() const { return client_status_ == SUCCESS; }

  int check_num() const { return check_num_; }
  void set_check_num(int num) { check_num_ = num; }

  void SetRpcStart();
  void SetRpcFinished();

  void Wait();

  std::string RpcCallStatus();

 private:
  FORBID_COPY_AND_ASSIGN(Rpc);
  int check_num_;

  // --------------- server -------------------- //
  std::unique_ptr<proto::Message> request_;
  std::unique_ptr<proto::Message> response_;
  std::unique_ptr<proto::Message> stream_;
  std::unique_ptr<Base::Closure> cb_final_;

  RpcResponseHeader::RpcReturnCode rpc_return_code_ = RpcResponseHeader::NONE;
  std::string return_msg_;

  // --------------- Client -------------------- //
  ClientStatus client_status_ = INIT;

  bool rpc_finished_ = false;
  std::mutex rpc_wait_mutex_;
  std::condition_variable rpc_wait_cond_;
};

}  // namespace RPC


#endif  /* RPC_BASE */
