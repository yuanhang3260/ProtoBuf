#ifndef SIMPLE_PB_H_
#define SIMPLE_PB_H_

#include <string>
#include <vector>

#include "Base/BaseTypes.h"
#include "Proto/Message.h"
#include "Proto/Descriptor.h"
#include "Proto/RepeatedFields.h"
#include "Proto/SerializedMessage.h"
#include "RPC/Rpc.h"
#include "RPC/RpcService.h"
#include "RPC/RpcServer.h"
#include "RPC/RpcClientChannel.h"
#include "RPC/RpcCommon.h"
#include "Utility/CallBack.h"

void static_init_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
void static_init_default_instances_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();

namespace HaiZhong {

class Pet: public ::proto::Message {
 public:
  enum PetType {
    DOG,
    PANDA,
  };

  // constructors and destructor //
  Pet();
  ~Pet();
  Pet(const Pet& other);  // copy constructor
  Pet(Pet&& other);  // move constructor
  Pet& operator=(const Pet& other); // copy assignment
  Pet& operator=(Pet&& other);  // move assignment
  void Swap(Pet* other);  // Swap
  ::proto::Message* New() const override;  // New()
  void CopyFrom(const Pet& other);  // CopyFrom()
  void MoveFrom(Pet&& other);  // MoveFrom()
  bool Equals(const Pet& other) const;  // Compare
  // Serialize() and DeSerialize().
  ::proto::SerializedMessage* Serialize() const override;
  void DeSerialize(const char* buf, unsigned int size) override;
  static const Pet& default_instance();
  const ::proto::MessageDescriptor* GetDescriptor() const override;
  const ::proto::MessageReflection* GetReflection() const override;
  void Print(int indent_num=0) const override;

  // --- Field accessors --- //

  // "name" = 1
  bool has_name() const;
  const std::string& name() const;
  void set_name(const std::string& name);
  void set_name(const char* name);
  void set_name(const char* name, int size);
  std::string mutable_name();
  void clear_name();

  // "type" = 2
  bool has_type() const;
  Pet::PetType type() const;
  void set_type(Pet::PetType type);
  void clear_type();

  // "friend_to" = 3
  int friend_to_size() const;
  Pet::PetType friend_to(int index) const;
  void set_friend_to(int index, Pet::PetType value);
  void add_friend_to(Pet::PetType value);
  void clear_friend_to();
  const ::proto::RepeatedField<Pet::PetType>& friend_to() const;
  ::proto::RepeatedField<Pet::PetType>& mutable_friend_to();

 private:
  // has bits
  char has_bits_[1];
  // message fields
  std::string name_ = "";
  Pet::PetType type_ = Pet::DOG;
  ::proto::RepeatedField<Pet::PetType> friend_to_;

  // InitAsDefaultInstance()
  void InitAsDefaultInstance() override;
  // default instance
  static Pet* default_instance_;

  friend void ::static_init_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
  friend void ::static_init_default_instances_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
};

class Student: public ::proto::Message {
 public:
  enum Sex {
    MALE,
    FEMALE,
  };

  // constructors and destructor //
  Student();
  ~Student();
  Student(const Student& other);  // copy constructor
  Student(Student&& other);  // move constructor
  Student& operator=(const Student& other); // copy assignment
  Student& operator=(Student&& other);  // move assignment
  void Swap(Student* other);  // Swap
  ::proto::Message* New() const override;  // New()
  void CopyFrom(const Student& other);  // CopyFrom()
  void MoveFrom(Student&& other);  // MoveFrom()
  bool Equals(const Student& other) const;  // Compare
  // Serialize() and DeSerialize().
  ::proto::SerializedMessage* Serialize() const override;
  void DeSerialize(const char* buf, unsigned int size) override;
  static const Student& default_instance();
  const ::proto::MessageDescriptor* GetDescriptor() const override;
  const ::proto::MessageReflection* GetReflection() const override;
  void Print(int indent_num=0) const override;

  // --- Field accessors --- //

