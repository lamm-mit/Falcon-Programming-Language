#include "BigInt.hpp"

typedef struct object*(*initfunc)(struct object*, struct object*, struct object* );
typedef struct object*(*iternextfunc)(struct object*);
typedef void (*delfunc)(struct object*);
typedef struct object*(*binopfunc)(struct object*,struct object*);
typedef struct object*(*unaryfunc)(struct object*);
typedef struct object*(*getfunc)(struct object*, struct object*);
typedef struct object*(*newfunc)(object* type, object* args, object* kwargs);
typedef struct object*(*lenfunc)(struct object*);
typedef struct object*(*reprfunc)(struct object*);
typedef object* (*setfunc)(object*, object*, object*);
typedef void (*appendfunc)(object*, object*);
typedef struct object*(*compfunc)(struct object*, struct object*, uint8_t type);
typedef object* (*callfunc)(object*, object*, object*);
typedef object* (*getattrfunc)(object*, object*);
typedef object* (*setattrfunc)(object*, object*, object*);


typedef object* (*cwrapperfunc)(object*, object*, object*);
typedef object* (*getter)(object*);
typedef object* (*setter)(object*, object*);

typedef object* (*descrgetfunc)(object*, object*, object*); //Last is owner
typedef object* (*descrsetfunc)(object*, object*, object*);

typedef void (*posttpcall)(object*);


typedef struct{    
    //binops
    binopfunc slot_add;
    binopfunc slot_sub;
    binopfunc slot_mul;
    binopfunc slot_div;
    binopfunc slot_mod;
    binopfunc slot_pow;
    binopfunc slot_and;
    binopfunc slot_or;
    binopfunc slot_lshift;
    binopfunc slot_rshift;
    binopfunc slot_fldiv;
    binopfunc slot_xor;

    //unaryops
    unaryfunc slot_neg;
    unaryfunc slot_not;
    unaryfunc slot_abs;

    //other
    unaryfunc slot_bool;
    unaryfunc slot_int;
    unaryfunc slot_float;
}NumberMethods;

typedef struct{
    const char* name;
    cwrapperfunc function;
}Method;

typedef struct{
    const char* name;
    size_t offset;
    bool readonly;
}OffsetMember;

typedef struct{
    const char* name;
    getter get;
    setter set;
}GetSets;

typedef struct{    
    getfunc slot_get;
    setfunc slot_set;
    lenfunc slot_len;
    appendfunc slot_append;
}Mappings;

typedef struct object_type{
    size_t refcnt;
    object* ob_prev;
    object* ob_next;
    uint32_t gen;
    object_type* type;

    string* name;
    size_t size;
    size_t var_base_size;
    bool gc_trackable;
    object* bases;
    size_t dict_offset; //BULL if no dict
    object* dict; //NULL if no dict
    getattrfunc slot_getattr;
    setattrfunc slot_setattr;

    initfunc slot_init;
    newfunc slot_new;
    delfunc slot_del;
    
    //Iterators
    iternextfunc slot_next;
    unaryfunc slot_iter;

    reprfunc slot_repr;
    reprfunc slot_str;
    callfunc slot_call;
    
    //number methods
    NumberMethods* slot_number;
    Mappings* slot_mappings;
    Method* slot_methods;
    GetSets* slot_getsets;
    OffsetMember* slot_offsets;

    compfunc slot_cmp;

    descrgetfunc slot_descrget;
    descrsetfunc slot_descrset;

    unaryfunc slot_enter;
    unaryfunc slot_exit;

    posttpcall slot_posttpcall;

    char* slot_doc;
}TypeObject;

#define OBJHEAD size_t refcnt; struct object* ob_prev; struct object* ob_next; uint32_t gen;
#define OBJHEAD_EXTRA OBJHEAD TypeObject* type;
#define OBJHEAD_VAR OBJHEAD_EXTRA uint32_t var_size; uint32_t gc_ref;


typedef struct object{
    OBJHEAD_EXTRA
}object;

typedef struct object_var{
    OBJHEAD_VAR
}object_var;

