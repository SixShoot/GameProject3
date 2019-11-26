// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Msg_ID.proto

#ifndef PROTOBUF_Msg_5fID_2eproto__INCLUDED
#define PROTOBUF_Msg_5fID_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)

namespace protobuf_Msg_5fID_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
inline void InitDefaults() {
}
}  // namespace protobuf_Msg_5fID_2eproto

enum MessageID {
  MSG_BEGIN = 0,
  MSG_NORMAL_MSGID_BEGIN = 100000,
  MSG_CHECK_VERSION_REQ = 100001,
  MSG_CHECK_VERSION_ACK = 100002,
  MSG_ACCOUNT_REG_REQ = 100003,
  MSG_ACCOUNT_REG_ACK = 100004,
  MSG_ACCOUNT_LOGIN_REQ = 100005,
  MSG_ACCOUNT_LOGIN_ACK = 100006,
  MSG_DB_EXE_SQL_REQ = 100007,
  MSG_DB_EXE_SQL_ACK = 100008,
  MSG_SERVER_LIST_REQ = 100009,
  MSG_SERVER_LIST_ACK = 100010,
  MSG_SELECT_SERVER_REQ = 100011,
  MSG_SELECT_SERVER_ACK = 100012,
  MSG_LOGIC_REGTO_LOGIN_REQ = 100013,
  MSG_LOGIC_REGTO_LOGIN_ACK = 100014,
  MSG_SEAL_ACCOUNT_REQ = 100015,
  MSG_SEAL_ACCOUNT_ACK = 100016,
  MSG_GAME_REGTO_LOGIC_REQ = 100017,
  MSG_GAME_REGTO_LOGIC_ACK = 100018,
  MSG_LOGIC_REGTO_CENTER_REQ = 100019,
  MSG_LOGIC_REGTO_CENTER_ACK = 100020,
  MSG_LOG_DATA_NTF = 100021,
  MSG_PHP_GM_COMMAND_REQ = 100022,
  MSG_PHP_GM_COMMAND_ACK = 100023,
  MSG_WATCH_HEART_BEAT_REQ = 100024,
  MSG_WATCH_HEART_BEAT_ACK = 100025,
  MSG_WATCH_UPDATE_SVR_REQ = 100026,
  MSG_WATCH_UPDATE_SVR_ACK = 100027,
  MSG_WATCH_START_SVR_REQ = 100028,
  MSG_WATCH_START_SVR_ACK = 100029,
  MSG_WATCH_STOP_SVR_REQ = 100030,
  MSG_WATCH_STOP_SVR_ACK = 100031,
  MSG_DISCONNECT_NTY = 100032,
  MSG_ROLE_DATA_CHANGE_NTY = 100033,
  MSG_SET_LAST_SERVER_NTY = 100034,
  MSG_GM_STOP_SERVER_REQ = 100035,
  MSG_GM_STOP_SERVER_ACK = 100036,
  MSG_NORMAL_MSGID_END = 199999,
  MSG_LOGICSVR_MSGID_BEGIN = 200000,
  MSG_ROLE_LIST_REQ = 200001,
  MSG_ROLE_LIST_ACK = 200002,
  MSG_ROLE_CREATE_REQ = 200003,
  MSG_ROLE_CREATE_ACK = 200004,
  MSG_ROLE_DELETE_REQ = 200005,
  MSG_ROLE_DELETE_ACK = 200006,
  MSG_ROLE_LOGIN_REQ = 200007,
  MSG_ROLE_LOGIN_ACK = 200008,
  MSG_ROLE_LOGOUT_REQ = 200009,
  MSG_ROLE_LOGOUT_ACK = 200010,
  MSG_DATA_UPDATE = 200011,
  MSG_NOTIFY_INTO_SCENE = 200014,
  MSG_COPYINFO_REPORT_REQ = 200016,
  MSG_MAIN_COPY_REQ = 200017,
  MSG_MAIN_COPY_ACK = 200018,
  MSG_ABORT_SCENE_NTF = 200019,
  MSG_XXX_XXXX_XXXX_1 = 200020,
  MSG_BACK_TO_CITY_REQ = 200021,
  MSG_BACK_TO_CITY_ACK = 200022,
  MSG_BATTLE_RESULT_NTY = 200023,
  MSG_MAINCOPY_RESULT_NTY = 200024,
  MSG_ROLE_CHANG_NTY = 200025,
  MSG_BAG_CHANGE_NTY = 200026,
  MSG_PET_CHANGE_NTY = 200027,
  MSG_EQUIP_CHANGE_NTY = 200028,
  MSG_PARTNER_CHANGE_NTY = 200029,
  MSG_MOUNT_CHANGE_NTY = 200030,
  MSG_ROLE_OTHER_LOGIN_NTY = 200031,
  MSG_CHAT_MESSAGE_REQ = 200032,
  MSG_CHAT_MESSAGE_ACK = 200033,
  MSG_CHAT_MESSAGE_NTY = 200034,
  MSG_SETUP_EQUIP_REQ = 200035,
  MSG_SETUP_EQUIP_ACK = 200036,
  MSG_UNSET_EQUIP_REQ = 200037,
  MSG_UNSET_EQUIP_ACK = 200038,
  MSG_SETUP_PET_REQ = 200039,
  MSG_SETUP_PET_ACK = 200040,
  MSG_UNSET_PET_REQ = 200041,
  MSG_UNSET_PET_ACK = 200042,
  MSG_SETUP_PARTNER_REQ = 200043,
  MSG_SETUP_PARTNER_ACK = 200044,
  MSG_UNSET_PARTNER_REQ = 200045,
  MSG_UNSET_PARTNER_ACK = 200046,
  MSG_SETUP_MOUNT_REQ = 200047,
  MSG_SETUP_MOUNT_ACK = 200048,
  MSG_UNSET_MOUNT_REQ = 200049,
  MSG_UNSET_MOUNT_ACK = 200050,
  MSG_USE_ITEM_REQ = 200051,
  MSG_USE_ITEM_ACK = 200052,
  MSG_SETUP_GEM_REQ = 200053,
  MSG_SETUP_GEM_ACK = 200054,
  MSG_UNSET_GEM_REQ = 200055,
  MSG_UNSET_GEM_ACK = 200056,
  MSG_ROLE_RECONNECT_REQ = 200057,
  MSG_ROLE_RECONNECT_ACK = 200058,
  MSG_MAIL_CHANGE_NTY = 200059,
  MSG_TASK_CHANGE_NTY = 200060,
  MSG_BROAD_MESSAGE_NOTIFY = 200061,
  MSG_GASVR_REGTO_PROXY_REQ = 200062,
  MSG_GASVR_REGTO_PROXY_ACK = 200063,
  MSG_STORE_BUY_REQ = 200064,
  MSG_STORE_BUY_ACK = 200065,
  MSG_GEM_CHANGE_NTY = 200066,
  MSG_RANDOM_NAME_REQ = 200067,
  MSG_RANDOM_NAME_ACK = 200068,
  MSG_ROLE_REBORN_REQ = 200069,
  MSG_ROLE_REBORN_ACK = 200070,
  MSG_CREATE_ROOM_REQ = 200071,
  MSG_CREATE_ROOM_ACK = 200072,
  MSG_JOIN_ROOM_REQ = 200073,
  MSG_JOIN_ROOM_ACK = 200074,
  MSG_KICK_ROOM_REQ = 200075,
  MSG_KICK_ROOM_ACK = 200076,
  MSG_LEAVE_ROOM_REQ = 200077,
  MSG_LEAVE_ROOM_ACK = 200078,
  MSG_START_ROOM_REQ = 200079,
  MSG_START_ROOM_ACK = 200080,
  MSG_BROAD_ROOM_NOTIFY = 200081,
  MSG_TEST_ADD_ITEM = 299998,
  MSG_LOGICSVR_MSGID_END = 299999,
  MSG_SCENESVR_MSGID_BEGIN = 300000,
  MSG_CREATE_SCENE_REQ = 300001,
  MSG_CREATE_SCENE_ACK = 300002,
  MSG_DELETE_SCENE_REQ = 300003,
  MSG_DELETE_SCENE_ACK = 300004,
  MSG_SCENE_DESTROY_REQ = 300005,
  MSG_SCENE_DESTROY_ACK = 300006,
  MSG_TRANSFER_DATA_REQ = 300007,
  MSG_TRANSFER_DATA_ACK = 300008,
  MSG_NOTIFY_ROLE_ENTER_REQ = 300009,
  MSG_NOTIFY_ROLE_ENTER_ACK = 300010,
  MSG_ENTER_SCENE_REQ = 300011,
  MSG_ENTER_SCENE_ACK = 300012,
  MSG_LEAVE_SCENE_REQ = 300013,
  MSG_LEAVE_SCENE_ACK = 300014,
  MSG_ABORT_SCENE_REQ = 300015,
  MSG_ABORT_SCENE_ACK = 300016,
  MSG_SKILL_CAST_REQ = 300017,
  MSG_SKILL_CAST_ACK = 300018,
  MSG_SKILL_CAST_NTF = 300019,
  MSG_SKILL_RESULT_NTF = 300020,
  MSG_OBJECT_NEW_NTF = 300021,
  MSG_OBJECT_CHANGE_NTF = 300022,
  MSG_OBJECT_REMOVE_NTF = 300023,
  MSG_OBJECT_ACTION_REQ = 300024,
  MSG_OBJECT_ACTION_ACK = 300025,
  MSG_HEART_BEAT_REQ = 300026,
  MSG_HEART_BEAT_ACK = 300027,
  MSG_USE_HP_BOOTTLE_REQ = 300028,
  MSG_USE_HP_BOOTTLE_ACK = 300029,
  MSG_USE_MP_BOOTTLE_REQ = 300030,
  MSG_USE_MP_BOOTTLE_ACK = 300031,
  MSG_OBJECT_DIE_NOTIFY = 300032,
  MSG_BATTLE_CHAT_REQ = 300033,
  MSG_BATTLE_CHAT_ACK = 300034,
  MSG_BULLET_NEW_NTF = 300035,
  MSG_SWITCH_MOUNT_REQ = 300036,
  MSG_SWITCH_MOUNT_ACK = 300037,
  MSG_PLAYER_CHAGE_NTF = 300038,
  MSG_ACTOR_HITEFFECT_NTF = 300039,
  MSG_MOUNT_RIDING_REQ = 300040,
  MSG_MOUNT_RIDING_ACK = 300041,
  MSG_SCENESVR_MSGID_END = 399999,
  MessageID_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  MessageID_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool MessageID_IsValid(int value);
const MessageID MessageID_MIN = MSG_BEGIN;
const MessageID MessageID_MAX = MSG_SCENESVR_MSGID_END;
const int MessageID_ARRAYSIZE = MessageID_MAX + 1;

const ::google::protobuf::EnumDescriptor* MessageID_descriptor();
inline const ::std::string& MessageID_Name(MessageID value) {
  return ::google::protobuf::internal::NameOfEnum(
    MessageID_descriptor(), value);
}
inline bool MessageID_Parse(
    const ::std::string& name, MessageID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MessageID>(
    MessageID_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::MessageID> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::MessageID>() {
  return ::MessageID_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Msg_5fID_2eproto__INCLUDED
