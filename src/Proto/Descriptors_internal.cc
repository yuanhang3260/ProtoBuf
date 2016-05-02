#include "Proto/Descriptors_internal.h"

#include "Base/Log.h"
#include "Proto/Descriptor.h"

namespace proto {

/// ProtoFileDescriptorImpl
void ProtoFileDescriptorImpl::AddMessageDescriptor(
          std::shared_ptr<MessageDescriptor> descriptor) {
  auto it = messages_map_.emplace(descriptor->full_name(), descriptor);
  if (!it.second) {
    LogFATAL("Failed to add enum descriptor to file-level enum map");
  }
}

void ProtoFileDescriptorImpl::AddEnumDescriptor(
         std::shared_ptr<EnumDescriptor> descriptor) {
  auto it = enums_map_.emplace(descriptor->full_name(), descriptor);
  if (!it.second) {
    LogFATAL("Failed to add message descriptor to file-level message map");
  }
}

void ProtoFileDescriptorImpl::AddServiceDescriptor(
         std::shared_ptr<ServiceDescriptor> descriptor) {
  auto it = services_map_.emplace(descriptor->full_name(), descriptor);
  if (!it.second) {
    LogFATAL("Failed to add service descriptor to file-level service map");
  }
}


/// MessageDescriptorImpl
void MessageDescriptorImpl::AddNestedEnumDescriptor(
         std::shared_ptr<EnumDescriptor> descriptor) {
  auto it = enums_map_.emplace(descriptor->name(), descriptor);
  if (!it.second) {
    LogFATAL("Failed to add message descriptor to message-level message map");
  }
}

/// EnumDescriptorImpl
EnumDescriptorImpl::EnumDescriptorImpl(bool nested) : is_nested_(nested) {

}

}  // namespace proto