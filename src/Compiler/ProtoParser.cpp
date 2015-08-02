#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "ProtoParser.h"
#include "../IO/FileDescriptor.h"
#include "../Utility/BufferedDataReader.h"
#include "../Utility/BufferedDataWriter.h"
#include "../Utility/Strings.h"
#include "../Utility/Utils.h"

namespace PandaProto {
namespace Compiler {

ProtoParser::ProtoParser(LANGUAGE lang, std::string file) :
    lang_(lang),
    proto_file_(file) {
  if (!StringUtils::EndWith(proto_file_, ".proto")) {
    init_success_ = false;
    fprintf(stderr, "ERROR: proto file name must have \".proto\" postfix.\n");
    return;
  }
  init_success_ = true;
}

ProtoParser::~ProtoParser() {}

bool ProtoParser::ReadProtoFile() {
  if (!init_success_) {
    return false;
  }

  std::unique_ptr<IO::FileDescriptor> fd(
      new IO::FileDescriptor(proto_file_, IO::FileDescriptor::READ_ONLY));
  if (fd->closed()) {
    return false;
  }
  Utility::BufferedDataReader br(std::move(fd));

  // Read each line and parse in a finite state machine.
  std::string line;
  while (br.ReadLine(&line)) {
    line_number_++;
    line = StringUtils::Strip(line);
    std::cout << "--------------------------------------------" << std::endl;
    PrintParseState();
    std::cout << "Parsing: \"" << line << "\"\n" << std::endl;

    // Skip empty and comment lines.
    if (line.length() == 0 || StringUtils::StartWith(line, "//")) {
      continue;
    }
    // remove comment in the line.
    std::size_t pos;
    if ((pos = line.find("//")) != std::string::npos) {
      line = StringUtils::Strip(line.substr(0, pos));
    }

    // Parse in Global state: Only accept line start with "package ",
    // "message ", "enum ".
    if (state_ == GLOBAL) {
      if (StringUtils::StartWith(line, "package ")) {
        if (!ParsePackageName(line)) {
          return false;
        }
      }
      // Parse message.
      else if (StringUtils::StartWith(line, "message ")) {
        if (!ParseMessageName(line)) {
          return false;
        }
        state_ = PARSINGMSG;
      }
      else if (StringUtils::StartWith(line, "enum ")) {
        if (!ParseEnumName(line)) {
          return false;
        }
        state_ = PARSINGENUM;
      }
      else {
        LogError("Illegal line in global");
        return false;
      }
    }

    // Parse a message state.
    else if (state_ == PARSINGMSG) {
      // Parse message field.
      if (StringUtils::StartWith(line, "enum ")) {
        if (!ParseEnumName(line)) {
          return false;
        }
        state_ = PARSINGNESTEDENUM;
      }
      else if (line == "}") {
        state_ = GLOBAL;
      }
      else if (IsMessageFiledLine(line)) {
        if (!ParseMessageField(line)) {
          return false;
        }
      }
      else {
        LogError("Illegal line in Parsing a message");
        return false;
      }
    }

    // Parse a enum state.
    else if (state_ == PARSINGENUM) {
      if (line == "}") {
        state_ = GLOBAL;
      }
      else if (!ParseEnumValue(line)) {
        return false;
      }
    }

    // Parse a nested enum state.
    else if (state_ == PARSINGNESTEDENUM) {
      if (line == "}") {
        state_ = PARSINGMSG;
      }
      else if (!ParseEnumValue(line)) {
        return false;
      }
    }

    // Syntax Error
    else {
      LogError("Illegal line, can't parse");
      return false;
    }
  }
  return true;
}

bool ProtoParser::ParsePackageName(std::string line) {
  if (line[line.length()-1] != ';') {
    LogError("Expect \";\" at line end");
    return false;
  }
  line = StringUtils::Strip(line, ";");
  std::vector<std::string> result = StringUtils::SplitGreedy(line, ' ');
  if (result.size() != 2) {
    LogError("Expect 2 tokens, actual %d", result.size());
    return false;
  }
  if (result[0] != "package") {
    LogError("Unknown key word", result[0].c_str());
    return false;
  }
  current_package_ = result[1];
  result = StringUtils::Split(current_package_, '.');
  pkg_stack_.clear();
  for (auto& pkg: result) {
    if (!IsValidVariableName(pkg)) {
      LogError("Invalid package name %s in %s",
               pkg.c_str(), current_package_.c_str());
      return false;
    }
  }
  return true;
}

bool ProtoParser::ParseMessageName(std::string line) {
  std::vector<std::string> result = StringUtils::SplitGreedy(line, ' ');
  if (result.size() != 2 && result.size() != 3) {
    LogError("Expect 2 or 3 tokens, actual %d", result.size());
    return false;
  }
  if (result[0] != "message") {
    LogError("Unknown keyword \"%s\"\n", result[0].c_str());
    return false;
  }
  if (result.size() > 2 && result[2] != "{") {
    LogError("Syntax error, expect \"{\" at line end\n");
    return false;
  }
  if (result.size() == 2 && result[1][result[1].length()-1] != '{') {
    LogError("Syntax error, expect \"{\" at line end\n");
    return false;
  }

  // Get message name.
  std::string message_name = result[1];
  if (result.size() == 2) {
    message_name = message_name.substr(0, message_name.length() - 1);
  }
  if (!IsValidVariableName(message_name)) {
    LogError("invalid message name \"%s\"", message_name.c_str());
    return false;
  }
  // Check name duplication.
  if (messages_map_.find(message_name) != messages_map_.end()) {
    LogError("message name \"%s\" already exists", message_name.c_str());
    return false;
  }
  if (enums_map_.find(message_name) != enums_map_.end()) {
    LogError("name \"%s\" already exists as a enum type", message_name.c_str());
    return false;
  }

  // Add new message to message map.
  std::shared_ptr<Message> new_message(new Message(message_name,
                                                   current_package_));
  messages_list_.push_back(new_message);
  messages_map_[message_name] = new_message;
  current_message_ = new_message.get();
  return true;
}

bool ProtoParser::ParseMessageField(std::string line) {
  if (line[line.length()-1] != ';') {
    LogError("Expect \";\" at line end");
    return false;
  }
  line = StringUtils::Strip(line, ";");
  std::vector<std::string> result = StringUtils::SplitGreedy(line, ' ');

  if (result.size() < 3) {
    LogError("Syntax error");
    return false;
  }
  // Parse field modifier.
  MessageField::FIELD_MODIFIER modifier;
  if ((modifier = MessageField::GetMessageFieldModifier(result[0])) ==
      MessageField::UNKNOWN_MODIFIER) {
    LogError("Unknown modifier \"%s\"", result[0].c_str());
    return false;
  }
  // Parse field type.
  std::string type_name = result[1];
  FIELD_TYPE type;
  PbType* type_class = NULL;
  if ((type = PbCommon::GetMessageFieldType(type_name)) == UNDETERMINED) {
    if (current_message_->FindEnumType(type_name)) {
      type = ENUMTYPE;
      type_class =
          static_cast<PbType*>(current_message_->FindEnumType(type_name));
    }
    else if (enums_map_.find(type_name) != enums_map_.end()) {
      type = ENUMTYPE;
      type_class = static_cast<PbType*>(enums_map_.at(type_name).get());
    }
    else if (messages_map_.find(type_name) != messages_map_.end()) {
      type = MESSAGETYPE;
      type_class = static_cast<PbType*>(messages_map_.at(type_name).get());
    }
    else {
      LogError("Unknown field type \"%s\"", type_name.c_str());
      return false;
    }
  }

  // Parse name and tag.
  std::string remain;
  for (unsigned int i = 2; i < result.size(); i++) {
    remain += (result[i] + " ");
  }

  std::string nametag = remain, defaultblock = "";
  std::size_t pos = remain.find("[");
  if (pos != std::string::npos) {
    nametag = StringUtils::Strip(remain.substr(0, pos));
    defaultblock = StringUtils::Strip(remain.substr(pos));
    if (defaultblock[defaultblock.length()-1] != ']') {
      LogError("Expect \"]\" after default assignement");
      return false;
    }
    defaultblock = StringUtils::Strip(defaultblock, "[]");   
  }

  std::string name, tag;
  if (!ParseAssignExpression(nametag, &name, &tag, INT32)) {
    return false;
  }
  int tag_num = std::stoi(tag);

  // Parse default block.
  std::string default_name, default_value = "";
  if (defaultblock.length() > 0) {
    // Value is validated inside ParseAssignExpression(), except for enum type.
    if (!ParseAssignExpression(defaultblock, &default_name, &default_value,
                               type)) {
      return false;
    }
    // Validate default value of enum type.
    if (type == ENUMTYPE) {
      EnumType* enumclass = static_cast<EnumType*>(type_class);
      if (!enumclass->ContainsEnum(default_value)) {
        LogError("Enum value \"%s\" is not a valid value in enum type %s",
                 default_value.c_str(), type_class->name().c_str());
        return false;
      }
    }
    if (default_name != "default") {
      LogError("Can't recognize \"%s\", should be \"default\"",
               default_name.c_str());
      return false;
    }
  }

  // Add new field to current message.
  std::shared_ptr<MessageField> new_field(
      new MessageField(modifier, type, type_class, name, tag_num,
                       default_value));
  if (!current_message_->AddField(new_field)) {
    LogError("Add field \"%s\" to message \"%s\" failed",
             name.c_str(), current_message_->name().c_str());
    return false;
  }
  return true;
}

bool ProtoParser::ParseEnumName(std::string line) {
  std::vector<std::string> result = StringUtils::SplitGreedy(line, ' ');
  if (result.size() != 2 && result.size() != 3) {
    LogError("Expect 2 or 3 least tokens, actual %d", result.size());
    return false;
  }
  if (result[0] != "enum") {
    LogError("Unknown keyword \"%s\"\n", result[0].c_str());
    return false;
  }
  if (result.size() > 2 && result[2] != "{") {
    LogError("Syntax error, expect \"{\" at line end\n");
    return false;
  }
  if (result.size() == 2 && result[1][result[1].length()-1] != '{') {
    LogError("Syntax error, expect \"{\" at line end\n");
    return false;
  }

  // Get enum name.
  std::string enum_name = result[1];
  if (result.size() == 2) {
    enum_name = enum_name.substr(0, enum_name.length() - 1);
  }
  if (!IsValidVariableName(enum_name)) {
    LogError("invalid enum name \"%s\"", enum_name.c_str());
    return false;
  }
  // Check name duplication
  if (state_ == PARSINGMSG && 
      current_message_->enums_map().find(enum_name) !=
          current_message_->enums_map().end()) {
    LogError("enum name \"%s\" already exists in message \"%s\"",
             enum_name.c_str(), current_message_->name().c_str());
    return false;
  }
  if (state_ == GLOBAL && 
      enums_map_.find(enum_name) != enums_map_.end()) {
    LogError("enum name \"%s\" already exists", enum_name.c_str());
    return false;
  }


  // Add new enum to the enum map
  std::shared_ptr<EnumType> new_enum;
  if (state_ == GLOBAL) {
    new_enum.reset(new EnumType(enum_name, current_package_));
    enums_map_[enum_name] = new_enum;
    currentEnum_ = new_enum.get();
  }
  else if (state_ == PARSINGMSG) {
    new_enum.reset(new EnumType(enum_name, current_package_,
                                current_message_->name()));
    current_message_->AddEnum(new_enum);
    currentEnum_ = new_enum.get();
  }

  return true;
}

bool ProtoParser::ParseEnumValue(std::string line) {
  if (line[line.length()-1] != ',') {
    LogError("Expect \",\" at line end");
    return false;
  }
  std::string name = line.substr(0, line.length() - 1);
  if (!IsValidVariableName(name)) {
    LogError("invalid enum field name \"%s\"", name.c_str());
    return false;
  }
  currentEnum_->AddEnumValue(name);
  return true;
}

bool ProtoParser::IsMessageFiledLine(std::string line) {
  return StringUtils::StartWith(line, "optional ") ||
         StringUtils::StartWith(line, "required ") ||
         StringUtils::StartWith(line, "repeated ");
}

bool ProtoParser::ParseAssignExpression(std::string line,
                                        std::string* left,
                                        std::string* right,
                                        FIELD_TYPE type) const {
  line = StringUtils::Strip(line);
  std::size_t pos = line.find("=");
  if (pos == std::string::npos) {
    LogError("Expect \"variable = value\" but actual \"%s\"", line.c_str());
    return false;
  }
  *left = StringUtils::Strip(line.substr(0, pos));
  *right = StringUtils::Strip(line.substr(pos + 1));
  if ((*left).length() == 0 || !IsValidVariableName(*left)) {
    LogError("invalid variable name \"%s\"", (*left).c_str());
    return false;
  }
  if ((*right).length() == 0) {
    LogError("value of %s must not be empty", (*left).c_str());
    return false;
  }
  switch (type) {
    case INT32:
      try {
        int value = std::stoi(*right);
        (void)value;
      }
      catch (std::exception& err) {
        LogError("Can't parse \"%s\" as int32 value", (*right).c_str());
        return false;
      }
      break;
    case UINT32:
      try {
        unsigned long value = std::stoul(*right);
        (void)value;
      }
      catch (std::exception& err) {
        LogError("Can't parse \"%s\" as uint32 value", (*right).c_str());
        return false;
      }
      break;
    case INT64:
      try {
        long long value = std::stoll(*right);
        (void)value;
      }
      catch (std::exception& err) {
        LogError("Can't parse \"%s\" as int64 value", (*right).c_str());
        return false;
      }
      break;
    case UINT64:
      try {
        unsigned long long value = std::stoull(*right);
        (void)value;
      }
      catch (std::exception& err) {
        LogError("Can't parse %s as int64 value", (*right).c_str());
        return false;
      }
      break;
    case DOUBLE:
      try {
        double value = std::stod(*right);
        (void)value;
      }
      catch (std::exception& err) {
        LogError("Can't parse \"%s\" as double value", (*right).c_str());
        return false;
      }
      break;
    case BOOL:
      if (*right != "true" && *right != "false" &&
          *right != "True" && *right != "False") {
        LogError("Invalid boolean value \"%s\"", (*right).c_str());
        return false;
      }
      break;
    case STRING:
      {
        std::string value = *right;
        if (!StringUtils::StartWith(value, "\"") ||
            !StringUtils::EndWith(value, "\"")) {
          LogError(
              "Invalid string value: must be double quotated, actual - \"%s\"",
              (*right).c_str());
          return false;
        }
        *right = StringUtils::Strip(*right, "\"");
      }
      break;
    default:
      break;
  }

  return true;
}

bool ProtoParser::ParseProto() {
  if (!ReadProtoFile()) {
    fprintf(stderr, "ERROR: Can't parse proto %s\n", proto_file_.c_str());
    return false;
  }
  PrintParsedProto();
  return true;
}

void ProtoParser::PrintParsedProto() const {
  for (auto& message : messages_list_) {
    message->Print();
    std::cout << std::endl << std::endl;
  }
  for (auto& e : enums_map_) {
    e.second->Print();
    std::cout << std::endl << std::endl;
  }
}

bool ProtoParser::IsValidVariableName(std::string str) {
  if (str.length() == 0) {
    return false;
  }
  for (unsigned int i = 0; i < str.length(); i++) {
    if (!StringUtils::IsLetterOrDigitOrUnderScore(str[i])) {
      return false;
    }
  }
  return true;
}

ProtoParser::LANGUAGE
ProtoParser::GetLanguageFromString(std::string lang) {
  if (lang == "cpp") {
    return CPP;
  }
  if (lang == "python") {
    return PYTHON;
  }
  if (lang == "java") {
    return JAVA;
  }
  return UNKNOWN_LANGUAGE;
}

void ProtoParser::PrintToken(std::string description, std::string str) {
  std::cout << "[" << description << "] = \"" << str << "\"" << std::endl;
}

void ProtoParser::LogError(const char* error_msg, ...) const {
  fprintf(stderr, "%s:%d: ", proto_file_.c_str(), line_number_);
  va_list args;
  va_start(args, error_msg);
  vfprintf(stderr, error_msg, args);
  va_end(args);
  fprintf(stderr, ".\n");
}

void ProtoParser::PrintParseState() const {
  switch (state_) {
    case GLOBAL:
      std::cout << "State: Global" << std::endl;
      break;
    case PARSINGMSG:
      std::cout << "State: Parsing Messsage" << std::endl;
      break;
    case PARSINGENUM:
      std::cout << "State: Parsing Enum" << std::endl;
      break;
    case PARSINGNESTEDENUM:
      std::cout << "State: Parsing Nested Enum" << std::endl;
      break;
    default:
      break;
  }
}

}  // Compiler
}  // PandaProto