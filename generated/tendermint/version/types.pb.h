// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tendermint/version/types.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_tendermint_2fversion_2ftypes_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_tendermint_2fversion_2ftypes_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "gogoproto/gogo.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_tendermint_2fversion_2ftypes_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_tendermint_2fversion_2ftypes_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_tendermint_2fversion_2ftypes_2eproto;
namespace tendermint {
namespace version {
class App;
struct AppDefaultTypeInternal;
extern AppDefaultTypeInternal _App_default_instance_;
class Consensus;
struct ConsensusDefaultTypeInternal;
extern ConsensusDefaultTypeInternal _Consensus_default_instance_;
}  // namespace version
}  // namespace tendermint
PROTOBUF_NAMESPACE_OPEN
template<> ::tendermint::version::App* Arena::CreateMaybeMessage<::tendermint::version::App>(Arena*);
template<> ::tendermint::version::Consensus* Arena::CreateMaybeMessage<::tendermint::version::Consensus>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace tendermint {
namespace version {

// ===================================================================

class App final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:tendermint.version.App) */ {
 public:
  inline App() : App(nullptr) {}
  ~App() override;
  explicit PROTOBUF_CONSTEXPR App(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  App(const App& from);
  App(App&& from) noexcept
    : App() {
    *this = ::std::move(from);
  }

  inline App& operator=(const App& from) {
    CopyFrom(from);
    return *this;
  }
  inline App& operator=(App&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const App& default_instance() {
    return *internal_default_instance();
  }
  static inline const App* internal_default_instance() {
    return reinterpret_cast<const App*>(
               &_App_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(App& a, App& b) {
    a.Swap(&b);
  }
  inline void Swap(App* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(App* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  App* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<App>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const App& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const App& from) {
    App::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(App* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "tendermint.version.App";
  }
  protected:
  explicit App(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSoftwareFieldNumber = 2,
    kProtocolFieldNumber = 1,
  };
  // string software = 2;
  void clear_software();
  const std::string& software() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_software(ArgT0&& arg0, ArgT... args);
  std::string* mutable_software();
  PROTOBUF_NODISCARD std::string* release_software();
  void set_allocated_software(std::string* software);
  private:
  const std::string& _internal_software() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_software(const std::string& value);
  std::string* _internal_mutable_software();
  public:

  // uint64 protocol = 1;
  void clear_protocol();
  uint64_t protocol() const;
  void set_protocol(uint64_t value);
  private:
  uint64_t _internal_protocol() const;
  void _internal_set_protocol(uint64_t value);
  public:

  // @@protoc_insertion_point(class_scope:tendermint.version.App)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr software_;
    uint64_t protocol_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_tendermint_2fversion_2ftypes_2eproto;
};
// -------------------------------------------------------------------

class Consensus final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:tendermint.version.Consensus) */ {
 public:
  inline Consensus() : Consensus(nullptr) {}
  ~Consensus() override;
  explicit PROTOBUF_CONSTEXPR Consensus(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Consensus(const Consensus& from);
  Consensus(Consensus&& from) noexcept
    : Consensus() {
    *this = ::std::move(from);
  }

  inline Consensus& operator=(const Consensus& from) {
    CopyFrom(from);
    return *this;
  }
  inline Consensus& operator=(Consensus&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Consensus& default_instance() {
    return *internal_default_instance();
  }
  static inline const Consensus* internal_default_instance() {
    return reinterpret_cast<const Consensus*>(
               &_Consensus_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Consensus& a, Consensus& b) {
    a.Swap(&b);
  }
  inline void Swap(Consensus* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Consensus* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Consensus* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Consensus>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Consensus& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Consensus& from) {
    Consensus::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Consensus* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "tendermint.version.Consensus";
  }
  protected:
  explicit Consensus(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBlockFieldNumber = 1,
    kAppFieldNumber = 2,
  };
  // uint64 block = 1;
  void clear_block();
  uint64_t block() const;
  void set_block(uint64_t value);
  private:
  uint64_t _internal_block() const;
  void _internal_set_block(uint64_t value);
  public:

  // uint64 app = 2;
  void clear_app();
  uint64_t app() const;
  void set_app(uint64_t value);
  private:
  uint64_t _internal_app() const;
  void _internal_set_app(uint64_t value);
  public:

  // @@protoc_insertion_point(class_scope:tendermint.version.Consensus)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    uint64_t block_;
    uint64_t app_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_tendermint_2fversion_2ftypes_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// App

// uint64 protocol = 1;
inline void App::clear_protocol() {
  _impl_.protocol_ = uint64_t{0u};
}
inline uint64_t App::_internal_protocol() const {
  return _impl_.protocol_;
}
inline uint64_t App::protocol() const {
  // @@protoc_insertion_point(field_get:tendermint.version.App.protocol)
  return _internal_protocol();
}
inline void App::_internal_set_protocol(uint64_t value) {
  
  _impl_.protocol_ = value;
}
inline void App::set_protocol(uint64_t value) {
  _internal_set_protocol(value);
  // @@protoc_insertion_point(field_set:tendermint.version.App.protocol)
}

// string software = 2;
inline void App::clear_software() {
  _impl_.software_.ClearToEmpty();
}
inline const std::string& App::software() const {
  // @@protoc_insertion_point(field_get:tendermint.version.App.software)
  return _internal_software();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void App::set_software(ArgT0&& arg0, ArgT... args) {
 
 _impl_.software_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:tendermint.version.App.software)
}
inline std::string* App::mutable_software() {
  std::string* _s = _internal_mutable_software();
  // @@protoc_insertion_point(field_mutable:tendermint.version.App.software)
  return _s;
}
inline const std::string& App::_internal_software() const {
  return _impl_.software_.Get();
}
inline void App::_internal_set_software(const std::string& value) {
  
  _impl_.software_.Set(value, GetArenaForAllocation());
}
inline std::string* App::_internal_mutable_software() {
  
  return _impl_.software_.Mutable(GetArenaForAllocation());
}
inline std::string* App::release_software() {
  // @@protoc_insertion_point(field_release:tendermint.version.App.software)
  return _impl_.software_.Release();
}
inline void App::set_allocated_software(std::string* software) {
  if (software != nullptr) {
    
  } else {
    
  }
  _impl_.software_.SetAllocated(software, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.software_.IsDefault()) {
    _impl_.software_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:tendermint.version.App.software)
}

// -------------------------------------------------------------------

// Consensus

// uint64 block = 1;
inline void Consensus::clear_block() {
  _impl_.block_ = uint64_t{0u};
}
inline uint64_t Consensus::_internal_block() const {
  return _impl_.block_;
}
inline uint64_t Consensus::block() const {
  // @@protoc_insertion_point(field_get:tendermint.version.Consensus.block)
  return _internal_block();
}
inline void Consensus::_internal_set_block(uint64_t value) {
  
  _impl_.block_ = value;
}
inline void Consensus::set_block(uint64_t value) {
  _internal_set_block(value);
  // @@protoc_insertion_point(field_set:tendermint.version.Consensus.block)
}

// uint64 app = 2;
inline void Consensus::clear_app() {
  _impl_.app_ = uint64_t{0u};
}
inline uint64_t Consensus::_internal_app() const {
  return _impl_.app_;
}
inline uint64_t Consensus::app() const {
  // @@protoc_insertion_point(field_get:tendermint.version.Consensus.app)
  return _internal_app();
}
inline void Consensus::_internal_set_app(uint64_t value) {
  
  _impl_.app_ = value;
}
inline void Consensus::set_app(uint64_t value) {
  _internal_set_app(value);
  // @@protoc_insertion_point(field_set:tendermint.version.Consensus.app)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace version
}  // namespace tendermint

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_tendermint_2fversion_2ftypes_2eproto