  // "name" = 1
  bool has_name() const;
  const std::string& name() const;
  void set_name(const std::string& name);
  void set_name(const char* name);
  void set_name(const char* name, int size);
  std::string mutable_name();
  void clear_name();

  // "age" = 2
  bool has_age() const;
  uint32 age() const;
  void set_age(uint32 age);
  void clear_age();

  // "xyz" = 3
  bool has_xyz() const;
  int32 xyz() const;
  void set_xyz(int32 xyz);
  void clear_xyz();

  // "def" = 4
  bool has_def() const;
  uint64 def() const;
  void set_def(uint64 def);
  void clear_def();

  // "ghi" = 5
  bool has_ghi() const;
  int64 ghi() const;
  void set_ghi(int64 ghi);
  void clear_ghi();

  // "graduated" = 6
  bool has_graduated() const;
  bool graduated() const;
  void set_graduated(bool graduated);
  void clear_graduated();

  // "weight" = 7
  bool has_weight() const;
  double weight() const;
  void set_weight(double weight);
  void clear_weight();

  // "pets" = 9
  int pets_size() const;
  const Pet& pets(int index) const;
  Pet* add_pets();
  Pet* mutable_pets(int index);
  void clear_pets();
  const ::proto::RepeatedPtrField<Pet>& pets() const;
  ::proto::RepeatedPtrField<Pet>& mutable_pets();

  // "scores" = 11
  int scores_size() const;
  int32 scores(int index) const;
  void set_scores(int index, int32 value);
  void add_scores(int32 value);
  void clear_scores();
  const ::proto::RepeatedField<int32>& scores() const;
  ::proto::RepeatedField<int32>& mutable_scores();

  // "first_pet" = 12
  bool has_first_pet() const;
  const Pet& first_pet() const;
  Pet* mutable_first_pet();
  void set_allocated_first_pet(Pet* first_pet);
  Pet* release_first_pet();
  void clear_first_pet();

  // "alias" = 15
  int alias_size() const;
  const std::string& alias(int index) const;
  void set_alias(int index, const std::string& value);
  void set_alias(int index, const char* value);
  void set_alias(int index, const char* value, int size);
  std::string* add_alias();
  void add_alias(const std::string& value);
  void add_alias(const char* value);
  void add_alias(const char* value, int size);
  std::string* mutable_alias(int index);
  void clear_alias();
  const ::proto::RepeatedPtrField<std::string>& alias() const;
  ::proto::RepeatedPtrField<std::string>& mutable_alias();

  // "partner" = 18
  bool has_partner() const;
  const Student& partner() const;
  Student* mutable_partner();
  void set_allocated_partner(Student* partner);
  Student* release_partner();
  void clear_partner();

  // "symbol" = 19
  bool has_symbol() const;
  char symbol() const;
  void set_symbol(char symbol);
  void clear_symbol();

  // "sex" = 25
  bool has_sex() const;
  Student::Sex sex() const;
  void set_sex(Student::Sex sex);
  void clear_sex();

 private:
  // has bits
  char has_bits_[4];
  // message fields
  std::string name_ = "";
  uint32 age_ = 0;
  int32 xyz_ = 0;
  uint64 def_ = 0;
  int64 ghi_ = 0;
  bool graduated_ = false;
  double weight_ = 0;
  ::proto::RepeatedPtrField<Pet> pets_;
  ::proto::RepeatedField<int32> scores_;
  Pet* first_pet_ = nullptr;
  ::proto::RepeatedPtrField<std::string> alias_;
  Student* partner_ = nullptr;
  char symbol_ = 0;
  Student::Sex sex_ = Student::MALE;

  // InitAsDefaultInstance()
  void InitAsDefaultInstance() override;
  // default instance
  static Student* default_instance_;