map<BigInt, object*> int_map;
map<double, object*> float_map;
map<string, object*> str_map;

static object* trueobj=NULL;
static object* falseobj=NULL;
static object* noneobj=NULL;

const size_t nbuiltins=71;
object* builtins[nbuiltins];

TypeObject TypeError;
TypeObject ValueError;
TypeObject AttributeError;
TypeObject IndexError;
TypeObject KeyError;
TypeObject NameError;
TypeObject MemoryError;
TypeObject RecursionError;
TypeObject StopIteration;
TypeObject FileNotFoundError;
TypeObject InvalidOperationError;
TypeObject ImportError;
TypeObject KeyboardInterrupt;
TypeObject AssertionError;
TypeObject ZeroDivisionError;
TypeObject OSError;

bool setup_memory_error=false;
bool hit_memory_error=false;

Parser parser;

#define FPLINCREF(object) object->refcnt++;
#define FPLDECREF(delobj)   (delobj)->refcnt--;\
                            if ((delobj)->refcnt==0){\
                                if ((delobj)->type->slot_del!=NULL){\
                                    (delobj)->type->slot_del(delobj);\
                                }\
                                if ((delobj)->refcnt==0){\
                                    if (!(delobj)->type->gc_trackable){\
                                        fpl_free(delobj);\
                                    }\
                                }\
                            }

inline void _FPLDECREF(struct object* object);
inline object* _FPLINCREF(struct object* object);

object* new_object(TypeObject* type);
object_var* new_object_var(TypeObject* type, size_t size);
bool object_istype(TypeObject* self, TypeObject* other);
void gc_collect(struct vm* vm);
void type_set_cwrapper(TypeObject* tp, cwrapperfunc func, string name);

object* object_str(object* obj);
object* object_repr(object* obj);
void object_print(object* obj);
string object_cstr(object* obj);
object* object_getattr(object* obj, object* attr);
object* object_setattr(object* obj, object* attr, object* val);
object* object_genericgetattr(object* obj, object* attr);
object* object_genericsetattr(object* obj, object* attr, object* val);
bool object_find_bool_dict_keys(object* dict, object* needle);
object* object_call(object* obj, object* args, object* kwargs);
string object_crepr(object* obj);
bool object_issubclass(object* obj, TypeObject* t);
object* generic_iter_iter(object* self);
object* object_getattr_noerror(object* obj, object* attr);
object* object_cmp(object* self, object* other, uint8_t type);
object* object_call_nokwargs(object* obj, object* args);
object* object_genericgetattr_notype(object* obj, object* attr);
object* object_in_iter(object* left, object* right);
object* object_in_iter(object* left, object* right);
object* object_enter_with(object* self);
object* object_exit_with(object* self);
object* object_genericgetattr_deref(object* obj, object* attr);
object* object_genericgetattr_notype_deref(object* obj, object* attr);
object* object_getattr_deref(object* obj, object* attr);
object* object_setattr_deref(object* obj, object* attr, object* val);

object* builtin___build_class__(object* self, object* args);

#define list_index_int(self, i) CAST_LIST(self)->array[i]
#define tuple_index_int(self, i) CAST_TUPLE(self)->array[i]

const bool NEWTP_PRIMARY_COPY=true;
const bool NEWTP_NUMBER_COPY=true;
const bool NEWTP_MAPPINGS_COPY=true;

int glblargc_raw;
char** glblargv_raw;

vector<TypeObject*> fplbases;

string* glblfildata=NULL;

object* run_vm(object* codeobj, uint32_t* ip);
struct vm* new_vm(uint32_t id, object* code, struct instructions* instructions, string* filedata);
struct vm* new_vm_raw(uint32_t id);
void vm_del(struct vm* vm);

void vm_add_err(TypeObject* exception, struct vm* vm, const char *_format, ...);
object* vm_setup_err(TypeObject* exception, struct vm* vm, const char *_format, ...);

inline void add_callframe(struct callstack* stack, object* line, string* name, object* code, object* callable, uint32_t* ip);
inline void pop_callframe(struct callstack* stack);
void print_traceback();

