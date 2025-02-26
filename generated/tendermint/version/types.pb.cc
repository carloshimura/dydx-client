// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tendermint/version/types.proto

#include "tendermint/version/types.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace tendermint {
namespace version {
PROTOBUF_CONSTEXPR App::App(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.software_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.protocol_)*/uint64_t{0u}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct AppDefaultTypeInternal {
  PROTOBUF_CONSTEXPR AppDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~AppDefaultTypeInternal() {}
  union {
    App _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 AppDefaultTypeInternal _App_default_instance_;
PROTOBUF_CONSTEXPR Consensus::Consensus(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.block_)*/uint64_t{0u}
  , /*decltype(_impl_.app_)*/uint64_t{0u}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct ConsensusDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ConsensusDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ConsensusDefaultTypeInternal() {}
  union {
    Consensus _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ConsensusDefaultTypeInternal _Consensus_default_instance_;
}  // namespace version
}  // namespace tendermint
static ::_pb::Metadata file_level_metadata_tendermint_2fversion_2ftypes_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_tendermint_2fversion_2ftypes_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_tendermint_2fversion_2ftypes_2eproto = nullptr;

const uint32_t TableStruct_tendermint_2fversion_2ftypes_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::tendermint::version::App, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::tendermint::version::App, _impl_.protocol_),
  PROTOBUF_FIELD_OFFSET(::tendermint::version::App, _impl_.software_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::tendermint::version::Consensus, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::tendermint::version::Consensus, _impl_.block_),
  PROTOBUF_FIELD_OFFSET(::tendermint::version::Consensus, _impl_.app_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::tendermint::version::App)},
  { 8, -1, -1, sizeof(::tendermint::version::Consensus)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::tendermint::version::_App_default_instance_._instance,
  &::tendermint::version::_Consensus_default_instance_._instance,
};

const char descriptor_table_protodef_tendermint_2fversion_2ftypes_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\036tendermint/version/types.proto\022\022tender"
  "mint.version\032\024gogoproto/gogo.proto\")\n\003Ap"
  "p\022\020\n\010protocol\030\001 \001(\004\022\020\n\010software\030\002 \001(\t\"-\n"
  "\tConsensus\022\r\n\005block\030\001 \001(\004\022\013\n\003app\030\002 \001(\004:\004"
  "\350\240\037\001B7Z5github.com/cometbft/cometbft/pro"
  "to/tendermint/versionb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_tendermint_2fversion_2ftypes_2eproto_deps[1] = {
  &::descriptor_table_gogoproto_2fgogo_2eproto,
};
static ::_pbi::once_flag descriptor_table_tendermint_2fversion_2ftypes_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_tendermint_2fversion_2ftypes_2eproto = {
    false, false, 229, descriptor_table_protodef_tendermint_2fversion_2ftypes_2eproto,
    "tendermint/version/types.proto",
    &descriptor_table_tendermint_2fversion_2ftypes_2eproto_once, descriptor_table_tendermint_2fversion_2ftypes_2eproto_deps, 1, 2,
    schemas, file_default_instances, TableStruct_tendermint_2fversion_2ftypes_2eproto::offsets,
    file_level_metadata_tendermint_2fversion_2ftypes_2eproto, file_level_enum_descriptors_tendermint_2fversion_2ftypes_2eproto,
    file_level_service_descriptors_tendermint_2fversion_2ftypes_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_tendermint_2fversion_2ftypes_2eproto_getter() {
  return &descriptor_table_tendermint_2fversion_2ftypes_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_tendermint_2fversion_2ftypes_2eproto(&descriptor_table_tendermint_2fversion_2ftypes_2eproto);
namespace tendermint {
namespace version {

// ===================================================================

class App::_Internal {
 public:
};

App::App(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:tendermint.version.App)
}
App::App(const App& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  App* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.software_){}
    , decltype(_impl_.protocol_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.software_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.software_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_software().empty()) {
    _this->_impl_.software_.Set(from._internal_software(), 
      _this->GetArenaForAllocation());
  }
  _this->_impl_.protocol_ = from._impl_.protocol_;
  // @@protoc_insertion_point(copy_constructor:tendermint.version.App)
}

inline void App::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.software_){}
    , decltype(_impl_.protocol_){uint64_t{0u}}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.software_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.software_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

App::~App() {
  // @@protoc_insertion_point(destructor:tendermint.version.App)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void App::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.software_.Destroy();
}

void App::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void App::Clear() {
// @@protoc_insertion_point(message_clear_start:tendermint.version.App)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.software_.ClearToEmpty();
  _impl_.protocol_ = uint64_t{0u};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* App::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 protocol = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.protocol_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string software = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_software();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "tendermint.version.App.software"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* App::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:tendermint.version.App)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 protocol = 1;
  if (this->_internal_protocol() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_protocol(), target);
  }

  // string software = 2;
  if (!this->_internal_software().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_software().data(), static_cast<int>(this->_internal_software().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "tendermint.version.App.software");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_software(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:tendermint.version.App)
  return target;
}