  friend void ::static_init_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
  friend void ::static_init_default_instances_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
};

class SchoolClass: public ::proto::Message {
 public:
  // constructors and destructor //
  SchoolClass();
  ~SchoolClass();
  SchoolClass(const SchoolClass& other);  // copy constructor
  SchoolClass(SchoolClass&& other);  // move constructor
  SchoolClass& operator=(const SchoolClass& other); // copy assignment
  SchoolClass& operator=(SchoolClass&& other);  // move assignment
  void Swap(SchoolClass* other);  // Swap
  ::proto::Message* New() const override;  // New()
  void CopyFrom(const SchoolClass& other);  // CopyFrom()
  void MoveFrom(SchoolClass&& other);  // MoveFrom()
  bool Equals(const SchoolClass& other) const;  // Compare
  // Serialize() and DeSerialize().
  ::proto::SerializedMessage* Serialize() const override;
  void DeSerialize(const char* buf, unsigned int size) override;
  static const SchoolClass& default_instance();
  const ::proto::MessageDescriptor* GetDescriptor() const override;
  const ::proto::MessageReflection* GetReflection() const override;
  void Print(int indent_num=0) const override;

  // --- Field accessors --- //

  // "number" = 1
  bool has_number() const;
  int32 number() const;
  void set_number(int32 number);
  void clear_number();

  // "alias" = 2
  bool has_alias() const;
  const std::string& alias() const;
  void set_alias(const std::string& alias);
  void set_alias(const char* alias);
  void set_alias(const char* alias, int size);
  std::string mutable_alias();
  void clear_alias();

  // "captain" = 3
  bool has_captain() const;
  const Student& captain() const;
  Student* mutable_captain();
  void set_allocated_captain(Student* captain);
  Student* release_captain();
  void clear_captain();

  // "students" = 5
  int students_size() const;
  const Student& students(int index) const;
  Student* add_students();
  Student* mutable_students(int index);
  void clear_students();
  const ::proto::RepeatedPtrField<Student>& students() const;
  ::proto::RepeatedPtrField<Student>& mutable_students();

 private:
  // has bits
  char has_bits_[1];
  // message fields
  int32 number_ = 0;
  std::string alias_ = "";
  Student* captain_ = nullptr;
  ::proto::RepeatedPtrField<Student> students_;

  // InitAsDefaultInstance()
  void InitAsDefaultInstance() override;
  // default instance
  static SchoolClass* default_instance_;

  friend void ::static_init_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
  friend void ::static_init_default_instances_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
};

class StudentRequest: public ::proto::Message {
 public:
  enum OpType {
    ADD,
    REMOVE,
    UPDATE,
  };

  // constructors and destructor //
  StudentRequest();
  ~StudentRequest();
  StudentRequest(const StudentRequest& other);  // copy constructor
  StudentRequest(StudentRequest&& other);  // move constructor
  StudentRequest& operator=(const StudentRequest& other); // copy assignment
  StudentRequest& operator=(StudentRequest&& other);  // move assignment
  void Swap(StudentRequest* other);  // Swap
  ::proto::Message* New() const override;  // New()
  void CopyFrom(const StudentRequest& other);  // CopyFrom()
  void MoveFrom(StudentRequest&& other);  // MoveFrom()
  bool Equals(const StudentRequest& other) const;  // Compare
  // Serialize() and DeSerialize().
  ::proto::SerializedMessage* Serialize() const override;
  void DeSerialize(const char* buf, unsigned int size) override;
  static const StudentRequest& default_instance();
  const ::proto::MessageDescriptor* GetDescriptor() const override;
  const ::proto::MessageReflection* GetReflection() const override;
  void Print(int indent_num=0) const override;

  // --- Field accessors --- //

  // "op_type" = 1
  bool has_op_type() const;
  StudentRequest::OpType op_type() const;
  void set_op_type(StudentRequest::OpType op_type);
  void clear_op_type();

  // "class_number" = 2
  bool has_class_number() const;
  int32 class_number() const;
  void set_class_number(int32 class_number);
  void clear_class_number();

  // "student_name" = 3
  bool has_student_name() const;
  const std::string& student_name() const;
  void set_student_name(const std::string& student_name);
  void set_student_name(const char* student_name);
  void set_student_name(const char* student_name, int size);
  std::string mutable_student_name();
  void clear_student_name();

  // "student" = 4
  bool has_student() const;
  const Student& student() const;
  Student* mutable_student();
  void set_allocated_student(Student* student);
  Student* release_student();
  void clear_student();