struct datastack* new_datastack(int size);
struct callstack* new_callstack();
struct blockstack* new_blockstack(int size);

void finalize_threads();

parse_ret parseretglbl;
struct compiler* new_compiler();
struct object* compile(struct compiler* compiler, parse_ret ast);

object* new_list();
object* new_none();
object* new_dict();
object* new_tuple();
object* new_code_fromargs(object* args);
object* new_bool_true();
object* new_bool_false();
object* str_new_fromstr(string val);
object* new_int_fromint(int i);

object* finalize_type(TypeObject* newtype);
void inherit_type_dict(TypeObject* tp);
object* setup_type_methods(TypeObject* tp);
object* setup_type_getsets(TypeObject* tp);
object* setup_type_offsets(TypeObject* tp);

object* type_wrapper_add(object* self, object* args, object* kwargs);
object* type_wrapper_sub(object* self, object* args, object* kwargs);
object* type_wrapper_mul(object* self, object* args, object* kwargs);
object* type_wrapper_div(object* self, object* args, object* kwargs);
object* type_wrapper_pow(object* self, object* args, object* kwargs);
object* type_wrapper_mod(object* self, object* args, object* kwargs);
object* type_wrapper_and(object* self, object* args, object* kwargs);
object* type_wrapper_or(object* self, object* args, object* kwargs);
object* type_wrapper_lshift(object* self, object* args, object* kwargs);
object* type_wrapper_rshift(object* self, object* args, object* kwargs);
object* type_wrapper_fldiv(object* self, object* args, object* kwargs);
object* type_wrapper_xor(object* self, object* args, object* kwargs);

object* type_wrapper_bool(object* self, object* args, object* kwargs);
object* type_wrapper_neg(object* self, object* args, object* kwargs);
object* type_wrapper_int(object* self, object* args, object* kwargs);
object* type_wrapper_float(object* self, object* args, object* kwargs);
object* type_wrapper_abs(object* self, object* args, object* kwargs);
object* type_wrapper_not(object* self, object* args, object* kwargs);

object* type_wrapper_del(object* self, object* args, object* kwargs);
object* type_wrapper_init(object* self, object* args, object* kwargs);
object* type_wrapper_new(object* self, object* args, object* kwargs);
object* type_wrapper_iter(object* self, object* args, object* kwargs);
object* type_wrapper_next(object* self, object* args, object* kwargs);
object* type_wrapper_str(object* self, object* args, object* kwargs);
object* type_wrapper_repr(object* self, object* args, object* kwargs);
object* type_wrapper_call(object* self, object* args, object* kwargs);

object* type_wrapper_descrget(object* self, object* args, object* kwargs);
object* type_wrapper_descrset(object* self, object* args, object* kwargs);
object* type_wrapper_getattr(object* self, object* args, object* kwargs);
object* type_wrapper_setattr(object* self, object* args, object* kwargs);

object* type_wrapper_eq(object* self, object* args, object* kwargs);
object* type_wrapper_ne(object* self, object* args, object* kwargs);
object* type_wrapper_gt(object* self, object* args, object* kwargs);
object* type_wrapper_lt(object* self, object* args, object* kwargs);
object* type_wrapper_gte(object* self, object* args, object* kwargs);
object* type_wrapper_lte(object* self, object* args, object* kwargs);
object* type_wrapper_in(object* self, object* args, object* kwargs);

object* type_wrapper_enter(object* self, object* args, object* kwargs);
object* type_wrapper_exit(object* self, object* args, object* kwargs);

enum blocktype{
    TRY_BLOCK,
    FOR_BLOCK,
    WHILE_BLOCK,
    WITH_BLOCK,
};
void add_blockframe(uint32_t* ip, struct vm* vm, struct blockstack* stack, uint32_t arg, enum blocktype tp);
void pop_blockframe(struct blockstack* stack);


struct blockframe* in_blockstack(struct blockstack* stack, enum blocktype type);

void gil_lock(int id);
int gil_unlock();

