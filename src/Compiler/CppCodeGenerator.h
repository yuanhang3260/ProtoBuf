#ifndef CPP_CODE_GENERATOR_
#define CPP_CODE_GENERATOR_

#include "ProtoParser.h"
#include "../IO/TextPrinter.h"

namespace proto {
namespace ProtoParser {

class CppCodeGenerator : public ProtoParser {
 public:
  CppCodeGenerator(std::string file) : ProtoParser(CPP, file) {}
  ~CppCodeGenerator() {}
  CppCodeGenerator(const CppCodeGenerator&) = delete;
  CppCodeGenerator& operator=(const CppCodeGenerator&) = delete;

  void GenerateCode() override;
 
 private:
  // ------------------------ Generate header file. ------------------------- //
  void GenerateHeader();

  void GenerateProtoPathName();

  // Declare global enum.
  void DeclareGlobalEnum(EnumType* enum_p);

  // Declare a message class.
  void DeclareMessageClass(Message* message);

  // Declare an rpc service class.
  void DeclareRpcMethodClass(ServiceType* service);

  // Declare nested enums.
  void DeclareNestedEnums(Message* message);

  // Declare constructors, assigners, destructor and swapper.
  void DeclarePrimitiveMethods(Message* message);

  // Declare private fields.
  void DeclarePrivateFields(Message* message);

  // Declare field accessors.
  void DeclareAccessors(Message* message, MessageField* field);
  void DeclareSingularNumericTypeAccessors(Message* message,
                                           MessageField* field);
  void DeclareSingularStringTypeAccessors(Message* message,
                                          MessageField* field);
  void DeclareSingularMessageTypeAccessors(Message* message,
                                           MessageField* field);
  void DeclareRepeatedNumericTypeAccessors(Message* message,
                                           MessageField* field);
  void DeclareRepeatedNonNumericTypeAccessors(Message* message,
                                              MessageField* field);
  
  // ------------------------ Generate cpp file. ---------------------------- //
  void GenerateCC();

  // Define reflection.
  void DefineStaticMetadata();
  void DefineStaticInitDefaultInstances();
  void DefineStaticInit();

  // Define all methods of a message.
  void DefineClassMethods(Message* message);

  // Define default constructor
  void DefineConstructor(Message* message);

  // Define copiers.
  void PrintCopyClassCode(Message* message);
  void DefineCopyConstructor(Message* message);
  void DefineMoveConstructor(Message* message);

  // Define movers.
  void PrintMoveClassCode(Message* message);
  void DefineCopyAssigner(Message* message);
  void DefineMoveAssigner(Message* message);

  // Define New()
  void DefineNew(Message* message);

  // Define CopyFrom()
  void DefineCopyFrom(Message* message);

  // Define MoveFrom()
  void DefineMoveFrom(Message* message);

  // Define Serialize()
  void DefineSerialize(Message* message);

  // Define DeSerialize()
  void DefineDeSerialize(Message* message);

  // Define InitAsDefaultInstance()
  void DefineInitAsDefaultInstance(Message* message);

  // Define default_instance()
  void DefineGetDefaultInstance(Message* message);

  // Define Swapper.
  void DefineSwapper(Message* message);

  // Define destructor.
  void DefineDestructor(Message* message);

  // Define field accessors.
  void DefineAccessors(Message* message, MessageField* field);
  void DefineSingularNumericTypeAccessors(Message* message,
                                          MessageField* field);
  void DefineSingularStringTypeAccessors(Message* message,
                                         MessageField* field);
  void DefineSingularMessageTypeAccessors(Message* message,
                                          MessageField* field);
  void DefineRepeatedNumericTypeAccessors(Message* message,
                                          MessageField* field);
  void DefineRepeatedNonNumericTypeAccessors(Message* message,
                                             MessageField* field);

  // Define service class.
  void DefineServiceClass(ServiceType* service);
  void DefineServiceClassMethods(ServiceType* service);
  void DefineStubClass(ServiceType* service);

  // -------------------------- Helpers methods ----------------------------- //
  std::map<std::string, std::string>
  GetFieldMatchMap(Message* message, MessageField* field);

  std::map<std::string, std::string>
  GetRpcMatchMap(ServiceType* service, RpcMethod* rpc);
  
  void CheckoutNameSpace(std::vector<std::string>& context_stk,
                         const std::vector<std::string>& target_stk);
  
  std::string GetNameSpacePrefix(const std::vector<std::string>& context_stk,
                                 const std::vector<std::string>& target_stk);

  // Text printer.
  IO::TextPrinter printer;

  std::string proto_path_name_;
};

}  // Compiler
}  // PandaProto

#endif  /* CPP_CODE_GENERATOR_ */