 private:
  // has bits
  char has_bits_[1];
  // message fields
  StudentRequest::OpType op_type_ = StudentRequest::ADD;
  int32 class_number_ = 0;
  std::string student_name_ = "";
  Student* student_ = nullptr;

  // InitAsDefaultInstance()
  void InitAsDefaultInstance() override;
  // default instance
  static StudentRequest* default_instance_;

  friend void ::static_init_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
  friend void ::static_init_default_instances_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
};

class StudentResponse: public ::proto::Message {
 public:
  // constructors and destructor //
  StudentResponse();
  ~StudentResponse();
  StudentResponse(const StudentResponse& other);  // copy constructor
  StudentResponse(StudentResponse&& other);  // move constructor
  StudentResponse& operator=(const StudentResponse& other); // copy assignment
  StudentResponse& operator=(StudentResponse&& other);  // move assignment
  void Swap(StudentResponse* other);  // Swap
  ::proto::Message* New() const override;  // New()
  void CopyFrom(const StudentResponse& other);  // CopyFrom()
  void MoveFrom(StudentResponse&& other);  // MoveFrom()
  bool Equals(const StudentResponse& other) const;  // Compare
  // Serialize() and DeSerialize().
  ::proto::SerializedMessage* Serialize() const override;
  void DeSerialize(const char* buf, unsigned int size) override;
  static const StudentResponse& default_instance();
  const ::proto::MessageDescriptor* GetDescriptor() const override;
  const ::proto::MessageReflection* GetReflection() const override;
  void Print(int indent_num=0) const override;

  // --- Field accessors --- //

  // "return_code" = 1
  bool has_return_code() const;
  int32 return_code() const;
  void set_return_code(int32 return_code);
  void clear_return_code();

  // "error_message" = 2
  bool has_error_message() const;
  const std::string& error_message() const;
  void set_error_message(const std::string& error_message);
  void set_error_message(const char* error_message);
  void set_error_message(const char* error_message, int size);
  std::string mutable_error_message();
  void clear_error_message();

 private:
  // has bits
  char has_bits_[1];
  // message fields
  int32 return_code_ = -1;
  std::string error_message_ = "";

  // InitAsDefaultInstance()
  void InitAsDefaultInstance() override;
  // default instance
  static StudentResponse* default_instance_;

  friend void ::static_init_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
  friend void ::static_init_default_instances_usr_local_google_home_hangyuan_Desktop_test_ProtoBuf_examples_simple();
};

class StudentManagement: public ::RPC::RpcService {
 public:
  virtual ~StudentManagement() {}
  virtual const ::RPC::RpcDescriptor* descriptor();

  static StudentManagement* NewStub(::RPC::RpcClientChannel* channel);
  static StudentManagement* NewStub(::RPC::RpcClientChannel* channel, const ::RPC::RpcStubOptions options);

  virtual void RegisterToServer(::RPC::RpcServer* server);
  virtual void DeRegisterFromServer(::RPC::RpcServer* server);

  virtual void InternalRegisterHandlers(::RPC::RpcServer* server);
  virtual void InternalDeRegisterHandlers(::RPC::RpcServer* server);

  // AddStudent() to be Implemented by user.
  virtual void AddStudent(
      ::RPC::Rpc* rpc,
      const ::HaiZhong::StudentRequest* arg,
      ::HaiZhong::StudentResponse* result,
      ::Base::Closure* cb);

  // DeleteStudent() to be Implemented by user.
  virtual void DeleteStudent(
      ::RPC::Rpc* rpc,
      const ::HaiZhong::StudentRequest* arg,
      ::HaiZhong::StudentResponse* result,
      ::Base::Closure* cb);

 protected:
  StudentManagement();
  class Stub;
  static const ::RPC::RpcDescriptor* descriptor_;

 private:
  void internal_AddStudent(::RPC::Rpc* rpc);
  void internal_DeleteStudent(::RPC::Rpc* rpc);
};

}  // namespace HaiZhong


#endif  /* SIMPLE_PB_H_ */