struct callframe{
    object* line;
    string* name;
    struct callframe* next;
    struct object* locals;
    object* code;
    string* filedata;
    object* callable;
    object* annotations;
    uint32_t* ip;
};

struct blockframe{
    enum blocktype type;
    uint32_t arg;
    object* obj;
    uint32_t other;
    struct blockframe* next;
    uint32_t callstack_size;
    uint32_t start_ip;
};

struct callstack{
    struct callframe* data;
    uint32_t size;
};

struct blockstack{
    struct blockframe* data;
    uint32_t size;
    uint32_t capacity;
};

struct datastack{
    object** data;
    uint32_t size;
    uint32_t capacity;
};

struct vm{
    struct datastack* objstack;
    struct callstack* callstack;
    struct blockstack* blockstack;
    uint32_t id;

    int ret_val;
    uint32_t ip;
    uint32_t exec;

    object* exception;
    string* filedata;

    object* globals;
    object* path;
    object* global_annotations;
};

enum opcode{
    LOAD_CONST,
    STORE_NAME,
    LOAD_NAME,
    STORE_GLOBAL,
    LOAD_GLOBAL,
    BINOP_ADD,
    BINOP_SUB,
    UNARY_NEG,
    BINOP_MUL,
    BINOP_DIV,
    MAKE_FUNCTION,
    RETURN_VAL,
    CALL_FUNCTION,
    BUILD_TUPLE,
    BUILD_DICT,
    LOAD_BUILD_CLASS,
    LOAD_ATTR,
    STORE_ATTR,
    BUILD_LIST,
    BINOP_IS,
    BINOP_ISNOT,
    BINOP_EE,
    POP_JMP_TOS_FALSE,
    JUMP_DELTA,
    BINOP_SUBSCR,
    RAISE_EXC,
    STORE_SUBSCR,
    DUP_TOS,
    POP_TOS,
    SETUP_TRY,
    FINISH_TRY,
    BINOP_EXC_CMP,
    BINOP_GT,
    BINOP_GTE,
    BINOP_LT,
    BINOP_LTE,
    FOR_TOS_ITER,
    JUMP_TO,
    EXTRACT_ITER,
    BREAK_LOOP,
    CONTINUE_LOOP,
    UNPACK_SEQ,
    IMPORT_NAME,
    IMPORT_FROM_MOD,
    MAKE_SLICE,
    BINOP_NE,
    DEL_SUBSCR,
    DEL_NAME,
    BINOP_MOD,
    BINOP_POW,
    BINOP_AND,
    BINOP_OR,
    UNARY_NOT,
    BUILD_STRING,
    POP_JMP_TOS_TRUE,
    RAISE_ASSERTIONERR,
    DEL_GLBL,
    DEL_ATTR,
    MAKE_CLOSURE,
    LOAD_NONLOCAL,
    STORE_NONLOCAL,
    DEL_NONLOCAL,
    BITWISE_NOT,
    BITWISE_AND,
    BITWISE_OR,
    BITWISE_LSHIFT,
    BITWISE_RSHIFT,
    BINOP_NOTIN,
    BINOP_IN,
    BINOP_FLDIV,
    TERNARY_TEST,
    CALL_FUNCTION_BOTTOM,
    ANNOTATE_GLOBAL,
    ANNOTATE_NAME,
    ANNOTATE_NONLOCAL,
    STORE_ATTR_ANNOTATE,
    YIELD_VALUE,
    MAKE_GENERATOR,
    MAKE_CLOSURE_GENERATOR,
    BUILD_SET,
    CLEAR_EXC,
    ENTER_WHILE,
    EXIT_WHILE,
    ENTER_WITH,
    EXIT_WITH,
    SEQ_APPEND,
    DICT_SET,
    BITWISE_XOR,
    BYTES_STRING,
    CALL_FUNCTION_KW,
    CALL_FUNCTION_U,
    CALL_FUNCTION_KW_U,
    CALL_FUNCTION_BOTTOM_KW,
    CALL_FUNCTION_BOTTOM_U,
    CALL_FUNCTION_BOTTOM_KW_U,
};