size_t App::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:tendermint.version.App)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string software = 2;
  if (!this->_internal_software().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_software());
  }

  // uint64 protocol = 1;
  if (this->_internal_protocol() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_protocol());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData App::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    App::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*App::GetClassData() const { return &_class_data_; }


void App::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<App*>(&to_msg);
  auto& from = static_cast<const App&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:tendermint.version.App)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_software().empty()) {
    _this->_internal_set_software(from._internal_software());
  }
  if (from._internal_protocol() != 0) {
    _this->_internal_set_protocol(from._internal_protocol());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void App::CopyFrom(const App& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:tendermint.version.App)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool App::IsInitialized() const {
  return true;
}

void App::InternalSwap(App* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.software_, lhs_arena,
      &other->_impl_.software_, rhs_arena
  );
  swap(_impl_.protocol_, other->_impl_.protocol_);
}

::PROTOBUF_NAMESPACE_ID::Metadata App::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_tendermint_2fversion_2ftypes_2eproto_getter, &descriptor_table_tendermint_2fversion_2ftypes_2eproto_once,
      file_level_metadata_tendermint_2fversion_2ftypes_2eproto[0]);
}

// ===================================================================

class Consensus::_Internal {
 public:
};

Consensus::Consensus(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:tendermint.version.Consensus)
}
Consensus::Consensus(const Consensus& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Consensus* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.block_){}
    , decltype(_impl_.app_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.block_, &from._impl_.block_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.app_) -
    reinterpret_cast<char*>(&_impl_.block_)) + sizeof(_impl_.app_));
  // @@protoc_insertion_point(copy_constructor:tendermint.version.Consensus)
}

inline void Consensus::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.block_){uint64_t{0u}}
    , decltype(_impl_.app_){uint64_t{0u}}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

Consensus::~Consensus() {
  // @@protoc_insertion_point(destructor:tendermint.version.Consensus)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Consensus::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Consensus::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Consensus::Clear() {
// @@protoc_insertion_point(message_clear_start:tendermint.version.Consensus)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.block_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.app_) -
      reinterpret_cast<char*>(&_impl_.block_)) + sizeof(_impl_.app_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Consensus::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 block = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.block_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint64 app = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.app_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Consensus::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:tendermint.version.Consensus)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 block = 1;
  if (this->_internal_block() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_block(), target);
  }

  // uint64 app = 2;
  if (this->_internal_app() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(2, this->_internal_app(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:tendermint.version.Consensus)
  return target;
}

size_t Consensus::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:tendermint.version.Consensus)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint64 block = 1;
  if (this->_internal_block() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_block());
  }

  // uint64 app = 2;
  if (this->_internal_app() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_app());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Consensus::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Consensus::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Consensus::GetClassData() const { return &_class_data_; }


void Consensus::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Consensus*>(&to_msg);
  auto& from = static_cast<const Consensus&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:tendermint.version.Consensus)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_block() != 0) {
    _this->_internal_set_block(from._internal_block());
  }
  if (from._internal_app() != 0) {
    _this->_internal_set_app(from._internal_app());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Consensus::CopyFrom(const Consensus& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:tendermint.version.Consensus)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Consensus::IsInitialized() const {
  return true;
}

void Consensus::InternalSwap(Consensus* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Consensus, _impl_.app_)
      + sizeof(Consensus::_impl_.app_)
      - PROTOBUF_FIELD_OFFSET(Consensus, _impl_.block_)>(
          reinterpret_cast<char*>(&_impl_.block_),
          reinterpret_cast<char*>(&other->_impl_.block_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Consensus::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_tendermint_2fversion_2ftypes_2eproto_getter, &descriptor_table_tendermint_2fversion_2ftypes_2eproto_once,
      file_level_metadata_tendermint_2fversion_2ftypes_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace version
}  // namespace tendermint
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::tendermint::version::App*
Arena::CreateMaybeMessage< ::tendermint::version::App >(Arena* arena) {
  return Arena::CreateMessageInternal< ::tendermint::version::App >(arena);
}
template<> PROTOBUF_NOINLINE ::tendermint::version::Consensus*
Arena::CreateMaybeMessage< ::tendermint::version::Consensus >(Arena* arena) {
  return Arena::CreateMessageInternal< ::tendermint::version::Consensus >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
