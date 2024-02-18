#ifndef IL2CPP_H
#define IL2CPP_H
#include <stdint.h>

typedef void(*Il2CppMethodPointer)();

struct MethodInfo;

struct VirtualInvokeData
{
    Il2CppMethodPointer methodPtr;
    const MethodInfo* method;
};

struct Il2CppType
{
    void* data;
    unsigned int bits;
};

struct Il2CppClass;

struct Il2CppObject
{
    Il2CppClass *klass;
    void *monitor;
};

union Il2CppRGCTXData
{
    void* rgctxDataDummy;
    const MethodInfo* method;
    const Il2CppType* type;
    Il2CppClass* klass;
};

struct Il2CppRuntimeInterfaceOffsetPair
{
    Il2CppClass* interfaceType;
    int32_t offset;
};
struct Il2CppClass_1
{
    void* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    Il2CppType byval_arg;
    Il2CppType this_arg;
    Il2CppClass* element_class;
    Il2CppClass* castClass;
    Il2CppClass* declaringType;
    Il2CppClass* parent;
    void *generic_class;
    void* typeMetadataHandle;
    void* interopData;
    Il2CppClass* klass;
    void* fields;
    void* events;
    void* properties;
    void* methods;
    Il2CppClass** nestedTypes;
    Il2CppClass** implementedInterfaces;
    Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
};

struct Il2CppClass_2
{
    Il2CppClass** typeHierarchy;
    void *unity_user_data;
    uint32_t initializationExceptionGCHandle;
    uint32_t cctor_started;
    uint32_t cctor_finished;
    size_t cctor_thread;
    void* genericContainerHandle;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint8_t typeHierarchyDepth;
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t naturalAligment;
    uint8_t packingSize;
    uint8_t bitflags1;
    uint8_t bitflags2;
};

struct Il2CppClass
{
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    VirtualInvokeData vtable[255];
};

typedef uintptr_t il2cpp_array_size_t;
typedef int32_t il2cpp_array_lower_bound_t;
struct Il2CppArrayBounds
{
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
};

typedef void (*InvokerMethod)(Il2CppMethodPointer, const MethodInfo*, void*, void**, void*);
struct MethodInfo
{
    Il2CppMethodPointer methodPointer;
    Il2CppMethodPointer virtualMethodPointer;
    InvokerMethod invoker_method;
    const char* name;
    Il2CppClass *klass;
    const Il2CppType *return_type;
    const Il2CppType** parameters;
    union
    {
        const Il2CppRGCTXData* rgctx_data;
        const void* methodMetadataHandle;
    };
    union
    {
        const void* genericMethod;
        const void* genericContainerHandle;
    };
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t bitflags;
};

struct __declspec(align(8)) System_String_Fields {
    int32_t _stringLength;
    uint16_t _firstChar;
};
struct System_String_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
    VirtualInvokeData _4_CompareTo;
    VirtualInvokeData _5_System_Collections_IEnumerable_GetEnumerator;
    VirtualInvokeData _6_System_Collections_Generic_IEnumerable_System_Char__GetEnumerator;
    VirtualInvokeData _7_CompareTo;
    VirtualInvokeData _8_Equals;
    VirtualInvokeData _9_GetTypeCode;
    VirtualInvokeData _10_System_IConvertible_ToBoolean;
    VirtualInvokeData _11_System_IConvertible_ToChar;
    VirtualInvokeData _12_System_IConvertible_ToSByte;
    VirtualInvokeData _13_System_IConvertible_ToByte;
    VirtualInvokeData _14_System_IConvertible_ToInt16;
    VirtualInvokeData _15_System_IConvertible_ToUInt16;
    VirtualInvokeData _16_System_IConvertible_ToInt32;
    VirtualInvokeData _17_System_IConvertible_ToUInt32;
    VirtualInvokeData _18_System_IConvertible_ToInt64;
    VirtualInvokeData _19_System_IConvertible_ToUInt64;
    VirtualInvokeData _20_System_IConvertible_ToSingle;
    VirtualInvokeData _21_System_IConvertible_ToDouble;
    VirtualInvokeData _22_System_IConvertible_ToDecimal;
    VirtualInvokeData _23_System_IConvertible_ToDateTime;
    VirtualInvokeData _24_ToString;
    VirtualInvokeData _25_System_IConvertible_ToType;
    VirtualInvokeData _26_Clone;
};
struct System_String_c {
    Il2CppClass_1 _1;
    struct System_String_StaticFields* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    System_String_VTable vtable;
};
struct System_String_o {
    System_String_c* klass;
    void* monitor;
    System_String_Fields fields;
};
struct GameData_Profile_AchievementData_Fields {
    struct System_String_o* Id;
    struct System_String_o* StreamVariable;
    struct System_String_o* Description;
    int32_t IntData;
    struct System_Int32_array* IntArrayData;
    struct System_String_o* StringData;
    struct System_String_array* StringArrayData;
    uint8_t AchievementType;
};
struct GameData_Profile_AchievementData_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
};
struct GameData_Profile_AchievementData_c {
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    GameData_Profile_AchievementData_VTable vtable;
};
struct GameData_Profile_AchievementData_o {
    GameData_Profile_AchievementData_Fields fields;
};
struct GameData_Profile_AchievementData_array {
    Il2CppObject obj;
    Il2CppArrayBounds* bounds;
    il2cpp_array_size_t max_length;
    GameData_Profile_AchievementData_o m_Items[65535];
};
typedef struct Il2CppGenericInst
{
    uint32_t type_argc;
    const Il2CppType** type_argv;
} Il2CppGenericInst;
typedef struct Il2CppGenericContext
{
    /* The instantiation corresponding to the class generic parameters */
    const Il2CppGenericInst* class_inst;
    /* The instantiation corresponding to the method generic parameters */
    const Il2CppGenericInst* method_inst;
} Il2CppGenericContext;
typedef struct Il2CppGenericMethod
{
    const MethodInfo* methodDefinition;
    Il2CppGenericContext context;
} Il2CppGenericMethod;
typedef const struct ___Il2CppMetadataMethodHandle* Il2CppMetadataMethodDefinitionHandle;
typedef const struct ___Il2CppMetadataGenericContainerHandle* Il2CppMetadataGenericContainerHandle;

#endif