#define CAST_VAR(obj) ((object_var*)obj)
#define CAST_INT(obj) ((IntObject*)obj)
#define CAST_STRING(obj) ((StrObject*)obj)
#define CAST_LIST(obj) ((ListObject*)obj)
#define CAST_DICT(obj) ((DictObject*)obj)
#define CAST_CODE(obj) ((CodeObject*)obj)
#define CAST_BOOL(obj) ((BoolObject*)obj)
#define CAST_TUPLE(obj) ((TupleObject*)obj)
#define CAST_FUNC(obj) ((FuncObject*)obj)
#define CAST_NONE(obj) ((NoneObject*)obj)
#define CAST_BUILTIN(obj) ((BuiltinObject*)obj)
#define CAST_TYPE(obj) ((TypeObject*)obj)
#define CAST_EXCEPTION(obj) ((ExceptionObject*)obj)
#define CAST_FILE(obj) ((FileObject*)obj)
#define CAST_CWRAPPER(obj) ((CWrapperObject*)obj)
#define CAST_SLOTWRAPPER(obj) ((SlotWrapperObject*)obj)
#define CAST_FLOAT(obj) ((FloatObject*)obj)
#define CAST_LISTITER(obj) ((ListIterObject*)obj)
#define CAST_TUPLEITER(obj) ((TupleIterObject*)obj)
#define CAST_DICTITER(obj) ((DictIterObject*)obj)
#define CAST_STRITER(obj) ((StrIterObject*)obj)
#define CAST_FILE(obj) ((FileObject*)obj)
#define CAST_MODULE(obj) ((ModuleObject*)obj)
#define CAST_SLICE(obj) ((SliceObject*)obj)
#define CAST_ENUM(obj) ((EnumObject*)obj)
#define CAST_RANGE(obj) ((RangeObject*)obj)
#define CAST_ZIP(obj) ((ZipObject*)obj)
#define CAST_OFFSETWRAPPER(obj) ((OffsetWrapperObject*)obj)
#define CAST_SUPER(obj) ((SuperObject*)obj)
#define CAST_METHOD(obj) ((MethodObject*)obj)
#define CAST_MAP(obj) ((MapObject*)obj)
#define CAST_CLASSMETHOD(obj) ((ClassMethodObject*)obj)
#define CAST_STATICMETHOD(obj) ((StaticMethodObject*)obj)
#define CAST_PROPERTY(obj) ((PropertyObject*)obj)
#define CAST_GEN(obj) ((GeneratorObject*)obj)
#define CAST_SET(obj) ((SetObject*)obj)
#define CAST_SETITER(obj) ((SetIterObject*)obj)
#define CAST_BYTES(obj) ((BytesObject*)obj)
#define CAST_BYTESITER(obj) ((BytesIterObject*)obj)

#define object_istype(this, other) (this==other)


#define CMP_EQ 0
#define CMP_GT 1
#define CMP_GTE 2
#define CMP_LT 3
#define CMP_LTE 4
#define CMP_NE 5
#define CMP_IN 6


#define FUNC_STRICTARGS 0
#define FUNC_STARARGS 1
#define FUNC_STARKWARGS 2
#define FUNC_STAR 3

#define SETSLOT(tp, base, slot) if (base_tp->slot!=NULL){tp->slot=base->slot;}
object* finalize_type(TypeObject* newtype);

#ifdef DEBUG
ostream& operator<<(ostream& os, object* o){
    cout<<object_crepr(o);
    return os;
}

ostream& operator<<(ostream& os, TypeObject* o){
    cout<<object_crepr((object*)o);
    return os;
}
#endif

#include "../vm/vm_stack_manip.cpp"

#include "typeobject.cpp"
#include "types.cpp"
#include "gc.h"
#include "object.cpp"
#include "../fpl/fpl.h"

#include "../builtins/builtins.h"
#include "integerobject.cpp"
#include "stringobject.cpp"
#include "listobject.cpp"
#include "dictobject.cpp"
#include "codeobject.cpp"
#include "boolobject.cpp"
#include "tupleobject.cpp"
#include "funcobject.cpp"
#include "noneobject.cpp"
#include "builtinobject.cpp"
#include "objectobject.cpp"
#include "exceptionobject.cpp"
#include "fileobject.cpp"
#include "cwrapperobject.cpp"
#include "slotwrapperobject.cpp"
#include "floatobject.cpp"
#include "moduleobject.cpp"
#include "sliceobject.cpp"
#include "enumobject.cpp"
#include "rangeobject.cpp"
#include "zipobject.cpp"
#include "offsetwrapperobject.cpp"
#include "superobject.cpp"
#include "methodobject.cpp"
#include "wrappermethodobject.cpp"
#include "staticmethodobject.cpp"
#include "classmethodobject.cpp"
#include "mapobject.cpp"
#include "propertyobject.cpp"
#include "genobject.cpp"
#include "setobject.cpp"
#include "bytesobject.cpp"


void setup_types_consts(){
    fplbases.clear();
    int_map.clear();
    float_map.clear();
    str_map.clear();

    setup_object_type(); 

    trueobj=_new_bool_true();
    falseobj=_new_bool_false();
    noneobj=_new_none();

    setup_type_type();
    setup_int_type();
    setup_str_type();
    setup_list_type();
    setup_dict_type();
    setup_code_type();
    setup_bool_type();
    setup_tuple_type();
    setup_func_type();
    setup_none_type();
    setup_builtin_type();
    setup_exception_type();
    setup_file_type();  
    setup_cwrapper_type();  
    setup_slotwrapper_type();
    setup_float_type();
    setup_listiter_type();
    setup_tupleiter_type();
    setup_dictiter_type();
    setup_striter_type();
    setup_module_type();
    setup_slice_type();
    setup_enum_type();
    setup_range_type();
    setup_zip_type();  
    setup_offsetwrapper_type();
    setup_offsetwrapperreadonly_type();
    setup_slotwrapperreadoly_type();
    setup_super_type();
    setup_method_type();
    setup_wrappermethod_type();
    setup_staticmethod_type();
    setup_classmethod_type();
    setup_map_type();
    setup_property_type();
    setup_gen_type();
    setup_set_type();
    setup_setiter_type();
    setup_bytes_type();
    setup_bytesiter_type();

    setup_builtins();
    
    inherit_type_dict(&ObjectType);
    setup_type_getsets(&ObjectType);
    setup_type_offsets(&ObjectType);

    inherit_type_dict(&TypeType);
    setup_type_getsets(&TypeType);
    setup_type_offsets(&TypeType);

    inherit_type_dict(&IntType);
    setup_type_offsets(&IntType);
    setup_type_getsets(&IntType);

    inherit_type_dict(&StrType);
    setup_type_offsets(&StrType);
    setup_type_getsets(&StrType);
    setup_type_methods(&StrType);

    inherit_type_dict(&ListType);
    setup_type_methods(&ListType);
    setup_type_offsets(&ListType);
    setup_type_getsets(&ListType);

    inherit_type_dict(&DictType);    
    setup_type_offsets(&DictType);
    setup_type_getsets(&DictType);
    setup_type_methods(&DictType);

    inherit_type_dict(&CodeType);
    setup_type_offsets(&CodeType);
    setup_type_getsets(&CodeType);

    inherit_type_dict(&BoolType);
    setup_type_offsets(&BoolType);
    setup_type_getsets(&BoolType);

    inherit_type_dict(&TupleType);
    setup_type_methods(&TupleType);
    setup_type_offsets(&TupleType);
    setup_type_getsets(&TupleType);

    inherit_type_dict(&FuncType);
    setup_type_offsets(&FuncType);
    setup_type_getsets(&FuncType);

    inherit_type_dict(&NoneType);
    setup_type_offsets(&NoneType);
    setup_type_getsets(&NoneType);

    inherit_type_dict(&BuiltinType);
    setup_type_offsets(&BuiltinType);
    setup_type_getsets(&BuiltinType);

    inherit_type_dict(&ExceptionType);
    setup_type_offsets(&ExceptionType);
    setup_type_getsets(&ExceptionType);

    inherit_type_dict(&FileType);
    setup_type_offsets(&FileType);
    setup_type_methods(&FileType);
    setup_type_getsets(&FileType);

    inherit_type_dict(&CWrapperType);
    setup_type_offsets(&CWrapperType);
    setup_type_getsets(&CWrapperType);

    inherit_type_dict(&FloatType); 
    setup_type_offsets(&FloatType);
    setup_type_getsets(&FloatType);

    inherit_type_dict(&ListIterType); 
    setup_type_offsets(&ListIterType);
    setup_type_getsets(&ListIterType);

    inherit_type_dict(&TupleIterType);    
    setup_type_offsets(&TupleIterType);
    setup_type_getsets(&TupleIterType);

    inherit_type_dict(&StrIterType);    
    setup_type_offsets(&StrIterType);
    setup_type_getsets(&StrIterType);
    
    inherit_type_dict(&ModuleType);
    setup_type_offsets(&ModuleType);
    setup_type_getsets(&ModuleType);
    
    inherit_type_dict(&SliceType);
    setup_type_offsets(&SliceType);
    setup_type_getsets(&SliceType);

    inherit_type_dict(&EnumType);
    setup_type_offsets(&EnumType);
    setup_type_getsets(&EnumType);

    inherit_type_dict(&RangeType);
    setup_type_offsets(&RangeType);
    setup_type_getsets(&RangeType);

    inherit_type_dict(&ZipType);
    setup_type_offsets(&ZipType);
    setup_type_getsets(&ZipType);

    inherit_type_dict(&OffsetWrapperType);
    setup_type_offsets(&OffsetWrapperType);
    setup_type_getsets(&OffsetWrapperType);

    inherit_type_dict(&OffsetWrapperReadonlyType);
    setup_type_offsets(&OffsetWrapperReadonlyType);
    setup_type_getsets(&OffsetWrapperReadonlyType);

    inherit_type_dict(&SlotWrapperReadonlyType);
    setup_type_offsets(&SlotWrapperReadonlyType);
    setup_type_getsets(&SlotWrapperReadonlyType);

    inherit_type_dict(&SuperType);
    setup_type_offsets(&SuperType);
    setup_type_getsets(&SuperType);
    
    inherit_type_dict(&MethodType);
    setup_type_offsets(&MethodType);
    setup_type_getsets(&MethodType);
    
    inherit_type_dict(&WrapperMethodType);
    setup_type_offsets(&WrapperMethodType);
    setup_type_getsets(&WrapperMethodType);
    
    inherit_type_dict(&StaticMethodType);
    setup_type_offsets(&StaticMethodType);
    setup_type_getsets(&StaticMethodType);
    
    inherit_type_dict(&ClassMethodType);
    setup_type_offsets(&ClassMethodType);
    setup_type_getsets(&ClassMethodType);
    
    inherit_type_dict(&MapType);
    setup_type_offsets(&MapType);
    setup_type_getsets(&MapType);
    
    inherit_type_dict(&PropertyType);
    setup_type_offsets(&PropertyType);
    setup_type_getsets(&PropertyType);
    setup_type_methods(&PropertyType);
    
    inherit_type_dict(&GeneratorType);
    setup_type_offsets(&GeneratorType);
    setup_type_getsets(&GeneratorType);

    inherit_type_dict(&SetType);
    setup_type_methods(&SetType);
    setup_type_offsets(&SetType);
    setup_type_getsets(&SetType);

    inherit_type_dict(&SetIterType); 
    setup_type_offsets(&SetIterType);
    setup_type_getsets(&SetIterType);

    inherit_type_dict(&BytesType); 
    setup_type_methods(&BytesType);
    setup_type_offsets(&BytesType);
    setup_type_getsets(&BytesType);
    
    inherit_type_dict(&BytesIterType); 
    setup_type_offsets(&BytesIterType);
    setup_type_getsets(&BytesIterType);
}